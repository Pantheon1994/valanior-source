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
  * Scripts for spells with SPELLFAMILY_PALADIN and SPELLFAMILY_GENERIC spells used by paladin players.
  * Ordered alphabetically using scriptname.
  * Scriptnames of files in this file should be prefixed with "spell_pal_".
  */

#include "Group.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "UnitAI.h"
#include "SpellAuras.h"
#include "SpellAuraDefines.h"
#include "Unit.h"

enum PaladinSpells
{
    SPELL_PALADIN_DIVINE_PLEA = 54428,
    SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF = 67480,
    SPELL_PALADIN_BLESSING_OF_SANCTUARY_ENERGIZE = 57319,

    SPELL_PALADIN_HOLY_SHOCK_R1 = 48825,
    SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE = 25912,
    SPELL_PALADIN_HOLY_SHOCK_R1_HEALING = 25914,

    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID = 37878,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN = 37879,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST = 37880,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN = 37881,

    SPELL_PALADIN_DIVINE_STORM = 53385,
    SPELL_PALADIN_DIVINE_STORM_DUMMY = 54171,
    SPELL_PALADIN_DIVINE_STORM_HEAL = 54172,

    SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE = 25997,

    SPELL_PALADIN_FORBEARANCE = 25771,

    SPELL_PALADIN_HAND_OF_SACRIFICE = 6940,
    SPELL_PALADIN_DIVINE_SACRIFICE = 64205,

    SPELL_PALADIN_INFUSION_OF_LIGHT_R1 = 53672,
    SPELL_PALADIN_INFUSION_OF_LIGHT_R2 = 54149,

    SPELL_PALADIN_JUDGEMENT_DAMAGE = 54158,
    SPELL_PALADIN_JUDGEMENT_OF_JUSTICE = 20184,
    SPELL_PALADIN_JUDGEMENT_OF_LIGHT = 20185,
    SPELL_PALADIN_JUDGEMENT_OF_WISDOM = 20186,

    SPELL_PALADIN_GLYPH_OF_SALVATION = 63225,

    SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT = 31790,

    SPELL_PALADIN_SANCTIFIED_WRATH = 57318,
    SPELL_PALADIN_SANCTIFIED_WRATH_TALENT_R1 = 53375,

    SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS = 25742,
    SPELL_PALADIN_CONCENTRACTION_AURA = 19746,
    SPELL_PALADIN_SANCTIFIED_RETRIBUTION_R1 = 31869,
    SPELL_PALADIN_SWIFT_RETRIBUTION_R1 = 53379,
    SPELL_PALADIN_IMPROVED_CONCENTRACTION_AURA = 63510,
    SPELL_PALADIN_IMPROVED_DEVOTION_AURA = 63514,
    SPELL_PALADIN_SANCTIFIED_RETRIBUTION_AURA = 63531,
    SPELL_PALADIN_AURA_MASTERY_IMMUNE = 64364,

    SPELL_GENERIC_ARENA_DAMPENING = 74410,
    SPELL_GENERIC_BATTLEGROUND_DAMPENING = 74411,

    SPELL_PALADIN_CONSECRATION = 48819,
    SPELL_PALADIN_EXORCISM = 48801,
    SPELL_PALADIN_RETRIBUTION_AURA = 54043,
    SPELL_PALADIN_SHIELD_OF_RIGHTEOUS = 61411,

    SPELL_PALADIN_SEAL_OF_DISCIPLINE_PROC = 86501,
    SPELL_PALADIN_SEAL_OF_FAITH_PROC = 86504,
    SPELL_PALADIN_BEACON_OF_WRATH = 86506,
    SPELL_PALADIN_BEACON_OF_WRATH_PROC = 86507,
    SPELL_PALADIN_GODS_JUDGEMENT_DAMAGE = 86513,
    SPELL_PALADIN_INQUISITION = 86515,
    SPELL_PALADIN_DIVINE_ZEAL = 86508,
    SPELL_PALADIN_SEAL_OF_DISCIPLINE = 86500,
    SPELL_PALADIN_SANCTIFIED_FLAME = 86516,
    SPELL_PALADIN_RIGHTEOUS_BARRAGE_WAVE = 86519,
    SPELL_PALADIN_REPRIMAND = 86514,

    TALENT_PALADIN_BREAK_THEIR_KNEECAPS_PROC = 86555,
    TALENT_PALADIN_BLESSED_BY_THE_LIGHT_PROC = 86604,
};

enum PaladinSpellIcons
{
    PALADIN_ICON_ID_RETRIBUTION_AURA = 555
};

class spell_pal_seal_of_command_aura : public AuraScript
{
    PrepareAuraScript(spell_pal_seal_of_command_aura);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor() || !eventInfo.GetActionTarget())
        {
            return false;
        }

        if (SpellInfo const* procSpell = eventInfo.GetSpellInfo())
        {
            if (procSpell->SpellIconID == 3025) // Righteous Vengeance, should not proc SoC
            {
                return false;
            }
        }

        return true;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        int32 targets = 3;
        if (SpellInfo const* procSpell = eventInfo.GetSpellInfo())
        {
            if (procSpell->IsAffectingArea())
            {
                targets = 1;
            }
        }

        Unit* target = eventInfo.GetActionTarget();
        if (target->IsAlive())
        {
            eventInfo.GetActor()->CastCustomSpell(aurEff->GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, SPELLVALUE_MAX_TARGETS, targets, target, false, nullptr, aurEff);
        }
    }

    void Register() override
    {
        if (m_scriptSpellId == 20375)
        {
            DoCheckProc += AuraCheckProcFn(spell_pal_seal_of_command_aura::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_pal_seal_of_command_aura::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    }
};

class spell_pal_seal_of_command : public SpellScript
{
    PrepareSpellScript(spell_pal_seal_of_command);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (SpellValue const* spellValue = GetSpellValue())
            if (spellValue->MaxAffectedTargets == 1)
                targets.clear();
    }

    void Register() override
    {
        if (m_scriptSpellId == 20424)
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_seal_of_command::FilterTargets, EFFECT_0, TARGET_UNIT_TARGET_ENEMY);
    }
};

class spell_pal_divine_intervention : public AuraScript
{
    PrepareAuraScript(spell_pal_divine_intervention);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetTarget()->IsInCombat() && GetTarget()->GetTypeId() == TYPEID_PLAYER)
            GetTarget()->RemoveAurasDueToSpell(GetTarget()->ToPlayer()->GetTeamId() == TEAM_ALLIANCE ? 57723 : 57724);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_divine_intervention::HandleRemove, EFFECT_0, SPELL_AURA_SCHOOL_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pal_seal_of_light : public AuraScript
{
    PrepareAuraScript(spell_pal_seal_of_light);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        // xinef: skip divine storm self hit (dummy) and righteous vengeance (0x20000000=
        return eventInfo.GetActor() != eventInfo.GetProcTarget() && (!eventInfo.GetSpellInfo() || !eventInfo.GetSpellInfo()->SpellFamilyFlags.HasFlag(0x20000000));
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_seal_of_light::CheckProc);
    }
};

class spell_pal_sacred_shield_base : public AuraScript
{
    PrepareAuraScript(spell_pal_sacred_shield_base);

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
        {
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(GetSpellInfo()->Effects[aurEff->GetEffIndex()].TriggerSpell);
            amount = spellInfo->Effects[EFFECT_0].CalcValue();

            // ratios

            int32 sp = CalculatePct(caster->SpellBaseDamageBonusDone(spellInfo->GetSchoolMask()), 139.5f);
            int32 ap = CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), 93.0f);
            amount += (ap + sp);

            // Xinef: removed divine guardian because it will affect triggered spell with increased amount
            // Arena - Dampening
            if (AuraEffect const* dampening = caster->GetAuraEffect(SPELL_GENERIC_ARENA_DAMPENING, EFFECT_0))
            {
                AddPct(amount, dampening->GetAmount());
            }
            // Battleground - Dampening
            else if (AuraEffect const* dampening2 = caster->GetAuraEffect(SPELL_GENERIC_BATTLEGROUND_DAMPENING, EFFECT_0))
            {
                AddPct(amount, dampening2->GetAmount());
            }
        }
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        HealInfo* healinfo = eventInfo.GetHealInfo();
        DamageInfo* damageinfo = eventInfo.GetDamageInfo();
        return !(eventInfo.GetHitMask() & PROC_EX_INTERNAL_HOT) && ((healinfo && healinfo->GetHeal() > 0) || (damageinfo && damageinfo->GetDamage() > 0));
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        if (eventInfo.GetTypeMask() & PROC_FLAG_TAKEN_SPELL_MAGIC_DMG_CLASS_POS)
        {
            Unit* caster = eventInfo.GetActor();

            HealInfo* healinfo = eventInfo.GetHealInfo();

            if (!healinfo || !healinfo->GetHeal())
            {
                return;
            }

            SpellInfo const* procSpell = healinfo->GetSpellInfo();
            if (!procSpell)
            {
                return;
            }

            if (caster && procSpell->SpellFamilyName == SPELLFAMILY_PALADIN &&
                procSpell->SpellFamilyFlags.HasFlag(0x40000000) && caster->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL, SPELLFAMILY_PALADIN, 3021, 0)) // need infusion of light
            {
                int32 basepoints = int32(float(healinfo->GetHeal()) / 12.0f);
                // Item - Paladin T9 Holy 4P Bonus (Flash of Light)
                if (AuraEffect const* aurEffect = caster->GetAuraEffect(67191, EFFECT_0))
                    AddPct(basepoints, aurEffect->GetAmount());

                caster->CastCustomSpell(eventInfo.GetActionTarget(), 66922, &basepoints, nullptr, nullptr, true, nullptr, aurEff, caster->GetGUID());
                return;
            }

            return;
        }

        uint32 triggered_spell_id = GetSpellInfo()->Effects[aurEff->GetEffIndex()].TriggerSpell;
        if (eventInfo.GetActionTarget()->HasSpellCooldown(triggered_spell_id))
            return;

        uint32 cooldown = eventInfo.GetProcCooldown();
        int32 basepoints = aurEff->GetAmount();

        // Item - Paladin T8 Holy 4P Bonus
        if (Unit* caster = aurEff->GetCaster())
            if (AuraEffect const* aurEffect = caster->GetAuraEffect(64895, 0))
                cooldown = aurEffect->GetAmount() * IN_MILLISECONDS;

        eventInfo.GetActionTarget()->AddSpellCooldown(triggered_spell_id, 0, cooldown);
        eventInfo.GetActionTarget()->CastCustomSpell(eventInfo.GetActionTarget(), triggered_spell_id, &basepoints, nullptr, nullptr, true, nullptr, aurEff, eventInfo.GetActionTarget()->GetGUID());
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_sacred_shield_base::CalculateAmount, EFFECT_0, SPELL_AURA_DUMMY);
        DoCheckProc += AuraCheckProcFn(spell_pal_sacred_shield_base::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_sacred_shield_base::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 31850 - Ardent Defender
class spell_pal_ardent_defender : public AuraScript
{
    PrepareAuraScript(spell_pal_ardent_defender);

public:
    spell_pal_ardent_defender()
    {
        absorbPct = 0;
        healPct = 0;
    }

private:
    uint32 absorbPct, healPct;

    enum Spell
    {
        PAL_SPELL_ARDENT_DEFENDER_HEAL = 66235
    };

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ PAL_SPELL_ARDENT_DEFENDER_HEAL });
    }

    bool Load() override
    {
        healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue();
        absorbPct = GetSpellInfo()->Effects[EFFECT_2].CalcValue();
        return GetUnitOwner()->GetTypeId() == TYPEID_PLAYER;
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* victim = GetTarget();
        int32 remainingHealth = victim->GetHealth() - dmgInfo.GetDamage();
        uint32 allowedHealth = victim->CountPctFromMaxHealth(1);
        // If damage kills us
        if (remainingHealth <= 0 && !victim->ToPlayer()->HasSpellCooldown(PAL_SPELL_ARDENT_DEFENDER_HEAL))
        {
            // Cast healing spell, completely avoid damage
            absorbAmount = dmgInfo.GetDamage();

            uint32 defenseSkillValue = victim->GetDefenseSkillValue();
            // Max heal when defense skill denies critical hits from raid bosses
            // Formula: max defense at level + 140 (raiting from gear)
            uint32 reqDefForMaxHeal = victim->getLevel() * 5 + 140;
            float pctFromDefense = (defenseSkillValue >= reqDefForMaxHeal)
                ? 1.0f
                : float(defenseSkillValue) / float(reqDefForMaxHeal);

            int32 healAmount = int32(victim->CountPctFromMaxHealth(uint32(healPct * pctFromDefense)));
            victim->CastCustomSpell(PAL_SPELL_ARDENT_DEFENDER_HEAL, SPELLVALUE_BASE_POINT0, healAmount, victim, true, nullptr, aurEff);
            victim->ToPlayer()->AddSpellCooldown(PAL_SPELL_ARDENT_DEFENDER_HEAL, 0, 60000);
        }
        else if (remainingHealth < int32(allowedHealth))
        {
            // Reduce damage that brings us under 35% (or full damage if we are already under 35%) by x%
            uint32 damageToReduce = (victim->GetHealth() < allowedHealth)
                ? dmgInfo.GetDamage()
                : allowedHealth - remainingHealth;
            absorbAmount = CalculatePct(damageToReduce, absorbPct);
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_ardent_defender::CalculateAmount, EFFECT_2, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_ardent_defender::Absorb, EFFECT_2);
    }
};

// 31884 - Avenging Wrath
class spell_pal_avenging_wrath : public AuraScript
{
    PrepareAuraScript(spell_pal_avenging_wrath);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_SANCTIFIED_WRATH, SPELL_PALADIN_SANCTIFIED_WRATH_TALENT_R1 });
    }

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (AuraEffect const* aurEff = target->GetAuraEffectOfRankedSpell(SPELL_PALADIN_SANCTIFIED_WRATH_TALENT_R1, EFFECT_2))
        {
            int32 basepoints = aurEff->GetAmount();
            target->CastCustomSpell(target, SPELL_PALADIN_SANCTIFIED_WRATH, &basepoints, &basepoints, nullptr, true, nullptr, aurEff);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->RemoveAurasDueToSpell(SPELL_PALADIN_SANCTIFIED_WRATH);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pal_avenging_wrath::HandleApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_pal_avenging_wrath::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 37877 - Blessing of Faith
class spell_pal_blessing_of_faith : public SpellScript
{
    PrepareSpellScript(spell_pal_blessing_of_faith);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID,
                SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN,
                SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST,
                SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN
            });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* unitTarget = GetHitUnit())
        {
            uint32 spell_id = 0;
            switch (unitTarget->getClass())
            {
            case CLASS_DRUID:
                spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID;
                break;
            case CLASS_PALADIN:
                spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN;
                break;
            case CLASS_PRIEST:
                spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST;
                break;
            case CLASS_SHAMAN:
                spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN;
                break;
            default:
                return; // ignore for non-healing classes
            }
            Unit* caster = GetCaster();
            caster->CastSpell(caster, spell_id, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_blessing_of_faith::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 20911 - Blessing of Sanctuary
// 25899 - Greater Blessing of Sanctuary
class spell_pal_blessing_of_sanctuary : public AuraScript
{
    PrepareAuraScript(spell_pal_blessing_of_sanctuary);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF, SPELL_PALADIN_BLESSING_OF_SANCTUARY_ENERGIZE });
    }

    void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        if (Unit* caster = GetCaster())
        {
            // xinef: hack
            int32 value = 9;
            caster->CastCustomSpell(target, SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF, &value, &value, 0, true);
        }
    }

    void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetTarget();
        target->RemoveAura(SPELL_PALADIN_BLESSING_OF_SANCTUARY_BUFF, GetCasterGUID());
    }

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        return GetTarget()->getPowerType() == POWER_MANA;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(GetTarget(), SPELL_PALADIN_BLESSING_OF_SANCTUARY_ENERGIZE, true, nullptr, aurEff);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_pal_blessing_of_sanctuary::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        AfterEffectRemove += AuraEffectRemoveFn(spell_pal_blessing_of_sanctuary::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        DoCheckProc += AuraCheckProcFn(spell_pal_blessing_of_sanctuary::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_blessing_of_sanctuary::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 64205 - Divine Sacrifice
class spell_pal_divine_sacrifice : public AuraScript
{
    PrepareAuraScript(spell_pal_divine_sacrifice);

    uint32 groupSize, minHpPct;
    int32 remainingAmount;

    bool Load() override
    {
        if (Unit* caster = GetCaster())
        {
            if (caster->GetTypeId() == TYPEID_PLAYER)
            {
                if (caster->ToPlayer()->GetGroup())
                    groupSize = caster->ToPlayer()->GetGroup()->GetMembersCount();
                else
                    groupSize = 1;
            }
            else
                return false;

            remainingAmount = (caster->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_2].CalcValue(caster)) * groupSize);
            minHpPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(caster);
            return true;
        }
        return false;
    }

    void Split(AuraEffect* /*aurEff*/, DamageInfo& /*dmgInfo*/, uint32& splitAmount)
    {
        remainingAmount -= splitAmount;
        // break when absorbed everything it could, or if the casters hp drops below 20%
        if (Unit* caster = GetCaster())
            if (remainingAmount <= 0 || (caster->GetHealthPct() < minHpPct))
                caster->RemoveAura(SPELL_PALADIN_DIVINE_SACRIFICE);
    }

    void Register() override
    {
        OnEffectSplit += AuraEffectSplitFn(spell_pal_divine_sacrifice::Split, EFFECT_0);
    }
};

// 53385 - Divine Storm
class spell_pal_divine_storm : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_storm);

    uint32 healPct;

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_DIVINE_STORM_DUMMY });
    }

    bool Load() override
    {
        healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
        return true;
    }

    void TriggerHeal()
    {
        Unit* caster = GetCaster();
        if (GetHitUnit() != caster)
            caster->CastCustomSpell(SPELL_PALADIN_DIVINE_STORM_DUMMY, SPELLVALUE_BASE_POINT0, (GetHitDamage() * healPct) / 100, caster, true);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_pal_divine_storm::TriggerHeal);
    }
};

// 54171 - Divine Storm (Dummy)
class spell_pal_divine_storm_dummy : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_storm_dummy);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_DIVINE_STORM_HEAL });
    }

    void CountTargets(std::list<WorldObject*>& targetList)
    {
        Acore::Containers::RandomResize(targetList, GetSpellValue()->MaxAffectedTargets);
        _targetCount = targetList.size();
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (!_targetCount || !GetHitUnit())
            return;

        int32 heal = GetEffectValue() / _targetCount;
        GetCaster()->CastCustomSpell(GetHitUnit(), SPELL_PALADIN_DIVINE_STORM_HEAL, &heal, nullptr, nullptr, true);
    }
private:
    uint32 _targetCount;

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_divine_storm_dummy::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_divine_storm_dummy::CountTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
    }
};

// 33695 - Exorcism and Holy Wrath Damage
class spell_pal_exorcism_and_holy_wrath_damage : public AuraScript
{
    PrepareAuraScript(spell_pal_exorcism_and_holy_wrath_damage);

    void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
    {
        if (!spellMod)
        {
            spellMod = new SpellModifier(aurEff->GetBase());
            spellMod->op = SPELLMOD_DAMAGE;
            spellMod->type = SPELLMOD_FLAT;
            spellMod->spellId = GetId();
            spellMod->mask[1] = 0x200002;
        }

        spellMod->value = aurEff->GetAmount();
    }

    void Register() override
    {
        DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_pal_exorcism_and_holy_wrath_damage::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// -9799 - Eye for an Eye
class spell_pal_eye_for_an_eye : public AuraScript
{
    PrepareAuraScript(spell_pal_eye_for_an_eye);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE });
    }

    void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage())
        {
            return;
        }

        // return damage % to attacker but < 50% own total health
        int32 damage = std::min(CalculatePct(static_cast<int32>(damageInfo->GetDamage()), aurEff->GetAmount()), static_cast<int32>(GetTarget()->GetMaxHealth()) / 2);
        GetTarget()->CastCustomSpell(SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE, SPELLVALUE_BASE_POINT0, damage, eventInfo.GetProcTarget(), true, nullptr, aurEff);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_eye_for_an_eye::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 54968 - Glyph of Holy Light
class spell_pal_glyph_of_holy_light : public SpellScript
{
    PrepareSpellScript(spell_pal_glyph_of_holy_light);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        uint32 const maxTargets = GetSpellInfo()->MaxAffectedTargets;

        if (targets.size() > maxTargets)
        {
            targets.sort(Acore::HealthPctOrderPred());
            targets.resize(maxTargets);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_glyph_of_holy_light::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 63521 - Guarded by The Light
class spell_pal_guarded_by_the_light : public SpellScript
{
    PrepareSpellScript(spell_pal_guarded_by_the_light);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_DIVINE_PLEA });
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        // Divine Plea
        if (Aura* aura = GetCaster()->GetAura(SPELL_PALADIN_DIVINE_PLEA))
            aura->RefreshDuration();
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_guarded_by_the_light::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 6940 - Hand of Sacrifice
class spell_pal_hand_of_sacrifice_aura : public AuraScript
{
    PrepareAuraScript(spell_pal_hand_of_sacrifice_aura);

    int32 remainingAmount;

    bool Load() override
    {
        if (Unit* caster = GetCaster())
        {
            remainingAmount = caster->GetMaxHealth();
            return true;
        }
        return false;
    }

    void Split(AuraEffect* /*aurEff*/, DamageInfo& /*dmgInfo*/, uint32& splitAmount)
    {
        remainingAmount -= splitAmount;

        if (remainingAmount <= 0)
        {
            GetTarget()->RemoveAura(SPELL_PALADIN_HAND_OF_SACRIFICE);
        }
    }

    void Register() override
    {
        OnEffectSplit += AuraEffectSplitFn(spell_pal_hand_of_sacrifice_aura::Split, EFFECT_0);
    }
};

class spell_pal_hand_of_sacrifice : public SpellScript
{
    PrepareSpellScript(spell_pal_hand_of_sacrifice);

    SpellCastResult CheckTarget()
    {
        Unit* target = GetExplTargetUnit();
        if (!target || target->HasAura(SPELL_PALADIN_DIVINE_SACRIFICE))
            return SPELL_FAILED_TARGET_AURASTATE;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_hand_of_sacrifice::CheckTarget);
    }
};

// 1038 - Hand of Salvation
class spell_pal_hand_of_salvation : public AuraScript
{
    PrepareAuraScript(spell_pal_hand_of_salvation);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* caster = GetCaster())
        {
            // Glyph of Salvation
            if (caster->GetGUID() == GetUnitOwner()->GetGUID())
                if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_PALADIN_GLYPH_OF_SALVATION, EFFECT_0))
                    amount -= aurEff->GetAmount();
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_hand_of_salvation::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
    }
};

// -20473 - Holy Shock
class spell_pal_holy_shock : public SpellScript
{
    PrepareSpellScript(spell_pal_holy_shock);

    bool Validate(SpellInfo const* spellInfo) override
    {
        SpellInfo const* firstRankSpellInfo = sSpellMgr->GetSpellInfo(SPELL_PALADIN_HOLY_SHOCK_R1);
        if (!firstRankSpellInfo)
            return false;

        // can't use other spell than holy shock due to spell_ranks dependency
        if (!spellInfo->IsRankOf(firstRankSpellInfo))
            return false;

        uint8 rank = spellInfo->GetRank();
        if (!sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE, rank, true) || !sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_HEALING, rank, true))
            return false;

        return true;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (Unit* unitTarget = GetHitUnit())
        {
            uint8 rank = GetSpellInfo()->GetRank();
            if (caster->IsFriendlyTo(unitTarget))
                caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_HEALING, rank), true);
            else
                caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE, rank), true);
        }
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (Unit* target = GetExplTargetUnit())
        {
            if (!caster->IsFriendlyTo(target))
            {
                if (!caster->IsValidAttackTarget(target))
                    return SPELL_FAILED_BAD_TARGETS;

                if (!caster->isInFront(target))
                    return SPELL_FAILED_UNIT_NOT_INFRONT;
            }
        }
        else
            return SPELL_FAILED_BAD_TARGETS;
        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_holy_shock::CheckCast);
        OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 53407 - Judgement of Justice
// 20271 - Judgement of Light
// 53408 - Judgement of Wisdom
class spell_pal_judgement : public SpellScript
{
    PrepareSpellScript(spell_pal_judgement);

public:
    spell_pal_judgement(uint32 spellId) : SpellScript(), _spellId(spellId) { }
    
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_JUDGEMENT_DAMAGE, _spellId });
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        uint32 spellId2 = 0;

        // some seals have SPELL_AURA_DUMMY in EFFECT_2
        Unit::AuraEffectList const& auras = GetCaster()->GetAuraEffectsByType(SPELL_AURA_DUMMY);
        for (Unit::AuraEffectList::const_iterator i = auras.begin(); i != auras.end(); ++i)
        {
            if ((*i)->GetSpellInfo()->GetSpellSpecific() == SPELL_SPECIFIC_SEAL && (*i)->GetEffIndex() == EFFECT_2)
                if (sSpellMgr->GetSpellInfo((*i)->GetAmount()))
                {
                    spellId2 = (*i)->GetAmount();
                    break;
                }
        }

        caster->CastSpell(GetHitUnit(), _spellId, true);
        caster->CastSpell(GetHitUnit(), spellId2, true);

        // Judgement of the Just
        if (caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_PALADIN, 3015, 0))
            caster->CastSpell(GetHitUnit(), 68055, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_judgement::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }

private:
    uint32 const _spellId;
};

// 20425 - Judgement of Command
class spell_pal_judgement_of_command : public SpellScript
{
    PrepareSpellScript(spell_pal_judgement_of_command);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* unitTarget = GetHitUnit())
            if (SpellInfo const* spell_proto = sSpellMgr->GetSpellInfo(GetEffectValue()))
                GetCaster()->CastSpell(unitTarget, spell_proto, true, nullptr);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_judgement_of_command::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// -633 - Lay on Hands
class spell_pal_lay_on_hands : public SpellScript
{
    PrepareSpellScript(spell_pal_lay_on_hands);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PALADIN_FORBEARANCE,
            });
    }

    bool Load() override
    {
        _manaAmount = 0;
        return true;
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (Unit* target = GetExplTargetUnit())
            if (caster == target)
                if (target->HasAura(SPELL_PALADIN_FORBEARANCE))
                    return SPELL_FAILED_TARGET_AURASTATE;

        // Xinef: Glyph of Divinity
        if (Unit* target = GetExplTargetUnit())
            if (target->getPowerType() == POWER_MANA)
                _manaAmount = target->GetPower(POWER_MANA);

        return SPELL_CAST_OK;
    }

    void HandleScript()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        if (caster == target)
        {
            caster->CastSpell(caster, SPELL_PALADIN_FORBEARANCE, true);
        }
        // Xinef: Glyph of Divinity
        else if (target && caster->HasAura(54939) && GetSpellInfo()->Id != 633 && _manaAmount > 0) // excluding first rank
        {
            _manaAmount = target->GetPower(POWER_MANA) - _manaAmount;
            if (_manaAmount > 0)
                caster->CastCustomSpell(54986 /*Energize*/, SPELLVALUE_BASE_POINT1, _manaAmount, caster, true);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_lay_on_hands::CheckCast);
        AfterHit += SpellHitFn(spell_pal_lay_on_hands::HandleScript);
    }

    int32 _manaAmount;
};

// 31789 - Righteous Defense
class spell_pal_righteous_defense : public SpellScript
{
    PrepareSpellScript(spell_pal_righteous_defense);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT });
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (caster->GetTypeId() != TYPEID_PLAYER)
            return SPELL_FAILED_DONT_REPORT;

        if (Unit* target = GetExplTargetUnit())
        {
            if (!target->IsFriendlyTo(caster) || target->getAttackers().empty())
                return SPELL_FAILED_BAD_TARGETS;
        }
        else
            return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void HandleTriggerSpellLaunch(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);
    }

    void HandleTriggerSpellHit(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_righteous_defense::CheckCast);
        //! WORKAROUND
        //! target select will be executed in hitphase of effect 0
        //! so we must handle trigger spell also in hit phase (default execution in launch phase)
        //! see issue #3718
        OnEffectLaunchTarget += SpellEffectFn(spell_pal_righteous_defense::HandleTriggerSpellLaunch, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
        OnEffectHitTarget += SpellEffectFn(spell_pal_righteous_defense::HandleTriggerSpellHit, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

// 20154, 21084 - Seal of Righteousness - melee proc dummy (addition ${$MWS*(0.022*$AP+0.044*$SPH)} damage)
class spell_pal_seal_of_righteousness : public AuraScript
{
    PrepareAuraScript(spell_pal_seal_of_righteousness);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetProcTarget();
        if (!target)
            return false;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage())
        {
            return false;
        }

        return target->IsAlive() && !eventInfo.GetTriggerAuraSpell() && (damageInfo->GetDamage() || (eventInfo.GetHitMask() & PROC_EX_ABSORB));
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        float ap = GetTarget()->GetTotalAttackPowerValue(BASE_ATTACK);
        int32 holy = GetTarget()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY);
        holy += eventInfo.GetProcTarget()->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_HOLY);

        // Xinef: Libram of Divine Purpose
        if (AuraEffect* aurEffPaladin = GetTarget()->GetDummyAuraEffect(SPELLFAMILY_PALADIN, 2025, EFFECT_0))
        {
            holy += aurEffPaladin->GetAmount();
        }

        int32 bp = std::max<int32>(0, int32((ap * 0.022f + 0.044f * holy) * GetTarget()->GetAttackTime(BASE_ATTACK) / 1000));
        GetTarget()->CastCustomSpell(SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS, SPELLVALUE_BASE_POINT0, bp, eventInfo.GetProcTarget(), true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_seal_of_righteousness::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_seal_of_righteousness::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_forbearance : public SpellScript
{
    PrepareSpellScript(spell_pal_forbearance);

    void HandleProc()
    {
        GetCaster()->CastSpell(GetExplTargetUnit(), 25771, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnCast += SpellCastFn(spell_pal_forbearance::HandleProc);
    }
};

class spell_pal_exorcism : public SpellScript
{
    PrepareSpellScript(spell_pal_exorcism);

    void HandleScriptEffect()
    {
        Creature* creature = GetCaster()->FindNearestCreature(500502, 30);
        if (!creature || creature->GetCharmerOrOwnerGUID() != GetCaster()->GetGUID())
            return;

        for (auto const& targetburn : FindCreatures(creature))
        {
            GetCaster()->AddAura(48801, targetburn);
        }
    }

    std::list <Unit*> FindCreatures(Creature* creature)
    {
        auto const& threatlist = GetCaster()->getAttackers();
        Position creaturepos = creature->GetPosition();
        std::list <Unit*> targetAvailable;

        for (auto const& target : threatlist)
        {
            Position targetpos = target->GetPosition();
            float distance = creature->GetDistance(targetpos);

            if (distance <= 8)
            {
                targetAvailable.push_back(target);
            }
        } return targetAvailable;
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pal_exorcism::HandleScriptEffect);
    }
};

class spell_pal_consecration : public SpellScript
{
    PrepareSpellScript(spell_pal_consecration);

    void HandleScriptEffect()
    {
        GetCaster()->CastSpell(GetCaster(), 80121, true);

        Aura* auraEff = GetCaster()->GetAura(80121);
        int32 duration = auraEff->GetDuration();

        GetCaster()->SummonCreature(500502, GetCaster()->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, duration);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pal_consecration::HandleScriptEffect);
    }
};

class spell_pal_seraphim : public AuraScript
{
    PrepareAuraScript(spell_pal_seraphim);

    void ApplyHasteAndMeleeCritical(bool apply)
    {
        Unit* caster = GetCaster();

        caster->ApplyAttackTimePercentMod(BASE_ATTACK, 8.0f, apply);
        caster->ApplyAttackTimePercentMod(OFF_ATTACK, 8.0f, apply);
        caster->ApplyAttackTimePercentMod(RANGED_ATTACK, 8.0f, apply);
        caster->ApplyCastTimePercentMod(8.0f, apply);

        caster->ToPlayer()->HandleBaseModValue(CRIT_PERCENTAGE, FLAT_MOD, 8.0f, apply);
        caster->ToPlayer()->HandleBaseModValue(OFFHAND_CRIT_PERCENTAGE, FLAT_MOD, 8.0f, apply);
        caster->ToPlayer()->HandleBaseModValue(RANGED_CRIT_PERCENTAGE, FLAT_MOD, 8.0f, apply);
    }

    void HandleBuff(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        ApplyHasteAndMeleeCritical(true);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        ApplyHasteAndMeleeCritical(false);
    }

    void Register()
    {
        OnEffectApply += AuraEffectApplyFn(spell_pal_seraphim::HandleBuff, EFFECT_1, SPELL_AURA_MOD_MASTERY_PCT, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_seraphim::HandleRemove, EFFECT_1, SPELL_AURA_MOD_MASTERY_PCT, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pal_ret_aura : public AuraScript
{
    PrepareAuraScript(spell_pal_ret_aura);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        if (GetCaster()->HasAura(80039))
        {
            float remainingDuration = GetCaster()->GetAura(80039)->GetDuration();
            GetCaster()->GetAura(80039)->SetDuration(remainingDuration + 4000);
        }
        else
        {
            GetCaster()->CastSpell(GetCaster(), 80039, TRIGGERED_FULL_MASK);
            GetCaster()->GetAura(80039)->SetDuration(4000);
        }
        GetCaster()->CastSpell(GetCaster(), 80041, TRIGGERED_FULL_MASK);
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* victim = GetTarget();
        uint32 healthPct = CalculatePct(victim->GetMaxHealth(), 50);

        if (GetCaster()->HasAura(80041))
            return false;
        if (!eventInfo.GetDamageInfo())
            return false;
        if (eventInfo.GetDamageInfo()->GetDamage() < healthPct)
            return false;

        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_ret_aura::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_ret_aura::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_shield_righteous : public SpellScript
{
    PrepareSpellScript(spell_pal_shield_righteous);

    void HandleDummy(SpellEffIndex effIndex)
    {
        int32 armor = CalculatePct(GetCaster()->GetStat(STAT_STRENGTH), GetEffectValue());

        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        GetCaster()->CastCustomSpell(80042, SPELLVALUE_BASE_POINT0, armor, GetCaster(), TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectHit += SpellEffectFn(spell_pal_shield_righteous::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
    }
};

class spell_pal_holy_power : public SpellScript
{
    PrepareSpellScript(spell_pal_holy_power);

    void HandleEnergy()
    {
        Unit* caster = GetCaster();
        if (caster->GetPower(POWER_ENERGY) < 5) {
            caster->SetPower(POWER_ENERGY, caster->GetPower(POWER_ENERGY) + 1);
        }
    }

    void Register()
    {
        OnCast += SpellCastFn(spell_pal_holy_power::HandleEnergy);
    }
};

class spell_pal_infusion_of_light_power : public AuraScript
{
    PrepareAuraScript(spell_pal_infusion_of_light_power);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        GetCaster()->SetPower(POWER_ENERGY, GetCaster()->GetPower(POWER_ENERGY) + 1);

        if (GetCaster()->HasAura(SPELL_PALADIN_INFUSION_OF_LIGHT_R1))
        {
            if (int32 charge = GetCaster()->GetAura(SPELL_PALADIN_INFUSION_OF_LIGHT_R1)->GetCharges() > 1)
                GetCaster()->GetAura(SPELL_PALADIN_INFUSION_OF_LIGHT_R1)->SetCharges(charge - 1);
            else
                GetCaster()->RemoveAura(SPELL_PALADIN_INFUSION_OF_LIGHT_R1);
        }

        if (GetCaster()->HasAura(SPELL_PALADIN_INFUSION_OF_LIGHT_R2))
        {
            if (int32 charge = GetCaster()->GetAura(SPELL_PALADIN_INFUSION_OF_LIGHT_R2)->GetCharges() > 1)
                GetCaster()->GetAura(SPELL_PALADIN_INFUSION_OF_LIGHT_R2)->SetCharges(charge - 1);
            else
                GetCaster()->RemoveAura(SPELL_PALADIN_INFUSION_OF_LIGHT_R2);
        }
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_infusion_of_light_power::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_light_of_dawn : public SpellScript
{
    PrepareSpellScript(spell_pal_light_of_dawn);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::RaidCheck(GetCaster(), false));

        uint32 const maxTargets = 5;

        if (targets.size() > maxTargets)
        {
            targets.sort(Acore::HealthPctOrderPred());
            targets.resize(maxTargets);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_light_of_dawn::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ALLY);
    }
};

class spell_pal_light_of_the_martyr : public SpellScript
{
    PrepareSpellScript(spell_pal_light_of_the_martyr);

    void HandleProc()
    {
        float damagePct = sSpellMgr->AssertSpellInfo(80043)->GetEffect(EFFECT_2).BasePoints + 1;
        if (damagePct <= 0)
            return;

        float ap = CalculatePct(int32(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK)), 105);
        int32 holysp = CalculatePct(int32(GetCaster()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY)), 157);

        int32 sum = (ap + holysp);

        int32 damage = int32(CalculatePct(sum, damagePct));

        damage = std::max<int32>(0, damage);

        GetCaster()->CastCustomSpellTrigger(80044, SPELLVALUE_BASE_POINT0, damage, GetCaster(), TRIGGERED_IGNORE_AURA_SCALING);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pal_light_of_the_martyr::HandleProc);
    }
};

class spell_pal_beacon_of_virtue : public SpellScript
{
    PrepareSpellScript(spell_pal_beacon_of_virtue);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::RaidCheck(GetCaster(), false));

        uint32 const maxTargets = 3;

        if (targets.size() > maxTargets)
        {
            targets.sort(Acore::HealthPctOrderPred());
            targets.resize(maxTargets);
        }
        for (auto const& target : targets)
        {
            Unit* player = target->ToUnit();
            GetCaster()->AddAura(80055, player);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_beacon_of_virtue::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

class spell_pal_final_reckoning : public AuraScript
{
    PrepareAuraScript(spell_pal_final_reckoning);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!GetCaster()->HasSpell(80052))
            return false;
        if (GetCaster()->HasSpellCooldown(80052))
            return false;
        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_final_reckoning::CheckProc);
    }
};

class spell_pal_beacon : public AuraScript
{
    PrepareAuraScript(spell_pal_beacon);

    std::list <Unit*> FindTargets(int32 spellId)
    {
        Player* caster = GetCaster()->ToPlayer();
        std::list <Unit*> targetAvailable;
        auto const& allyList = caster->GetGroup()->GetMemberSlots();

        for (auto const& target : allyList)
        {
            Player* player = ObjectAccessor::FindPlayer(target.guid);
            if (player)
                if (player->HasAura(spellId))
                    if (player->GetAura(spellId)->GetCasterGUID() == GetCaster()->GetGUID())
                    {
                        Unit* dummy = player->ToUnit();
                        if (dummy)
                            targetAvailable.push_back(dummy);
                    }
        }
        return targetAvailable;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        if (eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0)
        {
            int32 heal = eventInfo.GetHealInfo()->GetHeal();

            int32 healpct = CalculatePct(heal, aurEff->GetAmount());
            if (GetCaster()->HasSpell(80049))
                healpct = CalculatePct(healpct, 70);

            for (auto const& targetheal : FindTargets(53563))
            {
                GetCaster()->CastCustomSpell(80051, SPELLVALUE_BASE_POINT0, healpct, targetheal, true, nullptr);
            }

            for (auto const& targetheal : FindTargets(80049))
            {
                GetCaster()->CastCustomSpell(80050, SPELLVALUE_BASE_POINT0, healpct, targetheal, true, nullptr);
            }

            for (auto const& targetheal : FindTargets(80055))
            {
                GetCaster()->CastCustomSpell(80051, SPELLVALUE_BASE_POINT0, healpct, targetheal, true, nullptr);
            }
        }
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetCaster()->ToPlayer();
        if (!player->GetGroup())
            return false;
        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_beacon::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_beacon::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_beacon_listener : public SpellScript
{
    PrepareSpellScript(spell_pal_beacon_listener);

    void HandleProc()
    {
        GetCaster()->AddAura(80054, GetCaster());
    }

    void Register()
    {
        OnCast += SpellCastFn(spell_pal_beacon_listener::HandleProc);
    }
};

class spell_pal_justicars_scaling : public SpellScript
{
    PrepareSpellScript(spell_pal_justicars_scaling);

    void HandleDamage(SpellEffIndex effIndex)
    {
        float ap = CalculatePct(int32(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK)), 105);
        int32 holysp = CalculatePct(int32(GetCaster()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY)), 70);

        int32 sum = std::max<int32>(0, int32(ap + holysp));

        if (Unit* target = GetHitUnit())
        {
            sum = GetCaster()->SpellDamageBonusDone(target, GetSpellInfo(), uint32(sum), SPELL_DIRECT_DAMAGE, effIndex);
            sum = target->SpellDamageBonusTaken(GetCaster(), GetSpellInfo(), uint32(sum), SPELL_DIRECT_DAMAGE);
        }

        if (GetExplTargetUnit()->GetHealthPct() <= 35)
            sum = CalculatePct(int32(sum), 150);

        SetHitDamage(sum);

        GetCaster()->CastCustomSpellTrigger(80057, SPELLVALUE_BASE_POINT0, sum, GetCaster(), TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_justicars_scaling::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_pal_absolution : public SpellScript
{
    PrepareSpellScript(spell_pal_absolution);

    std::list <Unit*> FindTargets()
    {
        Player* caster = GetCaster()->ToPlayer();
        std::list <Unit*> targetAvailable;
        auto const& allyList = caster->GetGroup()->GetMemberSlots();

        for (auto const& target : allyList)
        {
            Player* player = ObjectAccessor::FindPlayer(target.guid);
            if (player)
                if (player->isDead())
                {
                    Unit* dummy = player->ToUnit();
                    if (dummy)
                        targetAvailable.push_back(dummy);
                }
        }
        return targetAvailable;
    }

    void HandleProc()
    {
        Player* player = GetCaster()->ToPlayer();
        if (!player->GetGroup())
            return;

        for (auto const& target : FindTargets())
        {
            GetCaster()->CastSpell(target, 80059, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pal_absolution::HandleProc);
    }
};

class spell_pal_wake_of_ashes : public SpellScript
{
    PrepareSpellScript(spell_pal_wake_of_ashes);

    void HandleEnergy()
    {
        GetCaster()->SetPower(POWER_ENERGY, GetCaster()->GetPower(POWER_ENERGY) + 3);
    }

    void Register()
    {
        OnCast += SpellCastFn(spell_pal_wake_of_ashes::HandleEnergy);
    }
};

class spell_pal_execution_sentence : public AuraScript
{
    PrepareAuraScript(spell_pal_execution_sentence);


    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;
        if (eventInfo.GetDamageInfo()->GetDamage() < 0)
            return false;
        if (!eventInfo.GetDamageInfo()->GetVictim())
            return false;
        return true;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* Victim = eventInfo.GetDamageInfo()->GetVictim();

        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        if (!Victim || !Victim->IsAlive())
            return;

        if (!Victim->HasAura(80064))
            return;

        int32 damagedealt = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());
        int32 amount = damagedealt + GetAura()->GetEffect(EFFECT_1)->GetAmount();

        GetAura()->GetEffect(EFFECT_1)->SetAmount(amount);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_execution_sentence::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_execution_sentence::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_execution_sentence_listener : public AuraScript
{
    PrepareAuraScript(spell_pal_execution_sentence_listener);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        if (GetCaster()->HasAura(80063))
            GetCaster()->RemoveAura(80063);

        int32 amount = aurEff->GetAmount();
        GetCaster()->CastCustomSpell(80063, SPELLVALUE_BASE_POINT0, amount, GetTarget(), TRIGGERED_FULL_MASK);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        float ap = int32(CalculatePct(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK), GetAura()->GetEffect(EFFECT_1)->GetAmount()));
        float sp = int32(CalculatePct(GetCaster()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY), GetAura()->GetEffect(EFFECT_2)->GetAmount()));
        float bonusdmg = GetCaster()->GetAura(80063)->GetEffect(EFFECT_1)->GetAmount();
        int32 amount = ap + sp + bonusdmg;

        GetCaster()->CastCustomSpell(80088, SPELLVALUE_BASE_POINT0, amount, GetTarget(), TRIGGERED_FULL_MASK);
        GetCaster()->RemoveAura(80063);
    }

    void Register()
    {
        OnEffectApply += AuraEffectApplyFn(spell_pal_execution_sentence_listener::HandleProc, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_execution_sentence_listener::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pal_art_of_the_blade : public AuraScript
{
    PrepareAuraScript(spell_pal_art_of_the_blade);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        if (Player* caster = GetTarget()->ToPlayer())
            caster->RemoveSpellCooldown(80045, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_art_of_the_blade::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_art_of_war : public AuraScript
{
    PrepareAuraScript(spell_pal_art_of_war);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Player* caster = GetTarget()->ToPlayer();

        if (!caster || !caster->IsAlive())
            return;

        if (caster)
            caster->ModifySpellCooldown(48801, -aurEff->GetAmount());
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_art_of_war::HandleProc, EFFECT_1, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

class spell_pal_shield_of_vengeance_absorb : public SpellScript
{
    PrepareSpellScript(spell_pal_shield_of_vengeance_absorb);

    void HandleAbsorb()
    {
        int32 hp = CalculatePct(GetCaster()->GetMaxHealth(), 30);
        GetCaster()->CastCustomSpell(80067, SPELLVALUE_BASE_POINT0, hp, GetCaster());
    }

    void Register()
    {
        OnCast += SpellCastFn(spell_pal_shield_of_vengeance_absorb::HandleAbsorb);
    }
};

class spell_pal_shield_of_vengeance_damage : public AuraScript
{
    PrepareAuraScript(spell_pal_shield_of_vengeance_damage);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        int32 hp = CalculatePct(GetCaster()->GetMaxHealth(), 30);
        GetCaster()->CastCustomSpell(80068, SPELLVALUE_BASE_POINT0, hp, GetCaster());
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_shield_of_vengeance_damage::HandleProc, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pal_crusaders_might : public AuraScript
{
    PrepareAuraScript(spell_pal_crusaders_might);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        Player* caster = GetTarget()->ToPlayer();

        if (!caster || !caster->IsAlive())
            return;

        if (Player* target = GetTarget()->ToPlayer())
            target->ModifySpellCooldown(48825, -aurEff->GetAmount());
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_crusaders_might::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_glimmer_of_light_heal : public AuraScript
{
    PrepareAuraScript(spell_pal_glimmer_of_light_heal);

    std::list <Unit*> FindTargets()
    {
        Player* caster = GetCaster()->ToPlayer();
        std::list <Unit*> targetAvailable;
        auto const& allyList = caster->GetGroup()->GetMemberSlots();

        for (auto const& target : allyList)
        {
            Player* player = ObjectAccessor::FindPlayer(target.guid);
            if (player)
                if (player->HasAura(80087))
                    if (player->GetAura(80087)->GetCasterGUID() == GetCaster()->GetGUID())
                    {
                        Unit* dummy = player->ToUnit();
                        if (dummy)
                            targetAvailable.push_back(dummy);
                    }
        }
        return targetAvailable;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        for (auto const& targetheal : FindTargets())
        {
            GetCaster()->CastSpell(targetheal, 80086, TRIGGERED_FULL_MASK);
        }
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* player = GetCaster()->ToPlayer();
        if (!player->GetGroup())
            return false;
        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_glimmer_of_light_heal::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_glimmer_of_light_heal::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_glimmer_of_light_damage : public AuraScript
{
    PrepareAuraScript(spell_pal_glimmer_of_light_damage);

    std::list <Unit*> FindTargets()
    {
        auto const& threatlist = GetCaster()->getAttackers();
        std::list <Unit*> targetAvailable;

        for (auto const& target : threatlist)
        {
            if (target)
                if (target->HasAura(80087))
                    if (target->GetAura(80087)->GetCasterGUID() == GetCaster()->GetGUID())
                    {
                        Unit* dummy = target->ToUnit();
                        if (dummy)
                            targetAvailable.push_back(dummy);
                    }
        }return targetAvailable;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        for (auto const& targetdamage : FindTargets())
        {
            GetCaster()->CastSpell(targetdamage, 80085, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_glimmer_of_light_damage::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_glimmer_of_light_listener : public SpellScript
{
    PrepareSpellScript(spell_pal_glimmer_of_light_listener);

    void HandleProc()
    {
        if (GetCaster()->HasSpell(80084))
            if (!GetExplTargetUnit()->HasAura(80087))
                GetCaster()->CastSpell(GetExplTargetUnit(), 80087, TRIGGERED_FULL_MASK);
        if (GetCaster()->HasSpell(80084))
        {
            int32 duration = GetExplTargetUnit()->GetAura(80087)->GetMaxDuration();
            GetExplTargetUnit()->GetAura(80087)->SetDuration(duration);
        }

    }

    void Register()
    {
        AfterCast += SpellCastFn(spell_pal_glimmer_of_light_listener::HandleProc);
    }
};

class spell_pal_shining_light : public AuraScript
{
    PrepareAuraScript(spell_pal_shining_light);

    void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        Aura* aura = GetAura();
        Unit* caster = GetCaster();
        Unit* target = GetTarget();

        if (!target || !target->IsAlive())
            return;

        if (!aura)
            return;

        if (!caster || !caster->IsAlive())
            return;

        Aura* auraStack = caster->GetAura(80094);

        if (!auraStack)
            return;

        uint32 stacksAmount = auraStack->GetStackAmount();
        uint32 requireStacks = aura->GetSpellInfo()->GetEffect(EFFECT_0).BasePoints + 1;

        if (stacksAmount < requireStacks)
            return;

        caster->CastSpell(GetCaster(), 80095, TRIGGERED_FULL_MASK);
        caster->RemoveAura(80094);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_shining_light::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

class spell_pal_sacred_duty : public SpellScript
{
    PrepareSpellScript(spell_pal_sacred_duty);

    void HandleProc()
    {
        if (GetCaster()->HasAura(31848) || GetCaster()->HasAura(31849))
            GetCaster()->CastSpell(GetCaster(), 80102, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnCast += SpellCastFn(spell_pal_sacred_duty::HandleProc);
    }
};

class spell_pal_grand_crusader : public AuraScript
{
    PrepareAuraScript(spell_pal_grand_crusader);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        GetCaster()->ToPlayer()->RemoveSpellCooldown(48827, true);

        if (GetCaster()->HasAura(80105))
            GetCaster()->CastSpell(GetCaster(), 80104, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_grand_crusader::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_seal_of_discipline : public AuraScript
{
    PrepareAuraScript(spell_pal_seal_of_discipline);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetProcTarget();
        if (!target)
            return false;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage())
        {
            return false;
        }

        return target->IsAlive();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->CastSpell(eventInfo.GetActionTarget(), SPELL_PALADIN_SEAL_OF_DISCIPLINE_PROC, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_seal_of_discipline::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_seal_of_discipline::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_seal_of_faith : public AuraScript
{
    PrepareAuraScript(spell_pal_seal_of_faith);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetProcTarget();
        if (!target)
            return false;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage())
        {
            return false;
        }

        return target->IsAlive();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->CastSpell(eventInfo.GetActionTarget(), SPELL_PALADIN_SEAL_OF_FAITH_PROC, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_seal_of_faith::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_seal_of_faith::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_beacon_of_wrath : public AuraScript
{
    PrepareAuraScript(spell_pal_beacon_of_wrath);

    std::list <Unit*> FindTargets()
    {
        auto const& threatlist = GetCaster()->getAttackers();
        std::list <Unit*> targetAvailable;

        for (auto const& target : threatlist)
        {
            if (target)
                if (target->HasAura(SPELL_PALADIN_BEACON_OF_WRATH))
                    if (target->GetAura(SPELL_PALADIN_BEACON_OF_WRATH)->GetCasterGUID() == GetCaster()->GetGUID())
                    {
                        Unit* dummy = target->ToUnit();
                        if (dummy)
                            targetAvailable.push_back(dummy);
                    }
        }return targetAvailable;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage() || damageInfo->GetDamage() == 0)
        {
            return false;
        }

        return GetCaster()->IsAlive();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        int32 amount = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());

        for (auto const& target : FindTargets())
        {
            caster->CastCustomSpell(SPELL_PALADIN_BEACON_OF_WRATH_PROC, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_beacon_of_wrath::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_beacon_of_wrath::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_gods_judgement : public AuraScript
{
    PrepareAuraScript(spell_pal_gods_judgement);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage() || damageInfo->GetDamage() == 0)
        {
            return false;
        }

        return eventInfo.GetActor()->GetGUID() == GetCaster()->GetGUID();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        AuraEffect* storage = GetEffect(EFFECT_1);
        uint32 dmgPct = aurEff->GetAmount();
        uint32 damage = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), dmgPct);
        
        storage->ChangeAmount(damage);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster->IsAlive())
            return;

        uint32 storedDamage = GetEffect(EFFECT_1)->GetAmount();

        float sp = int32(CalculatePct(GetCaster()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY), GetAura()->GetEffect(EFFECT_2)->GetAmount()));
        uint32 damage = storedDamage + sp;

        caster->CastCustomSpell(SPELL_PALADIN_GODS_JUDGEMENT_DAMAGE, SPELLVALUE_BASE_POINT0, damage, GetUnitOwner(), TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_gods_judgement::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_gods_judgement::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_gods_judgement::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pal_inquisition : public SpellScript
{
    PrepareSpellScript(spell_pal_inquisition);

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        uint32 reduction = sSpellMgr->AssertSpellInfo(SPELL_PALADIN_INQUISITION)->GetEffect(EFFECT_1).CalcValue();
        GetCaster()->ToPlayer()->ModifySpellCooldown(SPELL_PALADIN_DIVINE_ZEAL, reduction);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_inquisition::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_pal_way_of_the_inquisitor: public AuraScript
{
    PrepareAuraScript(spell_pal_way_of_the_inquisitor);

    void HandleLearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->learnSpell(SPELL_PALADIN_SEAL_OF_DISCIPLINE);
        target->learnSpell(SPELL_PALADIN_SANCTIFIED_FLAME);
    }

    void HandleUnlearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->removeSpell(SPELL_PALADIN_SEAL_OF_DISCIPLINE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PALADIN_SANCTIFIED_FLAME, SPEC_MASK_ALL, false);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pal_way_of_the_inquisitor::HandleLearn, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_way_of_the_inquisitor::HandleUnlearn, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pal_break_their_kneecaps : public AuraScript
{
    PrepareAuraScript(spell_pal_break_their_kneecaps);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActor();
        if (!target || !target->IsAlive())
            return false;

        Unit* caster = eventInfo.GetActionTarget();
        if (!caster || !caster->IsAlive())
            return false;

        return target != caster;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->CastSpell(eventInfo.GetActor(), TALENT_PALADIN_BREAK_THEIR_KNEECAPS_PROC, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_break_their_kneecaps::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_break_their_kneecaps::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_book_mastery: public AuraScript
{
    PrepareAuraScript(spell_pal_book_mastery);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActionTarget();
        if (!target)
            return false;

        DamageInfo* damageInfo = eventInfo.GetDamageInfo();

        if (!damageInfo || !damageInfo->GetDamage())
        {
            return false;
        }

        return target->IsAlive();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        uint32 procSpell = eventInfo.GetProcSpell()->GetSpellInfo()->Id;

        GetCaster()->CastSpell(eventInfo.GetActionTarget(), procSpell, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_book_mastery::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_book_mastery::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_the_art_of_inquisiting: public AuraScript
{
    PrepareAuraScript(spell_pal_the_art_of_inquisiting);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->ToPlayer()->RemoveSpellCooldown(SPELL_PALADIN_EXORCISM, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pal_the_art_of_inquisiting::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_blessed_armor : public AuraScript
{
    PrepareAuraScript(spell_pal_blessed_armor);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActor();
        if (!target || !target->IsAlive())
            return false;

        Unit* caster = eventInfo.GetActionTarget();
        if (!caster || !caster->IsAlive())
            return false;

        return target != caster;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->CastSpell(eventInfo.GetActionTarget(), SPELL_PALADIN_RIGHTEOUS_BARRAGE_WAVE, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_blessed_armor::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_blessed_armor::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_blessed_by_the_light : public AuraScript
{
    PrepareAuraScript(spell_pal_blessed_by_the_light);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActionTarget();
        if (!target)
            return false;

        HealInfo* healInfo = eventInfo.GetHealInfo();

        if (!healInfo || !healInfo->GetHeal())
        {
            return false;
        }

        return target->IsAlive();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        uint32 amount = CalculatePct(eventInfo.GetHealInfo()->GetHeal(), aurEff->GetAmount());

        GetCaster()->CastCustomSpell(TALENT_PALADIN_BLESSED_BY_THE_LIGHT_PROC, SPELLVALUE_BASE_POINT0, amount, eventInfo.GetActionTarget(), TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_blessed_by_the_light::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_blessed_by_the_light::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pal_holy_vendetta : public AuraScript
{
    PrepareAuraScript(spell_pal_holy_vendetta);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActionTarget();
        if (!target)
            return false;

        DamageInfo* healInfo = eventInfo.GetDamageInfo();

        if (!healInfo || !healInfo->GetDamage())
        {
            return false;
        }

        return target->IsAlive();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        uint32 spell = aurEff->GetAmount();

        GetCaster()->CastSpell(eventInfo.GetActionTarget(), spell, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_holy_vendetta::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_holy_vendetta::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_paladin_spell_scripts()
{
    RegisterSpellAndAuraScriptPair(spell_pal_seal_of_command, spell_pal_seal_of_command_aura);
    RegisterSpellScript(spell_pal_divine_intervention);
    RegisterSpellScript(spell_pal_seal_of_light);
    RegisterSpellScript(spell_pal_sacred_shield_base);
    RegisterSpellScript(spell_pal_ardent_defender);
    RegisterSpellScript(spell_pal_avenging_wrath);
    RegisterSpellScript(spell_pal_blessing_of_faith);
    RegisterSpellScript(spell_pal_blessing_of_sanctuary);
    RegisterSpellScript(spell_pal_divine_sacrifice);
    //RegisterSpellScript(spell_pal_divine_storm);
    RegisterSpellScript(spell_pal_divine_storm_dummy);
    RegisterSpellScript(spell_pal_exorcism_and_holy_wrath_damage);
    //RegisterSpellScript(spell_pal_eye_for_an_eye);
    RegisterSpellScript(spell_pal_glyph_of_holy_light);
    RegisterSpellScript(spell_pal_guarded_by_the_light);
    RegisterSpellAndAuraScriptPair(spell_pal_hand_of_sacrifice, spell_pal_hand_of_sacrifice_aura);
    RegisterSpellScript(spell_pal_hand_of_salvation);
    RegisterSpellScript(spell_pal_holy_shock);
    RegisterSpellScriptWithArgs(spell_pal_judgement, "spell_pal_judgement_of_justice", SPELL_PALADIN_JUDGEMENT_OF_JUSTICE);
    RegisterSpellScriptWithArgs(spell_pal_judgement, "spell_pal_judgement_of_light", SPELL_PALADIN_JUDGEMENT_OF_LIGHT);
    RegisterSpellScriptWithArgs(spell_pal_judgement, "spell_pal_judgement_of_wisdom", SPELL_PALADIN_JUDGEMENT_OF_WISDOM);
    RegisterSpellScript(spell_pal_judgement_of_command);
    RegisterSpellScript(spell_pal_lay_on_hands);
    RegisterSpellScript(spell_pal_righteous_defense);
    RegisterSpellScript(spell_pal_seal_of_righteousness);
    RegisterSpellScript(spell_pal_forbearance);
    RegisterSpellScript(spell_pal_seraphim);
    RegisterSpellScript(spell_pal_exorcism);
    RegisterSpellScript(spell_pal_consecration);
    RegisterSpellScript(spell_pal_ret_aura);
    RegisterSpellScript(spell_pal_shield_righteous);
    RegisterSpellScript(spell_pal_holy_power);
    RegisterSpellScript(spell_pal_infusion_of_light_power);
    RegisterSpellScript(spell_pal_light_of_dawn);
    RegisterSpellScript(spell_pal_light_of_the_martyr);
    RegisterSpellScript(spell_pal_beacon_of_virtue);
    RegisterSpellScript(spell_pal_final_reckoning);
    RegisterSpellScript(spell_pal_beacon);
    RegisterSpellScript(spell_pal_beacon_listener);
    RegisterSpellScript(spell_pal_justicars_scaling);
    RegisterSpellScript(spell_pal_absolution);
    RegisterSpellScript(spell_pal_wake_of_ashes);
    RegisterSpellScript(spell_pal_execution_sentence);
    RegisterSpellScript(spell_pal_execution_sentence_listener);
    RegisterSpellScript(spell_pal_art_of_the_blade);
    RegisterSpellScript(spell_pal_art_of_war);
    RegisterSpellScript(spell_pal_shield_of_vengeance_absorb);
    RegisterSpellScript(spell_pal_shield_of_vengeance_damage);
    RegisterSpellScript(spell_pal_crusaders_might);
    RegisterSpellScript(spell_pal_glimmer_of_light_heal);
    RegisterSpellScript(spell_pal_glimmer_of_light_damage);
    RegisterSpellScript(spell_pal_glimmer_of_light_listener);
    RegisterSpellScript(spell_pal_shining_light);
    RegisterSpellScript(spell_pal_sacred_duty);
    RegisterSpellScript(spell_pal_grand_crusader);
    RegisterSpellScript(spell_pal_seal_of_discipline);
    RegisterSpellScript(spell_pal_seal_of_faith);
    RegisterSpellScript(spell_pal_beacon_of_wrath);
    RegisterSpellScript(spell_pal_gods_judgement);
    RegisterSpellScript(spell_pal_inquisition);
    RegisterSpellScript(spell_pal_way_of_the_inquisitor);
    RegisterSpellScript(spell_pal_break_their_kneecaps);
    RegisterSpellScript(spell_pal_book_mastery);
    RegisterSpellScript(spell_pal_the_art_of_inquisiting);
    RegisterSpellScript(spell_pal_blessed_armor);
    RegisterSpellScript(spell_pal_blessed_by_the_light);
    RegisterSpellScript(spell_pal_holy_vendetta);
}
