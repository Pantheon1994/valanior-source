/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "RunesManager.h"
#include "LuaEngine.h"
#include "Spell.h"
#include "PetDefines.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Totem.h"
#include "UnitAI.h"
#include "Log.h"
#include "ScriptedGossip.h"
#include "SpellInfo.h"

enum Items {
    ITEM_RUNIC_DUST =   70008,
    ITEM_RUNIC_ESSENCE = 70009,
    ITEM_SEALED_RUNE = 70002,
};


const std::vector<uint32> exceptionCreatureIds = { 8901, 9956, 108901, 109956, 208901, 209956, 6978, 106978, 206978, 7276, 7286, 107276, 107286, 207276, 207286, 7603, 6981, 107603, 106981, 207603, 206981 };

class RunicDust_MiscScript : public MiscScript
{
public:
    RunicDust_MiscScript() : MiscScript("Runes_MiscScript") { }

    void AddRunicDustToLoot(uint32 minValue, Loot* loot)
    {
        float multiplier = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_MULTIPLIER");
        int augmentation = minValue * multiplier / 100;
        uint32 value = minValue + augmentation;
        LootStoreItem runicDust(ITEM_RUNIC_DUST, 0, 100, 0, LOOT_MODE_DEFAULT, 0, value, value);
        loot->AddItem(runicDust);
    }

    void AddRunicEssenceToLoot(uint32 minValue, Loot* loot)
    {
        float multiplier = sWorld->GetValue("CONFIG_DROP_ESSENCE_MULTIPLIER");
        int augmentation = minValue * multiplier / 100;
        uint32 value = minValue + augmentation;

        LootStoreItem runicEssence(ITEM_RUNIC_ESSENCE, 0, 100, 0, LOOT_MODE_DEFAULT, 0, value, value);
        loot->AddItem(runicEssence);
    }



    void AddBonusRunicDustAndRunicEssence(Creature* creature, Player* player, Loot* loot) {

        if (std::find(exceptionCreatureIds.begin(), exceptionCreatureIds.end(), creature->GetEntry()) != exceptionCreatureIds.end())
            return;

        if (creature->IsSummon())
            return;

        uint32 maxLevel = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);

        Map* map = creature->GetMap();

        int32 diff = player->getLevel() - creature->getLevel();

        if (diff > 10)
            return;

        const int CONFIG_DROP_RUNIC_ESSENCE_NORMAL_CREATURE = sWorld->GetValue("CONFIG_DROP_RUNIC_ESSENCE_NORMAL_CREATURE");
        const int CONFIG_DROP_RUNIC_ESSENCE_NORMAL_BOSS = sWorld->GetValue("CONFIG_DROP_RUNIC_ESSENCE_NORMAL_BOSS");
        const int CONFIG_DROP_RUNIC_ESSENCE_HEROIC_BOSS = sWorld->GetValue("CONFIG_DROP_RUNIC_ESSENCE_HEROIC_BOSS");
        const int CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS = sWorld->GetValue("CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS");

        const int CONFIG_DROP_RUNIC_ESSENCE_NORMAL_BOSS_RAID = sWorld->GetValue("CONFIG_DROP_RUNIC_ESSENCE_NORMAL_BOSS_RAID");
        const int CONFIG_DROP_RUNIC_ESSENCE_HEROIC_BOSS_RAID = sWorld->GetValue("CONFIG_DROP_RUNIC_ESSENCE_HEROIC_BOSS_RAID");
        const int CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS_RAID = sWorld->GetValue("CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS_RAID");

        const int CONFIG_DROP_RUNIC_DUST_NORMAL_CREATURE = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_NORMAL_CREATURE");
        const int CONFIG_DROP_RUNIC_DUST_NORMAL_BOSS = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_NORMAL_BOSS");
        const int CONFIG_DROP_RUNIC_DUST_HEROIC_BOSS = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_HEROIC_BOSS");
        const int CONFIG_DROP_RUNIC_DUST_MYTHIC_BOSS = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_MYTHIC_BOSS");

        const int CONFIG_DROP_RUNIC_DUST_NORMAL_BOSS_RAID = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_NORMAL_BOSS_RAID");
        const int CONFIG_DROP_RUNIC_DUST_HEROIC_BOSS_RAID = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_HEROIC_BOSS_RAID");
        const int CONFIG_DROP_RUNIC_DUST_MYTHIC_BOSS_RAID = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_MYTHIC_BOSS_RAID");


        if (creature->isWorldBoss()) {
            AddRunicDustToLoot(CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS_RAID, loot);
            AddRunicEssenceToLoot(CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS_RAID, loot);
        }
        else {
            if (creature->IsDungeonBoss()) {
                if (map->IsNonRaidDungeon())
                {
                    if (map->GetDifficulty() == DUNGEON_DIFFICULTY_NORMAL)
                    {
                        AddRunicEssenceToLoot(CONFIG_DROP_RUNIC_ESSENCE_NORMAL_BOSS, loot);
                        AddRunicDustToLoot(CONFIG_DROP_RUNIC_DUST_NORMAL_BOSS, loot);
                    }
                    if (map->GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC)
                    {
                        AddRunicEssenceToLoot(CONFIG_DROP_RUNIC_ESSENCE_HEROIC_BOSS, loot);
                        AddRunicDustToLoot(CONFIG_DROP_RUNIC_DUST_HEROIC_BOSS, loot);
                    }
                    if (map->GetDifficulty() == DUNGEON_DIFFICULTY_EPIC)
                    {
                        AddRunicEssenceToLoot(CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS, loot);
                        AddRunicDustToLoot(CONFIG_DROP_RUNIC_DUST_MYTHIC_BOSS, loot);
                    }
                }

                if (map->IsRaid())
                {
                    if (map->GetDifficulty() == RAID_DIFFICULTY_10_25MAN_NORMAL)
                    {
                        AddRunicDustToLoot(CONFIG_DROP_RUNIC_DUST_NORMAL_BOSS_RAID, loot);
                        AddRunicEssenceToLoot(CONFIG_DROP_RUNIC_ESSENCE_NORMAL_BOSS_RAID, loot);
                    }
                    if (map->GetDifficulty() == RAID_DIFFICULTY_10_25MAN_HEROIC)
                    {
                        AddRunicDustToLoot(CONFIG_DROP_RUNIC_DUST_HEROIC_BOSS_RAID, loot);
                        AddRunicEssenceToLoot(CONFIG_DROP_RUNIC_ESSENCE_HEROIC_BOSS_RAID, loot);
                    }
                    if (map->GetDifficulty() == RAID_DIFFICULTY_10_25MAN_MYTHIC)
                    {
                        AddRunicDustToLoot(CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS_RAID, loot);
                        AddRunicEssenceToLoot(CONFIG_DROP_RUNIC_ESSENCE_MYTHIC_BOSS_RAID, loot);
                    }
                }
            }
            else {
                if (roll_chance_i(50)) {
                    AddRunicEssenceToLoot(CONFIG_DROP_RUNIC_ESSENCE_NORMAL_CREATURE, loot);
                }

                if (roll_chance_i(50)) {
                    AddRunicDustToLoot(CONFIG_DROP_RUNIC_DUST_NORMAL_CREATURE, loot);
                }
            }
        }
       
    }

    void OnAfterLootTemplateProcess(Loot* loot, LootTemplate const* tab, LootStore const& store, Player* lootOwner, bool personal, bool noEmptyError, uint16 lootMode, WorldObject* source)
    {
        bool isFishing = store.GetEntryName() == "area id";

        if (isFishing)
        {
            int valueFishing = sWorld->GetValue("CONFIG_FISHING_RUNIC_DUST_MIN");
            AddRunicDustToLoot(valueFishing, loot);
            AddRunicEssenceToLoot(valueFishing, loot);
        }

        if (!source)
            return;

        if (GameObject* go = source->ToGameObject())
        {
            uint32 lockId = go->GetGOInfo()->GetLockId();
            LockEntry const* lock = sLockStore.LookupEntry(lockId);

            for (int j = 0; j < MAX_LOCK_CASE; ++j)
            {
                switch (lock->Type[j])
                {
                case LOCK_KEY_SKILL:
                    uint32 skillId = SkillByLockType(LockType(lock->Index[j]));

                    if (skillId == SKILL_HERBALISM || skillId == SKILL_MINING)
                    {
                        if (uint32 pureSkillValue = lootOwner->GetPureSkillValue(skillId))
                        {
                            int valueFromMinningAndHerborsimMin = sWorld->GetValue("CONFIG_MINNING_AND_HERBORISM_RUNIC_DUST_MIN");
                            int valueFromMinningAndHerborsimMax = sWorld->GetValue("CONFIG_MINNING_AND_HERBORISM_RUNIC_DUST_MAX");
                            AddRunicDustToLoot(valueFromMinningAndHerborsimMin, loot);
                            AddRunicEssenceToLoot(valueFromMinningAndHerborsimMin, loot);
                        }
                    }
                    break;
                }
            }
        }

        if (Creature* creature = source->ToCreature())
        {
            if (creature->GetCreatureTemplate()->SkinLootId > 0)
            {
                if (uint32 pureSkillValue = lootOwner->GetPureSkillValue(SKILL_SKINNING) && creature->getLevel() >= lootOwner->getLevel())
                {
                    int valueFromSkinningMin = sWorld->GetValue("CONFIG_SKINNING_RUNIC_DUST_MIN");
                    int valueFromSkinningMax = sWorld->GetValue("CONFIG_SKINNING_RUNIC_DUST_MAX");
                    AddRunicDustToLoot(valueFromSkinningMin, loot);
                    AddRunicEssenceToLoot(valueFromSkinningMin, loot);
                }
            }
            AddBonusRunicDustAndRunicEssence(creature, lootOwner, loot);
        }
    }
};

class RunicDust_PlayerScripts : public PlayerScript
{
public:
    RunicDust_PlayerScripts() : PlayerScript("RunicDust_PlayerScripts") { }


    void OnQuestRewardItem(Player* player, Item* item, uint32 count)
    {
        uint32 entry = item->GetEntry();

        if (entry == ITEM_RUNIC_DUST)
        {
            float multiplier = sWorld->GetValue("CONFIG_DROP_RUNIC_DUST_MULTIPLIER");
            int augmentation = count * multiplier / 100;
            player->AddItem(ITEM_RUNIC_DUST, augmentation);
        }
    }

};


void AddSC_RunicDust_Scripts()
{
    new RunicDust_MiscScript();
    new RunicDust_PlayerScripts();
}
