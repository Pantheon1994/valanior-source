#pragma once

#include "PlayerSpecialization.h"
#include "boost/bind.hpp"
#include "Config.h"
#include "ElunaIncludes.h"
#include "LuaEngine.h"
#include "boost/iterator/counting_iterator.hpp"
#include "RunesManager.h"

std::map<uint64 /* guid */, Spec> PlayerSpecialization::m_PlayersSpecialization = {};
std::map<uint32 /* specId */, Specialization> PlayerSpecialization::m_Specializations = {};
std::map<uint32 /* specId */, std::vector<uint32>> PlayerSpecialization::m_SpecSpells = {};

void PlayerSpecialization::LoadAllSpecsPlayers()
{
    m_PlayersSpecialization = {};

    QueryResult result = CharacterDatabase.Query("SELECT guid, specId, preferedSpecId FROM characters");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint64 guid = fields[0].Get<uint64>();
        uint32 specId = fields[1].Get<uint32>();
        int32 PreferredSpecId = fields[2].Get<int32>();
        m_PlayersSpecialization[guid] = { specId, PreferredSpecId };
    } while (result->NextRow());
}

void PlayerSpecialization::LoadAllSpecsSpells()
{
    m_SpecSpells = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM specialization_spells");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 specId = fields[0].Get<uint32>();
        uint32 spellId = fields[1].Get<uint32>();
        m_SpecSpells[specId].push_back(spellId);
    } while (result->NextRow());
}

void PlayerSpecialization::InitializeSpecializations()
{
    m_Specializations[WARRIOR_ARMS] = { 1, 12294, "Arms", 1, 200000, 23.78,	false,	0, POWER_ALL };
    m_Specializations[WARRIOR_FURY] = { 2, 20375, "Fury", 1, 200003, 19.45, false,	0, POWER_ALL };
    m_Specializations[WARRIOR_PROTECTION] = { 3, 71, "Protection", 1, 200005, 17.83,	true,	190750, POWER_ALL };
    m_Specializations[WARRIOR_HOPLITE] = { 33, 84551, "Hoplite", 1, 199998, 107.00,	false,	0, POWER_ALL };

    m_Specializations[MAGE_ARCANE] = { 4, 42995, "Arcane", 8, 300111, 21.40, true, 300113, POWER_ALL };
    m_Specializations[MAGE_FIRE] = { 5, 42833, "Fire", 8, 300109,	35.67,	false,	0, POWER_ALL };
    m_Specializations[MAGE_FROST] = { 6, 42842, "Frost", 8, 300105,	14.27,	true,	299998, POWER_ALL };
    m_Specializations[MAGE_SPELLBLADE] = { 34, 300114 , "Spellblade", 8, 300114, 8.92, true, 300115, POWER_ALL };

    m_Specializations[PALADIN_HOLY] = { 17, 48782, "Holy", 2, 400000, 17.83, false,	0, POWER_ALL };
    m_Specializations[PALADIN_PROTECTION] = { 18, 48952, "Protection", 2, 400002, 26.75, true, 400004, POWER_ALL };
    m_Specializations[PALADIN_RETRIBUTION] = { 19, 35395, "Retribution", 2, 400006,	16.46, true, 400008, POWER_ALL };
    m_Specializations[PALADIN_INQUISITOR] = { 37, 86510, "Inquisitor", 2, 399999,	14.27, true, 399998, POWER_ALL };

    m_Specializations[HUNTER_BEAST] = { 14, 80132, "Beast Mastery", 3, 500003, 14.27, true,	500006, POWER_ALL };
    m_Specializations[HUNTER_MARSKMANSHIP] = { 15, 80140, "Marksmanship", 3, 500004, 19.45,	true, 500007, POWER_ALL  };
    m_Specializations[HUNTER_SURVIVAL] = { 16, 19306, "Survival", 3, 500005, 16.46,	true, 500002, POWER_ALL };
    m_Specializations[HUNTER_DARK_RANGER] = { 35, 85012, "Dark Ranger", 3, 499996, 13.38, true, 499997, POWER_ALL };

    m_Specializations[DK_BLOOD] = { 7, 50371, "Blood", 6, 590001, 13.38, true, 590004, POWER_ALL };
    m_Specializations[DK_FROST] = { 8, 50385, "Frost", 6, 600000, 16.46, true, 600002, POWER_ALL };
    m_Specializations[DK_UNHOLY] = { 9, 50392, "Unholy", 6, 600005, 17.83, true, 590000, POWER_ALL };
    m_Specializations[DK_SOULWEAVER] = { 39, 87000, "Soulweaver", 6, 590005, 21.40, false, 0, POWER_ALL };

    m_Specializations[DRUID_BALANCE] = { 10, 80536, "Balance", 11, 700000, 23.78, false, 0, POWER_ALL };
    m_Specializations[DRUID_FERAL] = { 11, 80549, "Feral", 11, 700004, 17.83, true, 700006, POWER_ALL };
    m_Specializations[DRUID_RESTO] = { 12, 53251, "Restoration", 11, 700010, 53.50, false, 0, POWER_ALL };
    m_Specializations[DRUID_GUARDIAN] = { 13, 80510, "Guardian", 11, 700007, 26.75, true, 700009, POWER_ALL };

    m_Specializations[PRIEST_DISCI] = { 29, 48066, "Discipline", 5, 900000, 21.40, true, 900001, POWER_ALL };
    m_Specializations[PRIEST_HOLY] = { 30, 48078, "Holy", 5, 900005, 21.40, false, 0, POWER_ALL };
    m_Specializations[PRIEST_SHADOW] = { 31, 81048, "Shadow", 5, 900008, 53.50, false, 0, POWER_ALL };
    m_Specializations[PRIEST_ABSOLUTION] = { 36, 900013, "Absolution", 5, 900010, 53.50, false, 0, POWER_ALL };

    m_Specializations[SHAMAN_ELEMENTAL] = { 23, 403, "Elemental", 7, 1000000, 21.40, false, 0, POWER_RUNIC_POWER };
    m_Specializations[SHAMAN_ENCHANCEMENT] = { 24, 324, "Enchancement", 7, 1000002, 16.46, true, 1000003, POWER_MANA };
    m_Specializations[SHAMAN_RESTORATION] = { 25, 331, "Restoration", 7, 1000005, 11.89, false, 0, POWER_MANA };
    m_Specializations[SHAMAN_SPIRIT_MASTER] = { 32, 84101, "Spirit Master", 7, 1000007, 26.75, true, 1000009, POWER_MANA };

    m_Specializations[ROGUE_ASSASSINATION] = { 20, 57993, "Assassination", 4, 1100000, 16.46, true, 1100001, POWER_ALL };
    m_Specializations[ROGUE_COMBAT] = { 21, 51690, "Combat", 4, 1100003, 11.89, false, 0, POWER_ALL };
    m_Specializations[ROGUE_SUBTLETY] = { 22, 82016 , "Subtlety", 4, 1100005, 11.89, true, 1100006, POWER_ALL };
    m_Specializations[ROGUE_OUTLAW] = { 38, 82082, "Outlaw", 4, 1099999, 35.67, true, 1099998, POWER_ALL };

    m_Specializations[WARLOCK_AFFLICTION] = { 26, 83051, "Affliction", 9, 1100018, 11.89, true, 1100021, POWER_ALL };
    m_Specializations[WARLOCK_DEMONOLOGY] = { 27, 83031, "Demonology", 9, 1100020, 17.83, true, 1100023, POWER_ALL };
    m_Specializations[WARLOCK_DESTRUCTION] = { 28, 47820 , "Destruction", 9, 1100019, 26.75, false, 0, POWER_ALL };
    m_Specializations[WARLOCK_DEMONBOUND] = { 40, 61610, "Demonbound", 9, 1100024, 8.92, true, 1100025, POWER_ALL };
}
    
void PlayerSpecialization::ActivateSpecialization(Player* player, uint32 newSpecId)
{
    if (player->GetMap()->IsDungeon()) {
        player->GetSession()->SendAreaTriggerMessage("You cannot change your specialization while in a dungeon.");
        return;
    }

    auto match = m_Specializations.find(newSpecId);

    if (match == m_Specializations.end()) {
        sEluna->OnActivateSpec(player, "This specialization does not exist!", false, 0);
        return;
    }

    Specialization newSpec = m_Specializations[newSpecId];

    if (newSpec.classInfo != player->getClass()) {
        sEluna->OnActivateSpec(player, "You cannot do that", false, 0);
        return;
    }

    player->CastCustomSpell(79852, SPELLVALUE_BASE_POINT0, newSpecId, player, TRIGGERED_NONE);
}


void PlayerSpecialization::UpdateMastery(Player* player, uint32 rating)
{
    uint32 currentSpecId = GetCurrentSpecId(player);

    if (currentSpecId == 0)
        return;

    Specialization spec = m_Specializations[currentSpecId];

    if (Aura* aura = player->GetAura(spec.masteryTalentId)) {
        const float value = rating / spec.modifierPerPoint;
        player->SetMastery(value);
        if (spec.update) {
            player->RemoveAura(spec.castSpellId);
            player->CastSpell(player, spec.castSpellId, TRIGGERED_IGNORE_CAST_IN_PROGRESS);
        }
    }
}

bool PlayerSpecialization::Exception(Player* player, uint32 spellId)
{
    return (player->HasAura(SPELL_DRUID_AVATAR_OF_ASHAMANE_REPLACER) && spellId == SPELL_DRUID_BERSERK_CAT)
        || (player->HasAura(SPELL_DRUID_GUARDIAN_OF_URSOC_REPLACER) && spellId == SPELL_DRUID_BERSERK_BEAR)
        || (player->HasAura(SPELL_WARRIOR_WARBREAKER_REPLACER) && spellId == SPELL_WARRIOR_COLOSSUS_SMASH)
        || (player->HasAura(SPELL_DRUID_RAZE_REPLACER) && spellId == SPELL_DRUID_MAUL);
}

uint32 PlayerSpecialization::GetSpellException(Player* player, uint32 spellId)
{
    if (player->HasAura(SPELL_DRUID_AVATAR_OF_ASHAMANE_REPLACER) && spellId == SPELL_DRUID_BERSERK_CAT)
    {
        return SPELL_DRUID_AVATAR_OF_ASHAMANE;
    }

    if (player->HasAura(SPELL_DRUID_GUARDIAN_OF_URSOC_REPLACER) && spellId == SPELL_DRUID_BERSERK_BEAR)
    {
        return SPELL_DRUID_GUARDIAN_OF_URSOC;
    }

    if (player->HasAura(SPELL_WARRIOR_WARBREAKER_REPLACER) && spellId == SPELL_WARRIOR_COLOSSUS_SMASH)
    {
        return SPELL_WARRIOR_WARBREAKER;
    }

    if (player->HasAura(SPELL_DRUID_RAZE_REPLACER) && spellId == SPELL_DRUID_MAUL)
    {
        return SPELL_DRUID_RAZE;
    }
}

void PlayerSpecialization::RemoveSpellWhenTalentChange(Player* player)
{
    // Druid Orbital Strike
    if (player->HasSpell(RUNE_DRUID_ORBITAL_STRIKE))
        player->removeSpell(RUNE_DRUID_ORBITAL_STRIKE, SPEC_MASK_ALL, false);
}


void PlayerSpecialization::RemoveSpellsAndAurasOnSpecChange(Player* player)
{
    if (player->HasAura(SPELL_HUNTER_LONE_WOLF))
        player->RemoveAura(SPELL_HUNTER_LONE_WOLF);

    if (player->HasAura(SPELL_DRUID_AVATAR_OF_ASHAMANE_REPLACER) && !player->HasSpell(SPELL_DRUID_BERSERK_CAT))
    {
        player->removeSpell(SPELL_DRUID_AVATAR_OF_ASHAMANE, SPEC_MASK_ALL, false, true);
        player->RemoveAura(SPELL_DRUID_AVATAR_OF_ASHAMANE);
    }

    if (player->HasAura(SPELL_DRUID_GUARDIAN_OF_URSOC_REPLACER) && !player->HasSpell(SPELL_DRUID_BERSERK_BEAR))
    {
        player->removeSpell(SPELL_DRUID_GUARDIAN_OF_URSOC, SPEC_MASK_ALL, false, true);
        player->RemoveAura(SPELL_DRUID_GUARDIAN_OF_URSOC);
    }

    if (player->HasAura(SPELL_DRUID_RAZE_REPLACER) && !player->HasSpell(SPELL_DRUID_MAUL))
    {
        player->removeSpell(SPELL_DRUID_RAZE, SPEC_MASK_ALL, false, true);
    }

    if (player->HasAura(SPELL_WARRIOR_WARBREAKER_REPLACER) && !player->HasSpell(SPELL_WARRIOR_COLOSSUS_SMASH))
    {
        player->removeSpell(SPELL_WARRIOR_WARBREAKER, SPEC_MASK_ALL, false, true);
    } 
}

std::vector<std::string> PlayerSpecialization::GetSpecializations(Player* player)
{
    std::vector<std::string> elements = {};
    uint32 currentSpecId = GetCurrentSpecId(player);
    uint32 PreferredSpecId = GetPreferredSpecId(player);

    std::stringstream fmt;
    fmt << currentSpecId << ";" << PreferredSpecId;

    elements.push_back(fmt.str());

    for (auto const& spec : m_Specializations) {
        Specialization specialization = spec.second;
        if (spec.second.classInfo == player->getClass()) {
            std::string spellsIds = "#";
            for (auto const& spellId : m_SpecSpells[spec.second.id])
                spellsIds += std::to_string(spellId) + "#";

            std::stringstream fmt2;
            fmt2 << specialization.id << ";" << specialization.name << ";" << specialization.spellIcon << ";" << spellsIds;
            elements.push_back(fmt2.str());
        }
    }
    return elements;
}

SpecValue PlayerSpecialization::GetSpecValue(uint32 currentSpec) {

    if (!currentSpec)
        return { -1, 0 };

    switch (currentSpec) {
        case WARRIOR_ARMS: return { 1, 1 };
        case WARRIOR_FURY: return { 2, 1 };
        case WARRIOR_PROTECTION: return { 4, 1 };
        case WARRIOR_HOPLITE: return { 8, 1 };
        case MAGE_ARCANE: return { 1, 2 };
        case MAGE_FIRE: return { 2, 2 };
        case MAGE_FROST: return { 4, 2 };
        case MAGE_SPELLBLADE: return { 8, 1 };
        case DK_BLOOD: return { 1, 1 };
        case DK_FROST: return { 2, 1 };
        case DK_UNHOLY: return { 4, 1 };
        case DK_SOULWEAVER: return { 8, 1 };
        case DRUID_BALANCE: return { 1, 2 };
        case DRUID_FERAL: return { 2, 1 };
        case DRUID_RESTO: return { 4, 2 };
        case DRUID_GUARDIAN: return { 8, 1 };
        case HUNTER_BEAST: return { 1, 1 };
        case HUNTER_MARSKMANSHIP: return { 2, 1 };
        case HUNTER_SURVIVAL: return { 4, 1 };
        case HUNTER_DARK_RANGER: return { 8, 1 };
        case PALADIN_HOLY: return { 1, 2 };
        case PALADIN_PROTECTION: return { 2, 1 };
        case PALADIN_RETRIBUTION: return { 4, 1 };
        case PALADIN_INQUISITOR: return { 8, 2 };
        case ROGUE_ASSASSINATION: return { 1, 1 };
        case ROGUE_COMBAT: return { 2, 1 };
        case ROGUE_SUBTLETY: return { 4, 1 };
        case ROGUE_OUTLAW: return { 8, 1 };
        case SHAMAN_ELEMENTAL: return { 1, 2 };
        case SHAMAN_ENCHANCEMENT: return { 2, 1 };
        case SHAMAN_RESTORATION: return { 4, 2 };
        case SHAMAN_SPIRIT_MASTER: return { 8, 1 };
        case WARLOCK_AFFLICTION: return { 1, 2 };
        case WARLOCK_DEMONOLOGY: return { 2, 2};
        case WARLOCK_DESTRUCTION: return { 4, 2 };
        case WARLOCK_DEMONBOUND: return { 8, 1 };
        case PRIEST_DISCI: return { 1, 2 };
        case PRIEST_HOLY: return { 2, 2 };
        case PRIEST_SHADOW: return { 4, 2 };
        case PRIEST_ABSOLUTION: return { 8, 2 };
    }
    return { -1, 0 };
}

uint32 PlayerSpecialization::GetCurrentSpecId(Player* player)
{
    uint32 specId = 0;
    auto match = m_PlayersSpecialization.find(player->GetGUID().GetCounter());

    if (match != m_PlayersSpecialization.end())
        specId = match->second.specId;

    return specId;
}

uint32 PlayerSpecialization::GetPreferredSpecId(Player* player)
{
    uint32 specId = 0;
    auto match = m_PlayersSpecialization.find(player->GetGUID().GetCounter());

    if (match != m_PlayersSpecialization.end())
        specId = match->second.PreferredSpecId;

    return specId;
}

void PlayerSpecialization::SetPreferredSpecId(Player* player, uint32 specMask)
{
    auto match = m_PlayersSpecialization.find(player->GetGUID().GetCounter());

    if (match != m_PlayersSpecialization.end())
        match->second.PreferredSpecId = specMask;

    CharacterDatabase.Query("UPDATE characters SET preferedSpecId = {} WHERE guid = {}", specMask, player->GetGUID().GetCounter());
}
