#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Item.h"
#include "Mythic.h"
#include "MythicManager.h"
#include "Chat.h"
#include "LuaEngine.h"

Mythic::Mythic(ObjectGuid guid, Map* map, uint32 dungeonId, uint32 level, uint32 bonusMultiplier)
{
    EnemyForces = 0.f;
    DungeonId = dungeonId;
    Dungeon = map;
    TimeToComplete = sMythicMgr->GetTimeToCompleteByDungeonId(dungeonId);
    StartTimer = 10 * IN_MILLISECONDS;
    Countdown = 0;
    Iteration = 10;
    Started = false;
    ChestDecrapeted = false;
    Done = false;
    ElapsedTime = 0;
    Deaths = 0;
    Level = level;
    KeyOwnerGuid = guid;
    BonusMultiplier = bonusMultiplier;
    StateBossMythicStore = sMythicMgr->GetMythicBossesByDungeonId(dungeonId);
}

Mythic::~Mythic()
{

}

void Mythic::Update(uint32 diff)
{
    if (IsDungeonDone())
        return;

    if (IsDungeonNotStarted()) {

        Map* dungeon = Dungeon;

        if (!dungeon)
            return;

        Map::PlayerList const& playerList = dungeon->GetPlayers();

        Countdown += diff;
        StartTimer -= diff;

        if (Countdown > 1000) {
            Iteration -= 1;
            Countdown = 0;
            for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration) {
                if (Player* player = playerIteration->GetSource()) {
                    std::string countdownMessage = "Start in " + std::to_string(Iteration) + "...";
                    ChatHandler(player->GetSession()).SendSysMessage(countdownMessage);
                }
            }
        }

        if (StartTimer <= 0) {
            StartTimer = 0;
            Started = true;
            for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration) {
                if (Player* player = playerIteration->GetSource()) {
                    player->ClearUnitState(UNIT_STATE_ROOT);
                    player->SetControlled(false, UNIT_STATE_ROOT);
                    sEluna->SendStartMythicDungeon(player);
                }
            }
        }
    }
    else {
        if (IsAllowedTimeOver())
            ElapsedTime += diff;

        if (ElapsedTime >= TimeToComplete && !ChestDecrapeted && !Done) {
            ChestDecrapeted = true;
        }
    }
}



void Mythic::SaveMythicDungeon()
{
    uint32 config = sWorld->GetValue("CONFIG_PATCH");
    uint8 upgrade = CalculateUpgradeKey();

    Map::PlayerList const& playerList = Dungeon->GetPlayers();

    for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
    {
        if (Player* player = playerIteration->GetSource())
        {
            CharacterDatabase.Query("INSERT INTO `character_mythic_completed` (`guid`, `mapId`, `level`, `timeToComplete`, `elapsedTime`, `upgrade`, `patch`, `createdAt`, `dungeonId`) VALUES ({}, {}, {}, {}, {}, {}, {}, NOW(), {})",
                player->GetGUID().GetCounter(), Dungeon->GetEntry()->MapID, Level, TimeToComplete, ElapsedTime, upgrade, config, DungeonId);
        }
    }
    
}

void Mythic::SetBossDead(uint32 creatureId)
{
    for (auto ij = StateBossMythicStore.begin(); ij != StateBossMythicStore.end(); ++ij)
    {
        if (ij->creatureId == creatureId)
        {
            ij->alive = false;
        }
    }
}

uint32 Mythic::GetBossIndex(uint32 creatureId)
{
    for (MythicBossState& boss : StateBossMythicStore)
        if (boss.creatureId == creatureId)
            return boss.index;

    return 0;
}

void Mythic::OnCompleteMythicDungeon(Player* player)
{
    if (!player || Done)
        return;

    Done = true;

    int8 upgrade = CalculateUpgradeKey();

    Map::PlayerList const& playerList = Dungeon->GetPlayers();
    for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
        if (Player* currentPlayer = playerIteration->GetSource())
            sEluna->SendCompletedMythicDungeon(currentPlayer, TimeToComplete - ElapsedTime, upgrade);

    GiveRewards();
    SaveMythicDungeon();
    sMythicMgr->UpdatePlayerKey(KeyOwnerGuid, upgrade);
    sMythicMgr->RemoveMythic(player->GetInstanceId());

}

void Mythic::OnKillBoss(Player* player, Creature* killed)
{
    Map::PlayerList const& playerList = Dungeon->GetPlayers();

    if (playerList.IsEmpty())
        return;

    if (IsDungeonDone() || IsDungeonNotStarted())
        return;

    SetBossDead(killed->GetEntry());

    uint32 index = GetBossIndex(killed->GetEntry());

    killed->loot.clear();

    if (!index)
        return;

    for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
        if (Player* player = playerIteration->GetSource())
            sEluna->SendMythicUpdateBossKill(player, index);

    if (!MeetTheConditionsToCompleteTheDungeon())
        return;

    OnCompleteMythicDungeon(player);
}

void Mythic::OnKillCreature(Player* player, Creature* killed)
{
    if (IsDungeonDone() || IsDungeonNotStarted())
        return;

    if (EnemyForces >= 100)
        return;

    if (Done)
        return;

    float amountToKill = sMythicMgr->GetAmountToKillByDungeonId(DungeonId);
    float count = (float)100 / amountToKill;

    if ((EnemyForces + count) > 100)
        EnemyForces = 100;
    else
        EnemyForces += count;

    Map::PlayerList const& playerList = Dungeon->GetPlayers();

    killed->loot.clear();

    if (playerList.IsEmpty())
        return;

    for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
        if (Player* player = playerIteration->GetSource())
            sEluna->SendMythicUpdateEnemyForces(player, EnemyForces);

    if (!MeetTheConditionsToCompleteTheDungeon())
        return;

    OnCompleteMythicDungeon(player);
}

void Mythic::OnPlayerKilledByCreature()
{
    Deaths += 1;

    uint32 timeToReduce = 5000;

    ElapsedTime += timeToReduce;

    Map::PlayerList const& playerList = Dungeon->GetPlayers();

    if (playerList.IsEmpty())
        return;

    for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
        if (Player* player = playerIteration->GetSource()) 
            sEluna->SendMythicUpdateDeath(player, Deaths);
}

void Mythic::OnPlayerRelease(Player* player)
{
    MythicDungeon dungeon;
    sMythicMgr->GetMythicDungeonByDungeonId(DungeonId, dungeon);
    player->ResurrectPlayer(25.f, false);
    player->TeleportTo(dungeon.mapId, dungeon.x, dungeon.y, dungeon.z, dungeon.o, 0, nullptr, false);
}

bool Mythic::MeetTheConditionsToCompleteTheDungeon()
{
    bool allBossesAreDead = true;

    for (auto ij = StateBossMythicStore.begin(); ij != StateBossMythicStore.end(); ++ij)
    {
        if (ij->alive == true)
        {
            allBossesAreDead = false;
        }
    }

    return allBossesAreDead && EnemyForces >= 100.0f;
}

void Mythic::GiveRewards()
{
    srand(static_cast<unsigned int>(time(0)));

    MythicRewardToken reward = sMythicMgr->GetMythicRewardTokenByLevel(Level);

    Map::PlayerList const& playerList = Dungeon->GetPlayers();

    for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
    {
        if (Player* player = playerIteration->GetSource())
        {
            float bonus = (BonusMultiplier / 100);
            uint32 runicDust = reward.runicDust * bonus;
            uint32 runicEssence = reward.runicEssence * bonus;
            uint32 tokenCount = reward.tokenCount * bonus;

            player->AddItem(70008, runicDust);
            player->AddItem(70009, runicEssence);
            player->AddItem(reward.tokenId, tokenCount);

            int guaranteedRewards = BonusMultiplier / 100;
            float extraChance = BonusMultiplier % 100;

            for (int i = 0; i < guaranteedRewards; ++i)
            {
                if (uint32 itemId = sMythicMgr->GetMythicRewardItemByLevel(player, Level))
                {
                    player->AddItem(itemId, 1);
                }
            }

            float randomValue = static_cast<float>(rand()) / RAND_MAX;

            if (randomValue < (extraChance / 100.0))
            {
                if (uint32 itemId = sMythicMgr->GetMythicRewardItemByLevel(player, Level))
                {
                    player->AddItem(itemId, 1);
                }
            }
        }
    }
}

int8 Mythic::CalculateUpgradeKey()
{
    if (ChestDecrapeted)
        return 0;

    uint8 upgrade = 1;

    uint32 difference = std::max<uint32>(0, TimeToComplete - ElapsedTime);

    float pourcentage = (difference / ElapsedTime) * 100;

    if (pourcentage >= 65.0f)
        upgrade = 3;
    if (pourcentage < 65.0f && pourcentage > 45.0f)
        upgrade = 2;


    return upgrade;
}
