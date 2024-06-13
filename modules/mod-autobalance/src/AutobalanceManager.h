#pragma once

#include "Player/Player.h"
#include "DatabaseEnv.h"
#include "Map.h"
#include "Creature.h"

struct AutobalanceScalingInfo {
    double meleeDamageModifier;
    double healthModifier;
    double spellDamageModifier;
    double periodicDamageModifier;
};

struct CreatureInfo {
    uint32 prevMaxHealth;
    uint32 prevMaxMana;
};

struct Role {
    bool isTank;
    bool isDps;
    bool isHealer;
};

class AutoBalanceManager {

private:
    static std::map<uint8, AutobalanceScalingInfo> m_ScalingPerSpecialization;
    static std::map<uint32, float> m_ScalingPerSpecializationValueHealth;
    static std::map<uint32, AutobalanceScalingInfo> m_OverrideScalingPerCreatureId;
    static std::map<uint32, Role> m_PlayerRoles;
    static std::map<uint32, std::map<Difficulty, AutobalanceScalingInfo>> m_ScalingDungeonDifficulty;
public:
    static void InitializeScalingPerSpecialization();
    static void InitializeScalingRaid();
    static std::list<Player*> GetPlayersMap(Map* map);

    static AutobalanceScalingInfo GetScalingInfo(Map* map, Unit* creature);
    static void ApplyScalingHealthAndMana(Map* map, Creature* creature);
    static float CalculateHealthRaidScaling(uint8 playerCount);
    static float CalculateDamageDungeonScaling(Map* map);
    static float CalculateHealthDungeonScaling(Map* map);
    static float GetPlayerSpecializationHealthValueForScaling(Player* player);
    static float GetPlayerSpecializationDamageValueForScaling(Player* player);
    static void  InitializePlayerRoleDependingOnTalentTree(Player* player);
    static Role* GetRealRole(Player* player);

    static bool IsATalentDps(uint32 tab);
    static bool IsATalentTank(uint32 tab);
    static bool IsATalentHeal(uint32 tab);

    static bool IsATankSpec(Player* player);
    static bool IsADpsSpec(Player* player);
    static bool IsAHealerSpec(Player* player);

    static void SendMessageScalingInfo(Map* map);
};

