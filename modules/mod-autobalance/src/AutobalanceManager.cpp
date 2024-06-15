#include "AutobalanceManager.h"
#include "PlayerSpecialization.h"
#include "WorldSession.h"
#include "Chat.h"

std::map<uint8, AutobalanceScalingInfo> AutoBalanceManager::m_ScalingPerSpecialization = {};
std::map<uint32, float> AutoBalanceManager::m_ScalingPerSpecializationValueHealth = {
    { }

};
std::map<uint32, AutobalanceScalingInfo> AutoBalanceManager::m_OverrideScalingPerCreatureId = {};
std::map<uint32, std::map<Difficulty, AutobalanceScalingInfo>> AutoBalanceManager::m_ScalingDungeonDifficulty = {};


std::map<uint32, Role> AutoBalanceManager::m_PlayerRoles = {};


std::list<Player*> AutoBalanceManager::GetPlayersMap(Map* map)
{
    std::list<Player*> players = {};

    Map::PlayerList const& playerList = map->GetPlayers();
    if (!playerList.IsEmpty())
        for (Map::PlayerList::const_iterator playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
            if (Player* playerHandle = playerIteration->GetSource())
                if(!playerHandle->IsGameMaster())
                    players.push_back(playerHandle);

    return players;
}

void AutoBalanceManager::SendMessageScalingInfo(Map* map)
{

    if (!map->IsDungeon() && !map->IsRaid())
        return;

    std::list<Player*> players = GetPlayersMap(map);

    if (players.size() == 0)
        return;

    std::string mapName = map->GetMapName();

    uint32 maxPlayers = map->IsRaid() && players.size() < 10 ? 10 : players.size();

    for (const auto& player : players)
    {
        ChatHandler(player->GetSession()).SendSysMessage(mapName + " is now scaling for " + std::to_string(maxPlayers) + " player(s).");
    }
}


void AutoBalanceManager::InitializeScalingPerSpecialization()
{
    m_ScalingPerSpecialization = {};



    QueryResult result = WorldDatabase.Query("SELECT * FROM scalings_per_specialization");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint8 specialization = fields[0].Get<uint8>();
        float meleeDamage = fields[1].Get<float>();
        float healthModifier = fields[2].Get<float>();
        float spellDamageModifier = fields[3].Get<float>();
        float periodicDamageModifier = fields[4].Get<float>();
        AutobalanceScalingInfo info = { meleeDamage, healthModifier, spellDamageModifier, periodicDamageModifier };
        m_ScalingPerSpecialization[specialization] = info;
    } while (result->NextRow());
}

void AutoBalanceManager::InitializeScalingRaid()
{
    m_ScalingDungeonDifficulty = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM scaling_instance");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 mapId = fields[0].Get<uint32>();
        uint32 difficulty = fields[1].Get<uint32>();
        double healthModifier = fields[2].Get<double>();
        double damageModifier = fields[3].Get<double>();

        AutobalanceScalingInfo info = { damageModifier, healthModifier, 0, 0 };

        m_ScalingDungeonDifficulty[mapId].insert(std::make_pair(Difficulty(difficulty), info));
    } while (result->NextRow());
}

AutobalanceScalingInfo AutoBalanceManager::GetScalingInfo(Map* map, Unit* creature)
{
    if (!map->IsRaid() && !map->IsDungeon())
        return {};

    if (creature->isDead())
        return {};

    bool isRaid = map->IsRaid();
    Difficulty difficulty = map->GetDifficulty();
    uint8 playerCount = map->GetPlayers().getSize();

    if (playerCount <= 1 && !isRaid) {
        auto mapPlayer = map->GetPlayers().getFirst();
        Player* player = mapPlayer->GetSource();

        if (!player)
            return {};

        uint8 CurrentSpecialization = PlayerSpecialization::GetCurrentSpecId(player);

        if (CurrentSpecialization <= 0)
            return { 0.5, 0.3, 0, 0 };

        auto match = m_ScalingPerSpecialization.find(CurrentSpecialization);

        if (match != m_ScalingPerSpecialization.end())
            return match->second;

        return {};
    }

    if (playerCount > 1) {
        auto match = m_ScalingDungeonDifficulty.find(map->GetId());
        if (match != m_ScalingDungeonDifficulty.end()) {
            auto found = match->second.find(map->GetDifficulty());
            if (found != match->second.end())
                return found->second;
        }
    }

    return {};
}

void AutoBalanceManager::ApplyScalingHealthAndMana(Map* map, Creature* creature)
{

    if (!creature || !creature->GetMap())
        return;

    if (!creature->GetMap()->IsDungeon() && !creature->GetMap()->IsBattleground())
        return;

    if (creature->IsPet() || (creature->IsSummon() && creature->IsControlledByPlayer()) || creature->IsControlledByPlayer())
        return;

    if (!creature->IsAlive())
        return;

    uint32 playerCount = map->GetPlayersCountExceptGMs();
    bool isRaid = map->IsRaid();

    if (playerCount == 0)
        return;

    bool shouldRecalculate = (playerCount != creature->AutobalancePlayerCount) || creature->ShouldRecalculate == true;

    if (!shouldRecalculate)
        return;

    creature->AutobalancePlayerCount = playerCount;

    CreatureTemplate const* creatureTemplate = creature->GetCreatureTemplate();

    if (!creatureTemplate)
        return;

    if (creature->prevMaxHealth <= 0)
        creature->prevMaxHealth = creature->GetMaxHealth();

    uint32 scaledHealth = 0;
    creature->ShouldRecalculate = false;

    if (map->IsRaid())
    {
        double totalReduction = CalculateHealthRaidScaling(playerCount);
        scaledHealth = creature->prevMaxHealth * totalReduction;
    }
    else
    {
        double totalReduction = CalculateHealthDungeonScaling(map);
        scaledHealth = creature->prevMaxHealth * totalReduction;
    }

    creature->SetMaxHealth(scaledHealth);
    creature->SetCreateHealth(scaledHealth);
    creature->SetModifierValue(UNIT_MOD_HEALTH, BASE_VALUE, (float)scaledHealth);
    creature->ResetPlayerDamageReq();
    creature->SetHealth(scaledHealth);
}

float AutoBalanceManager::CalculateHealthRaidScaling(uint8 totalPlayerInRaid)
{
    if (totalPlayerInRaid < 10)
        totalPlayerInRaid = 10;

    return ((totalPlayerInRaid - 10) * 0.10) + 1;
}

float AutoBalanceManager::CalculateHealthDungeonScaling(Map* map)
{
    std::list<Player*> players = GetPlayersMap(map);

    float healthScaling = 0;

    for (auto const& i : players) {
        const float value = GetPlayerSpecializationHealthValueForScaling(i);
        healthScaling += value;
    }

    return healthScaling;
}

float AutoBalanceManager::CalculateDamageDungeonScaling(Map* map)
{
    bool hasDps = false;
    bool hasHealer = false;
    bool hasTank = false;

    Map::PlayerList const& playerList = map->GetPlayers();
    for (Map::PlayerList::const_iterator playerIteration = playerList.begin(); playerIteration != playerList.end(); ++playerIteration)
    {
        if (Player* player = playerIteration->GetSource())
        {
            if (!player->IsGameMaster())
            {
                Role* realRole = GetRealRole(player);
                bool isDps = IsADpsSpec(player) || realRole && realRole->isDps;
                bool isHealer = IsAHealerSpec(player) || realRole && realRole->isHealer;
                bool isTank = IsATankSpec(player) || realRole && realRole->isTank;
                
                if (!hasTank && isTank)
                {
                    hasTank = true;
                }
                else if (!hasHealer && isHealer)
                {
                    hasHealer = true;
                }
                else if (!hasDps && isDps)
                {
                    hasDps = true;
                }

                // Stop the loop if all roles are found
                if (hasDps && hasHealer && hasTank)
                    break;
            }
        }
    }

    if (hasDps && !hasHealer && !hasTank)
        return 0.15f; // onlyDps
    if (!hasDps && hasHealer && !hasTank)
        return 0.25f; // onlyHealer
    if (!hasDps && !hasHealer && hasTank)
        return 0.50f; // onlyTank
    if (!hasDps && hasHealer && hasTank)
        return 1.0f; // healerAndTank
    if (hasDps && hasHealer && !hasTank)
        return 0.50f; // healerAndDps
    if (hasDps && !hasHealer && hasTank)
        return 0.50f; // tankAndDps
    if (hasDps && hasHealer && hasTank)
        return 1.0f; // fullHouse

    return 0.15f;
}



float AutoBalanceManager::GetPlayerSpecializationHealthValueForScaling(Player* player)
{
    Role* realRole = GetRealRole(player);

    bool isHealer = IsAHealerSpec(player) || (realRole && realRole->isHealer);
    bool isTank = IsATankSpec(player) || (realRole && realRole->isTank);
    bool isDps = IsADpsSpec(player) || (realRole && realRole->isDps);

    if (isDps) return 0.25f;
    if (isTank) return 0.15f;
    if (isHealer) return 0.10f;

    return 0.25;
}

void AutoBalanceManager::InitializePlayerRoleDependingOnTalentTree(Player* player)
{
    uint32 dpsTalentCount = 0;
    uint32 healTalentCount = 0;
    uint32 tankTalentCount = 0;

    m_PlayerRoles[player->GetGUID().GetCounter()].isTank = false;
    m_PlayerRoles[player->GetGUID().GetCounter()].isHealer = false;
    m_PlayerRoles[player->GetGUID().GetCounter()].isDps = false;

    const PlayerTalentMap& talentMap = player->GetTalentMap();
    for (const auto& itr : talentMap)
    {
        if (const TalentSpellPos* talentPos = GetTalentSpellPos(itr.first))
        {
            if (const TalentEntry* itrTalentInfo = sTalentStore.LookupEntry(talentPos->talent_id))
            {
                uint32 tab = itrTalentInfo->TalentTab;
                bool hasTalent = false;

                for (uint8 j = 0; j < MAX_TALENT_RANK; ++j)
                {
                    if (itrTalentInfo->RankID[j])
                    {
                        if (player->HasSpell(itrTalentInfo->RankID[j]) || player->HasAura(itrTalentInfo->RankID[j]))
                        {
                            hasTalent = true;
                            break;
                        }
                    }
                }

                if (!hasTalent)
                    continue;

                if (IsATalentDps(tab)) dpsTalentCount += 1;
                if (IsATalentTank(tab)) tankTalentCount += 1;
                if (IsATalentHeal(tab)) healTalentCount += 1;
            }
        }
    }

    if (tankTalentCount > 20)
    {
        m_PlayerRoles[player->GetGUID().GetCounter()].isTank = true;
    }
    if (healTalentCount > 20)
    {
        m_PlayerRoles[player->GetGUID().GetCounter()].isHealer = true;
    }
    if (dpsTalentCount > 20)
    {
        m_PlayerRoles[player->GetGUID().GetCounter()].isDps = true;
    }
}

Role* AutoBalanceManager::GetRealRole(Player* player)
{
    auto it = m_PlayerRoles.find(player->GetGUID().GetCounter());

    if (it != m_PlayerRoles.end())
        return &it->second;

    return nullptr;
}

bool AutoBalanceManager::IsATalentDps(uint32 tab)
{
    switch (tab)
    {
    case TALENT_TREE_WARRIOR_ARMS:
    case TALENT_TREE_WARRIOR_FURY:
    case TALENT_TREE_WARRIOR_HOPLITE:
    case TALENT_TREE_PALADIN_RETRIBUTION:
    case TALENT_TREE_PALADIN_INQUISITOR:
    case TALENT_TREE_HUNTER_BEAST_MASTERY:
    case TALENT_TREE_HUNTER_MARKSMANSHIP:
    case TALENT_TREE_HUNTER_SURVIVAL:
    case TALENT_TREE_HUNTER_DARK_RANGER:
    case TALENT_TREE_ROGUE_ASSASSINATION:
    case TALENT_TREE_ROGUE_COMBAT:
    case TALENT_TREE_ROGUE_SUBTLETY:
    case TALENT_TREE_ROGUE_OUTLAW:
    case TALENT_TREE_PRIEST_SHADOW:
    case TALENT_TREE_PRIEST_ABSOLUTION:
    case TALENT_TREE_DEATH_KNIGHT_FROST:
    case TALENT_TREE_DEATH_KNIGHT_UNHOLY:
    case TALENT_TREE_SHAMAN_ELEMENTAL:
    case TALENT_TREE_SHAMAN_ENHANCEMENT:
    case TALENT_TREE_MAGE_ARCANE:
    case TALENT_TREE_MAGE_FIRE:
    case TALENT_TREE_MAGE_FROST:
    case TALENT_TREE_MAGE_SPELLBLADE:
    case TALENT_TREE_WARLOCK_AFFLICTION:
    case TALENT_TREE_WARLOCK_DEMONOLOGY:
    case TALENT_TREE_WARLOCK_DESTRUCTION:
    case TALENT_TREE_DRUID_BALANCE:
    case TALENT_TREE_DRUID_FERAL_COMBAT:
        return true;
    default:
        return false;
    }
}

bool AutoBalanceManager::IsATalentTank(uint32 tab)
{
    switch (tab)
    {
    case TALENT_TREE_WARRIOR_PROTECTION:
    case TALENT_TREE_PALADIN_PROTECTION:
    case TALENT_TREE_DRUID_GUARDIAN:
    case TALENT_TREE_DEATH_KNIGHT_BLOOD:
    case TALENT_TREE_WARLOCK_DEMONBOUND:
        return true;
    default:
        return false;
    }
}

bool AutoBalanceManager::IsATalentHeal(uint32 tab)
{
    switch (tab)
    {
    case TALENT_TREE_DRUID_RESTORATION:
    case TALENT_TREE_SHAMAN_RESTORATION:
    case TALENT_TREE_PRIEST_DISCIPLINE:
    case TALENT_TREE_PRIEST_HOLY:
    case TALENT_TREE_SHAMAN_SPIRIT_MASTER:
    case TALENT_TREE_DEATH_KNIGHT_SOULWEAVER:
        return true;
    default:
        return false;
    }
}

bool AutoBalanceManager::IsATankSpec(Player* player)
{
    uint32 specId = PlayerSpecialization::GetCurrentSpecId(player);

    if (!specId)
        return false;

    switch (specId) {
        case WARRIOR_PROTECTION:
        case DK_BLOOD:
        case DRUID_GUARDIAN:
        case PALADIN_PROTECTION:
        case SHAMAN_SPIRIT_MASTER:
        case WARLOCK_DEMONBOUND:
            return true;
        break;
    }

    return false;
}

bool AutoBalanceManager::IsADpsSpec(Player* player)
{
    uint32 specId = PlayerSpecialization::GetCurrentSpecId(player);

    if (!specId)
        return false;

    switch (specId) {
        // DPS
        case WARRIOR_ARMS:
        case WARRIOR_FURY:
        case WARRIOR_HOPLITE:
        case MAGE_ARCANE:
        case MAGE_FIRE:
        case MAGE_FROST:
        case MAGE_SPELLBLADE:
        case DK_FROST:
        case DK_UNHOLY:
        case DRUID_BALANCE:
        case DRUID_FERAL:
        case HUNTER_BEAST:
        case HUNTER_MARSKMANSHIP:
        case HUNTER_SURVIVAL:
        case HUNTER_DARK_RANGER:
        case PALADIN_RETRIBUTION:
        case PALADIN_INQUISITOR:
        case ROGUE_ASSASSINATION:
        case ROGUE_COMBAT:
        case ROGUE_SUBTLETY:
        case ROGUE_OUTLAW:
        case SHAMAN_ELEMENTAL:
        case SHAMAN_ENCHANCEMENT:
        case WARLOCK_AFFLICTION:
        case WARLOCK_DEMONOLOGY:
        case WARLOCK_DESTRUCTION:
        case PRIEST_SHADOW:
        case PRIEST_ABSOLUTION:
        return true;
        break;
    }

    return false;
}

bool AutoBalanceManager::IsAHealerSpec(Player* player)
{
    uint32 specId = PlayerSpecialization::GetCurrentSpecId(player);

    if (!specId)
        return false;

    switch (specId) {
        // Heal
        case DK_SOULWEAVER:
        case DRUID_RESTO:
        case PALADIN_HOLY:
        case SHAMAN_RESTORATION:
        case PRIEST_DISCI:
        case PRIEST_HOLY:
            return true;
        break;
    }
    return false;
}
