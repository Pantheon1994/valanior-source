#include "TimeDungeonManager.h"
#include "Group.h"
#include "Config.h"
#include "ElunaIncludes.h"
#include "LuaEngine.h"
#include "boost/iterator/counting_iterator.hpp"

std::map<uint32, TimedDungeon> TimedDungeonManager::m_TimedDungeon = {};
std::map<uint32, std::vector<TimedRewardDungeon>> TimedDungeonManager::m_TimedRewardDungeon = {};
std::map<uint32, std::vector<DungeonBoss>> TimedDungeonManager::m_TimedDungeonBosses = {};
std::map<uint64, MythicKey> TimedDungeonManager::m_PlayerKey = {};
std::vector<Affixe> TimedDungeonManager::m_WeeklyAffixes = {};
std::map<uint32, TimedRun> TimedDungeonManager::m_TimedRun = {};

void TimedDungeonManager::InitializeMythicKeys()
{

    m_PlayerKey = {};
    QueryResult result = CharacterDatabase.Query("SELECT * FROM character_mythic_key");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint64 guid = fields[0].Get<uint64>();
        uint32 mapId = fields[2].Get<uint32>();
        uint32 level = fields[3].Get<uint32>();
        bool enable = fields[4].Get<bool>();
        MythicKey dungeon = { mapId, level };
        m_PlayerKey[guid] = dungeon;
    } while (result->NextRow());
}

void TimedDungeonManager::InitializeWeeklyAffixes()
{
    m_WeeklyAffixes = {};
    QueryResult result = WorldDatabase.Query("SELECT * FROM dungeon_mythic_affixes");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 spellId = fields[0].Get<uint32>();
        uint32 level = fields[1].Get<uint32>();
        Affixe affixe = { spellId, level };
        m_WeeklyAffixes.push_back(affixe);
    } while (result->NextRow());
}

void TimedDungeonManager::Update(Map* map, uint32 diff)
{
    auto it = m_TimedRun.find(map->GetInstanceId());

    if (it == m_TimedRun.end())
        return;

    if (it->second.done || it->second.chestDecrapeted)
        return;

    if (!it->second.started) {
        Map::PlayerList const& playerList = map->GetPlayers();

        if (playerList.IsEmpty())
            return;

        it->second.startTimer -= diff;

        if (it->second.startTimer <= 0) {
            it->second.startTimer = 0;
            it->second.started = true;
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
        it->second.elapsedTime += diff;
        TimedDungeon dungeon = m_TimedDungeon[map->GetId()];
        if (it->second.elapsedTime >= dungeon.timeToComplete && !it->second.chestDecrapeted && !it->second.done) {
            it->second.chestDecrapeted = true;
            Map::PlayerList const& playerList = map->GetPlayers();

            if (!playerList.IsEmpty())
                for (auto playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
                    if (Player* player = playerIteration->GetSource())
                        sEluna->SendMythicUpdateChestDecrapeted(player);
        }
    }
}

void TimedDungeonManager::InitializeTimedDungeons()
{
    m_TimedDungeonBosses = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM dungeon_mythic_bosses ORDER by `order` ASC");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 mapId = fields[0].Get<uint32>();
        uint32 order = fields[1].Get<uint32>();
        uint32 bossId = fields[2].Get<uint32>();
        DungeonBoss boss = { mapId, order, bossId };
        m_TimedDungeonBosses[mapId].push_back(boss);
    } while (result->NextRow());
}

void TimedDungeonManager::InitializeRewardsDungeons()
{
    m_TimedRewardDungeon = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM dungeon_mythic_rewards");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 mapId = fields[0].Get<uint32>();
        uint32 itemId = fields[1].Get<uint32>();
        uint32 level = fields[2].Get<uint32>();
        TimedRewardDungeon reward = { mapId, itemId, level };
        m_TimedRewardDungeon[mapId].push_back(reward);
    } while (result->NextRow());
}

void TimedDungeonManager::InitializeTimedDungeonBosses()
{
    m_TimedRewardDungeon = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM dungeon_mythic_rewards");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 mapId = fields[0].Get<uint32>();
        uint32 itemId = fields[1].Get<uint32>();
        uint32 level = fields[2].Get<uint32>();
        TimedRewardDungeon reward = { mapId, itemId, level };
        m_TimedRewardDungeon[mapId].push_back(reward);
    } while (result->NextRow());
}


void TimedDungeonManager::HandleChangeDungeonDifficulty(Player* _player, uint8 mode)
{
    Group* group = _player->GetGroup();
    if (group)
    {
        if (group->IsLeader(_player->GetGUID()))
        {
            for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
            {
                Player* groupGuy = itr->GetSource();
                if (!groupGuy)
                    continue;

                if (!groupGuy->IsInWorld())
                {
                    _player->SendDungeonDifficulty(group != nullptr);
                    return;
                }

                if (groupGuy->GetGUID() == _player->GetGUID() ? groupGuy->GetMap()->IsDungeon() : groupGuy->GetMap()->IsNonRaidDungeon())
                {
                    _player->SendDungeonDifficulty(group != nullptr);
                    return;
                }
            }

            group->ResetInstances(INSTANCE_RESET_CHANGE_DIFFICULTY, false, _player);
            group->SetDungeonDifficulty(Difficulty(mode));
        }
    }
    else {
        _player->SetDungeonDifficulty(Difficulty(mode));
        _player->SendDungeonDifficulty(false, DUNGEON_DIFFICULTY_EPIC);
        Player::ResetInstances(_player->GetGUID(), INSTANCE_RESET_CHANGE_DIFFICULTY, false);
    }
}

std::vector<std::string> TimedDungeonManager::GetDungeonsEnabled(Player* player)
{
    std::vector<std::string> elements = {};

    for (auto const& dungeon : m_TimedDungeon)
    {
        if (dungeon.second.enable) {
            std::string fmt =
                std::to_string(dungeon.second.mapId)
                + ";" + std::to_string(dungeon.second.timeToComplete)
                + ";" + std::to_string(dungeon.second.totalEnemyForces);
            elements.push_back(fmt);
        }
    }
    return elements;
}

std::vector<std::string> TimedDungeonManager::GetWeeklyAffixes(Player* player)
{
    std::vector<std::string> elements = {};


    player->GetSummonedUnits();

    for (auto const& dungeon : m_WeeklyAffixes)
    {
        std::string fmt =
            std::to_string(dungeon.spellId)
            + ";" + std::to_string(dungeon.level);
        elements.push_back(fmt);
    }
    return elements;
}

std::vector<std::string> TimedDungeonManager::GetDungeonBosses(Player* player)
{
    std::vector<std::string> elements = {};
    uint32 mapId = player->GetMapId();

    std::vector<DungeonBoss> DungeonBosses = m_TimedDungeonBosses[mapId];

    for (auto const& timed : DungeonBosses) {

    }

    return elements;
}

void TimedDungeonManager::StartMythicDungeon(Player* player, uint32 keyId, uint32 level)
{
    // Check if the player highest key.
    // Lower the key

    Map* map = player->GetMap();

    if (!map)
        return;

    if (map->GetId() != keyId)
        return;

    if (player->GetDungeonDifficulty() != DUNGEON_DIFFICULTY_EPIC)
        return;

    Group* group = player->GetGroup();

    std::vector<TimedDungeonBoss> m_TimedDungeonBoss = {};
    std::vector<Affixe> affixes = {};
    std::vector<DungeonBoss> DungeonBosses = m_TimedDungeonBosses[keyId];
    TimedDungeon dungeon = m_TimedDungeon[keyId];

    for (auto const& timed : DungeonBosses)
        m_TimedDungeonBoss.push_back({ timed.bossId, true });

    uint32 totalDeath = 0;

    TimedRun run = { keyId, level, dungeon.timeToComplete, false, false, false, 0, m_TimedDungeonBoss, 0.0f, totalDeath, 10 * IN_MILLISECONDS };
    m_TimedRun[map->GetInstanceId()] = run;

    if (group) {

        if (group->GetLeaderGUID() != player->GetGUID())
            return;

        if (group->GetMembersCount() <= 1)
            return;

        auto const& allyList = group->GetMemberSlots();

        for (auto const& target : allyList)
        {
            Player* member = ObjectAccessor::FindPlayer(target.guid);
            if (member) {
                SendStatsMythicRun(member, run);
                member->ClearUnitState(UNIT_STATE_ROOT);
                member->SetControlled(true, UNIT_STATE_ROOT);
                AreaTriggerTeleport const* at = sObjectMgr->GetMapEntranceTrigger(map->GetId());
                if (at) {
                    member->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, at->target_Orientation);
                }
            }
        }
    }
    else {
        SendStatsMythicRun(player, run);
        player->ClearUnitState(UNIT_STATE_ROOT);
        player->SetControlled(true, UNIT_STATE_ROOT);
        AreaTriggerTeleport const* at = sObjectMgr->GetMapEntranceTrigger(map->GetId());

        if (at) {
            player->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, at->target_Orientation);
        }
    }
}

void TimedDungeonManager::OnKillBoss(Player* player, Creature* killed)
{
    Map* map = player->GetMap();

    auto it = m_TimedRun.find(map->GetInstanceId());

    if (it == m_TimedRun.end())
        return;

    if (!it->second.started)
        return;

    if (it->second.done)
        return;

    if (!killed->IsDungeonBoss())
        return;

    for (auto ij = it->second.bosses.begin(); ij != it->second.bosses.end(); ++ij) {
        if (ij->creatureId == killed->GetEntry()) {
            ij->alive = false;
            if (Group* group = player->GetGroup()) {
                auto const& allyList = group->GetMemberSlots();

                for (auto const& target : allyList)
                {
                    Player* member = ObjectAccessor::FindPlayer(target.guid);
                    if (member) {
                        sEluna->SendMythicUpdateBossKill(member, killed->GetEntry());
                    }
                }
            }
            else
                sEluna->SendMythicUpdateBossKill(player, killed->GetEntry());
        }
    }

    if (MeetTheConditionsToCompleteTheDungeon(it->second)) {
        CompleteMythicDungeon(it->second, player);
    }
}

void TimedDungeonManager::OnKillMinion(Player* player, Creature* killed)
{
    Map* map = player->GetMap();

    auto it = m_TimedRun.find(map->GetInstanceId());

    if (it == m_TimedRun.end())
        return;

    if (it->second.done)
        return;

    if (!it->second.started)
        return;

    if (killed->IsDungeonBoss())
        return;

    TimedDungeon dungeon = m_TimedDungeon[map->GetId()];

    uint32 point = 1;

    if (killed->isElite())
        point = 2;

    float currentEnemyForces = it->second.enemyForces;
    uint32 totalEnemyForces = dungeon.totalEnemyForces;

    it->second.enemyForces += (point / totalEnemyForces) * 100;
    it->second.enemyForces = std::max(it->second.enemyForces, 100.0f);

    if (Group* group = player->GetGroup()) {
        auto const& allyList = group->GetMemberSlots();

        for (auto const& target : allyList)
        {
            Player* member = ObjectAccessor::FindPlayer(target.guid);
            if (member) {
                sEluna->SendMythicUpdateEnemyForces(member, it->second.enemyForces);
            }
        }
    }
    else
        sEluna->SendMythicUpdateEnemyForces(player, it->second.enemyForces);

    if (MeetTheConditionsToCompleteTheDungeon(it->second)) {
        CompleteMythicDungeon(it->second, player);
    }
}

void TimedDungeonManager::OnPlayerKilledByCreature(Creature* killer, Player* killed)
{
    Map* map = killed->GetMap();

    auto it = m_TimedRun.find(map->GetInstanceId());

    if (it == m_TimedRun.end())
        return;

    if (!it->second.started)
        return;

    it->second.deaths += 1;
    int32 totalDeath = it->second.deaths;
    int32 timeToReduce = std::max(((5 * IN_MILLISECONDS) * totalDeath), (30 * IN_MILLISECONDS));
    it->second.elapsedTime += timeToReduce;

    if (Group* group = killed->GetGroup()) {
        auto const& allyList = group->GetMemberSlots();

        for (auto const& target : allyList)
        {
            Player* member = ObjectAccessor::FindPlayer(target.guid);
            if (member) {
                sEluna->SendMythicUpdateDeath(member, totalDeath);
                sEluna->SendMythicUpdateTimer(member, timeToReduce);
            }
        }
    }
    else {
        sEluna->SendMythicUpdateDeath(killed, totalDeath);
        sEluna->SendMythicUpdateTimer(killed, timeToReduce);
    }
}

void TimedDungeonManager::CompleteMythicDungeon(TimedRun run, Player* player)
{
    run.done = true;
    if (Group* group = player->GetGroup()) {
        auto const& allyList = group->GetMemberSlots();

        for (auto const& target : allyList)
        {
            Player* member = ObjectAccessor::FindPlayer(target.guid);
            if (member) {

            }
        }
    }
    else {

    }

    // Save the result in the database;
    // Change the key and increase it (check by how much they completed the key) save to the database or give a new key level -1;
    // Give rewards to everyone
}

void TimedDungeonManager::OnPlayerRelease(Player* player)
{
    Map* map = player->GetMap();

    auto it = m_TimedRun.find(map->GetInstanceId());

    if (it == m_TimedRun.end())
        return;

    if (!it->second.started)
        return;

    AreaTriggerTeleport const* at = sObjectMgr->GetMapEntranceTrigger(map->GetId());

    if (at) {
        player->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, at->target_Orientation);
    }
}


bool TimedDungeonManager::MeetTheConditionsToCompleteTheDungeon(TimedRun run)
{
    bool allBossesAreDead = true;

    for (auto ij = run.bosses.begin(); ij != run.bosses.end(); ++ij)
        if (ij->alive)
            allBossesAreDead = false;

    return allBossesAreDead && run.enemyForces >= 100.0f;
}

std::vector<std::string> TimedDungeonManager::SendStatsMythicRun(Player* player, TimedRun run)
{
    std::vector<std::string> elements = {};
    std::string first =
        std::to_string(run.level)
        + ";" + std::to_string(run.enemyForces)
        + ";" + std::to_string(run.timeToComplete)
        + ";" + std::to_string(run.elapsedTime)
        + ";" + std::to_string(run.deaths);

    elements.push_back(first);

    std::string bossStatus = "";
    for (auto const& boss : run.bosses) {
        bossStatus += ";" + std::to_string(boss.creatureId) +  "+" + std::to_string(boss.alive);
    }

    elements.push_back(bossStatus);

    return elements;
}

MythicKey TimedDungeonManager::GetCurrentMythicKey(Player* player)
{
    auto it = m_PlayerKey.find(player->GetGUID().GetCounter());

    if (it != m_PlayerKey.end())
        return it->second;

    return {};
}
