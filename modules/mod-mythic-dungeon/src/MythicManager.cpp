#include "MythicManager.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Config.h"
#include "Player.h"
#include "LuaEngine.h"
#include "Loot/LootMgr.h"

MythicManager::~MythicManager()
{
}

MythicManager* MythicManager::instance()
{
    static MythicManager instance;
    return &instance;
}

void MythicManager::InitializeMythicDungeonBosses()
{
    MythicDungeonBossStore = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM dungeon_mythic_bosses ORDER by `order` ASC");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 mapId = fields[0].Get<uint32>();
        uint32 order = fields[1].Get<uint32>();
        uint32 bossId = fields[2].Get<uint32>();
        MythicBoss boss = { mapId, order, bossId };
        MythicDungeonBossStore[mapId].push_back(boss);
    } while (result->NextRow());
}

void MythicManager::InitializeMythicDungeons()
{
    MythicDungeonStore = {};

    QueryResult result = WorldDatabase.Query("SELECT id, amountToKill, timeToComplete, mapId, `name`, position_x, position_y, position_z, orientation, itemId, `bonus` FROM dungeon_mythic WHERE `enable` = 1");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 id = fields[0].Get<uint32>();
        uint32 amountToKill = fields[1].Get<uint32>();
        uint32 timeToComplete = fields[2].Get<uint32>();
        uint32 mapId = fields[3].Get<uint32>();
        std::string name = fields[4].Get<std::string>();
        float x = fields[5].Get<float>();
        float y = fields[6].Get<float>();
        float z = fields[7].Get<float>();
        float o = fields[8].Get<float>();
        uint32 itemId = fields[9].Get<uint32>();
        uint32 bonus = fields[10].Get<uint32>();
        MythicDungeon dungeon = { id, amountToKill, timeToComplete, mapId, x, y, z, o, itemId, bonus };
        MythicDungeonStore.push_back(dungeon);
    } while (result->NextRow());
}

void MythicManager::InitializePlayerMythicKeys()
{
    MythicPlayerKeyStore = {};

    QueryResult result = CharacterDatabase.Query("SELECT * FROM character_mythic_key");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint64 guid = fields[0].Get<uint64>();
        uint32 dungeonId = fields[1].Get<uint32>();
        uint32 level = fields[2].Get<uint32>();
        MythicKey key = { dungeonId, level };
        MythicPlayerKeyStore[guid] = key;
    } while (result->NextRow());
}

void MythicManager::InitializeRewardsToken()
{
    MythicDungeonRewardTokenStore = {};
    QueryResult result = WorldDatabase.Query("SELECT * FROM dungeon_mythic_token_rewards");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 level = fields[0].Get<uint32>();
        uint32 runicEssence = fields[1].Get<uint32>();
        uint32 runicDust = fields[2].Get<uint32>();
        uint32 tokenId = fields[3].Get<uint32>();
        uint32 tokenCount = fields[4].Get<uint32>();

        MythicDungeonRewardTokenStore[level] = { level, runicEssence, runicDust, tokenId, tokenCount };
    } while (result->NextRow());
}

void MythicManager::InitializeRewardsItems()
{
    MythicDungeonRewardItemsStore = {};
    QueryResult result = WorldDatabase.Query("SELECT * FROM dungeon_mythic_rewards");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 itemId = fields[0].Get<uint32>();
        uint32 minLevel = fields[1].Get<uint32>();
        uint32 maxLevel = fields[2].Get<uint32>();
        uint32 classId = fields[3].Get<uint32>();
        uint32 subClassId = fields[4].Get<uint32>();
        uint32 statType1 = fields[5].Get<uint32>();
        MythicDungeonRewardItemsStore.push_back({ itemId, minLevel, maxLevel, classId, subClassId, statType1 });
    } while (result->NextRow());
}

void MythicManager::InitializeMultipliers()
{
    MythicMultiplierStore = {};
    QueryResult result = WorldDatabase.Query("SELECT * FROM dungeon_mythic_scaling");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 level = fields[0].Get<uint32>();
        float damage = fields[1].Get<float>();
        float health = fields[2].Get<float>();
        MythicMultiplier multi = { health, damage};
        MythicMultiplierStore[level] = multi;
    } while (result->NextRow());
}

void MythicManager::HandleChangeDungeonDifficulty(Player* _player, uint8 mode)
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

void MythicManager::SaveMythicKey(Player* player, uint32 newDungeonId, uint32 level)
{
    CharacterDatabase.Query("REPLACE INTO `character_mythic_key` (`guid`, `dungeonId`, `level`) VALUES ({}, {}, {})", player->GetGUID().GetCounter(), newDungeonId, level);
}

void MythicManager::Update(uint32 diff)
{
    if (MythicStore.empty()) {
        return;
    }

    for (auto it = MythicStore.begin(); it != MythicStore.end(); ) {
        if (it->second) {
            std::cerr << "Updating Mythic instance with key: " << it->first << std::endl;
            try {
                it->second->Update(diff);
            }
            catch (const std::exception& e) {
                std::cerr << "Exception caught during Mythic::Update: " << e.what() << std::endl;
            }
            catch (...) {
                std::cerr << "Unknown exception caught during Mythic::Update." << std::endl;
            }
        }
        else {
            std::cerr << "Mythic instance is null for key: " << it->first << std::endl;
        }
        ++it;
    }
}

void MythicManager::AddMythicDungeon(uint32 instanceId, Mythic* m)
{
    auto it = MythicStore.find(instanceId);
    if (it == MythicStore.end()) {
        MythicStore[instanceId] = std::unique_ptr<Mythic>(m);
    }
}

void MythicManager::RemoveAnyOtherMythicDungeon(Player* player)
{
    for (auto it = MythicStore.begin(); it != MythicStore.end(); it++)
    {
        if (Mythic* oldMythic = it->second.get())
        {
            if (oldMythic->KeyOwnerGuid == player->GetGUID())
                MythicStore.erase(it);
        }
    }
}

void MythicManager::RemoveMythic(uint32 instanceId)
{
    MythicStore.erase(instanceId);
}

bool MythicManager::IsThisMapIdAvailableForMythic(uint32 mapId)
{
    return false;
}

bool MythicManager::IsPlayerMeetingConditionsToStartMythic(Player* player)
{
    return false;
}

uint32 MythicManager::GetRandomMythicDungeonForPlayer(Player* player)
{
    if (MythicDungeonStore.empty())
        return 0;

    return MythicDungeonStore[urand(0, MythicDungeonStore.size() - 1)].id;
}


uint32 MythicManager::GetItemIdWithDungeonId(uint32 dungeonId)
{
    for (auto const& dg : MythicDungeonStore)
        if (dg.id == dungeonId)
            return dg.itemId;

    return 0;
}

uint32 MythicManager::GetEnchantByMythicLevel(uint32 level)
{
    return level + 4006;
}

MythicRewardToken MythicManager::GetMythicRewardTokenByLevel(uint32 level)
{
    uint32 levelKey = level;
    uint32 maxLevelKey = sWorld->GetValue("CONFIG_UNLOCK_MYTHIC_LEVEL");

    if (levelKey > maxLevelKey)
        levelKey = maxLevelKey;

    auto find = MythicDungeonRewardTokenStore.find(levelKey);

    if (find == MythicDungeonRewardTokenStore.end())
        return {};

    return find->second;
}

uint32 MythicManager::GetMythicRewardItemByLevel(Player* player, uint32 level)
{
    std::vector<MythicRewardItem> itemsCopy = { };
    std::vector<uint32> items = { };

    uint32 maxLevelKey = sWorld->GetValue("CONFIG_UNLOCK_MYTHIC_LEVEL");

    if (level > maxLevelKey)
        level = maxLevelKey;

    std::copy_if(MythicDungeonRewardItemsStore.begin(), MythicDungeonRewardItemsStore.end(), std::back_inserter(itemsCopy),
        [&](const MythicRewardItem& obj) { return obj.minLevel <= level && obj.maxLevel >= level;  });

    uint8 currentSpec = PlayerSpecialization::GetCurrentSpecId(player);

    for (auto& item : itemsCopy) {
        if (IsItemAllowableClass(player->getClass(), item.classId, item.subClassId) && (IsStatTypeAllowableSpec(currentSpec, item.statType1) ||
            item.statType1 == ITEM_MOD_MANA ||
            item.statType1 == ITEM_MOD_STAMINA)) {
            items.push_back(item.itemId);
        }
    }

    if (items.empty())
        return 0;

    uint32 rand = urand(0, items.size() - 1);

    return items[rand];
}

bool MythicManager::IsItemAllowableClass(uint32 classPlayer, uint32 classId, uint32 subClassId)
{
    switch (classId)
    {
    case ITEM_CLASS_WEAPON:
        switch (subClassId)
        {
        case ITEM_SUBCLASS_WEAPON_AXE:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_WARRIOR || classPlayer == CLASS_SHAMAN || classPlayer == CLASS_DEATH_KNIGHT
                || classPlayer == CLASS_ROGUE;
        case ITEM_SUBCLASS_WEAPON_AXE2:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_PALADIN || classPlayer == CLASS_WARRIOR  || classPlayer == CLASS_SHAMAN
                || classPlayer == CLASS_DEATH_KNIGHT;
        case ITEM_SUBCLASS_WEAPON_BOW:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_WARRIOR || classPlayer == CLASS_ROGUE;
        case ITEM_SUBCLASS_WEAPON_GUN:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_WARRIOR || classPlayer == CLASS_ROGUE;
        case ITEM_SUBCLASS_WEAPON_MACE:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_WARRIOR || classPlayer == CLASS_DEATH_KNIGHT || classPlayer == CLASS_ROGUE
                || classPlayer == CLASS_PALADIN || classPlayer == CLASS_PRIEST;
        case ITEM_SUBCLASS_WEAPON_MACE2:
            return classPlayer == CLASS_WARRIOR || classPlayer == CLASS_DEATH_KNIGHT || classPlayer == CLASS_PALADIN
                || classPlayer == CLASS_DRUID;
        case ITEM_SUBCLASS_WEAPON_POLEARM:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_PALADIN || classPlayer == CLASS_WARRIOR || classPlayer == CLASS_DRUID;
        case ITEM_SUBCLASS_WEAPON_SWORD:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_DEATH_KNIGHT || classPlayer == CLASS_WARLOCK || classPlayer == CLASS_WARRIOR
                || classPlayer == CLASS_MAGE || classPlayer == CLASS_PALADIN
                || classPlayer == CLASS_ROGUE;
        case ITEM_SUBCLASS_WEAPON_SWORD2:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_WARRIOR || classPlayer == CLASS_DEATH_KNIGHT
                || classPlayer == CLASS_PALADIN;
        case ITEM_SUBCLASS_WEAPON_STAFF:
            return classPlayer == CLASS_PRIEST || classPlayer == CLASS_WARLOCK || classPlayer == CLASS_MAGE || classPlayer == CLASS_DRUID;
        case ITEM_SUBCLASS_WEAPON_DAGGER:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_WARLOCK || classPlayer == CLASS_MAGE
                || classPlayer == CLASS_ROGUE || classPlayer == CLASS_DRUID || classPlayer == CLASS_PRIEST;
        case ITEM_SUBCLASS_WEAPON_THROWN:
            return classPlayer == CLASS_ROGUE;
        case ITEM_SUBCLASS_WEAPON_SPEAR:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_DEATH_KNIGHT
                || classPlayer == CLASS_PALADIN || classPlayer == CLASS_DRUID;
        case ITEM_SUBCLASS_WEAPON_CROSSBOW:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_WARRIOR
                || classPlayer == CLASS_ROGUE;
        case ITEM_SUBCLASS_WEAPON_WAND:
            return classPlayer == CLASS_PRIEST || classPlayer == CLASS_WARLOCK
                || classPlayer == CLASS_MAGE;
        default:
            return 0;
        }
    case ITEM_CLASS_ARMOR:
        switch (subClassId)
        {
        case ITEM_SUBCLASS_ARMOR_MISC:
            return true;
        case ITEM_SUBCLASS_ARMOR_CLOTH:
            return classPlayer == CLASS_MAGE || classPlayer == CLASS_WARLOCK || classPlayer == CLASS_PRIEST;
        case ITEM_SUBCLASS_ARMOR_LEATHER:
            return classPlayer == CLASS_ROGUE || classPlayer == CLASS_DRUID;
        case ITEM_SUBCLASS_ARMOR_MAIL:
            return classPlayer == CLASS_HUNTER || classPlayer == CLASS_SHAMAN;
        case ITEM_SUBCLASS_ARMOR_PLATE:
            return classPlayer == CLASS_WARRIOR || classPlayer == CLASS_DEATH_KNIGHT || classPlayer == CLASS_PALADIN;
        case ITEM_SUBCLASS_ARMOR_SHIELD:
            return classPlayer == CLASS_WARRIOR || classPlayer == CLASS_PALADIN || classPlayer == CLASS_SHAMAN;
        case ITEM_SUBCLASS_ARMOR_LIBRAM:
            return classPlayer == CLASS_PALADIN;
        case ITEM_SUBCLASS_ARMOR_IDOL:
            return classPlayer == CLASS_DRUID;
        case ITEM_SUBCLASS_ARMOR_TOTEM:
            return classPlayer == CLASS_SHAMAN;
        case ITEM_SUBCLASS_ARMOR_SIGIL:
            return classPlayer == CLASS_DEATH_KNIGHT;
        default:
            return 0;
        }
    }
    return 0;

}

bool MythicManager::IsStatTypeAllowableSpec(uint32 currentSpec, uint32 statType)
{
    switch (currentSpec) {
        case WARRIOR_ARMS: return statType == ITEM_MOD_STRENGTH;
        case WARRIOR_FURY: return statType == ITEM_MOD_STRENGTH;
        case WARRIOR_PROTECTION: return statType == ITEM_MOD_STRENGTH;
        case WARRIOR_HOPLITE: return statType == ITEM_MOD_STRENGTH || statType == ITEM_MOD_AGILITY;
        case MAGE_ARCANE: return statType == ITEM_MOD_INTELLECT;
        case MAGE_FIRE: return statType == ITEM_MOD_INTELLECT;
        case MAGE_FROST: return statType == ITEM_MOD_INTELLECT;
        case MAGE_SPELLBLADE: return statType == ITEM_MOD_INTELLECT || statType == ITEM_MOD_AGILITY;
        case DK_BLOOD: return statType == ITEM_MOD_STRENGTH;
        case DK_FROST: return statType == ITEM_MOD_STRENGTH;
        case DK_UNHOLY: return statType == ITEM_MOD_STRENGTH;
        case DK_SOULWEAVER: return statType == ITEM_MOD_STRENGTH;
        case DRUID_BALANCE: return statType == ITEM_MOD_INTELLECT;
        case DRUID_FERAL: return statType == ITEM_MOD_AGILITY;
        case DRUID_RESTO: return statType == ITEM_MOD_INTELLECT;
        case DRUID_GUARDIAN: return statType == ITEM_MOD_AGILITY;
        case HUNTER_BEAST: return statType == ITEM_MOD_AGILITY;
        case HUNTER_MARSKMANSHIP: return statType == ITEM_MOD_AGILITY;
        case HUNTER_SURVIVAL: return statType == ITEM_MOD_AGILITY;
        case HUNTER_DARK_RANGER: return statType == ITEM_MOD_AGILITY;
        case PALADIN_HOLY: return statType == ITEM_MOD_INTELLECT;
        case PALADIN_PROTECTION: return statType == ITEM_MOD_STRENGTH;
        case PALADIN_RETRIBUTION: return statType == ITEM_MOD_STRENGTH;
        case PALADIN_INQUISITOR: return statType == ITEM_MOD_INTELLECT;
        case ROGUE_ASSASSINATION: return statType == ITEM_MOD_AGILITY;
        case ROGUE_COMBAT: return statType == ITEM_MOD_AGILITY;
        case ROGUE_SUBTLETY: return statType == ITEM_MOD_AGILITY;
        case ROGUE_OUTLAW: return statType == ITEM_MOD_AGILITY;
        case SHAMAN_ELEMENTAL: return statType == ITEM_MOD_INTELLECT;
        case SHAMAN_ENCHANCEMENT: return statType == ITEM_MOD_AGILITY;
        case SHAMAN_RESTORATION: return statType == ITEM_MOD_INTELLECT;
        case SHAMAN_SPIRIT_MASTER: return statType == ITEM_MOD_AGILITY || statType == ITEM_MOD_INTELLECT;
        case WARLOCK_AFFLICTION: return statType == ITEM_MOD_INTELLECT;
        case WARLOCK_DEMONOLOGY: return statType == ITEM_MOD_INTELLECT;
        case WARLOCK_DESTRUCTION: return statType == ITEM_MOD_INTELLECT;
        case WARLOCK_DEMONBOUND: return statType == ITEM_MOD_INTELLECT;
        case PRIEST_DISCI: return statType == ITEM_MOD_INTELLECT;
        case PRIEST_HOLY: return statType == ITEM_MOD_INTELLECT;
        case PRIEST_SHADOW: return statType == ITEM_MOD_INTELLECT;
        case PRIEST_ABSOLUTION: return statType == ITEM_MOD_INTELLECT;
    }
}

void MythicManager::UpdatePlayerKey(ObjectGuid guid, int8 upgrade)
{
    Player* player = ObjectAccessor::FindPlayer(guid);

    if (!player)
        return;

    MythicKey* key = GetCurrentPlayerMythicKey(player);

    if (!key)
        return;

    uint32 currentItemId = GetItemIdWithDungeonId(key->dungeonId);
    player->DestroyItemCount(currentItemId, 1, true);

    uint32 dungeonId = GetRandomMythicDungeonForPlayer(player);
    
    key->dungeonId = dungeonId;

    if (upgrade == 0)
        upgrade -= 1;

    key->level += upgrade;

    uint32 maxLevelKey = sWorld->GetValue("CONFIG_UNLOCK_MYTHIC_LEVEL");

    if (key->level > maxLevelKey)
        key->level = maxLevelKey;

    if (key->level < 2)
        key->level = 2;

    if (uint32 newItemId = GetItemIdWithDungeonId(dungeonId)) {

        player->AddItem(newItemId, 1);

        Item* item = player->GetItemByEntry(newItemId);

        if (item) {
            uint32 enchantId = GetEnchantByMythicLevel(key->level);
            item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantId, 0, 0, player->GetGUID());
        }

       SaveMythicKey(player, dungeonId, key->level);
       player->SaveToDB(false, false);
    }

}

bool MythicManager::ForceCompleteMythic(Player* player)
{
    if (!player)
        return false;

    if (MythicStore.empty())
        return false;

    Mythic* mythic = GetMythicPlayer(player);

    if (!mythic)
        return false;

    mythic->OnCompleteMythicDungeon(player);

    return true;
}


Mythic* MythicManager::GetMythicPlayer(Player* player)
{
    if (MythicStore.empty())
        return nullptr;

    auto itr = MythicStore.find(player->GetInstanceId());

    if (itr == MythicStore.end())
        return nullptr;

    if (itr != MythicStore.end())
        if(itr->second && itr->second->Dungeon && itr->second->Dungeon->GetInstanceId() == player->GetInstanceId())
            return itr->second.get();

    return nullptr;
}

Mythic* MythicManager::GetMythicInMap(Map* map)
{
    if (MythicStore.empty())
        return nullptr;

    auto itr = MythicStore.find(map->GetInstanceId());

    if (itr != MythicStore.end())
          return itr->second.get();

    return nullptr;
}

uint32 MythicManager::GetAmountToKillByDungeonId(uint32 dungeonId)
{
    uint32 count = 80;

    for (auto const& dg : MythicDungeonStore)
        if (dg.id == dungeonId)
            count = dg.amountToKill;

    return count;
}

MythicMultiplier MythicManager::GetMultplierByLevel(uint32 level)
{
    MythicMultiplier multiplier = { 1.f, 1.f };
    auto itr = MythicMultiplierStore.find(level);
    if (itr != MythicMultiplierStore.end())
        multiplier = itr->second;

    return multiplier;
}


void MythicManager::FindMythicDungeonByItsKeyItemId(uint32 itemId, MythicDungeon& dungeon)
{
    for (auto const& dg : MythicDungeonStore)
        if (dg.itemId == itemId)
            dungeon = dg;
}

void MythicManager::GetMythicDungeonByDungeonId(uint32 dungeonId, MythicDungeon& dungeon)
{
    for (auto const& dg : MythicDungeonStore)
        if (dg.id == dungeonId)
            dungeon = dg;
}

void MythicManager::GenerateFirstRandomMythicKey(Player* player)
{
    uint32 dungeonId = sMythicMgr->GetRandomMythicDungeonForPlayer(player);

    MythicKey key = { dungeonId, 2 };

    MythicPlayerKeyStore[player->GetGUID().GetCounter()] = key;

    if (uint32 newItemId = GetItemIdWithDungeonId(dungeonId)) {

        player->AddItem(newItemId, 1);

        Item* item = player->GetItemByEntry(newItemId);

        if (item) {
            uint32 enchantId = GetEnchantByMythicLevel(2);
            item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantId, 0, 0, player->GetGUID());
        }

        SaveMythicKey(player, dungeonId, 2);
    }
}

void MythicManager::GenerateMythicKeyByLevelAndDungeonId(Player* player, uint32 level, uint32 dungeonId)
{
    MythicDungeon dungeon;

    GetMythicDungeonByDungeonId(dungeonId, dungeon);

    if (!dungeon)
        return;

    MythicKey key = { dungeonId, level };

    MythicPlayerKeyStore[player->GetGUID().GetCounter()] = key;

    player->AddItem(dungeon.itemId, 1);
    if (Item* item = player->GetItemByEntry(dungeon.itemId))
    {
        uint32 enchantId = GetEnchantByMythicLevel(level);
        item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantId, 0, 0, player->GetGUID());
        SaveMythicKey(player, dungeonId, level);
    }

}

MythicKey* MythicManager::GetCurrentPlayerMythicKey(Player* player)
{
    if (!player)
        return nullptr;

    auto itr = MythicPlayerKeyStore.find(player->GetGUID().GetCounter());
    if (itr != MythicPlayerKeyStore.end()) {
        return &itr->second;
    }

    return nullptr;
}


uint32 MythicManager::GetTimeToCompleteByDungeonId(uint32 dungeonId)
{
    uint32 timeToComplete = 0;

    for (auto const& dg : MythicDungeonStore)
        if (dg.id == dungeonId)
            timeToComplete = dg.timeToComplete;

    return timeToComplete;
}


std::vector<MythicBossState> MythicManager::GetMythicBossesByDungeonId(uint32 dungeonId)
{
    std::vector<MythicBossState> bosses = {};
    auto itr = MythicDungeonBossStore.find(dungeonId);

    if (itr == MythicDungeonBossStore.end())
        return bosses;

    for (auto const& boss : itr->second)
        bosses.push_back({ boss.creatureId, true, boss.order + 1 });

    return bosses;
}

std::vector<std::string> MythicManager::GetDataMythicRun(Player* player)
{
    Mythic* mythic = GetMythicPlayer(player);

    if (!mythic)
        return {};

    std::vector<std::string> elements = {};
    std::string first =
        std::to_string(mythic->GetLevel())
        + ";" + std::to_string(mythic->GetEnemyForces())
        + ";" + std::to_string(mythic->GetTimeToComplete())
        + ";" + std::to_string(mythic->GetElapsedTime())
        + ";" + std::to_string(mythic->GetTotalDeaths())
        + ";" + player->GetMap()->GetMapName();

    elements.push_back(first);

    std::string bossStatus = "";

    for (auto const& boss : mythic->GetBosses()) {
        CreatureTemplate const* creatureTemplate = sObjectMgr->GetCreatureTemplate(boss.creatureId);
        bossStatus += ";" + creatureTemplate->Name + "+" + std::to_string(boss.alive);
    }

    elements.push_back(bossStatus);
    return elements;
}

std::vector<std::string> MythicManager::GetDataMythicBag(Item* item)
{
    uint64 guid = item->GetGUID().GetCounter();
    std::vector<std::string> elements = {};

    return elements;
}


uint32 MythicManager::GetDungeonKeyLevelPreperation(Player* player)
{
    MythicKey* mythicKey = GetCurrentPlayerMythicKey(player);

    if (!mythicKey)
        return 0;

    uint32 level = mythicKey->level;

    if (level <= 1)
        return 0;

    return level;
}


void MythicManager::ListenCreationMythicOnMapChanged(Player* leader)
{
    if (AsyncCreationMythic.empty())
        return;

    auto it = AsyncCreationMythic.find(leader->GetGUID());

    if (it == AsyncCreationMythic.end())
        return;

    MythicDungeon dungeon;

    GetMythicDungeonByDungeonId(it->second->dungeonId, dungeon);

    if (!dungeon)
        return;

    RemoveAnyOtherMythicDungeon(leader);

    Mythic* mythic = new Mythic(leader->GetGUID(), leader->GetMap(), it->second->dungeonId, it->second->level, dungeon.bonusMultiplier);
    AddMythicDungeon(leader->GetInstanceId(), mythic);

    AsyncCreationMythic.erase(it);
}

bool MythicManager::ShouldShowMythicUI(Player* player)
{
    if (!player)
        return false;

    Mythic* mythic = GetMythicPlayer(player);

    if (!mythic)
        return false;

    if (mythic->IsDungeonDone())
        return false;

    return true;
}

void MythicManager::OnKill(Player* player, Creature* killed)
{
    if (!killed)
        return;

    if (!player)
        return;


    Map* map = player->GetMap();

    Mythic* mythic = GetMythicPlayer(player);

    if (!mythic)
        return;

    if (killed->IsDungeonBoss())
        mythic->OnKillBoss(player, killed);
    else
        mythic->OnKillCreature(player, killed);

   
}

void MythicManager::OnPlayerDie(Player* player, Creature* killed)
{
    Map* map = player->GetMap();
    Mythic* mythic = GetMythicPlayer(player);

    if (!mythic)
        return;

    mythic->OnPlayerKilledByCreature();
}

void MythicManager::Update(Creature* creature)
{

    if (!creature)
        return;

    Map* map = creature->GetMap();

    if (!map)
        return;

    Mythic* mythic = GetMythicInMap(map);

    if (!mythic)
        return;

    if ((creature->IsHunterPet() || creature->IsPet() || creature->IsSummon()) && creature->IsControlledByPlayer())
        return;

    if (creature->HasAura(90000))
        return;

    if (mythic->GetLevel() == 2)
        return;

    MythicMultiplier multi = GetMultplierByLevel(mythic->GetLevel());

    int32 damage = multi.damage;
    int32 health = multi.hp;

    creature->CastCustomSpell(creature, 90000, &damage, &health, nullptr, true);
}

void MythicManager::PreparationMythicDungeon(Player* leader)
{
    MythicKey* mythicKey = GetCurrentPlayerMythicKey(leader);

    if (!mythicKey)
        return;

    MythicDungeon dungeon;

    GetMythicDungeonByDungeonId(mythicKey->dungeonId, dungeon);

    if(!dungeon)
        return;

    Group* group = leader->GetGroup();

    AsyncCreationMythic[leader->GetGUID()] = mythicKey;

    if (!group) {
        ResetPlayerInstanceBound(leader, dungeon.mapId);
        leader->ClearUnitState(UNIT_STATE_ROOT);
        leader->SetControlled(true, UNIT_STATE_ROOT);
        leader->TeleportTo(dungeon.mapId, dungeon.x, dungeon.y, dungeon.z, dungeon.o, 0, nullptr, true);
        return;
    }

    if (Group* group = leader->GetGroup()) {
        auto const& allyList = group->GetMemberSlots();
        for (auto const& target : allyList)
        {
            Player* member = ObjectAccessor::FindPlayer(target.guid);
            if (member) {
                member->ClearUnitState(UNIT_STATE_ROOT);
                member->SetControlled(true, UNIT_STATE_ROOT);
                ResetPlayerInstanceBound(member, dungeon.mapId);
            }
        }
    }

    if (Group* group = leader->GetGroup()) {
        auto const& allyList = group->GetMemberSlots();
        for (auto const& target : allyList)
        {
            Player* member = ObjectAccessor::FindPlayer(target.guid);
            if (member) {
                member->ClearUnitState(UNIT_STATE_ROOT);
                member->SetControlled(true, UNIT_STATE_ROOT);
                member->TeleportTo(dungeon.mapId, dungeon.x, dungeon.y, dungeon.z, dungeon.o, 0, nullptr, true);
            }
        }
    }

}

void MythicManager::ResetPlayerInstanceBound(Player* player, uint32 mapId)
{
    for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
    {
      sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUID(), mapId, Difficulty(i), true, player);
    }
}
