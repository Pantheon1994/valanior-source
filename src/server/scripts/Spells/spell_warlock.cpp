/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

 /*
  * Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
  * Ordered alphabetically using scriptname.
  * Scriptnames of files in this file should be prefixed with "spell_warl_".
  */

#include "Pet.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "TemporarySummon.h"

enum WarlockSpells
{
    //THEIRS
    SPELL_WARLOCK_DRAIN_SOUL_R1 = 1120,
    SPELL_WARLOCK_CREATE_SOULSHARD = 43836,
    SPELL_WARLOCK_CURSE_OF_DOOM_EFFECT = 18662,
    SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON = 48018,
    SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT = 48020,
    SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST = 62388,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS = 54435,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER = 54443,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD = 54508,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER = 54509,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP = 54444,
    SPELL_WARLOCK_FEL_SYNERGY_HEAL = 54181,
    SPELL_WARLOCK_GLYPH_OF_DRAIN_SOUL_AURA = 58070,
    SPELL_WARLOCK_GLYPH_OF_DRAIN_SOUL_PROC = 58068,
    SPELL_WARLOCK_GLYPH_OF_SHADOWFLAME = 63311,
    SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE = 56216,
    //SPELL_WARLOCK_HAUNT                             = 48181,
    SPELL_WARLOCK_HAUNT_HEAL = 48210,
    SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R1 = 18692,
    SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R2 = 18693,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1 = 18703,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2 = 18704,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1 = 60955,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2 = 60956,
    SPELL_WARLOCK_LIFE_TAP_ENERGIZE = 31818,
    SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2 = 32553,
    SPELL_WARLOCK_SOULSHATTER = 32835,
    SPELL_WARLOCK_SIPHON_LIFE_HEAL = 63106,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL = 31117,
    SPELL_WARLOCK_IMPROVED_DRAIN_SOUL_R1 = 18213,
    SPELL_WARLOCK_IMPROVED_DRAIN_SOUL_PROC = 18371,
    SPELL_WARLOCK_CURSE_OF_EXHAUSTION = 83026,

    //OURS
    SPELL_FELBOAR_CHARGE = 83005,
    SPELL_WARLOCK_AGONY = 83010,
    SPELL_WARLOCK_CHAOS_BOLT = 59172,
    SPELL_WARLOCK_DARK_PACT = 59092,
    SPELL_WARLOCK_DARK_PACT_DAMAGE = 83011,
    SPELL_WARLOCK_DARK_PACT_SHIELD = 83012,
    SPELL_WARLOCK_HAND_OF_GULDAN_ADDITIONAL_COST = 83219,
    SPELL_WARLOCK_HAUNT = 59164,
    SPELL_WARLOCK_SEED_OF_CORRUPTION = 47836,
    SPELL_WARLOCK_SEED_OF_CORRUPTION_DETONATION = 47834,
    SPELL_WARLOCK_SEED_OF_CORRUPTION_VISUAL = 37826,
    SPELL_WARLOCK_SHADOWBURN = 47827,
    SPELL_WARLOCK_CONFLAGRATE = 17962,
    SPELL_WARLOCK_SOUL_FIRE = 47825,
    SPELL_WARLOCK_BURNING_RUSH_DAMAGE = 83019,
    SPELL_WARLOCK_MALEFIC_RAPTURE_DAMAGE = 83021,
    SPELL_WARLOCK_SOUL_STRIKE = 83039,
    SPELL_WARLOCK_IMMOLATE = 47811,
    SPELL_WARLOCK_SHADOW_BOLT = 47809,
    SPELL_WARLOCK_SHADOW_BOLT_ENERGY = 83080,
    SPELL_WARLOCK_DRAIN_SOUL_ENERGY = 83081,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION = 47843,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_ENERGY = 83082,
    SPELL_WARLOCK_SOUL_STRIKE_ENERGY = 83083,
    SPELL_WARLOCK_CONFLAGRATE_ENERGY = 83084,
    SPELL_WARLOCK_IMMOLATE_ENERGY = 83085,
    SPELL_WARLOCK_INCINERATE = 47838,
    SPELL_WARLOCK_INCINERATE_ENERGY = 83086,
    SPELL_WARLOCK_SHADOWBURN_ENERGY = 83087,
    SPELL_WARLOCK_SOUL_FIRE_ENERGY = 83088,
    SPELL_WARLOCK_IMMOLATION_AURA_ENERGY = 83089,
    SPELL_WARLOCK_IMMOLATION_AURA_INITIAL_ENERGY = 83188,
    PET_SPELL_IMMOLATION_AURA_DAMAGE = 20153,
    SPELL_WARLOCK_SOUL_COLLECTOR = 83094,
    SPELL_WARLOCK_SOUL_COLLECTOR_FRAGMENT = 83095,
    SPELL_WARLOCK_SOUL_COLLECTOR_DEMON_BUFF = 83096,
    SPELL_WARLOCK_SOUL_COLLECTOR_HEAL = 83097,
    SPELL_WARLOCK_SEARING_PAIN_ENERGY = 83100,
    SPELL_WARLOCK_FEL_ARMOR_HEAL = 47894,
    SPELL_WARLOCK_FRAILTY_HEAL = 83104,
    SPELL_WARLOCK_SOUL_BOMB = 83102,
    SPELL_WARLOCK_SOUL_BOMB_DAMAGE = 83105,
    SPELL_WARLOCK_SUMMON_FELGUARD = 30146,
    SPELL_WARLOCK_SUMMON_FELHUNTER = 691,
    SPELL_WARLOCK_SUMMON_IMP = 688,
    SPELL_WARLOCK_SUMMON_SUCCUBUS = 712,
    SPELL_WARLOCK_SUMMON_VOIDWALKER = 697,
    SPELL_WARLOCK_EYE_OF_KILLROG = 126,
    SPELL_WARLOCK_IMMOLATION_AURA = 50589,
    SPELL_WARLOCK_SHADOW_CLEAVE = 50581,
    SPELL_WARLOCK_DEMON_CHARGE = 54785,
    SPELL_WARLOCK_SHROUD_OF_DARKNESS = 83114,
    SPELL_WARLOCK_DEMONIC_ASCENSION = 83110,
    SPELL_WARLOCK_DEMONIC_DEVASTATION_HEAL = 83222,
    SPELL_WARLOCK_DEMONIC_PROTECTION = 83111,
    SPELL_WARLOCK_DEMONIC_PROTECTION_MASTERY_BUFF = 83116,
    SPELL_WARLOCK_FRACTURE_ENERGY = 83107,
    SPELL_WARLOCK_METAMORPHOSIS = 47241,
    SPELL_WARLOCK_DEMONIC_CORE_BUFF = 83029,
    SPELL_WARLOCK_DEMONBOLT = 83028,

    // Talents
    TALENT_WARLOCK_RITUAL_OF_RUIN = 83074,
    TALENT_WARLOCK_RITUAL_OF_RUIN_STACK = 83075,
    TALENT_WARLOCK_RITUAL_OF_RUIN_BUFF = 83076,
    TALENT_WARLOCK_MOLTEN_HAND_BUFF_R1 = 47383,
    TALENT_WARLOCK_MOLTEN_HAND_BUFF_R2 = 71162,
    TALENT_WARLOCK_MOLTEN_HAND_BUFF_R3 = 71165,
    TALENT_WARLOCK_NIGHTFALL_BUFF = 83223,
    TALENT_WARLOCK_DEMON_SPIKES_DAMAGE = 83197,
    TALENT_WARLOCK_FORCED_ASCENSION_COOLDOWN = 83199,
    TALENT_WARLOCK_ARCHDEMON_DAMAGE = 83201,
    TALENT_WARLOCK_ARCHDEMON_MARK = 83202,
    TALENT_WARLOCK_ARCHDEMON_COOLDOWN = 83203,
    TALENT_WARLOCK_MOLTEN_HAND = 47245,
    TALENT_WARLOCK_IMPROVED_FELHUNTER_R1 = 54037,
    TALENT_WARLOCK_IMPROVED_FELHUNTER_R2 = 54038,

    // Masteries  
    MASTERY_WARLOCK_FEL_BLOOD = 1100024,
    MASTERY_WARLOCK_MASTER_DEMONOLOGIST = 1100020,

    SPELL_WARLOCK_GRIMOIRE_OF_SACRIFICE_DAMAGE = 83055,
    SPELL_WARLOCK_GRIMOIRE_FELGUARD = 83009,
    SPELL_WARLOCK_GRIMOIRE_FELGUARD_BUFF = 83031,
    SPELL_WARLOCK_CHARGE_FELGUARD = 25821,

    SPELL_WARLOCK_IMPLOSSION = 83038,
    SPELL_WARLOCK_DEMONBOLT_EMPOREWED = 83041,

    SPELL_WARLOCK_HAVOC_AURA = 83062,
    SPELL_WARLOCK_HAVOC_DAMAGE = 83061,

    SPELL_MINION_STAT_DREAD_STALKER = 75001,
    SPELL_MINION_STAT_WILD_IMP = 75002,
    SPELL_MINION_STAT_DARKGLARE = 75003,
    SPELL_MINION_STAT_VILEFIEND = 75004,
    SPELL_MINION_STAT_DEMONIC_TYRANT = 75005,
    SPELL_MINION_STAT_BOMBER = 74999,

    SPELL_MINION_INCREASE_DREAD_STALKER = 1100009,
    SPELL_MINION_INCREASE_WILD_IMP = 1100010,
    SPELL_MINION_INCREASE_DARKGLARE = 1100011,
    SPELL_MINION_INCREASE_VILEFIEND = 1100012,
    SPELL_MINION_INCREASE_DEMONIC_TYRANT = 1100013,
    SPELL_MINION_INCREASE_BOMBER = 1100014,

    // Runes
    RUNE_WARLOCK_SEIZED_VITALITY_DEBUFF = 800484,
    RUNE_WARLOCK_DREAD_TOUCH_BUFF = 800584,
    RUNE_WARLOCK_STOLEN_POWER_BUFF = 800825,
    RUNE_WARLOCK_DEMONIC_SERVITUDE = 800856,
    RUNE_WARLOCK_GULDANS_AMBITION_LISTENER = 800876,
    RUNE_WARLOCK_GULDANS_AMBITION_BUFF = 800877,
    RUNE_WARLOCK_CALCIFIED_SHIELD_BUFF = 801264,
    RUNE_WARLOCK_REVEL_IN_PAIN_SHIELD = 801302,

    // Sets
    T1_WARLOCK_AFFLI_4PC_BUFF = 98002,
    T1_WARLOCK_AFFLI_4PC_LISTENER = 98003,
    T1_WARLOCK_DEMONO_2PC = 98100,
    T1_WARLOCK_DEMONO_4PC = 98101,
    T1_WARLOCK_DEMONO_4PC_PET_BUFF = 98103,
    T1_WARLOCK_DEMONBOUND_4PC = 98302,
    T1_WARLOCK_DEMONBOUND_4PC_DAMAGE = 98303,
};

enum WarlockPets
{
    // Pet
    PET_WARLOCK_FELGUARD = 17252,
    PET_WARLOCK_FELHUNTER = 417,
    PET_WARLOCK_IMP = 416,
    PET_WARLOCK_SUCCUBUS = 1863,
    PET_WARLOCK_VOIDWALKER = 1860,

    // Guardians
    GUARDIAN_WARLOCK_BILESCOURGE = 600607,
    GUARDIAN_WARLOCK_DARKGLARE = 600604,
    GUARDIAN_WARLOCK_DEMONIC_TYRANT = 600603,
    GUARDIAN_WARLOCK_DOOMGUARD = 600616,
    GUARDIAN_WARLOCK_DREADSTALKER = 600600,
    GUARDIAN_WARLOCK_FELGUARD_GRIMOIRE = 600605,
    GUARDIAN_WARLOCK_INFERNAL = 89,
    GUARDIAN_WARLOCK_PORTAL_SUMMON = 600606,
    GUARDIAN_WARLOCK_VILEFIEND = 600602,
    GUARDIAN_WARLOCK_WILD_IMP = 600601,

    // Runes
    RUNE_GUARDIAN_WARLOCK_INQUISITORS_EYE = 800000,
    RUNE_GUARDIAN_WARLOCK_PIT_LORD = 800001,
};

enum WarlockScalingSpells
{
    // Pets
    FELGUARD_SCALING_STAMINA_AP_SP = 83500,
    FELHUNTER_SCALING_STAMINA_AP_SP = 83503,
    IMP_SCALING_STAMINA_AP_SP = 83506,
    SUCCUBUS_SCALING_STAMINA_AP_SP = 83509,
    VOIDWAKLER_SCALING_STAMINA_AP_SP = 83512,

    FELGUARD_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83501,
    FELHUNTER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83504,
    IMP_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83507,
    SUCCUBUS_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83510,
    VOIDWAKLER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83513,

    FELGUARD_SCALING_HASTE = 83502,
    FELHUNTER_SCALING_HASTE = 83505,
    IMP_SCALING_HASTE = 83508,
    SUCCUBUS_SCALING_HASTE = 83511,
    VOIDWAKLER_SCALING_HASTE = 83514,

    // Guardians
    DARKGLARE_SCALING_STAMINA_AP_SP = 83515,
    DEMONIC_TYRANT_SCALING_STAMINA_AP_SP = 83518,
    DOOMGUARD_SCALING_STAMINA_AP_SP = 83521,
    DREADSTALKER_SCALING_STAMINA_AP_SP = 83524,
    BILESCOURGE_SCALING_STAMINA_AP_SP = 83527,
    INFERNAL_SCALING_STAMINA_AP_SP = 83530,
    VILEFIEND_SCALING_STAMINA_AP_SP = 83533,
    WILD_IMP_SCALING_STAMINA_AP_SP = 83536,

    DARKGLARE_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83516,
    DEMONIC_TYRANT_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83519,
    DOOMGUARD_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83522,
    DREADSTALKER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83525,
    BILESCOURGE_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83528,
    INFERNAL_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83531,
    VILEFIEND_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83534,
    WILD_IMP_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83537,

    DARKGLARE_SCALING_HASTE = 83517,
    DEMONIC_TYRANT_SCALING_HASTE = 83520,
    DOOMGUARD_SCALING_HASTE = 83523,
    DREADSTALKER_SCALING_HASTE = 83526,
    BILESCOURGE_SCALING_HASTE = 83529,
    INFERNAL_SCALING_HASTE = 83532,
    VILEFIEND_SCALING_HASTE = 83535,
    WILD_IMP_SCALING_HASTE = 83538,

    // Runes
    PIT_LORD_SCALING_STAMINA_AP_SP = 83582,
    PIT_LORD_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT = 83583,
    PIT_LORD_SCALING_HASTE = 83584,
};

enum WarlockSpellIcons
{
    WARLOCK_ICON_ID_IMPROVED_LIFE_TAP = 208,
    WARLOCK_ICON_ID_MANA_FEED = 1982
};

class spell_warl_eye_of_kilrogg : public AuraScript
{
    PrepareAuraScript(spell_warl_eye_of_kilrogg);

    void HandleAuraApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        PreventDefaultAction();
        if (Player* player = GetTarget()->ToPlayer())
        {
            player->UnsummonPetTemporaryIfAny();

            // Glyph of Kilrogg
            if (player->HasAura(58081))
                if (Unit* charm = player->GetCharm())
                {
                    charm->SetSpeed(MOVE_RUN, 2.14f, true);
                    if (charm->GetMapId() == 530 || charm->GetMapId() == 571)
                    {
                        charm->SetCanFly(true);
                        charm->SetSpeed(MOVE_FLIGHT, 2.14f, true);
                        charm->SendMovementFlagUpdate();
                    }
                }
        }
    }

    void HandleAuraRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Player* player = GetTarget()->ToPlayer())
        {
            if (Unit* charm = player->GetCharm())
                charm->ToTempSummon()->UnSummon();

            player->ResummonPetTemporaryUnSummonedIfAny();
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_eye_of_kilrogg::HandleAuraApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_warl_eye_of_kilrogg::HandleAuraRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_shadowflame : public SpellScript
{
    PrepareSpellScript(spell_warl_shadowflame);

    void HandleSchoolDMG(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, (GetSpellInfo()->Id == 47897 ? 47960 : 61291), true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_shadowflame::HandleSchoolDMG, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warl_seduction : public AuraScript
{
    PrepareAuraScript(spell_warl_seduction);

    void HandleAuraApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* owner = caster->GetOwner())
                if (owner->GetAuraEffectDummy(56250))
                {
                    Unit* target = GetTarget();
                    target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, ObjectGuid::Empty, target->GetAura(32409)); // SW:D shall not be removed.
                    target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                    target->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_seduction::HandleAuraApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_improved_demonic_tactics : public AuraScript
{
    PrepareAuraScript(spell_warl_improved_demonic_tactics);

    bool Load() override
    {
        return GetUnitOwner()->GetTypeId() == TYPEID_PLAYER;
    }

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = 10 * IN_MILLISECONDS;
    }

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool&  /*canBeRecalculated*/)
    {
        /*if (aurEff->GetEffIndex() == EFFECT_0)*/
        amount = CalculatePct<int32, float>(GetUnitOwner()->ToPlayer()->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + static_cast<uint8>(SPELL_SCHOOL_SHADOW)), GetSpellInfo()->Effects[EFFECT_0].CalcValue());
        /*else
            amount = CalculatePct<int32, float>(GetUnitOwner()->ToPlayer()->GetFloatValue(PLAYER_CRIT_PERCENTAGE), GetSpellInfo()->Effects[EFFECT_0].CalcValue());*/
    }

    void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
    {
        //if (!spellMod)
        //{
        //    spellMod = new SpellModifier(aurEff->GetBase());
        //    spellMod->op = SpellModOp(aurEff->GetMiscValue());
        //    spellMod->type = SPELLMOD_FLAT;
        //    spellMod->spellId = GetId();
        //    spellMod->mask = flag96(0x0, 0x2000, 0x0); // Pet Passive
        //}

        spellMod->value = aurEff->GetAmount();
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        GetAura()->GetEffect(aurEff->GetEffIndex())->RecalculateAmount();
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_warl_improved_demonic_tactics::CalcPeriodic, EFFECT_ALL, SPELL_AURA_ADD_FLAT_MODIFIER);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_improved_demonic_tactics::CalculateAmount, EFFECT_ALL, SPELL_AURA_ADD_FLAT_MODIFIER);
        DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_warl_improved_demonic_tactics::HandleEffectCalcSpellMod, EFFECT_ALL, SPELL_AURA_ADD_FLAT_MODIFIER);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_improved_demonic_tactics::HandlePeriodic, EFFECT_ALL, SPELL_AURA_ADD_FLAT_MODIFIER);
    }
};

class spell_warl_ritual_of_summoning : public SpellScript
{
    PrepareSpellScript(spell_warl_ritual_of_summoning);

    SpellCastResult CheckCast()
    {
        if (GetCaster()->GetTypeId() == TYPEID_PLAYER)
            if (GetCaster()->ToPlayer()->InBattleground())
                return SPELL_FAILED_NOT_IN_BATTLEGROUND;
        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warl_ritual_of_summoning::CheckCast);
    }
};

class spell_warl_demonic_aegis : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_aegis);

    void HandleAuraApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // Remove Fel Armor and Demon Armor
        GetTarget()->RemoveAurasWithFamily(SPELLFAMILY_WARLOCK, 0, 0x20000020, 0, ObjectGuid::Empty);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_demonic_aegis::HandleAuraApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_demonic_knowledge : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_knowledge);

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
            amount = CalculatePct(caster->GetStat(STAT_STAMINA) + caster->GetStat(STAT_INTELLECT), aurEff->GetBaseAmount());
    }

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = 5 * IN_MILLISECONDS;
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        GetEffect(aurEff->GetEffIndex())->RecalculateAmount();
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_demonic_knowledge::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_DAMAGE_DONE);
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_warl_demonic_knowledge::CalcPeriodic, EFFECT_0, SPELL_AURA_MOD_DAMAGE_DONE);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_knowledge::HandlePeriodic, EFFECT_0, SPELL_AURA_MOD_DAMAGE_DONE);
    }
};

//class spell_warl_all_minion_scaling : public AuraScript
//{
//    PrepareAuraScript(spell_warl_all_minion_scaling);
//
//    void CalculateAPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
//    {
//        if (Player* owner = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself())
//        {
//            int32 fire = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE);
//            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
//            int32 maximum = (fire > shadow) ? fire : shadow;
//            amount = CalculatePct(std::max<int32>(0, maximum), 57);
//        }
//    }
//
//    void CalculateSPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
//    {
//        if (Player* owner = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself())
//        {
//            int32 fire = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE);
//            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
//            int32 maximum = (fire > shadow) ? fire : shadow;
//            amount = maximum;
//        }
//    }
//
//    void CalculateDamageAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
//    {
//        if (Player* owner = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself())
//        {
//            int32 newAmount = 0;
//
//            if (m_scriptSpellId == SPELL_MINION_STAT_DREAD_STALKER)
//                newAmount = owner->GetAura(SPELL_MINION_INCREASE_DREAD_STALKER)->GetEffect(EFFECT_0)->GetAmount();
//            if (m_scriptSpellId == SPELL_MINION_STAT_WILD_IMP)
//                newAmount = owner->GetAura(SPELL_MINION_INCREASE_WILD_IMP)->GetEffect(EFFECT_0)->GetAmount();
//            if (m_scriptSpellId == SPELL_MINION_STAT_DARKGLARE)
//                newAmount = owner->GetAura(SPELL_MINION_INCREASE_DARKGLARE)->GetEffect(EFFECT_0)->GetAmount();
//            if (m_scriptSpellId == SPELL_MINION_STAT_VILEFIEND)
//                newAmount = owner->GetAura(SPELL_MINION_INCREASE_VILEFIEND)->GetEffect(EFFECT_0)->GetAmount();
//            if (m_scriptSpellId == SPELL_MINION_STAT_DEMONIC_TYRANT)
//                newAmount = owner->GetAura(SPELL_MINION_INCREASE_DEMONIC_TYRANT)->GetEffect(EFFECT_0)->GetAmount();
//            if (m_scriptSpellId == SPELL_MINION_STAT_BOMBER)
//                newAmount = owner->GetAura(SPELL_MINION_INCREASE_BOMBER)->GetEffect(EFFECT_0)->GetAmount();
//
//            if (newAmount > 0) {
//                amount = newAmount;
//            }
//        }
//    }
//
//
//    void Register() override
//    {
//        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_all_minion_scaling::CalculateDamageAmount, EFFECT_2, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
//        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_all_minion_scaling::CalculateAPAmount, EFFECT_1, SPELL_AURA_MOD_ATTACK_POWER);
//        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_all_minion_scaling::CalculateSPAmount, EFFECT_0, SPELL_AURA_MOD_DAMAGE_DONE);
//    }
//};

class spell_warl_generic_scaling : public AuraScript
{
    struct PetStats {
        float stamina;
        float sp_to_ap;
        float sp_to_sp;
    };

    PrepareAuraScript(spell_warl_generic_scaling);

    void CalculateResistanceAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float scaling = GetArmorScaling(m_scriptSpellId);
            amount = CalculatePct(std::max<int32>(0, owner->GetResistance(SPELL_SCHOOL_MASK_NORMAL)), scaling);
        }
    }

    void CalculateMeleeCriticalChance(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            int32 critChanceFire = owner->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_FIRE);
            int32 critChanceShadow = owner->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_SHADOW);
            int32 maximum = (critChanceFire > critChanceShadow) ? critChanceFire : critChanceShadow;
            amount = CalculatePct(std::max<int32>(0, maximum), 100.f);
        }
    }

    void CalculateSpellCriticalChance(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            int32 critChanceFire = owner->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_FIRE);
            int32 critChanceShadow = owner->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_SHADOW);
            int32 maximum = (critChanceFire > critChanceShadow) ? critChanceFire : critChanceShadow;
            amount = CalculatePct(std::max<int32>(0, maximum), 100.f);
        }
    }

    void CalculateHasteAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float speed = owner->GetFloatValue(UNIT_MOD_CAST_SPEED) * 10;
            amount = std::max<int32>(0, speed);
        }
    }

    void CalculateStatAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            PetStats stat = GetSpApStamina(m_scriptSpellId);
            amount = CalculatePct(std::max<int32>(0, owner->GetStat(STAT_STAMINA)), stat.stamina);
        }
    }

    void CalculateAPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            PetStats stat = GetSpApStamina(m_scriptSpellId);
            int32 fire = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE);
            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
            int32 maximum = (fire > shadow) ? fire : shadow;
            amount = CalculatePct(std::max<int32>(0, maximum), stat.sp_to_ap);
        }
    }

    void CalculateSPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            PetStats stat = GetSpApStamina(m_scriptSpellId);
            int32 fire = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE);
            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
            int32 maximum = (fire > shadow) ? fire : shadow;
            amount = CalculatePct(std::max<int32>(0, maximum), stat.sp_to_sp);

            // xinef: Update appropriate player field
            if (owner->GetTypeId() == TYPEID_PLAYER)
                owner->SetUInt32Value(PLAYER_PET_SPELL_POWER, (uint32)amount);
        }
    }

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = 2 * IN_MILLISECONDS;
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (aurEff->GetAuraType() == SPELL_AURA_MOD_STAT && (aurEff->GetMiscValue() == STAT_STAMINA))
        {
            int32 currentAmount = aurEff->GetAmount();
            int32 newAmount = GetEffect(aurEff->GetEffIndex())->CalculateAmount(GetCaster());
            if (newAmount != currentAmount)
            {
                if (aurEff->GetMiscValue() == STAT_STAMINA)
                {
                    uint32 actStat = GetUnitOwner()->GetHealth();
                    GetEffect(aurEff->GetEffIndex())->ChangeAmount(newAmount, false);
                    GetUnitOwner()->SetHealth(std::min<uint32>(GetUnitOwner()->GetMaxHealth(), actStat));
                }
                else
                {
                    uint32 actStat = GetUnitOwner()->GetPower(POWER_MANA);
                    GetEffect(aurEff->GetEffIndex())->ChangeAmount(newAmount, false);
                    GetUnitOwner()->SetPower(POWER_MANA, std::min<uint32>(GetUnitOwner()->GetMaxPower(POWER_MANA), actStat));
                }
            }
        }
        else
            GetEffect(aurEff->GetEffIndex())->RecalculateAmount();
    }

    void Register() override
    {
        if (
            m_scriptSpellId == FELGUARD_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == IMP_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == FELHUNTER_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == SUCCUBUS_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == VOIDWAKLER_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == DARKGLARE_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == DEMONIC_TYRANT_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == DOOMGUARD_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == DREADSTALKER_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == BILESCOURGE_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == INFERNAL_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == VILEFIEND_SCALING_STAMINA_AP_SP
            || m_scriptSpellId == WILD_IMP_SCALING_STAMINA_AP_SP)
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_generic_scaling::CalculateStatAmount, EFFECT_0, SPELL_AURA_MOD_STAT);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_generic_scaling::CalculateAPAmount, EFFECT_1, SPELL_AURA_MOD_ATTACK_POWER);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_generic_scaling::CalculateSPAmount, EFFECT_2, SPELL_AURA_MOD_DAMAGE_DONE);
        }

        if (
            m_scriptSpellId == FELGUARD_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == IMP_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == FELHUNTER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == SUCCUBUS_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == VOIDWAKLER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == DARKGLARE_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == DEMONIC_TYRANT_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == DOOMGUARD_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == DREADSTALKER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == BILESCOURGE_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == INFERNAL_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == VILEFIEND_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT
            || m_scriptSpellId == WILD_IMP_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT)
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_generic_scaling::CalculateResistanceAmount, EFFECT_0, SPELL_AURA_MOD_RESISTANCE);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_generic_scaling::CalculateMeleeCriticalChance, EFFECT_1, SPELL_AURA_MOD_WEAPON_CRIT_PERCENT);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_generic_scaling::CalculateSpellCriticalChance, EFFECT_2, SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
        }

        if (
            m_scriptSpellId == FELGUARD_SCALING_HASTE
            || m_scriptSpellId == IMP_SCALING_HASTE
            || m_scriptSpellId == FELHUNTER_SCALING_HASTE
            || m_scriptSpellId == SUCCUBUS_SCALING_HASTE
            || m_scriptSpellId == VOIDWAKLER_SCALING_HASTE
            || m_scriptSpellId == DARKGLARE_SCALING_HASTE
            || m_scriptSpellId == DEMONIC_TYRANT_SCALING_HASTE
            || m_scriptSpellId == DOOMGUARD_SCALING_HASTE
            || m_scriptSpellId == DREADSTALKER_SCALING_HASTE
            || m_scriptSpellId == BILESCOURGE_SCALING_HASTE
            || m_scriptSpellId == INFERNAL_SCALING_HASTE
            || m_scriptSpellId == VILEFIEND_SCALING_HASTE
            || m_scriptSpellId == WILD_IMP_SCALING_HASTE)
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_generic_scaling::CalculateHasteAmount, EFFECT_0, SPELL_AURA_MOD_MELEE_RANGED_HASTE);
        }

        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_warl_generic_scaling::CalcPeriodic, EFFECT_ALL, SPELL_AURA_ANY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_generic_scaling::HandlePeriodic, EFFECT_ALL, SPELL_AURA_ANY);
    }

private:
    std::map<uint32, PetStats> spellsStaminaApSp;
    std::map<uint32, float> spellsArmor;


    PetStats GetSpApStamina(uint32 spellId) {

        spellsStaminaApSp[FELGUARD_SCALING_STAMINA_AP_SP] = { 85, 87, 45 };
        spellsStaminaApSp[FELHUNTER_SCALING_STAMINA_AP_SP] = { 75, 65, 65 };
        spellsStaminaApSp[IMP_SCALING_STAMINA_AP_SP] = { 75, 20, 75 };
        spellsStaminaApSp[SUCCUBUS_SCALING_STAMINA_AP_SP] = { 75, 35, 75 };
        spellsStaminaApSp[VOIDWAKLER_SCALING_STAMINA_AP_SP] = { 100, 35, 55 };
        spellsStaminaApSp[DARKGLARE_SCALING_STAMINA_AP_SP] = { 60, 35, 65 };
        spellsStaminaApSp[DEMONIC_TYRANT_SCALING_STAMINA_AP_SP] = { 60, 35, 75 };
        spellsStaminaApSp[DOOMGUARD_SCALING_STAMINA_AP_SP] = { 85, 45, 87 };
        spellsStaminaApSp[DREADSTALKER_SCALING_STAMINA_AP_SP] = { 50, 45, 25 };
        spellsStaminaApSp[BILESCOURGE_SCALING_STAMINA_AP_SP] = { 60, 35, 65 };
        spellsStaminaApSp[INFERNAL_SCALING_STAMINA_AP_SP] = { 85, 35, 65 };
        spellsStaminaApSp[VILEFIEND_SCALING_STAMINA_AP_SP] = { 60, 65, 35 };
        spellsStaminaApSp[WILD_IMP_SCALING_STAMINA_AP_SP] = { 40, 20, 60 };

        return spellsStaminaApSp[spellId];
    }

    float GetArmorScaling(uint32 spellId) {

        spellsArmor[FELGUARD_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 80.f;
        spellsArmor[FELHUNTER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 60.f;
        spellsArmor[IMP_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 60.f;
        spellsArmor[SUCCUBUS_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 75.f;
        spellsArmor[VOIDWAKLER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 100.f;
        spellsArmor[DARKGLARE_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 60.f;
        spellsArmor[DEMONIC_TYRANT_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 60.f;
        spellsArmor[DOOMGUARD_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 80.f;
        spellsArmor[DREADSTALKER_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 60.f;
        spellsArmor[BILESCOURGE_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 60.f;
        spellsArmor[INFERNAL_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 75.f;
        spellsArmor[VILEFIEND_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 60.f;
        spellsArmor[WILD_IMP_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT] = 60.f;

        return spellsArmor[spellId];
    }
};

class spell_warl_infernal_scaling : public AuraScript
{
    PrepareAuraScript(spell_warl_infernal_scaling);

    Aura* GetPrimordialInfernalAura(Unit* caster)
    {
        for (size_t i = 801136; i < 801142; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetInfernalBrandAura(Unit* caster)
    {
        for (size_t i = 801148; i < 801154; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void CalculateResistanceAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        // xinef: pet inherits 40% of resistance from owner and 35% of armor
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            SpellSchoolMask schoolMask = SpellSchoolMask(aurEff->GetSpellInfo()->Effects[aurEff->GetEffIndex()].MiscValue);
            int32 modifier = schoolMask == SPELL_SCHOOL_MASK_NORMAL ? 35 : 40;
            amount = CalculatePct(std::max<int32>(0, owner->GetResistance(schoolMask)), modifier);
        }
    }

    void CalculateStatAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        // xinef: by default warlock pet inherits 75% of stamina and 30% of intellect
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            Stats stat = Stats(aurEff->GetSpellInfo()->Effects[aurEff->GetEffIndex()].MiscValue);
            int32 modifier = stat == STAT_STAMINA ? 75 : 30;
            amount = CalculatePct(std::max<int32>(0, owner->GetStat(stat)), modifier);
        }
    }

    void CalculateAPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // xinef: by default warlock pet inherits 57% of max(SP FIRE, SP SHADOW) as AP
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            int32 fire = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE);
            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
            int32 maximum = (fire > shadow) ? fire : shadow;
            amount = CalculatePct(std::max<int32>(0, maximum), 57);
        }
    }

    void CalculateSPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // xinef: by default warlock pet inherits 15% of max(SP FIRE, SP SHADOW) as SP
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            int32 fire = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE);
            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
            int32 maximum = (fire > shadow) ? fire : shadow;
            amount = CalculatePct(std::max<int32>(0, maximum), 15);

            // xinef: Update appropriate player field
            if (owner->GetTypeId() == TYPEID_PLAYER)
                owner->SetUInt32Value(PLAYER_PET_SPELL_POWER, (uint32)amount);
        }
    }

    void HandleEffectApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* infernal = GetUnitOwner();

        if (!infernal || infernal->isDead())
            return;

        infernal->ApplySpellImmune(0, IMMUNITY_STATE, aurEff->GetAuraType(), true, SPELL_BLOCK_TYPE_POSITIVE);
        if (aurEff->GetAuraType() == SPELL_AURA_MOD_ATTACK_POWER)
            infernal->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_ATTACK_POWER_PCT, true, SPELL_BLOCK_TYPE_POSITIVE);
        else if (aurEff->GetAuraType() == SPELL_AURA_MOD_STAT)
            infernal->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE, true, SPELL_BLOCK_TYPE_POSITIVE);

        //Unit* caster = infernal->GetOwner();

        //if (!caster)
        //    return;

        //// Add damage increase from Primordial Infernal rune.
        //if (Aura* runeAura = GetPrimordialInfernalAura(caster))
        //{
        //    int32 procSpell = runeAura->GetEffect(EFFECT_2)->GetAmount();

        //    caster->CastSpell(infernal, procSpell, TRIGGERED_FULL_MASK);
        //}

        //// Add buff from Infernal Brand rune.
        //if (Aura* runeAura = GetInfernalBrandAura(caster))
        //{
        //    int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

        //    caster->CastSpell(infernal, procSpell, TRIGGERED_FULL_MASK);
        //}
    }

    void Register() override
    {
        if (m_scriptSpellId != 36186)
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_infernal_scaling::CalculateResistanceAmount, EFFECT_ALL, SPELL_AURA_MOD_RESISTANCE);

        if (m_scriptSpellId == 36186 || m_scriptSpellId == 36188)
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_infernal_scaling::CalculateStatAmount, EFFECT_ALL, SPELL_AURA_MOD_STAT);

        if (m_scriptSpellId == 36186)
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_infernal_scaling::CalculateAPAmount, EFFECT_ALL, SPELL_AURA_MOD_ATTACK_POWER);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_infernal_scaling::CalculateSPAmount, EFFECT_ALL, SPELL_AURA_MOD_DAMAGE_DONE);
        }

        OnEffectApply += AuraEffectApplyFn(spell_warl_infernal_scaling::HandleEffectApply, EFFECT_ALL, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

// -710 - Banish
class spell_warl_banish : public SpellScript
{
    PrepareSpellScript(spell_warl_banish);

    void HandleBanish(SpellMissInfo missInfo)
    {
        if (missInfo != SPELL_MISS_IMMUNE)
        {
            return;
        }

        if (Unit* target = GetHitUnit())
        {
            // Casting Banish on a banished target will remove applied aura
            if (Aura* banishAura = target->GetAura(GetSpellInfo()->Id, GetCaster()->GetGUID()))
            {
                banishAura->Remove();
            }
        }
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_warl_banish::HandleBanish);
    }
};

// 47193 - Demonic Empowerment
class spell_warl_demonic_empowerment : public SpellScript
{
    PrepareSpellScript(spell_warl_demonic_empowerment);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS,
                SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER,
                SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD,
                SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER,
                SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP
            });
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Creature* targetCreature = GetHitCreature())
        {
            if (targetCreature->IsPet())
            {
                CreatureTemplate const* ci = sObjectMgr->GetCreatureTemplate(targetCreature->GetEntry());
                switch (ci->family)
                {
                case CREATURE_FAMILY_SUCCUBUS:
                    targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS, true);
                    break;
                case CREATURE_FAMILY_VOIDWALKER:
                {
                    SpellInfo const* spellInfo = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER);
                    int32 hp = int32(targetCreature->CountPctFromMaxHealth(GetCaster()->CalculateSpellDamage(targetCreature, spellInfo, 0)));
                    targetCreature->CastCustomSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER, &hp, nullptr, nullptr, true);
                    //unitTarget->CastSpell(unitTarget, 54441, true);
                    break;
                }
                case CREATURE_FAMILY_FELGUARD:
                    targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD, true);
                    break;
                case CREATURE_FAMILY_FELHUNTER:
                    targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER, true);
                    break;
                case CREATURE_FAMILY_IMP:
                    targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP, true);
                    break;
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_demonic_empowerment::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 6201 - Create Healthstone (and ranks)
class spell_warl_create_healthstone : public SpellScript
{
    PrepareSpellScript(spell_warl_create_healthstone);

    static uint32 const iTypes[8][3];

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R1, SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R2 });
    }

    SpellCastResult CheckCast()
    {
        if (Player* caster = GetCaster()->ToPlayer())
        {
            uint8 spellRank = GetSpellInfo()->GetRank();
            ItemPosCountVec dest;
            InventoryResult msg = caster->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, iTypes[spellRank - 1][0], 1, nullptr);
            if (msg != EQUIP_ERR_OK)
                return SPELL_FAILED_TOO_MANY_OF_ITEM;
        }
        return SPELL_CAST_OK;
    }

    void HandleScriptEffect(SpellEffIndex effIndex)
    {
        if (Unit* unitTarget = GetHitUnit())
        {
            uint32 rank = 0;
            // Improved Healthstone
            if (AuraEffect const* aurEff = unitTarget->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, 284, 0))
            {
                switch (aurEff->GetId())
                {
                case SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R1:
                    rank = 1;
                    break;
                case SPELL_WARLOCK_IMPROVED_HEALTHSTONE_R2:
                    rank = 2;
                    break;
                default:
                    LOG_ERROR("spells", "Unknown rank of Improved Healthstone id: {}", aurEff->GetId());
                    break;
                }
            }
            uint8 spellRank = GetSpellInfo()->GetRank();
            if (spellRank > 0 && spellRank <= 8)
                CreateItem(effIndex, iTypes[spellRank - 1][rank]);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_create_healthstone::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        OnCheckCast += SpellCheckCastFn(spell_warl_create_healthstone::CheckCast);
    }
};

uint32 const spell_warl_create_healthstone::spell_warl_create_healthstone::iTypes[8][3] =
{
    { 5512, 19004, 19005},              // Minor Healthstone
    { 5511, 19006, 19007},              // Lesser Healthstone
    { 5509, 19008, 19009},              // Healthstone
    { 5510, 19010, 19011},              // Greater Healthstone
    { 9421, 19012, 19013},              // Major Healthstone
    {22103, 22104, 22105},              // Master Healthstone
    {36889, 36890, 36891},              // Demonic Healthstone
    {36892, 36893, 36894}               // Fel Healthstone
};

// 47422 - Everlasting Affliction
class spell_warl_everlasting_affliction : public SpellScript
{
    PrepareSpellScript(spell_warl_everlasting_affliction);

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* unitTarget = GetHitUnit())
            // Refresh corruption on target
            if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_WARLOCK, 0x2, 0, 0, GetCaster()->GetGUID()))
            {
                aur->GetBase()->RefreshTimersWithMods();
                aur->ChangeAmount(aur->CalculateAmount(aur->GetCaster()), false);
            }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_everlasting_affliction::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 18541 - Ritual of Doom Effect
class spell_warl_ritual_of_doom_effect : public SpellScript
{
    PrepareSpellScript(spell_warl_ritual_of_doom_effect);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        caster->CastSpell(caster, GetEffectValue(), true);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_warl_ritual_of_doom_effect::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// -27285 - Seed of Corruption
class spell_warl_seed_of_corruption : public SpellScript
{
    PrepareSpellScript(spell_warl_seed_of_corruption);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([&](WorldObject const* target)
            {
                if (Unit const* unitTarget = target->ToUnit())
                {
                    if (WorldLocation const* dest = GetExplTargetDest())
                    {
                        if (!unitTarget->IsWithinLOS(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ()))
                        {
                            return true;
                        }
                    }
                }

        return false;
            });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_seed_of_corruption::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 29858 - Soulshatter
class spell_warl_soulshatter : public SpellScript
{
    PrepareSpellScript(spell_warl_soulshatter);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_SOULSHATTER });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (Unit* target = GetHitUnit())
        {
            if (target->CanHaveThreatList() && target->GetThreatMgr().GetThreat(caster) > 0.0f)
                caster->CastSpell(target, SPELL_WARLOCK_SOULSHATTER, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_soulshatter::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 63108 - Siphon Life
class spell_warl_siphon_life : public AuraScript
{
    PrepareAuraScript(spell_warl_siphon_life);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_SIPHON_LIFE_HEAL, SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage())
        {
            return false;
        }

        return GetTarget()->IsAlive();
    }

    void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        int32 amount = CalculatePct(static_cast<int32>(eventInfo.GetDamageInfo()->GetDamage()), aurEff->GetAmount());
        // Glyph of Siphon Life
        if (AuraEffect const* glyph = GetTarget()->GetAuraEffect(SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE, EFFECT_0))
            AddPct(amount, glyph->GetAmount());

        GetTarget()->CastCustomSpell(SPELL_WARLOCK_SIPHON_LIFE_HEAL, SPELLVALUE_BASE_POINT0, amount, GetTarget(), true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_siphon_life::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_siphon_life::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_havoc : public AuraScript
{
    PrepareAuraScript(spell_warl_havoc);

    Aura* GetCryHavocAura(Unit* caster)
    {
        for (size_t i = 801052; i < 801058; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetRollingHavocAura(Unit* caster)
    {
        for (size_t i = 801064; i < 801070; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();

        return (spellInfo && damageInfo && damageInfo->GetDamage() && spellInfo->Id != SPELL_WARLOCK_HAVOC_DAMAGE);
    }

    Unit* FindTargetHavoc()
    {
        Unit* havocTarget = nullptr;
        auto const& threatList = GetCaster()->GetThreatMgr().GetThreatList();
        auto threatListCopy = threatList;

        if (threatListCopy.empty()) return nullptr;

        for (auto const& treathTarget : threatListCopy)
        {
            if (Unit* target = ObjectAccessor::GetUnit(*GetCaster(), treathTarget->getUnitGuid())) {
                if (target->HasAura(SPELL_WARLOCK_HAVOC_AURA))
                    havocTarget = target;
            }
        }

        return havocTarget;
    }

    void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {

        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo)
            return;

        int32 damagePourcentage = aurEff->GetAmount();

        uint32 spellId = eventInfo.GetSpellInfo()->Id;

        int32 totalDamage = CalculatePct(damageInfo->GetDamage(), damagePourcentage);
        Unit* havocTarget = FindTargetHavoc();

        if (!havocTarget || havocTarget->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        if (havocTarget == target)
            return;

        caster->CastCustomSpell(SPELL_WARLOCK_HAVOC_DAMAGE, SPELLVALUE_BASE_POINT0, totalDamage, havocTarget, TRIGGERED_FULL_MASK);

        // Deal aoe damage around target hit by Chaos Bolt through Havoc
        if (eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_CHAOS_BOLT)
            if (Aura* runeAura = GetCryHavocAura(caster))
            {
                int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
                caster->CastSpell(havocTarget, procSpell, TRIGGERED_FULL_MASK);
            }

        // increase damage when you hit a Havoc target.
        if (Aura* runeAura = GetRollingHavocAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
            caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_havoc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_havoc::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_vampirism : public AuraScript
{
    PrepareAuraScript(spell_vampirism);

    uint32 healPct;
    uint32 spellId;

    bool Load() override
    {
        healPct = GetAura()->GetEffect(EFFECT_0)->GetAmount();
        spellId = GetSpellInfo()->Effects[EFFECT_0].TriggerSpell;
        return true;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();
        if (!damageInfo || !damageInfo->GetDamage())
        {
            return false;
        }
        return GetTarget()->IsAlive();
    }

    void TriggerHeal(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (DamageInfo* damageInfo = eventInfo.GetDamageInfo()) {
            int32 amount = CalculatePct(static_cast<int32>(eventInfo.GetDamageInfo()->GetDamage()), healPct);
            int32 value = std::max(1, amount);
            GetCaster()->CastCustomSpell(spellId, SPELLVALUE_BASE_POINT0, value, GetCaster(), true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_vampirism::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_vampirism::TriggerHeal, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

// -1454 - Life Tap
#define LIFE_TAP_COEFFICIENT 0.9F
class spell_warl_life_tap : public SpellScript
{
    PrepareSpellScript(spell_warl_life_tap);

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_LIFE_TAP_ENERGIZE, SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2 });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        if (Unit* target = GetHitUnit())
        {
            int32 damage = GetEffectValue() + LIFE_TAP_COEFFICIENT;
            int32 damage2Mana = GetEffectValue();
            int32 mana = int32(damage2Mana + (caster->GetInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + static_cast<uint8>(SPELL_SCHOOL_SHADOW)) * 0.5f));

            // Shouldn't Appear in Combat Log
            target->ModifyHealth(-damage);

            // Improved Life Tap mod
            if (AuraEffect const* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, WARLOCK_ICON_ID_IMPROVED_LIFE_TAP, 0))
                AddPct(mana, aurEff->GetAmount());

            caster->CastCustomSpell(target, SPELL_WARLOCK_LIFE_TAP_ENERGIZE, &mana, nullptr, nullptr, false);

            // Mana Feed
            int32 manaFeedVal = 0;
            if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, WARLOCK_ICON_ID_MANA_FEED, 0))
                manaFeedVal = aurEff->GetAmount();

            if (manaFeedVal > 0)
            {
                ApplyPct(manaFeedVal, mana);
                caster->CastCustomSpell(caster, SPELL_WARLOCK_LIFE_TAP_ENERGIZE_2, &manaFeedVal, nullptr, nullptr, true, nullptr);
            }
        }
    }

    SpellCastResult CheckCast()
    {
        if ((int32(GetCaster()->GetHealth()) > int32(GetSpellInfo()->Effects[EFFECT_0].CalcValue() + (3.1 * GetSpellInfo()->BaseLevel) + LIFE_TAP_COEFFICIENT)))
            return SPELL_CAST_OK;
        return SPELL_FAILED_FIZZLE;
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_life_tap::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnCheckCast += SpellCheckCastFn(spell_warl_life_tap::CheckCast);
    }
};

// 48018 - Demonic Circle: Summon
class spell_warl_demonic_circle_summon : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_circle_summon);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT });
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
    {
        // If effect is removed by expire remove the summoned demonic circle too.
        if (!(mode & AURA_EFFECT_HANDLE_REAPPLY))
            GetTarget()->RemoveGameObject(GetId(), true);

        GetTarget()->RemoveAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
    }

    void HandleDummyTick(AuraEffect const* /*aurEff*/)
    {
        if (GameObject* circle = GetTarget()->GetGameObject(GetId()))
        {
            // Here we check if player is in demonic circle teleport range, if so add
            // WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST; allowing him to cast the WARLOCK_DEMONIC_CIRCLE_TELEPORT.
            // If not in range remove the WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST.

            SpellInfo const* spellInfo = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT);

            if (GetTarget()->IsWithinDist(circle, spellInfo->GetMaxRange(true)))
            {
                if (!GetTarget()->HasAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST))
                    GetTarget()->CastSpell(GetTarget(), SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, true);
            }
            else
                GetTarget()->RemoveAura(SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_demonic_circle_summon::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_circle_summon::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_warl_soul_power : public AuraScript
{
    PrepareAuraScript(spell_warl_soul_power);

    void HandleDummyTick(AuraEffect const* aurEff)
    {
        int32 maxRegenerate = aurEff->GetAmount();
        int32 amountRegenerate = aurEff->GetBase()->GetEffect(EFFECT_1)->GetAmount();

        if (GetCaster()->GetPower(POWER_ENERGY) < maxRegenerate)
            GetCaster()->ModifyPower(POWER_ENERGY, amountRegenerate);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return GetCaster() && !GetCaster()->IsInCombat() && GetCaster()->IsAlive();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_soul_power::CheckProc);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_soul_power::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 48020 - Demonic Circle: Teleport
class spell_warl_demonic_circle_teleport : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_circle_teleport);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON });
    }

    void HandleTeleport(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Player* player = GetTarget()->ToPlayer())
        {
            if (GameObject* circle = player->GetGameObject(SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON))
            {
                player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation(), false, false, false, true);
                player->RemoveAurasWithMechanic(1 << MECHANIC_SNARE);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_circle_teleport::HandleTeleport, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// -47230 - Fel Synergy
class spell_warl_fel_synergy : public AuraScript
{
    PrepareAuraScript(spell_warl_fel_synergy);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_FEL_SYNERGY_HEAL });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // Xinef: Added charm check

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage())
        {
            return false;
        }

        return (GetTarget()->GetGuardianPet() || GetTarget()->GetCharm()) && damageInfo->GetDamage();
    }

    void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        int32 heal = CalculatePct(static_cast<int32>(eventInfo.GetDamageInfo()->GetDamage()), aurEff->GetAmount());
        GetTarget()->CastCustomSpell(SPELL_WARLOCK_FEL_SYNERGY_HEAL, SPELLVALUE_BASE_POINT0, heal, (Unit*)nullptr, true, nullptr, aurEff); // TARGET_UNIT_PET
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_fel_synergy::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_fel_synergy::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

//// -48181 - Haunt
//class spell_warl_haunt : public SpellScript
//{
//    PrepareSpellScript(spell_warl_haunt);
//
//    void HandleAfterHit()
//    {
//        if (Aura* aura = GetHitAura())
//            if (AuraEffect* aurEff = aura->GetEffect(EFFECT_1))
//                aurEff->SetAmount(CalculatePct(aurEff->GetAmount(), GetHitDamage()));
//    }
//
//    void Register() override
//    {
//        AfterHit += SpellHitFn(spell_warl_haunt::HandleAfterHit);
//    }
//};
//
//class spell_warl_haunt_aura : public AuraScript
//{
//    PrepareAuraScript(spell_warl_haunt_aura);
//
//    bool Validate(SpellInfo const* /*spellInfo*/) override
//    {
//        return ValidateSpellInfo({ SPELL_WARLOCK_HAUNT_HEAL });
//    }
//
//    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
//    {
//        if (Unit* caster = GetCaster())
//        {
//            if (!caster || caster->isDead())
//                return;
//
//            int32 amount = aurEff->GetAmount();
//            GetTarget()->CastCustomSpell(caster, SPELL_WARLOCK_HAUNT_HEAL, &amount, nullptr, nullptr, true, nullptr, aurEff, GetCasterGUID());
//        }
//    }
//
//    void Register() override
//    {
//        OnEffectRemove += AuraEffectRemoveFn(spell_warl_haunt_aura::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
//    }
//};

// -30108 - Unstable Affliction
class spell_warl_unstable_affliction : public AuraScript
{
    PrepareAuraScript(spell_warl_unstable_affliction);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        caster->EnergizeBySpell(caster, SPELL_WARLOCK_UNSTABLE_AFFLICTION, GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(caster), POWER_ENERGY);
    }

    void HandleDispel(DispelInfo* dispelInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        caster->CastSpell(dispelInfo->GetDispeller(), SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_unstable_affliction::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        AfterDispel += AuraDispelFn(spell_warl_unstable_affliction::HandleDispel);
    }
};

// 47867 - Curse of Doom
class spell_warl_curse_of_doom : public AuraScript
{
    PrepareAuraScript(spell_warl_curse_of_doom);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_CURSE_OF_DOOM_EFFECT });
    }

    bool Load() override
    {
        return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        /*AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
        if (removeMode != AURA_REMOVE_BY_DEATH || !IsExpired())
            return;

        if (GetCaster()->ToPlayer()->isHonorOrXPTarget(GetTarget()))
            GetCaster()->CastSpell(GetTarget(), SPELL_WARLOCK_CURSE_OF_DOOM_EFFECT, true, nullptr, aurEff);*/
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_warl_curse_of_doom::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// -755 - Health Funnel
class spell_warl_health_funnel : public AuraScript
{
    PrepareAuraScript(spell_warl_health_funnel);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({
            SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2,
            SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2,
            SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1,
            SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1
            });
    }

    void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        Unit* target = GetTarget();
        if (caster->HasAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2))
            target->CastSpell(target, SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2, true);
        else if (caster->HasAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1))
            target->CastSpell(target, SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1, true);
    }

    void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        target->RemoveAurasDueToSpell(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1);
        target->RemoveAurasDueToSpell(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_health_funnel::RemoveEffect, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
        OnEffectApply += AuraEffectApplyFn(spell_warl_health_funnel::ApplyEffect, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
    }
};

// -6229 - Shadow Ward
class spell_warl_shadow_ward : public AuraScript
{
    PrepareAuraScript(spell_warl_shadow_ward);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        if (Unit* caster = GetCaster())
        {
            // +80.68% from sp bonus
            float bonus = 0.8068f;

            bonus *= caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
            bonus *= caster->CalculateLevelPenalty(GetSpellInfo());

            amount += int32(bonus);
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_shadow_ward::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// 63310 - Glyph of Shadowflame
class spell_warl_glyph_of_shadowflame : public AuraScript
{
    PrepareAuraScript(spell_warl_glyph_of_shadowflame);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_WARLOCK_GLYPH_OF_SHADOWFLAME });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_WARLOCK_GLYPH_OF_SHADOWFLAME, true, nullptr, aurEff);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_glyph_of_shadowflame::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 47855 - Drain Soul
class spell_warl_drain_soul : public AuraScript
{
    PrepareAuraScript(spell_warl_drain_soul);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (GetCaster() && GetCaster()->IsAlive())
            GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_DRAIN_SOUL_ENERGY, TRIGGERED_FULL_MASK);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        // Remove Soul Affliction Rune Buff
        for (size_t i = 800542; i < 800548; i++)
            if (caster->HasAura(i))
                caster->RemoveAura(i);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_drain_soul::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_drain_soul::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 83000 Call Dreadstalkers
class spell_warlock_summon_darkhound : public SpellScript
{
    PrepareSpellScript(spell_warlock_summon_darkhound);

    Aura* GetCarnivorousStalkersAura(Unit* caster)
    {
        for (size_t i = 800748; i < 800754; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetTheHoundmastersStratagemAura(Unit* caster)
    {
        for (size_t i = 800762; i < 800768; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleCast()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 totalSummons = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(player);

        for (size_t i = 0; i < totalSummons; i++)
        {
            int32 duration = GetSpellInfo()->GetDuration();

            if (AuraEffect* talent = player->GetAuraEffectOfRankedSpell(TALENT_WARLOCK_MOLTEN_HAND, EFFECT_1))
                duration += talent->GetAmount();

            TempSummon* summon = GetCaster()->SummonCreatureGuardian(GUARDIAN_WARLOCK_DREADSTALKER, player, player, duration, GUARDIAN_WARLOCK_DREADSTALKER_DIST + i, PET_FOLLOW_ANGLE);

            if (summon)
                summon->SetPositionReset(GUARDIAN_WARLOCK_DREADSTALKER_DIST + i, PET_FOLLOW_ANGLE);

            if (!summon || summon->isDead())
                return;

            if (Aura* runeAura = GetCarnivorousStalkersAura(player))
            {
                int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
                player->AddAura(procSpell, summon);
            }

            if (Aura* runeAura = GetTheHoundmastersStratagemAura(player))
            {
                int32 procSpell = runeAura->GetEffect(EFFECT_1)->GetAmount();
                player->AddAura(procSpell, summon);
            }
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warlock_summon_darkhound::HandleCast);
    }
};

// 83000 Call Dreadstalkers
class spell_warlock_call_dreadstalkers_aura : public AuraScript
{
    PrepareAuraScript(spell_warlock_call_dreadstalkers_aura);

    Aura* GetShadowsBiteAura(Unit* caster)
    {
        for (size_t i = 800736; i < 800742; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* runeAura = GetShadowsBiteAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
            caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
        }
    }

    void Register()
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_warlock_call_dreadstalkers_aura::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warlock_summon_gargoyle : public SpellScript
{
    PrepareSpellScript(spell_warlock_summon_gargoyle);

    SpellCastResult CheckCast()
    {
        if (Player* player = GetCaster()->ToPlayer())
            if (player->GetSelectedUnit())
                return SPELL_CAST_OK;

        return SPELL_FAILED_NO_VALID_TARGETS;
    }

    void HandleCast()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* target = player->GetSelectedUnit();

        if (!target || target->isDead())
            return;

        int32 duration = GetSpellInfo()->GetDuration();

        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);

        Map* map = player->GetMap();

        Position pos = target->GetNearPosition(3.f, 1.f);
        pos.m_positionZ += 5.0f;

        if (TempSummon* summon = map->SummonCreature(GUARDIAN_WARLOCK_BILESCOURGE, pos, properties, duration, GetCaster(), GetSpellInfo()->Id))
        {
            summon->SetTempSummonType(TEMPSUMMON_TIMED_DESPAWN);
            summon->GetMotionMaster()->Clear(false);
            summon->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE, MOTION_SLOT_ACTIVE);
            ((Guardian*)summon)->InitStatsForLevel(player->getLevel());
            summon->AI()->AttackStart(player->GetSelectedUnit());
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warlock_summon_gargoyle::CheckCast);
        OnCast += SpellCastFn(spell_warlock_summon_gargoyle::HandleCast);
    }
};

class spell_warlock_soul_strike : public SpellScript
{
    PrepareSpellScript(spell_warlock_soul_strike);

    Unit* GetPet()
    {
        Unit* controlledUnit = nullptr;
        if (Player* player = GetCaster()->ToPlayer())
            for (Unit::ControlSet::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                if (Unit* pet = (*itr))
                    if (pet->IsAlive() &&
                        pet->GetOwnerGUID() == player->GetGUID() &&
                        pet->GetEntry() == PET_WARLOCK_FELGUARD &&
                        pet->IsWithinDist(player, 100.0f, false))
                        controlledUnit = pet;

        return controlledUnit;
    }

    SpellCastResult CheckCast()
    {
        Unit* pet = GetPet();

        if (pet)
            return SPELL_CAST_OK;

        return SPELL_FAILED_NO_PET;
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* target = player->GetSelectedUnit();

        if (!target || target->isDead())
            return;

        Unit* pet = GetPet();

        if (!pet || pet->isDead())
            return;

        pet->ToCreature()->AI()->AttackStart(target);
        pet->CastSpell(target, SPELL_WARLOCK_SOUL_STRIKE, TRIGGERED_IGNORE_GCD, nullptr, nullptr, player->GetGUID());
        player->CastSpell(player, SPELL_WARLOCK_SOUL_STRIKE_ENERGY, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warlock_soul_strike::CheckCast);
        OnEffectHit += SpellEffectFn(spell_warlock_soul_strike::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class spell_warlock_summon_felboar : public SpellScript
{
    PrepareSpellScript(spell_warlock_summon_felboar);

    void HandleCast()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 totalSummons = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(player);

        for (size_t i = 0; i < totalSummons; i++)
        {
            int32 duration = GetSpellInfo()->GetDuration();
            TempSummon* summon = GetCaster()->SummonCreatureGuardian(GUARDIAN_WARLOCK_VILEFIEND, player, player, duration, GUARDIAN_WARLOCK_VILEFIEND_DIST + i, PET_FOLLOW_ANGLE);

            if (summon)
                summon->SetPositionReset(GUARDIAN_WARLOCK_VILEFIEND_DIST + i, PET_FOLLOW_ANGLE);

        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warlock_summon_felboar::HandleCast);
    }
};

class spell_warlock_summon_felguard : public SpellScript
{
    PrepareSpellScript(spell_warlock_summon_felguard);

    void HandleCast()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 duration = GetSpellInfo()->GetDuration();
        TempSummon* summon = GetCaster()->SummonCreatureGuardian(GUARDIAN_WARLOCK_FELGUARD_GRIMOIRE, player, player, duration, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);

        if (summon)
            summon->SetPositionReset(PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warlock_summon_felguard::HandleCast);
    }
};

// 83031 - Grimoire : Felguard aura
class spell_warl_grimoire_felguard_aura : public AuraScript
{
    PrepareAuraScript(spell_warl_grimoire_felguard_aura);

    void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* pet = GetUnitOwner();

        if (!pet || pet->isDead())
            return;

        Unit* caster = pet->GetOwner();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(T1_WARLOCK_DEMONO_4PC))
            caster->AddAura(T1_WARLOCK_DEMONO_4PC_PET_BUFF, caster);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_grimoire_felguard_aura::OnApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warlock_implosion : public SpellScript
{
    PrepareSpellScript(spell_warlock_implosion);

    void HandleCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Player* player = caster->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget());

        if (!target || target->isDead())
            return;

        auto summonedUnits = player->m_Controlled;

        for (auto const& unit : summonedUnits)
        {
            if (unit->isDead())
                continue;

            if (unit->GetEntry() == GUARDIAN_WARLOCK_WILD_IMP)
            {
                unit->CastSpell(target, SPELL_WARLOCK_IMPLOSSION, true, nullptr, nullptr, player->GetGUID());

                if (TempSummon* summon = unit->ToTempSummon())
                {
                    unit->ToTempSummon()->DespawnOrUnsummon();
                }

            }
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warlock_implosion::HandleCast);
    }
};

class spell_warlock_summon_darkglare : public SpellScript
{
    PrepareSpellScript(spell_warlock_summon_darkglare);

    void HandleCast()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        int32 duration = GetSpellInfo()->GetDuration();
        TempSummon* summon = GetCaster()->SummonCreatureGuardian(GUARDIAN_WARLOCK_DARKGLARE, player, player, duration, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);

        if (summon)
            summon->SetPositionReset(PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        for (auto const& target : targets)
        {
            if (Unit const* unitTarget = target->ToUnit())
            {
                auto const& auras = unitTarget->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE);
                for (Unit::AuraEffectList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                {
                    if ((*itr)->GetCasterGUID() == GetCaster()->GetGUID())
                    {
                        (*itr)->GetBase()->RefreshDuration();
                        (*itr)->ResetTicks();
                    }
                }
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warlock_summon_darkglare::HandleCast);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warlock_summon_darkglare::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_warlock_cataclysm : public SpellScript
{
    PrepareSpellScript(spell_warlock_cataclysm);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        for (auto const& target : targets)
        {
            if (Unit* unitTarget = target->ToUnit())
            {
                if (!unitTarget->HasAura(SPELL_WARLOCK_IMMOLATE))
                    GetCaster()->AddAura(SPELL_WARLOCK_IMMOLATE, unitTarget);
            }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warlock_cataclysm::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_warlock_summon_demonic_tyrant : public SpellScript
{
    PrepareSpellScript(spell_warlock_summon_demonic_tyrant);

    Aura* GetReignofTyrannyAura(Unit* caster)
    {
        for (size_t i = 800844; i < 800850; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleCast()
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            int32 timerIncrease = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(player);

            int32 duration = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(player);
            TempSummon* summon = GetCaster()->SummonCreatureGuardian(GUARDIAN_WARLOCK_DEMONIC_TYRANT, player, player, duration, GUARDIAN_WARLOCK_DEMONIC_TYRAN_DIST, PET_FOLLOW_ANGLE);

            if (summon)
                summon->SetPositionReset(GUARDIAN_WARLOCK_DEMONIC_TYRAN_DIST, PET_FOLLOW_ANGLE);

            // Give damage increased based on the amount of Demonic Servitude stacks
            if (Aura* runeAura = GetReignofTyrannyAura(player))
                if (Aura* demonicServitude = player->GetAura(RUNE_WARLOCK_DEMONIC_SERVITUDE))
                {
                    int32 stacks = demonicServitude->GetStackAmount();
                    int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

                    player->CastCustomSpell(procSpell, SPELLVALUE_AURA_STACK, stacks, summon, TRIGGERED_FULL_MASK);
                }

            for (auto itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                if (Unit* pet = *itr)
                    if (TempSummon* summon = pet->ToTempSummon())
                    {
                        if (summon->GetEntry() == GUARDIAN_WARLOCK_VILEFIEND || summon->GetEntry() == GUARDIAN_WARLOCK_DREADSTALKER)
                            summon->SetTimer(summon->GetTimer() + timerIncrease);
                    }
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warlock_summon_demonic_tyrant::HandleCast);
    }
};

// 83002
class spell_warlock_hand_of_guldan : public SpellScript
{
    PrepareSpellScript(spell_warlock_hand_of_guldan);

    void HandleHitTarget()
    {
        int32 damage = GetHitDamage();

        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Player* player = caster->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 runicPower = caster->GetPower(POWER_ENERGY);
        uint8 cost = runicPower > 15 ? 15 : runicPower;

        uint8 maxSummon = 0;

        if (cost == 15)
            maxSummon = 3;
        else if (cost < 15 && cost >= 10)
            maxSummon = 2;
        else
            maxSummon = 1;

        for (size_t i = 1; i < maxSummon; i++)
        {
            caster->CastSpell(caster, SPELL_WARLOCK_HAND_OF_GULDAN_ADDITIONAL_COST);
        }

        if (Unit* target = GetHitUnit()) {
            for (size_t i = 0; i < maxSummon; i++)
            {
                TempSummon* summon = GetCaster()->SummonCreatureGuardian(GUARDIAN_WARLOCK_WILD_IMP, target, player, 30000, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE + i);
                if (summon)
                    summon->SetPositionReset(PET_FOLLOW_DIST, PET_FOLLOW_ANGLE + i);
            }
            damage += damage;
        }

        SetHitDamage(damage);
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (!targets.empty())
            targets.resize(1);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warlock_hand_of_guldan::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        OnHit += SpellHitFn(spell_warlock_hand_of_guldan::HandleHitTarget);
    }
};

class spell_warlock_summon_nether_portal : public SpellScript
{
    PrepareSpellScript(spell_warlock_summon_nether_portal);

    void HandleCast()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 timerIncrease = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(player);

        int32 duration = GetSpellInfo()->GetDuration();
        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(83);
        Position pos = GetCaster()->GetNearPosition(PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
        TempSummon* summon = GetCaster()->GetMap()->SummonCreature(GUARDIAN_WARLOCK_PORTAL_SUMMON, pos, properties, duration, GetCaster(), GetSpellInfo()->Id);

        if (!summon || summon->isDead())
            return;

        summon->AddAura(40280, summon);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warlock_summon_nether_portal::HandleCast);
    }
};

class spell_warl_nether_portal_proc : public AuraScript
{
    PrepareAuraScript(spell_warl_nether_portal_proc);

    Aura* GetGuldansAmbitionAura(Unit* caster)
    {
        for (size_t i = 800870; i < 800876; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetNerzhulsVolitionAura(Unit* caster)
    {
        for (size_t i = 800878; i < 800884; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo() || eventInfo.GetSpellInfo()->PowerType != POWER_ENERGY)
            return false;

        return eventInfo.GetSpellInfo()->ManaCost > 0 && eventInfo.GetSpellInfo()->Id != SPELL_WARLOCK_HAND_OF_GULDAN_ADDITIONAL_COST;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        const SpellInfo* spellInfo = eventInfo.GetSpellInfo();
        uint32 soulPowerSpent = spellInfo->CalcPowerCost(caster, spellInfo->GetSchoolMask());
        int32 soulPowerThreshold = aurEff->GetAmount();

        if (soulPowerSpent >= soulPowerThreshold)
        {
            if (Player* player = caster->ToPlayer())
            {
                Unit* portal = player->FindNearestCreature(GUARDIAN_WARLOCK_PORTAL_SUMMON, 40.f, true);
                if (portal) {
                    int32 positionBias = urand(1, 5);
                    player->SummonCreatureGuardian(GUARDIAN_WARLOCK_WILD_IMP, portal, player, 30000, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE + positionBias);

                    int32 guldanMaxStacks = 0;
                    if (Aura* runeAura = GetGuldansAmbitionAura(player))
                    {
                        guldanMaxStacks = runeAura->GetEffect(EFFECT_0)->GetAmount();

                        if (Aura* guldanListener = caster->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_LISTENER))
                        {
                            if (guldanListener->GetStackAmount() < guldanMaxStacks)
                                guldanListener->ModStackAmount(1);
                        }
                        else
                            caster->CastSpell(caster, RUNE_WARLOCK_GULDANS_AMBITION_LISTENER, TRIGGERED_FULL_MASK);
                    }

                    if (Aura* runeAura = GetNerzhulsVolitionAura(player))
                    {
                        int32 procChance = runeAura->GetEffect(EFFECT_0)->GetAmount();

                        if (roll_chance_i(procChance))
                        {
                            int32 secondPositionBias = urand(1, 5);

                            while (secondPositionBias == positionBias)
                                secondPositionBias = urand(1, 5);

                            player->SummonCreatureGuardian(GUARDIAN_WARLOCK_WILD_IMP, portal, player, 30000, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE + urand(1, 5));

                            if (guldanMaxStacks > 0)
                                if (Aura* guldanListener = caster->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_LISTENER))
                                {
                                    if (guldanListener->GetStackAmount() < guldanMaxStacks)
                                        guldanListener->ModStackAmount(1);
                                }
                        }

                    }
                }
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            if (Aura* runeAura = GetGuldansAmbitionAura(player))
                if (Aura* guldanListener = player->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_LISTENER))
                {
                    int32 duration = runeAura->GetEffect(EFFECT_1)->GetAmount();
                    player->SummonCreatureGuardian(RUNE_GUARDIAN_WARLOCK_PIT_LORD, player, player, duration, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE + urand(1, 5));
                }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_nether_portal_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_nether_portal_proc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(spell_warl_nether_portal_proc::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_pit_lord_scaling : public AuraScript
{
    struct PetStats {
        float stamina;
        float sp_to_ap;
        float sp_to_sp;
    };

    PrepareAuraScript(spell_warl_pit_lord_scaling);

    void CalculateResistanceAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float scaling = 15;
            if (Aura* guldanListener = GetUnitOwner()->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_BUFF))
                scaling *= guldanListener->GetStackAmount();

            amount = CalculatePct(std::max<int32>(0, owner->GetResistance(SPELL_SCHOOL_MASK_NORMAL)), scaling);
        }
    }

    void CalculateMeleeCriticalChance(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float scaling = 10;
            if (Aura* guldanListener = GetUnitOwner()->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_BUFF))
                scaling *= guldanListener->GetStackAmount();

            int32 critChanceFire = owner->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_FIRE);
            int32 critChanceShadow = owner->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_SHADOW);
            int32 maximum = (critChanceFire > critChanceShadow) ? critChanceFire : critChanceShadow;
            amount = CalculatePct(std::max<int32>(0, maximum), scaling);
        }
    }

    void CalculateSpellCriticalChance(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float scaling = 10;
            if (Aura* guldanListener = GetUnitOwner()->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_BUFF))
                scaling *= guldanListener->GetStackAmount();

            int32 critChanceFire = owner->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_FIRE);
            int32 critChanceShadow = owner->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_SHADOW);
            int32 maximum = (critChanceFire > critChanceShadow) ? critChanceFire : critChanceShadow;
            amount = CalculatePct(std::max<int32>(0, maximum), scaling);
        }
    }

    void CalculateHasteAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float scaling = 10;
            if (Aura* guldanListener = GetUnitOwner()->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_BUFF))
                scaling *= guldanListener->GetStackAmount();

            float speed = owner->GetFloatValue(UNIT_MOD_CAST_SPEED) * 10;
            amount = CalculatePct(std::max<int32>(0, speed), scaling);
        }
    }

    void CalculateStatAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float scaling = 15;
            if (Aura* guldanListener = GetUnitOwner()->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_BUFF))
                scaling *= guldanListener->GetStackAmount();

            amount = CalculatePct(std::max<int32>(0, owner->GetStat(STAT_STAMINA)), scaling);
        }
    }

    void CalculateAPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float scaling = 10;
            if (Aura* guldanListener = GetUnitOwner()->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_BUFF))
                scaling *= guldanListener->GetStackAmount();

            int32 fire = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE);
            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
            int32 maximum = (fire > shadow) ? fire : shadow;
            amount = CalculatePct(std::max<int32>(0, maximum), scaling);
        }
    }

    void CalculateSPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            float scaling = 12;
            if (Aura* guldanListener = GetUnitOwner()->GetAura(RUNE_WARLOCK_GULDANS_AMBITION_BUFF))
                scaling *= guldanListener->GetStackAmount();

            int32 fire = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE);
            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
            int32 maximum = (fire > shadow) ? fire : shadow;
            amount = CalculatePct(std::max<int32>(0, maximum), scaling);

            // xinef: Update appropriate player field
            if (owner->GetTypeId() == TYPEID_PLAYER)
                owner->SetUInt32Value(PLAYER_PET_SPELL_POWER, (uint32)amount);
        }
    }

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = 2 * IN_MILLISECONDS;
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (aurEff->GetAuraType() == SPELL_AURA_MOD_STAT && (aurEff->GetMiscValue() == STAT_STAMINA))
        {
            int32 currentAmount = aurEff->GetAmount();
            int32 newAmount = GetEffect(aurEff->GetEffIndex())->CalculateAmount(GetCaster());
            if (newAmount != currentAmount)
            {
                if (aurEff->GetMiscValue() == STAT_STAMINA)
                {
                    uint32 actStat = GetUnitOwner()->GetHealth();
                    GetEffect(aurEff->GetEffIndex())->ChangeAmount(newAmount, false);
                    GetUnitOwner()->SetHealth(std::min<uint32>(GetUnitOwner()->GetMaxHealth(), actStat));
                }
                else
                {
                    uint32 actStat = GetUnitOwner()->GetPower(POWER_MANA);
                    GetEffect(aurEff->GetEffIndex())->ChangeAmount(newAmount, false);
                    GetUnitOwner()->SetPower(POWER_MANA, std::min<uint32>(GetUnitOwner()->GetMaxPower(POWER_MANA), actStat));
                }
            }
        }
        else
            GetEffect(aurEff->GetEffIndex())->RecalculateAmount();
    }

    void Register() override
    {
        if (m_scriptSpellId == PIT_LORD_SCALING_STAMINA_AP_SP)
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_pit_lord_scaling::CalculateStatAmount, EFFECT_0, SPELL_AURA_MOD_STAT);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_pit_lord_scaling::CalculateAPAmount, EFFECT_1, SPELL_AURA_MOD_ATTACK_POWER);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_pit_lord_scaling::CalculateSPAmount, EFFECT_2, SPELL_AURA_MOD_DAMAGE_DONE);
        }

        if (m_scriptSpellId == PIT_LORD_SCALING_ARMOR_MEELE_CRIT_SPELL_CRIT)
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_pit_lord_scaling::CalculateResistanceAmount, EFFECT_0, SPELL_AURA_MOD_RESISTANCE);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_pit_lord_scaling::CalculateMeleeCriticalChance, EFFECT_1, SPELL_AURA_MOD_WEAPON_CRIT_PERCENT);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_pit_lord_scaling::CalculateSpellCriticalChance, EFFECT_2, SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
        }

        if (m_scriptSpellId == PIT_LORD_SCALING_HASTE)
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_pit_lord_scaling::CalculateHasteAmount, EFFECT_0, SPELL_AURA_MOD_MELEE_RANGED_HASTE);
        }

        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_warl_pit_lord_scaling::CalcPeriodic, EFFECT_ALL, SPELL_AURA_ANY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_pit_lord_scaling::HandlePeriodic, EFFECT_ALL, SPELL_AURA_ANY);
    }
};

class spell_warl_agony : public AuraScript
{
    PrepareAuraScript(spell_warl_agony);

    void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        SpellInfo const* value = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_AGONY);
        uint32 initialStack = value->GetEffect(EFFECT_2).CalcValue(GetCaster());

        aurEff->GetBase()->SetStackAmount(initialStack);
    }

    void OnReApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        SpellInfo const* value = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_AGONY);
        uint32 maxStack = value->GetEffect(EFFECT_1).CalcValue(GetCaster());
        if (aurEff->GetBase()->GetStackAmount() > maxStack)
            aurEff->GetBase()->SetStackAmount(maxStack);
    }

    void OnPeriodic(AuraEffect const* aurEff)
    {
        SpellInfo const* value = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_AGONY);
        uint32 maxStack = value->GetEffect(EFFECT_1).CalcValue(GetCaster());
        uint32 currentStack = aurEff->GetBase()->GetStackAmount();
        if (currentStack < maxStack)
            aurEff->GetBase()->SetStackAmount(currentStack + 1);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_agony::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectApply += AuraEffectApplyFn(spell_warl_agony::OnReApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAPPLY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_agony::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

class spell_warlock_dark_pact : public SpellScript
{
    PrepareSpellScript(spell_warlock_dark_pact);

    Aura* GetIchorsofDevilsAura(Unit* caster)
    {
        for (size_t i = 800440; i < 800446; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    uint32 shieldAmount = 0;

    void HandleBeforeCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        SpellInfo const* value = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_DARK_PACT);
        int32 sacrificePct = CalculatePct(caster->GetHealth(), value->GetEffect(EFFECT_0).CalcValue(caster));
        shieldAmount = CalculatePct(sacrificePct, value->GetEffect(EFFECT_1).CalcValue(caster)) + CalculatePct(caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()), value->GetEffect(EFFECT_2).CalcValue(caster));

        if (Aura* runeAura = GetIchorsofDevilsAura(caster))
        {
            int32 reduction = runeAura->GetEffect(EFFECT_0)->GetAmount();
            sacrificePct -= reduction;
        }

        caster->CastCustomSpell(SPELL_WARLOCK_DARK_PACT_DAMAGE, SPELLVALUE_BASE_POINT0, sacrificePct, caster, TRIGGERED_FULL_MASK);
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        caster->CastCustomSpell(SPELL_WARLOCK_DARK_PACT_SHIELD, SPELLVALUE_BASE_POINT0, shieldAmount, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        BeforeCast += SpellCastFn(spell_warlock_dark_pact::HandleBeforeCast);
        AfterCast += SpellCastFn(spell_warlock_dark_pact::HandleAfterCast);
    }
};

class spell_warl_demon_armor : public AuraScript
{
    PrepareAuraScript(spell_warl_demon_armor);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = GetUnitOwner()->CountPctFromMaxHealth(amount);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_demon_armor::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_INCREASE_HEALTH);
    }
};

class spell_warl_fel_armor : public AuraScript
{
    PrepareAuraScript(spell_warl_fel_armor);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        amount = CalculatePct(GetCaster()->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()), amount);
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->GetHealthPct() < 100)
            caster->CastSpell(caster, SPELL_WARLOCK_FEL_ARMOR_HEAL, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_fel_armor::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_DAMAGE_DONE);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_fel_armor::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_warl_health_funnel_new : public AuraScript
{
    PrepareAuraScript(spell_warl_health_funnel_new);

    bool Load() override
    {
        Unit* caster = GetCaster();
        return caster && caster->GetTypeId() == TYPEID_PLAYER;
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        if (Unit* caster = GetCaster())
        {
            amount = CalculatePct(GetCaster()->ToPlayer()->GetMaxHealth(), amount) * 2 / 5;
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_health_funnel_new::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
    }
};

class spell_warl_haunt : public AuraScript
{
    PrepareAuraScript(spell_warl_haunt);


    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->ToPlayer()->RemoveSpellCooldown(SPELL_WARLOCK_HAUNT, true);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* target = GetUnitOwner();
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!target || target->isDead())
            return;

        // If target has the Seized Vitality debuff removes it.
        if (Aura* seizedVitalityDebuff = target->GetAura(RUNE_WARLOCK_SEIZED_VITALITY_DEBUFF))
            seizedVitalityDebuff->Remove();

        // Remove Haunted Soul Rune Buff
        for (size_t i = 800492; i < 800498; i++)
            if (caster->HasAura(i))
            {
                auto const& threatList = caster->getAttackers();
                auto threatListCopy = threatList;

                if (threatListCopy.empty()) continue;

                int32 hauntedEnemiesNbr = 0;

                for (auto const& enemy : threatListCopy)
                {
                    if (enemy->isDead())
                        continue;

                    if (enemy == target)
                        continue;

                    if (enemy->HasAura(SPELL_WARLOCK_HAUNT))
                        hauntedEnemiesNbr++;
                }

                if (hauntedEnemiesNbr == 0)
                    caster->RemoveAura(i);
            }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_haunt::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        AfterEffectRemove += AuraEffectRemoveFn(spell_warl_haunt::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_seed_of_corruption_handler : public AuraScript
{
    PrepareAuraScript(spell_warl_seed_of_corruption_handler);

    void HandleAfterEffect(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        int32 amount = CalculatePct(GetCaster()->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()), aurEff->GetAmount());
        aurEff->GetBase()->GetEffect(EFFECT_0)->SetAmount(amount);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || GetCaster()->isDead())
            return false;

        if (Unit* caster = eventInfo.GetActor())
        {
            if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 && eventInfo.GetSpellInfo() && caster->GetGUID() == GetCaster()->GetGUID())
                return true;
        }
        else
            return false;

        return false;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* target = GetAura()->GetOwner()->ToUnit();

        if (!target || target->isDead())
            return;

        Unit* caster = GetCaster();
        AuraEffect* effect1 = aurEff->GetBase()->GetEffect(EFFECT_1);
        int32 threshold = aurEff->GetAmount();
        int32 savedAmount = effect1->GetAmount();
        int32 damageTaken = eventInfo.GetDamageInfo()->GetDamage();

        if (damageTaken >= threshold || savedAmount >= threshold || eventInfo.GetSpellInfo()->Id == SPELL_WARLOCK_SEED_OF_CORRUPTION_DETONATION)
        {
            target->RemoveAura(SPELL_WARLOCK_SEED_OF_CORRUPTION);
        }
        else
        {
            effect1->SetAmount(savedAmount + damageTaken);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* target = GetTarget();
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!target || target->isDead())
            return;

        caster->CastSpell(target, SPELL_WARLOCK_SEED_OF_CORRUPTION_DETONATION, TRIGGERED_FULL_MASK);
        target->CastSpell(target, SPELL_WARLOCK_SEED_OF_CORRUPTION_VISUAL, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_warl_seed_of_corruption_handler::HandleAfterEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_warl_seed_of_corruption_handler::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_seed_of_corruption_handler::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_seed_of_corruption_handler::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 47834 - Seed of Corruption (Explosion)
class spell_warl_seed_of_corruption_explosion : public SpellScript
{
    PrepareSpellScript(spell_warl_seed_of_corruption_explosion);

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove one stack of T1 4pc listener.
        if (Aura* crashingChaosListener = caster->GetAura(T1_WARLOCK_AFFLI_4PC_LISTENER))
            crashingChaosListener->ModStackAmount(-1);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warl_seed_of_corruption_explosion::HandleAfterCast);
    }
};

// 59172 - Chaos Bolt
class spell_warl_chaos_bolt : public SpellScript
{
    PrepareSpellScript(spell_warl_chaos_bolt);

    Aura* GetChaosIncarnateAura(Unit* caster)
    {
        for (size_t i = 800928; i < 800934; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetAshenRemainsAura(Unit* caster)
    {
        for (size_t i = 800972; i < 800978; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove Ritual of Ruin buff.
        if (caster->HasAura(TALENT_WARLOCK_RITUAL_OF_RUIN_BUFF))
            caster->RemoveAura(TALENT_WARLOCK_RITUAL_OF_RUIN_BUFF);

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // Damage increased by an amount equal to your critical chances.
        int32 critChance = caster->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_FIRE);
        AddPct(damage, critChance);

        // increase damage by random amount.
        if (Aura* runeAura = GetChaosIncarnateAura(caster))
        {
            int32 minAmount = runeAura->GetEffect(EFFECT_0)->GetAmount();
            int32 maxAmount = runeAura->GetEffect(EFFECT_1)->GetAmount();
            int32 increasePct = urand(minAmount, maxAmount);

            AddPct(damage, increasePct);
        }

        // Increases damage if target has Immolate.
        if (Aura* runeAura = GetAshenRemainsAura(caster))
        {
            int32 increasePct = runeAura->GetEffect(EFFECT_0)->GetAmount();

            if (target->HasAura(SPELL_WARLOCK_IMMOLATE))
                AddPct(damage, increasePct);
        }

        SetHitDamage(damage);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove one stack of Crashing Chaos listener each cast.
        for (size_t i = 801178; i < 801184; i++)
            if (Aura* crashingChaosListener = caster->GetAura(i))
                crashingChaosListener->ModStackAmount(-1);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_chaos_bolt::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_warl_chaos_bolt::HandleAfterHit);
    }
};

class spell_warl_conflagrate : public SpellScript
{
    PrepareSpellScript(spell_warl_conflagrate);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // Apply damage increase of Conflagration of Chaos if you have the buff.
        for (size_t i = 801028; i < 801034; i++)
            if (Aura* buff = caster->GetAura(i))
            {
                int32 critChance = caster->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_FIRE);
                int32 critPct = buff->GetEffect(EFFECT_0)->GetAmount();
                int32 increasePct = CalculatePct(critChance, critPct);
                AddPct(damage, increasePct);
                buff->Remove();
            }

        SetHitDamage(damage);

        // Energize
        caster->CastSpell(caster, SPELL_WARLOCK_CONFLAGRATE_ENERGY, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_conflagrate::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warl_immolate_energy : public AuraScript
{
    PrepareAuraScript(spell_warl_immolate_energy);

    void OnPeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || !caster->IsAlive())
            return;

        caster->CastSpell(caster, SPELL_WARLOCK_IMMOLATE_ENERGY, TRIGGERED_FULL_MASK);

        uint32 procChance = GetEffect(EFFECT_2)->GetAmount();

        if (roll_chance_f(procChance) && caster->GetTypeId() == TYPEID_PLAYER)
        {
            caster->CastSpell(caster, SPELL_WARLOCK_IMMOLATE_ENERGY, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_immolate_energy::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 47838 - Incinerate
class spell_warl_incinerate : public SpellScript
{
    PrepareSpellScript(spell_warl_incinerate);

    Aura* GetAshenRemainsAura(Unit* caster)
    {
        for (size_t i = 800972; i < 800978; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // Increases damage if target has Immolate.
        if (Aura* runeAura = GetAshenRemainsAura(caster))
        {
            int32 increasePct = runeAura->GetEffect(EFFECT_0)->GetAmount();

            if (target->HasAura(SPELL_WARLOCK_IMMOLATE))
                AddPct(damage, increasePct);
        }

        SetHitDamage(damage);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove one stack of Burn to Ashes listener each cast.
        for (size_t i = 801004; i < 801010; i++)
        {
            if (Aura* burnToAshesListener = caster->GetAura(i))
                burnToAshesListener->ModStackAmount(-1);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_incinerate::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_warl_incinerate::HandleAfterHit);
    }
};

class spell_warl_incinerate_energy : public AuraScript
{
    PrepareAuraScript(spell_warl_incinerate_energy);

    Aura* GetDiabolicEmbersAura(Unit* caster)
    {
        for (size_t i = 800992; i < 800998; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 soulPower = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_INCINERATE)->GetEffect(EFFECT_1).CalcValue();

        if (eventInfo.GetHitMask() == PROC_EX_CRITICAL_HIT)
            soulPower *= 2;

        // Chance to double Soul Power generated.
        if (Aura* runeAura = GetDiabolicEmbersAura(caster))
        {
            int32 procChance = runeAura->GetEffect(EFFECT_0)->GetAmount();
            int32 powerIncrease = runeAura->GetEffect(EFFECT_1)->GetAmount();

            if (roll_chance_i(procChance))
                AddPct(soulPower, powerIncrease);
        }

        caster->EnergizeBySpell(caster, SPELL_WARLOCK_INCINERATE_ENERGY, soulPower, POWER_ENERGY);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_incinerate_energy::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 47827 - Shadowburn
class spell_warl_shadowburn : public SpellScript
{
    PrepareSpellScript(spell_warl_shadowburn);

    Aura* GetChaosIncarnateAura(Unit* caster)
    {
        for (size_t i = 800928; i < 800934; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetAshenRemainsAura(Unit* caster)
    {
        for (size_t i = 800972; i < 800978; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // increase damage by random amount.
        if (Aura* runeAura = GetChaosIncarnateAura(caster))
        {
            int32 minAmount = runeAura->GetEffect(EFFECT_0)->GetAmount();
            int32 maxAmount = runeAura->GetEffect(EFFECT_1)->GetAmount();
            int32 increasePct = urand(minAmount, maxAmount);

            AddPct(damage, increasePct);
        }

        // Increases damage if target has Immolate.
        if (Aura* runeAura = GetAshenRemainsAura(caster))
        {
            int32 increasePct = runeAura->GetEffect(EFFECT_0)->GetAmount();

            if (target->HasAura(SPELL_WARLOCK_IMMOLATE))
                AddPct(damage, increasePct);
        }

        // Apply damage increase of Conflagration of Chaos if you have the buff.
        for (size_t i = 801034; i < 801040; i++)
            if (Aura* buff = caster->GetAura(i))
            {
                int32 critChance = std::max<int32>(caster->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_FIRE),
                    caster->GetFloatValue(static_cast<uint16>(PLAYER_SPELL_CRIT_PERCENTAGE1) + SPELL_SCHOOL_SHADOW));
                int32 critPct = buff->GetEffect(EFFECT_0)->GetAmount();
                int32 increasePct = CalculatePct(critChance, critPct);
                AddPct(damage, increasePct);
                buff->Remove();
            }

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_shadowburn::HandleHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warl_shadowburn_death : public AuraScript
{
    PrepareAuraScript(spell_warl_shadowburn_death);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        uint32 increase = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_SHADOWBURN)->GetEffect(EFFECT_0).CalcValue(GetCaster());
        caster->EnergizeBySpell(caster, SPELL_WARLOCK_SHADOWBURN, increase, POWER_ENERGY);
        caster->RemoveSpellCooldown(SPELL_WARLOCK_SHADOWBURN, true);

    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_shadowburn_death::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_soul_fire_energy : public SpellScript
{
    PrepareSpellScript(spell_warl_soul_fire_energy);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        uint32 increase = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_SOUL_FIRE)->GetEffect(EFFECT_1).CalcValue(GetCaster());
        caster->EnergizeBySpell(caster, SPELL_WARLOCK_SOUL_FIRE, increase, POWER_ENERGY);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_soul_fire_energy::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warl_power_siphon : public SpellScript
{
    PrepareSpellScript(spell_warl_power_siphon);


    Unit* GetPet()
    {
        Unit* controlledUnit = nullptr;
        if (Player* player = GetCaster()->ToPlayer())
            for (Unit::ControlSet::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                if (Unit* pet = (*itr))
                    if (pet->IsAlive() &&
                        pet->GetOwnerGUID() == player->GetGUID() &&
                        pet->GetEntry() == GUARDIAN_WARLOCK_WILD_IMP &&
                        pet->IsWithinDist(player, 100.0f, false))
                        controlledUnit = pet;

        return controlledUnit;
    }

    SpellCastResult CheckCast()
    {
        Unit* pet = GetPet();

        if (pet)
            return SPELL_CAST_OK;

        return SPELL_FAILED_NO_PET;
    }

    void HandleCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        uint32 maxSacrifice = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(caster);
        uint8 totalSacrifice = 0;
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        auto summonedUnits = player->m_Controlled;

        for (auto const& unit : summonedUnits)
        {
            if (!unit || unit->isDead())
                return;

            if (unit->GetEntry() == GUARDIAN_WARLOCK_WILD_IMP)
            {

                if (totalSacrifice >= maxSacrifice)
                    return;

                if (Aura* aura = caster->GetAura(SPELL_WARLOCK_DEMONBOLT_EMPOREWED))
                    aura->SetCharges(aura->GetCharges() + 1);
                else
                {
                    caster->CastCustomSpell(SPELL_WARLOCK_DEMONBOLT_EMPOREWED, SPELLVALUE_AURA_CHARGE, 1, caster, true);
                    unit->ToTempSummon()->UnSummon();
                    totalSacrifice++;
                }
            }
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warl_power_siphon::CheckCast);
        OnCast += SpellCastFn(spell_warl_power_siphon::HandleCast);
    }
};

class spell_warl_burning_rush : public AuraScript
{
    PrepareAuraScript(spell_warl_burning_rush);

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        uint32 healthPct = aurEff->GetBase()->GetEffect(EFFECT_1)->GetAmount();
        uint32 damage = CalculatePct(caster->GetMaxHealth(), healthPct);
        caster->CastCustomSpell(SPELL_WARLOCK_BURNING_RUSH_DAMAGE, SPELLVALUE_BASE_POINT0, damage, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_burning_rush::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_warl_malefic_rapture : public SpellScript
{
    PrepareSpellScript(spell_warl_malefic_rapture);

    void HandleCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        auto const& threatList = caster->getAttackers();
        auto threatListCopy = threatList;

        if (threatListCopy.empty()) return;

        int32 durationIncrease = 0;

        // Check for T1 4pc listener and remove stack/listener accordingly.
        if (Aura* T14pcListener = caster->GetAura(T1_WARLOCK_AFFLI_4PC_LISTENER))
        {
            if (Aura* t1_4pc_buff = caster->GetAura(T1_WARLOCK_AFFLI_4PC_BUFF))
                durationIncrease = t1_4pc_buff->GetEffect(EFFECT_0)->GetAmount();

            if (T14pcListener->GetStackAmount() > 1)
                T14pcListener->ModStackAmount(-1);
            else
                T14pcListener->SetDuration(50);
        }

        for (auto const& target : threatListCopy)
        {
            if (target)
            {
                auto targetAuras = target->GetAppliedAuras();

                for (auto itj = targetAuras.begin(); itj != targetAuras.end(); ++itj) {
                    if (Aura* aura = itj->second->GetBase())
                    {
                        if (caster->GetGUID() != aura->GetCasterGUID())
                            continue;

                        SpellInfo const* auraInfo = aura->GetSpellInfo();

                        if (auraInfo->SpellFamilyFlags[2] & 0x80000000 && auraInfo->SpellFamilyName == SPELLFAMILY_WARLOCK)
                        {
                            caster->CastSpell(target, SPELL_WARLOCK_MALEFIC_RAPTURE_DAMAGE, TRIGGERED_FULL_MASK);

                            if (durationIncrease > 0)
                                aura->SetDuration(aura->GetDuration() + durationIncrease);
                        }
                    }
                }
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warl_malefic_rapture::HandleCast);
    }
};

// 83021 - Malefic Rapture (damage)
class spell_warl_malefic_rapture_damage : public SpellScript
{
    PrepareSpellScript(spell_warl_malefic_rapture_damage);

    Aura* GetFocusedMalignancyAura(Unit* caster)
    {
        for (size_t i = 800560; i < 800566; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetDreadTouchAura(Unit* caster)
    {
        for (size_t i = 800578; i < 800584; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleDamage(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // If target has Unstable Affliction apply the Focused Malignancy rune damage increase.
        if (Aura* runeAura = GetFocusedMalignancyAura(caster))
            if (target->HasAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION))
            {
                int32 increase = runeAura->GetEffect(EFFECT_0)->GetAmount();
                AddPct(damage, increase);
            }

        // If target has Unstable Affliction apply the Dread Touch rune buff.
        if (Aura* runeAura = GetDreadTouchAura(caster))
            if (target->HasAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION))
                caster->CastSpell(target, RUNE_WARLOCK_DREAD_TOUCH_BUFF, TRIGGERED_FULL_MASK);

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_malefic_rapture_damage::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warl_soul_swap : public AuraScript
{
    PrepareAuraScript(spell_warl_soul_swap);

    struct CopyAura {
        uint32 spellId;
        int32 duration;
    };

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* target = player->GetSelectedUnit();

        if (target) {
            auto effects = target->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE);

            for (auto effect : effects) {
                uint32 spellId = effect->GetSpellInfo()->Id;
                int32 duration = effect->GetBase()->GetDuration();
                int32 amount = effect->GetAmount();
                CopyAura aura = { spellId, duration };
                aurasCopied.push_back(aura);
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes  mode)
    {
        Player* player = GetCaster()->ToPlayer();
        AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
        Unit* target = player->GetSelectedUnit();

        if (target) {
            for (auto aura : aurasCopied) {
                CustomSpellValues values;
                values.AddSpellMod(SPELLVALUE_AURA_DURATION, aura.duration);
                GetCaster()->CastCustomSpell(aura.spellId, values, target, TRIGGERED_FULL_MASK);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_soul_swap::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_warl_soul_swap::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }

private:
    std::list<CopyAura> aurasCopied;
};

class spell_warl_grimoire_of_sacrifice : public AuraScript
{
    PrepareAuraScript(spell_warl_grimoire_of_sacrifice);

    void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        int32 amount = GetCaster()->CalculateSpellDamageWithRatio(SPELL_SCHOOL_MASK_SHADOW, 0.375f);
        int32 chance = aurEff->GetAmount();

        if (roll_chance_i(chance)) {
            GetCaster()->CastSpell(GetCaster()->GetVictim(), SPELL_WARLOCK_GRIMOIRE_OF_SACRIFICE_DAMAGE, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_grimoire_of_sacrifice::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_channel_demonfire : public SpellScript
{
    PrepareSpellScript(spell_warl_channel_demonfire);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* immolate = target->GetAura(SPELL_WARLOCK_IMMOLATE))
            immolate->RefreshDuration();
        else
            caster->CastSpell(target, SPELL_WARLOCK_IMMOLATE, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_channel_demonfire::HandleDummy, EFFECT_1, SPELL_EFFECT_APPLY_AURA);
    }
};

class spell_warl_xavians_teachings : public AuraScript
{
    PrepareAuraScript(spell_warl_xavians_teachings);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        uint32 spell = aurEff->GetAmount();

        if (!GetCaster() || GetCaster()->isDead())
            return;

        GetCaster()->CastSpell(GetCaster()->ToPlayer()->GetSelectedUnit(), spell, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_xavians_teachings::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_agonizing_corruption : public SpellScript
{
    PrepareSpellScript(spell_warl_agonizing_corruption);

    void FindTargets(std::list<WorldObject*>& targets)
    {
        if (targets.size() > 0)
        {
            for (auto const& target : targets)
                if (Aura* agony = target->ToUnit()->GetAura(SPELL_WARLOCK_AGONY))
                {
                    uint32 increase = sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_SEED_OF_CORRUPTION_DETONATION)->GetEffect(EFFECT_1).CalcValue(GetCaster());
                    agony->ModStackAmount(increase);
                }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_agonizing_corruption::FindTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_warl_ritual_of_ruin : public AuraScript
{
    PrepareAuraScript(spell_warl_ritual_of_ruin);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || GetCaster()->isDead())
            return false;

        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->ManaCost > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 powerCost = eventInfo.GetSpellInfo()->ManaCost;
        int32 maxStacks = aurEff->GetAmount();

        if (Aura* stackAura = caster->GetAura(TALENT_WARLOCK_RITUAL_OF_RUIN_STACK))
        {
            uint32 stackAmount = stackAura->GetStackAmount() + powerCost;

            if (stackAmount >= maxStacks)
            {
                stackAmount -= maxStacks;
                caster->CastSpell(caster, TALENT_WARLOCK_RITUAL_OF_RUIN_BUFF, TRIGGERED_FULL_MASK);

                if (stackAmount == 0)
                    stackAura->Remove();
                else
                    stackAura->SetStackAmount(stackAmount);
            }
            else
                stackAura->ModStackAmount(powerCost);
        }
        else
            caster->CastCustomSpell(TALENT_WARLOCK_RITUAL_OF_RUIN_STACK, SPELLVALUE_AURA_STACK, powerCost, caster, true, nullptr, aurEff);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_ritual_of_ruin::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_ritual_of_ruin::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_molten_hand : public AuraScript
{
    PrepareAuraScript(spell_warl_molten_hand);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return false;

        return caster->IsAlive() && caster->GetCharmerOrOwnerPlayerOrPlayerItself()->IsAlive();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        uint32 rank = aurEff->GetAmount();
        Unit* owner = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself();

        if (rank == 1)
            owner->CastSpell(owner, TALENT_WARLOCK_MOLTEN_HAND_BUFF_R1, TRIGGERED_FULL_MASK);
        else if (rank == 2)
            owner->CastSpell(owner, TALENT_WARLOCK_MOLTEN_HAND_BUFF_R2, TRIGGERED_FULL_MASK);
        else
            owner->CastSpell(owner, TALENT_WARLOCK_MOLTEN_HAND_BUFF_R3, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_molten_hand::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_molten_hand::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 47809 - Shadow Bolt
class spell_warl_shadow_bolt : public SpellScript
{
    PrepareSpellScript(spell_warl_shadow_bolt);

    Aura* GetWitheringBoltAura(Unit* caster)
    {
        for (size_t i = 800304; i < 800310; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetSacrificedSoulsAura(Unit* caster)
    {
        for (size_t i = 800630; i < 800636; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // Check for Withering Bolt Rune Buff and apply damage increase per Dot.
        if (Aura* runeAura = GetWitheringBoltAura(caster))
        {
            int32 dotQte = 0;
            auto targetAuras = target->GetAppliedAuras();

            for (auto itr = targetAuras.begin(); itr != targetAuras.end(); ++itr)
                if (Aura* aura = itr->second->GetBase())
                {
                    if (aura->GetCaster() != caster)
                        continue;

                    SpellInfo const* auraInfo = aura->GetSpellInfo();

                    if (auraInfo->SpellFamilyFlags[2] & 0x80000000 && auraInfo->SpellFamilyName == SPELLFAMILY_WARLOCK)
                        dotQte++;
                }

            if (dotQte > 0)
            {
                int32 increasePct = runeAura->GetEffect(EFFECT_0)->GetAmount() * dotQte;

                AddPct(damage, increasePct);
            }
        }

        if (Player* player = caster->ToPlayer())
        {
            // Check for Sacrificed Souls Rune Buff and apply damage increase per demon summoned.
            if (Aura* runeAura = GetSacrificedSoulsAura(caster))
            {
                int32 summonQte = 0;
                auto summonedUnits = player->m_Controlled;

                for (auto const& unit : summonedUnits)
                {
                    if (unit->isDead())
                        continue;

                    summonQte++;
                }

                if (summonQte > 0)
                {
                    int32 increasePct = runeAura->GetEffect(EFFECT_0)->GetAmount() * summonQte;

                    AddPct(damage, increasePct);
                }
            }
        }


        SetHitDamage(damage);

        // Energize if in Demonology spec
        if (caster->HasAura(MASTERY_WARLOCK_MASTER_DEMONOLOGIST))
            caster->CastSpell(caster, SPELL_WARLOCK_SHADOW_BOLT_ENERGY, TRIGGERED_FULL_MASK);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Stolen Power buff.
        if (caster->HasAura(RUNE_WARLOCK_STOLEN_POWER_BUFF))
            caster->RemoveAura(RUNE_WARLOCK_STOLEN_POWER_BUFF);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_shadow_bolt::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_warl_shadow_bolt::HandleAfterHit);
    }
};

// 83213 - Infernal - Fel Fire
class spell_warl_infernal_immolation_aura_energy : public AuraScript
{
    PrepareAuraScript(spell_warl_infernal_immolation_aura_energy);

    /*void HandleDamage(AuraEffect const* aurEff)
    {
        Unit* infernal = GetAura()->GetOwner()->ToUnit();
        if (Unit* caster = infernal->GetOwner())
        {
            int32 spellDamage = caster->CalculateSpellDamageWithRatio(SPELL_SCHOOL_MASK_SHADOW, 0.4972f);
            infernal->CastCustomSpell(PET_SPELL_IMMOLATION_AURA_DAMAGE, SPELLVALUE_BASE_POINT0, spellDamage, infernal);
        }
    }*/

    void HandleEnergy(AuraEffect const* aurEff)
    {
        Unit* infernal = GetAura()->GetOwner()->ToUnit();
        if (Unit* caster = infernal->GetOwner())
            if (caster && caster->IsAlive())
                caster->EnergizeBySpell(caster, SPELL_WARLOCK_IMMOLATION_AURA_ENERGY, aurEff->GetAmount(), POWER_ENERGY);
    }

    void Register() override
    {
        /*OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_infernal_immolation_aura_energy::HandleDamage, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);*/
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_infernal_immolation_aura_energy::HandleEnergy, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_warl_soul_collector : public AuraScript
{
    PrepareAuraScript(spell_warl_soul_collector);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return (GetCaster() && GetCaster()->IsAlive());
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_SOUL_COLLECTOR_FRAGMENT, TRIGGERED_FULL_MASK);

        if (Unit* target = eventInfo.GetActionTarget())
        {
            if (Creature* creature = target->ToCreature())
                if (CreatureTemplate const* cinfo = creature->GetCreatureTemplate())
                    if (cinfo && cinfo->type == CREATURE_TYPE_DEMON)
                        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_SOUL_COLLECTOR_DEMON_BUFF, TRIGGERED_FULL_MASK);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_soul_collector::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_soul_collector::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_soul_collector_fragment : public AuraScript
{
    PrepareAuraScript(spell_warl_soul_collector_fragment);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && (eventInfo.GetSpellInfo()->PowerType == POWER_ENERGY && eventInfo.GetSpellInfo()->CalcPowerCost(GetCaster(), eventInfo.GetSchoolMask()) > 0))
            return true;

        return false;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || GetCaster()->isDead())
            return;

        GetAura()->ModStackAmount(-1);

        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_SOUL_COLLECTOR_HEAL, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_soul_collector_fragment::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_soul_collector_fragment::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_searing_pain_energy : public SpellScript
{
    PrepareSpellScript(spell_warl_searing_pain_energy);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (caster->HasAura(MASTERY_WARLOCK_FEL_BLOOD))
        {
            caster->CastSpell(caster, SPELL_WARLOCK_SEARING_PAIN_ENERGY, TRIGGERED_FULL_MASK);

            if (roll_chance_i(GetSpellInfo()->GetEffect(EFFECT_1).CalcValue()))
                caster->CastSpell(caster, SPELL_WARLOCK_SOUL_COLLECTOR_FRAGMENT, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_searing_pain_energy::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warl_immolation_aura_energy : public SpellScript
{
    PrepareSpellScript(spell_warl_immolation_aura_energy);

    void HandleCast()
    {
        if (!GetCaster() || GetCaster()->isDead())
            return;

        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_IMMOLATION_AURA_INITIAL_ENERGY, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warl_immolation_aura_energy::HandleCast);
    }
};

class spell_warl_fracture_energy : public SpellScript
{
    PrepareSpellScript(spell_warl_fracture_energy);

    void HandleCast()
    {
        if (!GetCaster() || GetCaster()->isDead())
            return;

        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_IMMOLATION_AURA_INITIAL_ENERGY, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_warl_fracture_energy::HandleCast);
    }
};

class spell_warl_demonic_barrier : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_barrier);

    Aura* GetWillPoweredAura(Unit* caster)
    {
        for (size_t i = 801450; i < 801456; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void ApplyEffect(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 healthPct = caster->GetHealthPct();
        int32 baseRatio = aurEff->GetAmount();
        int32 minimumThreshold = 20;
        float effectiveness;

        // Calculate the effectiveness of the shield depending on current health
        if (healthPct <= minimumThreshold)
            effectiveness = 100;
        if (healthPct > minimumThreshold)
            effectiveness = 100 * (100 - healthPct) / (100 - minimumThreshold);

        int32 shieldRatio = CalculatePct(baseRatio, effectiveness);
        int32 baseShield = CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), shieldRatio);

        // Consume faragments to increase shield
        if (Aura* soulFragment = caster->GetAura(SPELL_WARLOCK_SOUL_COLLECTOR_FRAGMENT))
        {
            int32 fragmentShieldPct = GetEffect(EFFECT_1)->GetAmount();
            int32 fragmentShield = CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), fragmentShieldPct);
            int32 fragmentAmount = soulFragment->GetStackAmount() * fragmentShield;
            baseShield += fragmentAmount;

            // Chance to not consume fragments.
            if (Aura* runeAura = GetWillPoweredAura(caster))
            {
                int32 procChance = runeAura->GetEffect(EFFECT_0)->GetAmount();

                if (!roll_chance_i(procChance))
                    soulFragment->Remove();
            }
            else
                soulFragment->Remove();
        }

        // Grants the right amount to the shield
        GetEffect(EFFECT_0)->ChangeAmount(baseShield);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_barrier::ApplyEffect, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_soul_bomb : public SpellScript
{
    PrepareSpellScript(spell_warl_soul_bomb);

    SpellCastResult CheckCast()
    {
        if (!GetCaster()->HasAura(SPELL_WARLOCK_SOUL_COLLECTOR_FRAGMENT))
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        return SPELL_CAST_OK;
    }

    void HandleCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 damage = CalculatePct(caster->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_FIRE), sSpellMgr->AssertSpellInfo(SPELL_WARLOCK_SOUL_BOMB)->GetEffect(EFFECT_0).CalcValue(caster));

        if (Aura* soulFragment = caster->GetAura(SPELL_WARLOCK_SOUL_COLLECTOR_FRAGMENT))
        {
            int32 stackAmount = soulFragment->GetStackAmount();

            if (stackAmount <= 3)
            {
                for (int i = 0; i < stackAmount; ++i)
                    caster->CastSpell(caster, SPELL_WARLOCK_SOUL_COLLECTOR_HEAL, TRIGGERED_FULL_MASK);

                damage *= stackAmount;
                soulFragment->Remove();
            }
            else
            {
                for (int i = 0; i < 3; ++i)
                    caster->CastSpell(caster, SPELL_WARLOCK_SOUL_COLLECTOR_HEAL, TRIGGERED_FULL_MASK);

                damage *= 3;
                soulFragment->ModStackAmount(-3);
            }
        }

        caster->CastCustomSpell(SPELL_WARLOCK_SOUL_BOMB_DAMAGE, SPELLVALUE_BASE_POINT0, damage, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warl_soul_bomb::CheckCast);
        OnCast += SpellCastFn(spell_warl_soul_bomb::HandleCast);
    }
};

// 83105 - Soul Bomb (damage)
class spell_warl_soul_bomb_damage : public SpellScript
{
    PrepareSpellScript(spell_warl_soul_bomb_damage);

    void HandleCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove Soul Furnace buff.
        for (size_t i = 801432; i < 801438; i++)
            if (caster->HasAura(i))
                caster->RemoveAura(i);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warl_soul_bomb_damage::HandleCast);
    }
};

class spell_warl_frailty : public AuraScript
{
    PrepareAuraScript(spell_warl_frailty);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || GetCaster()->isDead())
            return false;

        if (Unit* caster = eventInfo.GetActor())
        {
            if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 && eventInfo.GetSpellInfo() && caster->GetGUID() == GetCaster()->GetGUID())
                return true;
        }
        else
            return false;

        return false;
    }

    void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (Unit* actor = eventInfo.GetActor()) {
            if (actor->GetGUID() == GetCaster()->GetGUID()) {
                Unit* caster = GetCaster();
                int32 healPct = aurEff->GetAmount();
                int32 damage = eventInfo.GetDamageInfo()->GetDamage();
                int32 amount = CalculatePct(damage, healPct);

                if (amount <= 0)
                    return;

                caster->CastCustomSpell(SPELL_WARLOCK_FRAILTY_HEAL, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
            }
        }
    }
    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_frailty::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_frailty::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_fracture_fragment : public SpellScript
{
    PrepareSpellScript(spell_warl_fracture_fragment);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (!GetCaster() || GetCaster()->isDead())
            return;

        if (roll_chance_i(GetSpellInfo()->GetEffect(EFFECT_1).CalcValue()))
            GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_SOUL_COLLECTOR_FRAGMENT, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_fracture_fragment::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warl_demonkin : public AuraScript
{
    PrepareAuraScript(spell_warl_demonkin);

    void HandleLearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->removeSpell(SPELL_WARLOCK_SUMMON_FELHUNTER, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_SUMMON_IMP, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_SUMMON_SUCCUBUS, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_SUMMON_VOIDWALKER, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_EYE_OF_KILLROG, SPEC_MASK_ALL, false);
        target->learnSpell(SPELL_WARLOCK_IMMOLATION_AURA);
        target->learnSpell(SPELL_WARLOCK_SHADOW_CLEAVE);
        target->learnSpell(SPELL_WARLOCK_DEMON_CHARGE);
        target->learnSpell(SPELL_WARLOCK_SHROUD_OF_DARKNESS);
        target->learnSpell(SPELL_WARLOCK_SOUL_BOMB);
        target->learnSpell(SPELL_WARLOCK_METAMORPHOSIS);

        target->UnsummonPetTemporaryIfAny();
    }

    void HandleUnlearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->removeSpell(SPELL_WARLOCK_IMMOLATION_AURA, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_SHADOW_CLEAVE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_DEMON_CHARGE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_SHROUD_OF_DARKNESS, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_SOUL_BOMB, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_WARLOCK_METAMORPHOSIS, SPEC_MASK_ALL, false);
        target->learnSpell(SPELL_WARLOCK_SUMMON_FELHUNTER);
        target->learnSpell(SPELL_WARLOCK_SUMMON_IMP);
        target->learnSpell(SPELL_WARLOCK_SUMMON_SUCCUBUS);
        target->learnSpell(SPELL_WARLOCK_SUMMON_VOIDWALKER);
        target->learnSpell(SPELL_WARLOCK_EYE_OF_KILLROG);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_demonkin::HandleLearn, EFFECT_0, SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_demonkin::HandleUnlearn, EFFECT_0, SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_demonic_protection_mastery : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_protection_mastery);

    Aura* GetCalcifiedShieldAura(Unit* caster)
    {
        for (size_t i = 801258; i < 801264; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* aura = caster->GetAura(MASTERY_WARLOCK_FEL_BLOOD))
        {
            int32 amount = aura->GetEffect(EFFECT_0)->GetAmount() + caster->ToPlayer()->GetMastery();

            caster->CastCustomSpell(SPELL_WARLOCK_DEMONIC_PROTECTION_MASTERY_BUFF, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Cast Calcified Shield rune damage reduction.
        if (Aura* runeAura = GetCalcifiedShieldAura(caster))
        {
            int32 stacks = runeAura->GetEffect(EFFECT_0)->GetAmount();
            caster->CastCustomSpell(RUNE_WARLOCK_CALCIFIED_SHIELD_BUFF, SPELLVALUE_AURA_STACK, stacks, caster, TRIGGERED_FULL_MASK);
        }

        if (Aura* aura = GetCaster()->GetAura(SPELL_WARLOCK_DEMONIC_PROTECTION_MASTERY_BUFF))
            aura->Remove();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_protection_mastery::HandleApply, EFFECT_0, SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_demonic_protection_mastery::HandleRemove, EFFECT_0, SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warl_chaos_brand : public AuraScript
{
    PrepareAuraScript(spell_warl_chaos_brand);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || GetCaster()->isDead())
            return false;

        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->CastSpell(eventInfo.GetActionTarget(), aurEff->GetAmount(), TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_chaos_brand::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_chaos_brand::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_demonic_thirst : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_thirst);

    void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || GetCaster()->isDead())
            return;

        GetCaster()->ToPlayer()->ModifySpellCooldown(SPELL_WARLOCK_DEMONIC_PROTECTION, aurEff->GetAmount());
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_warl_demonic_thirst::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_demon_spikes : public AuraScript
{
    PrepareAuraScript(spell_warl_demon_spikes);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActor();
        if (!target || !target->IsAlive())
            return false;

        Unit* caster = eventInfo.GetActionTarget();
        if (!caster || !caster->IsAlive())
            return false;

        if (!GetCaster()->HasAura(SPELL_WARLOCK_DEMONIC_PROTECTION))
            return false;

        return target != caster;
    }

    void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        int32 damage = CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), aurEff->GetAmount());
        caster->CastCustomSpell(TALENT_WARLOCK_DEMON_SPIKES_DAMAGE, SPELLVALUE_BASE_POINT0, damage, eventInfo.GetActor(), TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_demon_spikes::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_demon_spikes::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_forced_ascension : public AuraScript
{
    PrepareAuraScript(spell_warl_forced_ascension);

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* victim = GetTarget();

        if (!victim || victim->isDead())
            return;

        int32 remainingHealth = victim->GetHealth() - dmgInfo.GetDamage();

        if (remainingHealth <= 0 && !victim->HasAura(TALENT_WARLOCK_FORCED_ASCENSION_COOLDOWN))
        {
            absorbAmount = dmgInfo.GetDamage();
            victim->CastSpell(victim, SPELL_WARLOCK_DEMONIC_ASCENSION, TRIGGERED_FULL_MASK);
            victim->CastSpell(victim, TALENT_WARLOCK_FORCED_ASCENSION_COOLDOWN, TRIGGERED_FULL_MASK);
        }
        else
            absorbAmount = 0;
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_warl_forced_ascension::Absorb, EFFECT_0);
    }
};

class spell_warl_archdemon : public AuraScript
{
    PrepareAuraScript(spell_warl_archdemon);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || GetCaster()->isDead() || GetCaster()->HasAura(TALENT_WARLOCK_ARCHDEMON_COOLDOWN))
            return false;

        return true;
    }

    void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->CastSpell(eventInfo.GetActionTarget(), TALENT_WARLOCK_ARCHDEMON_MARK, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_archdemon::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_archdemon::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warl_archdemon_proc : public AuraScript
{
    PrepareAuraScript(spell_warl_archdemon_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || GetCaster()->isDead() || GetCaster()->HasAura(TALENT_WARLOCK_ARCHDEMON_COOLDOWN))
            return false;

        if (Unit* caster = eventInfo.GetActor())
        {
            if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0 && eventInfo.GetSpellInfo() && caster->GetGUID() == GetCaster()->GetGUID())
                return true;
        }
        else
            return false;

        return false;
    }

    void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        caster->CastSpell(GetAura()->GetOwner()->ToUnit(), TALENT_WARLOCK_ARCHDEMON_DAMAGE, TRIGGERED_FULL_MASK);
        caster->CastSpell(caster, TALENT_WARLOCK_ARCHDEMON_COOLDOWN, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warl_archdemon_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warl_archdemon_proc::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 47813 - Corruption
class spell_warl_corruption : public AuraScript
{
    PrepareAuraScript(spell_warl_corruption);

    Aura* GetAbsoluteCorruptionAura(Unit* caster)
    {
        for (size_t i = 800138; i < 800144; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* runeAura = GetAbsoluteCorruptionAura(caster))
        {
            int32 duration = runeAura->GetEffect(EFFECT_2)->GetAmount();

            if (target->IsPlayer())
                SetDuration(duration);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_corruption::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 47857 - Drain Life
class spell_warl_drain_life : public AuraScript
{
    PrepareAuraScript(spell_warl_drain_life);

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        GetEffect(EFFECT_0)->RecalculateAmount();
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        // Remove Inevitable Demise Rune Buff
        for (size_t i = 800162; i < 800168; i++)
            if (caster->HasAura(i))
                caster->RemoveAura(i);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_life::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_LEECH);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_drain_life::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_LEECH, AURA_EFFECT_HANDLE_REAL);
    }
};

// 83028 - Demonbolt
class spell_warl_demonbolt : public SpellScript
{
    PrepareSpellScript(spell_warl_demonbolt);

    Aura* GetSacrificedSoulsAura(Unit* caster)
    {
        for (size_t i = 800630; i < 800636; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleBeforeCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            // Check T1 2pc and reduce Grimoire: Felguard cooldown.
            if (Aura* setT1_2pc = player->GetAura(RUNE_WARLOCK_STOLEN_POWER_BUFF))
            {
                int32 cooldown = setT1_2pc->GetEffect(EFFECT_0)->GetAmount();
                player->ModifySpellCooldown(SPELL_WARLOCK_GRIMOIRE_FELGUARD, -cooldown);
            }
        }
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        if (Player* player = caster->ToPlayer())
        {
            player->EnergizeBySpell(caster, SPELL_WARLOCK_DEMONBOLT, GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(caster), POWER_ENERGY);

            if (Aura* aura = caster->GetAura(SPELL_WARLOCK_DEMONIC_CORE_BUFF))
            {
                aura->ModCharges(-1);

                if (Aura* set_T1_2pc = caster->GetAura(T1_WARLOCK_DEMONO_2PC))
                {
                    int32 cooldown = set_T1_2pc->GetEffect(EFFECT_0)->GetAmount();
                    player->ModifySpellCooldown(SPELL_WARLOCK_GRIMOIRE_FELGUARD, -cooldown);
                }
            }

            // Check for Sacrificed Souls Rune Buff and apply damage increase per demon summoned.
            if (Aura* runeAura = GetSacrificedSoulsAura(caster))
            {
                int32 summonQte = 0;
                auto summonedUnits = player->m_Controlled;

                for (auto const& unit : summonedUnits)
                {
                    if (unit->isDead())
                        continue;

                    summonQte++;
                }

                if (summonQte > 0)
                {
                    int32 increasePct = runeAura->GetEffect(EFFECT_0)->GetAmount() * summonQte;

                    AddPct(damage, increasePct);
                }
            }
        }

        SetHitDamage(damage);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Stolen Power buff.
        if (caster->HasAura(RUNE_WARLOCK_STOLEN_POWER_BUFF))
            caster->RemoveAura(RUNE_WARLOCK_STOLEN_POWER_BUFF);
    }

    void Register() override
    {
        BeforeCast += SpellCastFn(spell_warl_demonbolt::HandleBeforeCast);
        OnEffectHitTarget += SpellEffectFn(spell_warl_demonbolt::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_warl_demonbolt::HandleAfterHit);
    }
};

// 47820 - Rain of Fire
class spell_warl_rain_of_fire : public AuraScript
{
    PrepareAuraScript(spell_warl_rain_of_fire);

    Aura* GetMadnessoftheAzjAqirAura(Unit* caster)
    {
        for (size_t i = 800904; i < 800910; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Cast Madness of the Azj'Aqir Buff.
        if (Aura* runeAura = GetMadnessoftheAzjAqirAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_1)->GetAmount();

            caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
        }

        // remove Ritual of Ruin buff.
        if (caster->HasAura(TALENT_WARLOCK_RITUAL_OF_RUIN_BUFF))
            caster->RemoveAura(TALENT_WARLOCK_RITUAL_OF_RUIN_BUFF);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove one stack of Crashing Fire listener when it ends.
        for (size_t i = 801196; i < 801202; i++)
            if (Aura* crashingChaosListener = caster->GetAura(i))
                crashingChaosListener->ModStackAmount(-1);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_rain_of_fire::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_rain_of_fire::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 47818 - Rain of Fire (damage)
class spell_warl_rain_of_fire_damage : public SpellScript
{
    PrepareSpellScript(spell_warl_rain_of_fire_damage);

    Aura* GetChaosIncarnateAura(Unit* caster)
    {
        for (size_t i = 800928; i < 800934; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 damage = GetHitDamage();

        if (Aura* runeAura = GetChaosIncarnateAura(caster))
        {
            int32 minAmount = runeAura->GetEffect(EFFECT_0)->GetAmount();
            int32 maxAmount = runeAura->GetEffect(EFFECT_1)->GetAmount();
            int32 increasePct = urand(minAmount, maxAmount);

            AddPct(damage, increasePct);
        }

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_rain_of_fire_damage::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warl_demonic_strength : public SpellScript
{
    PrepareSpellScript(spell_warl_demonic_strength);

    Unit* GetPet()
    {
        Unit* controlledUnit = nullptr;
        if (Player* player = GetCaster()->ToPlayer())
            for (Unit::ControlSet::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                if (Unit* pet = (*itr))
                    if (pet->IsAlive() &&
                        pet->GetOwnerGUID() == player->GetGUID() &&
                        pet->GetEntry() == PET_WARLOCK_FELGUARD &&
                        pet->IsWithinDist(player, 100.0f, false))
                        controlledUnit = pet;

        return controlledUnit;
    }

    SpellCastResult CheckCast()
    {
        if (Unit* pet = GetPet())
            return SPELL_CAST_OK;

        return SPELL_FAILED_NO_PET;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_warl_demonic_strength::CheckCast);
    }
};

// 83112 - Demonic Devastation
class spell_warl_demonic_devastation : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_devastation);

    Aura* GetDiabolicalAura(Unit* caster)
    {
        for (size_t i = 801246; i < 801252; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Cast Demonic Ascension if not already under it's effect and give custom duration.
        if (Aura* runeAura = GetDiabolicalAura(caster))
            if (!caster->HasAura(SPELL_WARLOCK_DEMONIC_ASCENSION))
                if (Aura* ascension = caster->AddAura(SPELL_WARLOCK_DEMONIC_ASCENSION, caster))
                {
                    int32 duration = runeAura->GetEffect(EFFECT_0)->GetAmount();
                    ascension->SetDuration(duration);
                }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_demonic_devastation::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

// 83113 - Demonic Devastation Damage
class spell_warl_demonic_devastation_damage : public SpellScript
{
    PrepareSpellScript(spell_warl_demonic_devastation_damage);

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        caster->CastSpell(caster, SPELL_WARLOCK_DEMONIC_DEVASTATION_HEAL, TRIGGERED_FULL_MASK);

        int32 damage = GetHitDamage();

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warl_demonic_devastation_damage::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 83110 - Demonic Ascension
class spell_warl_demonic_ascension : public AuraScript
{
    PrepareAuraScript(spell_warl_demonic_ascension);

    Aura* GetIllidansDynastyAura(Unit* caster)
    {
        for (size_t i = 801284; i < 801290; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Cast Illidan's Dynasty Buff.
        if (Aura* runeAura = GetIllidansDynastyAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

            caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove Illidan's Dynasty buff.
        for (size_t i = 801290; i < 801296; i++)
            if (caster->HasAura(i))
                caster->RemoveAura(i);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_ascension::HandleApply, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_demonic_ascension::HandleRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 83108 - Fiery Symbol
class spell_warl_fiery_symbol : public AuraScript
{
    PrepareAuraScript(spell_warl_fiery_symbol);

    Aura* GetRevelinPainAura(Unit* caster)
    {
        for (size_t i = 801296; i < 801302; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetFieryDemiseAura(Unit* caster)
    {
        for (size_t i = 801304; i < 801310; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        // Cast Fiery Demise Buff.
        if (Aura* runeAura = GetFieryDemiseAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

            caster->CastSpell(target, procSpell, TRIGGERED_FULL_MASK);
        }
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        // T1 4pc, when it procs deal damage + shatter a Soul Fragment.
        if (Aura* setT1_4pc = caster->GetAura(T1_WARLOCK_DEMONBOUND_4PC))
        {
            int32 procChance = setT1_4pc->GetEffect(EFFECT_2)->GetAmount();

            if (roll_chance_i(procChance))
            {
                caster->CastSpell(target, T1_WARLOCK_DEMONBOUND_4PC_DAMAGE, TRIGGERED_FULL_MASK);
                caster->CastSpell(caster, SPELL_WARLOCK_SOUL_COLLECTOR_FRAGMENT, TRIGGERED_FULL_MASK);
            }
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        // Cast Revel in Pain Shield.
        if (Aura* runeAura = GetRevelinPainAura(caster))
        {
            int32 amount = runeAura->GetEffect(EFFECT_2)->GetAmount();
            int32 maxShield = CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), runeAura->GetEffect(EFFECT_1)->GetAmount());
            amount = std::min<int32>(amount, maxShield);

            caster->CastCustomSpell(RUNE_WARLOCK_REVEL_IN_PAIN_SHIELD, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
        }

        // remove Fiery Demise buff.
        for (size_t i = 801310; i < 801316; i++)
            if (target->HasAura(i))
                target->RemoveAura(i);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_fiery_symbol::HandleApply, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_fiery_symbol::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_fiery_symbol::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 50589 - Immolation Aura
class spell_warl_immolation_aura : public AuraScript
{
    PrepareAuraScript(spell_warl_immolation_aura);

    Aura* GetInfernalArmorAura(Unit* caster)
    {
        for (size_t i = 801372; i < 801378; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Cast Infernal Armor Buff.
        if (Aura* runeAura = GetInfernalArmorAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

            caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove Infernal Armor buff.
        for (size_t i = 801378; i < 801384; i++)
            if (caster->HasAura(i))
                caster->RemoveAura(i);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_immolation_aura::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_immolation_aura::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
    }
};

// 50581 - Shadow Cleave
class spell_warlock_shadow_cleave : public SpellScript
{
    PrepareSpellScript(spell_warlock_shadow_cleave);

    Aura* GetFocusedCleaveAura(Unit* caster)
    {
        for (size_t i = 801438; i < 801444; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // Increase damage on main target.
        if (Aura* runeAura = GetFocusedCleaveAura(caster))
        {
            Unit* mainTarget = ObjectAccessor::GetUnit(*caster, caster->GetTarget());

            if (mainTarget && target == mainTarget)
            {
                int32 damageIncrease = runeAura->GetEffect(EFFECT_0)->GetAmount();
                AddPct(damage, damageIncrease);
            }
        }

        SetHitDamage(damage);
    }

    void HandleCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove Soul Furnace buff.
        for (size_t i = 801432; i < 801438; i++)
            if (caster->HasAura(i))
                caster->RemoveAura(i);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_warlock_shadow_cleave::HandleCast);
        OnEffectHitTarget += SpellEffectFn(spell_warlock_shadow_cleave::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_warlock_voidwalker_sacrifice_shield : public AuraScript
{
    PrepareAuraScript(spell_warlock_voidwalker_sacrifice_shield);

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        canBeRecalculated = false;
        SpellSchoolMask schoolMask = GetSpellInfo()->GetSchoolMask();
        float newAmount = CalculatePct(caster->SpellBaseDamageBonusDone(schoolMask), aurEff->GetAmount());

        newAmount *= caster->SpellBaseHealingBonusDone(schoolMask);

        amount = newAmount;
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warlock_voidwalker_sacrifice_shield::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
    }
};

// 83208 - Shadow Blast
class spell_warlock_darkglare_shadow_blast : public SpellScript
{
    PrepareSpellScript(spell_warlock_darkglare_shadow_blast);

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* pet = GetCaster();

        if (!pet || pet->isDead())
            return;

        Unit* owner = pet->GetOwner();

        if (!owner || owner->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // 25% damage increase for each dot on the target
        if (uint8 count = target->GetDoTsByCaster(owner->GetGUID()))
        {
            int32 increasePct = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(owner);
            AddPct(damage, increasePct * count);
        }

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warlock_darkglare_shadow_blast::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 83211 - Doom Bolt
class spell_warlock_doomguard_doom_bolt : public SpellScript
{
    PrepareSpellScript(spell_warlock_doomguard_doom_bolt);

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* pet = GetCaster();

        if (!pet || pet->isDead())
            return;

        Unit* owner = pet->GetOwner();

        if (!owner || owner->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // 20% damage increase on target under 20% health
        int32 increasePct = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(owner);
        int32 healthThreshold = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(owner);

        if (target->GetHealthPct() <= healthThreshold)
            AddPct(damage, increasePct);

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warlock_doomguard_doom_bolt::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 54053 - Shadow Bite
class spell_warlock_felhunter_shadow_bite : public SpellScript
{
    PrepareSpellScript(spell_warlock_felhunter_shadow_bite);

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* pet = GetCaster();

        if (!pet || pet->isDead())
            return;

        Unit* owner = pet->GetOwner();

        if (!owner || owner->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        // 15% damage increase for each dot on the target
        if (uint8 count = target->GetDoTsByCaster(owner->GetGUID()))
        {
            int32 increasePct = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(owner);
            AddPct(damage, increasePct * count);
        }

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warlock_felhunter_shadow_bite::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 54037 - 54038 - Improved Felhunter
// 54425 - Improved Felhunter proc
class spell_warlock_improved_felhunter_proc : public AuraScript
{
    PrepareAuraScript(spell_warlock_improved_felhunter_proc);

    Aura* GetImprovedFelhunterAura(Unit* caster)
    {
        if (caster->HasAura(TALENT_WARLOCK_IMPROVED_FELHUNTER_R1))
            return caster->GetAura(TALENT_WARLOCK_IMPROVED_FELHUNTER_R1);

        if (caster->HasAura(TALENT_WARLOCK_IMPROVED_FELHUNTER_R2))
            return caster->GetAura(TALENT_WARLOCK_IMPROVED_FELHUNTER_R2);

        return nullptr;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* pet = GetUnitOwner();

        if (!pet || pet->isDead())
            return;

        Unit* caster = pet->GetOwner();

        if (!caster || caster->isDead())
            return;

        if (Aura* talentAura = GetImprovedFelhunterAura(caster))
        {
            if (caster->GetPower(POWER_ENERGY) < 100)
            {
                int32 amount = talentAura->GetEffect(EFFECT_0)->GetAmount();
                pet->ModifyPower(POWER_ENERGY, amount);
            }
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_warlock_improved_felhunter_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_warlock_improved_felhunter_proc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_warlock_flame_nourish_target : public SpellScript
{
    PrepareSpellScript(spell_warlock_flame_nourish_target);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* pet = GetCaster();

        if (!pet || pet->isDead())
            return;

        targets.remove(pet);

        Unit* caster = pet->GetOwner();

        if (!caster || caster->isDead())
            return;

        auto controlledList = caster->m_Controlled;

        targets.remove_if([&](WorldObject* target) -> bool
            {
                Unit* unit = target->ToUnit();
        return controlledList.find(unit) == controlledList.end();
            });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warlock_flame_nourish_target::FilterTargets, EFFECT_ALL, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 83069 - 83070 - Nightfall cast time/activation time reduction
class spell_warlock_nightfall_duration : public AuraScript
{
    PrepareAuraScript(spell_warlock_nightfall_duration);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        caster->AddAura(TALENT_WARLOCK_NIGHTFALL_BUFF, caster);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(TALENT_WARLOCK_NIGHTFALL_BUFF))
            caster->RemoveAura(TALENT_WARLOCK_NIGHTFALL_BUFF);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warlock_nightfall_duration::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_warlock_nightfall_duration::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warlock_foul_flame_target : public SpellScript
{
    PrepareSpellScript(spell_warlock_foul_flame_target);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove(GetExplTargetUnit());
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warlock_foul_flame_target::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_warl_ruin_pet : public AuraScript
{
    PrepareAuraScript(spell_warl_ruin_pet);

    Aura* GetTalentAura(Player* caster)
    {
        for (size_t i = 83224; i < 83229; i++)
        {
            if (caster->HasSpell(i))
                return caster->GetAura(i);
        }
        return nullptr;
    }

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        caster->learnSpell(GetAura()->GetEffect(EFFECT_1)->GetAmount());
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        if (Aura* talent = GetTalentAura(caster))
            caster->removeSpell(talent->GetId(), SPEC_MASK_ALL, false);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_warl_ruin_pet::HandleApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_warl_ruin_pet::HandleRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_warlock_vile_taint : public SpellScript
{
    PrepareSpellScript(spell_warlock_vile_taint);

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        caster->AddAura(SPELL_WARLOCK_AGONY, target);
        caster->AddAura(SPELL_WARLOCK_CURSE_OF_EXHAUSTION, target);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_warlock_vile_taint::HandleHit, EFFECT_0, SPELL_EFFECT_PERSISTENT_AREA_AURA);
    }
};

void AddSC_warlock_spell_scripts()
{
    RegisterSpellScript(spell_warl_eye_of_kilrogg);
    RegisterSpellScript(spell_warl_shadowflame);
    RegisterSpellScript(spell_warl_seduction);
    RegisterSpellScript(spell_warl_improved_demonic_tactics);
    RegisterSpellScript(spell_warl_ritual_of_summoning);
    RegisterSpellScript(spell_warl_demonic_aegis);
    RegisterSpellScript(spell_warl_demonic_knowledge);
    RegisterSpellScript(spell_warl_generic_scaling);
    RegisterSpellScript(spell_warl_infernal_scaling);
    RegisterSpellScript(spell_warl_banish);
    RegisterSpellScript(spell_warl_create_healthstone);
    RegisterSpellScript(spell_warl_curse_of_doom);
    RegisterSpellScript(spell_warl_demonic_circle_summon);
    RegisterSpellScript(spell_warl_demonic_circle_teleport);
    RegisterSpellScript(spell_warl_demonic_empowerment);
    RegisterSpellScript(spell_warl_everlasting_affliction);
    RegisterSpellScript(spell_warl_fel_synergy);
    RegisterSpellScript(spell_warl_glyph_of_shadowflame);
    //RegisterSpellAndAuraScriptPair(spell_warl_haunt, spell_warl_haunt_aura);
    //RegisterSpellScript(spell_warl_health_funnel);
    //RegisterSpellScript(spell_warl_life_tap);
    RegisterSpellScript(spell_warl_ritual_of_doom_effect);
    RegisterSpellScript(spell_warl_seed_of_corruption);
    RegisterSpellScript(spell_warl_seed_of_corruption_handler);
    RegisterSpellScript(spell_warl_seed_of_corruption_explosion);
    RegisterSpellScript(spell_warl_shadow_ward);
    RegisterSpellScript(spell_warl_siphon_life);
    RegisterSpellScript(spell_warl_soulshatter);
    RegisterSpellScript(spell_warl_unstable_affliction);
    RegisterSpellScript(spell_warl_drain_soul);
    RegisterSpellScript(spell_warlock_summon_darkglare);
    RegisterSpellScript(spell_warlock_summon_darkhound);
    RegisterSpellScript(spell_warlock_call_dreadstalkers_aura);
    RegisterSpellScript(spell_warlock_hand_of_guldan);
    RegisterSpellScript(spell_warlock_summon_felboar);
    RegisterSpellScript(spell_warlock_summon_felguard);
    RegisterSpellScript(spell_warl_grimoire_felguard_aura);
    RegisterSpellScript(spell_warlock_summon_demonic_tyrant);
    RegisterSpellScript(spell_warl_agony);
    RegisterSpellScript(spell_warlock_dark_pact);
    RegisterSpellScript(spell_warl_demon_armor);
    RegisterSpellScript(spell_warl_fel_armor);
    RegisterSpellScript(spell_warl_health_funnel_new);
    RegisterSpellScript(spell_warl_haunt);
    RegisterSpellScript(spell_warl_chaos_bolt);
    RegisterSpellScript(spell_warl_conflagrate);
    RegisterSpellScript(spell_warl_immolate_energy);
    RegisterSpellScript(spell_warl_incinerate);
    RegisterSpellScript(spell_warl_incinerate_energy);
    RegisterSpellScript(spell_warl_shadowburn);
    RegisterSpellScript(spell_warl_shadowburn_death);
    RegisterSpellScript(spell_warl_soul_fire_energy);
    RegisterSpellScript(spell_warl_burning_rush);
    RegisterSpellScript(spell_warl_malefic_rapture);
    RegisterSpellScript(spell_warl_malefic_rapture_damage);
    RegisterSpellScript(spell_warl_grimoire_of_sacrifice);
    RegisterSpellScript(spell_warl_channel_demonfire);
    RegisterSpellScript(spell_warlock_soul_strike);
    RegisterSpellScript(spell_warl_nether_portal_proc);
    RegisterSpellScript(spell_warlock_summon_nether_portal);
    RegisterSpellScript(spell_warl_pit_lord_scaling);
    RegisterSpellScript(spell_warlock_implosion);
    RegisterSpellScript(spell_warl_power_siphon);
    RegisterSpellScript(spell_warlock_summon_gargoyle);
    RegisterSpellScript(spell_warl_havoc);
    RegisterSpellScript(spell_warl_soul_power);
    RegisterSpellScript(spell_warl_soul_swap);
    RegisterSpellScript(spell_warlock_cataclysm);
    RegisterSpellScript(spell_warl_xavians_teachings);
    RegisterSpellScript(spell_warl_agonizing_corruption);
    RegisterSpellScript(spell_warl_ritual_of_ruin);
    RegisterSpellScript(spell_warl_molten_hand);
    //RegisterSpellScript(spell_warl_all_minion_scaling);
    RegisterSpellScript(spell_warl_shadow_bolt);
    RegisterSpellScript(spell_warl_infernal_immolation_aura_energy);
    RegisterSpellScript(spell_warl_soul_collector);
    RegisterSpellScript(spell_warl_searing_pain_energy);
    RegisterSpellScript(spell_warl_demonic_barrier);
    RegisterSpellScript(spell_warl_soul_collector_fragment);
    RegisterSpellScript(spell_warl_soul_bomb);
    RegisterSpellScript(spell_warl_soul_bomb_damage);
    RegisterSpellScript(spell_warl_frailty);
    RegisterSpellScript(spell_warl_fracture_fragment);
    RegisterSpellScript(spell_warl_demonkin);
    RegisterSpellScript(spell_warl_demonic_protection_mastery);
    RegisterSpellScript(spell_warl_chaos_brand);
    RegisterSpellScript(spell_warl_demonic_thirst);
    RegisterSpellScript(spell_warl_immolation_aura_energy);
    RegisterSpellScript(spell_warl_demon_spikes);
    RegisterSpellScript(spell_warl_forced_ascension);
    RegisterSpellScript(spell_warl_archdemon);
    RegisterSpellScript(spell_warl_archdemon_proc);
    RegisterSpellScript(spell_warl_fracture_energy);
    RegisterSpellScript(spell_warl_corruption);
    RegisterSpellScript(spell_warl_drain_life);
    RegisterSpellScript(spell_warl_demonbolt);
    RegisterSpellScript(spell_warl_rain_of_fire);
    RegisterSpellScript(spell_warl_rain_of_fire_damage);
    RegisterSpellScript(spell_warl_demonic_strength);
    RegisterSpellScript(spell_warl_demonic_devastation);
    RegisterSpellScript(spell_warl_demonic_devastation_damage);
    RegisterSpellScript(spell_warl_demonic_ascension);
    RegisterSpellScript(spell_warl_fiery_symbol);
    RegisterSpellScript(spell_warl_immolation_aura);
    RegisterSpellScript(spell_warlock_shadow_cleave);
    RegisterSpellScript(spell_warlock_voidwalker_sacrifice_shield);
    RegisterSpellScript(spell_warlock_darkglare_shadow_blast);
    RegisterSpellScript(spell_warlock_doomguard_doom_bolt);
    RegisterSpellScript(spell_warlock_felhunter_shadow_bite);
    RegisterSpellScript(spell_warlock_improved_felhunter_proc);
    RegisterSpellScript(spell_warlock_flame_nourish_target);
    RegisterSpellScript(spell_warlock_nightfall_duration);
    RegisterSpellScript(spell_warlock_foul_flame_target);
    RegisterSpellScript(spell_warl_ruin_pet);
    RegisterSpellScript(spell_warlock_vile_taint);
}
