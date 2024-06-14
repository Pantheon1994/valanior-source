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
  * Scripts for spells with SPELLFAMILY_PRIEST and SPELLFAMILY_GENERIC spells used by priest players.
  * Ordered alphabetically using scriptname.
  * Scriptnames of files in this file should be prefixed with "spell_pri_".
  */

#include "GridNotifiers.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "TemporarySummon.h"

enum PriestSpells
{
    // Spells
    SPELL_PRIEST_LIGHTWELL_RENEW = 48085,
    SPELL_PRIEST_LIGHTWELL_CHARGE = 59907,
    SPELL_PRIEST_AUTONEMENT = 81009,
    SPELL_PRIEST_AUTONEMENT_AURA = 81010,
    SPELL_PRIEST_AUTONEMENT_AOE = 81011,
    SPELL_PRIEST_AUTONEMENT_HEAL = 81012,
    SPELL_PRIEST_DEVOURING_PLAGUE = 48300,
    SPELL_PRIEST_DEVOURING_PLAGUE_EXTRA_DAMAGE = 63675,
    SPELL_PRIEST_DEVOURING_PLAGUE_HEAL = 75999,
    SPELL_PRIEST_DIVINE_AEGIS = 47753,
    SPELL_PRIEST_DIVINE_HYMN_HEAL = 64844,
    SPELL_PRIEST_DIVINE_WORD = 81033,
    SPELL_PRIEST_DIVINE_WORD_AURA = 81034,
    SPELL_PRIEST_DIVINE_FAVOR_CHASTISE = 81035,
    SPELL_PRIEST_DIVINE_FAVOR_SANCTIFY = 81036,
    SPELL_PRIEST_DIVINE_FAVOR_SERENITY = 81037,
    SPELL_PRIEST_EMPOWERED_RENEW = 63544,
    SPELL_PRIEST_EMPYREAL_BLAZE_BUFF = 81028,
    SPELL_PRIEST_EMPYREAL_BLAZE_LISTENER = 81039,
    SPELL_PRIEST_FLASH_HEAL = 48071,
    SPELL_PRIEST_GLYPH_OF_CIRCLE_OF_HEALING = 55675,
    SPELL_PRIEST_GLYPH_OF_LIGHTWELL = 55673,
    SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL = 56161,
    SPELL_PRIEST_GUARDIAN_SPIRIT = 47788,
    SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL = 48153,
    SPELL_PRIEST_HOLY_FIRE = 48135,
    SPELL_PRIEST_HOLY_WORD_CHASTISE = 81026,
    SPELL_PRIEST_HOLY_WORD_SALVATION = 81032,
    SPELL_PRIEST_HOLY_WORD_SALVATION_MENDING = 81040,
    SPELL_PRIEST_HOLY_WORD_SANCTIFY = 81029,
    SPELL_PRIEST_HOLY_WORD_SERENITY = 81025,
    SPELL_PRIEST_INSANITY_ENERGIZE = 81093,
    SPELL_PRIEST_ITEM_EFFICIENCY = 37595,
    SPELL_PRIEST_LEAP_OF_FAITH = 81003,
    SPELL_PRIEST_LEAP_OF_FAITH_PROC = 81004,
    SPELL_PRIEST_LEAP_OF_FAITH_GRAB = 81005,
    SPELL_PRIEST_LIGHTWELL_CHARGES = 59907,
    SPELL_PRIEST_MANA_LEECH_PROC = 34650,
    SPELL_PRIEST_MASS_RESURRECTION = 81002,
    SPELL_PRIEST_PENANCE_R1 = 47540,
    SPELL_PRIEST_PENANCE_PERIODIC_DAMAGE = 47758,
    SPELL_PRIEST_PENANCE_PERIODIC_HEAL = 47757,
    SPELL_PRIEST_POWER_INFUSION = 10060,
    SPELL_PRIEST_POWER_WORD_LIFE = 81006,
    SPELL_PRIEST_POWER_WORD_LIFE_LISTENER = 81007,
    SPELL_PRIEST_POWER_WORD_RADIANCE = 00000,
    SPELL_PRIEST_POWER_WORD_SHIELD = 48066,
    SPELL_PRIEST_PRAYER_OF_HEALING = 48072,
    SPELL_PRIEST_PRAYER_OF_MENDING = 48113,
    SPELL_PRIEST_PRAYER_OF_MENDING_HEAL = 48111,
    SPELL_PRIEST_PRESCIENCE_SPELL = 86217,
    SPELL_PRIEST_PURGE_THE_WICKED = 81017,
    SPELL_PRIEST_PURGE_THE_WICKED_AOE = 81018,
    SPELL_PRIEST_RAPTURE = 81019,
    SPELL_PRIEST_REFLECTIVE_SHIELD_TRIGGERED = 33619,
    SPELL_PRIEST_REFLECTIVE_SHIELD_R1 = 33201,
    SPELL_PRIEST_RENEW = 48068,
    SPELL_PRIEST_SHADOW_WORD_DEATH = 48158,
    SPELL_PRIEST_SHADOW_WORD_DEATH_SELFDAMAGE = 32409,
    SPELL_PRIEST_SHADOW_WORD_PAIN = 48125,
    SPELL_PRIEST_SHADOWY_APPARITIONS_AOE = 81085,
    SPELL_PRIEST_SHADOWY_APPARITIONS_DAMAGE = 81086,
    SPELL_PRIEST_T9_HEALING_2P = 67201,
    SPELL_PRIEST_VAMPIRIC_TOUCH = 48160,
    SPELL_PRIEST_VAMPIRIC_TOUCH_DISPEL = 64085,
    SPELL_PRIEST_VAMPIRIC_TOUCH_HEAL = 81000,
    SPELL_PRIEST_VOID_BOLT = 81045,
    SPELL_PRIEST_VOID_ERUPTION = 81042,
    SPELL_PRIEST_VOID_ERUPTION_DAMAGE = 81043,
    SPELL_PRIEST_VOIDFORM = 81044,
    SPELL_PRIEST_WAVE_OF_LIGHT_SHIELD = 86307,
    SPELL_PRIEST_HOLY_FLAME_DAMAGE = 86206,
    SPELL_PRIEST_HOLY_FLAME_HEAL = 86207,
    SPELL_PRIEST_HOLY_MIGHT = 86208,
    SPELL_PRIEST_HOLY_MIGHT_STRENGTH = 86209,
    SPELL_PRIEST_HOLY_MIGHT_AGILITY = 86210,
    SPELL_PRIEST_HOLY_MIGHT_INTELLECT = 86211,
    SPELL_PRIEST_HOLY_MIGHT_SPIRIT = 86212,
    SPELL_PRIEST_HOLY_MIGHT_AOE = 86214,
    SPELL_PRIEST_HOLY_WOUNDS_PROC = 86222,
    SPELL_PRIEST_HOLY_STRIKE = 86215,
    SPELL_PRIEST_HOLY_ERUPTION = 86204,
    SPELL_PRIEST_HOLY_ERUPTION_LIGHT_OVERLOAD = 86301,
    SPELL_PRIEST_BLISTERING_BARRIER = 86200,
    SPELL_PRIEST_BLISTERING_BARRIER_PROC = 86201,
    SPELL_PRIEST_POWER_WORD_SOLACE = 81016,
    SPELL_PRIEST_SHADOW_COVENANT = 81020,
    SPELL_PRIEST_EVANGELISM = 81021,
    SPELL_PRIEST_GREATER_HEAL = 48063,
    SPELL_PRIEST_HOLY_WORD_CHASTITE = 81026,
    SPELL_PRIEST_DESPERATE_PRAYER = 19243,
    SPELL_PRIEST_MIND_FLAY_DAMAGE = 58381,
    SPELL_PRIEST_LIGHTS_FADE = 86216,

    // Passives
    SPELL_GENERIC_ARENA_DAMPENING = 74410,
    SPELL_GENERIC_BATTLEGROUND_DAMPENING = 74411,
    SPELL_PRIEST_TWIN_DISCIPLINE_R1 = 47586,
    SPELL_PRIEST_SPIRITUAL_HEALING_R1 = 14898,
    SPELL_PRIEST_DIVINE_PROVIDENCE_R1 = 47562,

    // Talents
    TALENT_PRIEST_HOLY_WEAVING_PROC = 86252,
    TALENT_PRIEST_HOLY_BURST_PROC = 86281,
    TALENT_PRIEST_DEFY_FATE_HEAL = 86286,
    TALENT_PRIEST_DEFY_FATE_COOLDOWN = 86287,
    TALENT_PRIEST_CELERITY_R1 = 86246,
    TALENT_PRIEST_CELERITY_R2 = 86247,
    TALENT_PRIEST_CELERITY_R3 = 86248,
    TALENT_PRIEST_CELERITY_R1_BUFF = 86308,
    TALENT_PRIEST_CELERITY_R2_BUFF = 86309,
    TALENT_PRIEST_CELERITY_R3_BUFF = 86310,
    TALENT_PRIEST_CELERITY = 86246,
    TALENT_PRIEST_EMPOWERED_RENEW = 63534,
    TALENT_PRIEST_PAIN_AND_SUFFERING = 47580,
    TALENT_PRIEST_TWISTED_FAITH = 47573,
    TALENT_PRIEST_HOLY_BURST = 86278,
    TALENT_PRIEST_TIMELY_FAITH = 86293,

    // Runes
    RUNE_PRIEST_CRYSTALLINE_REFLECTION_DAMAGE = 900366,
    RUNE_PRIEST_SHIELD_DISCIPLINE_ENERGIZE = 900374,
    RUNE_PRIEST_PRAYERFUL_LITANY_HEAL = 900418,
    RUNE_PRIEST_PRAYERFUL_LITANY_LISTENER = 900419,
    RUNE_PRIEST_MENTAL_FORTITUDE_SHIELD = 901156,
    RUNE_PRIEST_HOLY_BLOOD_SHIELD = 901428,
    RUNE_PRIEST_LIGHTS_WARD_SHIELD = 901620,

    // Sets
    T1_PRIEST_DISCI_4PC = 98501,
    T1_PRIEST_SHADOW_2PC_SHADOW_WORD_DEATH = 98701,
    T1_PRIEST_SHADOW_2PC = 98700,
    T1_PRIEST_SHADOW_4PC = 98705,
    T1_PRIEST_SHADOW_4PC_BUFF = 98706,
    T1_PRIEST_ABSOLUTION_2PC = 98800,
    T1_PRIEST_ABSOLUTION_4PC_BUFF = 98802,
    T1_PRIEST_ABSOLUTION_4PC_DAMAGE = 98803,
};

enum PriestSpellIcons
{
    PRIEST_ICON_ID_BORROWED_TIME = 2899,
    PRIEST_ICON_ID_EMPOWERED_RENEW_TALENT = 3021,
    PRIEST_ICON_ID_PAIN_AND_SUFFERING = 2874,
};

enum Mics
{
    PRIEST_LIGHTWELL_NPC_1 = 31897,
    PRIEST_LIGHTWELL_NPC_2 = 31896,
    PRIEST_LIGHTWELL_NPC_3 = 31895,
    PRIEST_LIGHTWELL_NPC_4 = 31894,
    PRIEST_LIGHTWELL_NPC_5 = 31893,
    PRIEST_LIGHTWELL_NPC_6 = 31883
};

class spell_pri_shadowfiend_scaling : public AuraScript
{
    PrepareAuraScript(spell_pri_shadowfiend_scaling);

    Aura* GetPowerfulShadowfiendAura(Unit* caster)
    {
        for (size_t i = 900544; i < 900550; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetFiendFriendAura(Unit* caster)
    {
        for (size_t i = 900558; i < 900564; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetRabidShadowsAura(Unit* caster)
    {
        for (size_t i = 900564; i < 900570; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetPutrefyingClawsAura(Unit* caster)
    {
        for (size_t i = 900576; i < 900582; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetEssenceDevourerAura(Unit* caster)
    {
        for (size_t i = 900590; i < 900596; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void CalculateResistanceAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        // xinef: shadowfiend inherits 40% of resistance from owner and 35% of armor (guessed)
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            SpellSchoolMask schoolMask = SpellSchoolMask(aurEff->GetSpellInfo()->Effects[aurEff->GetEffIndex()].MiscValue);
            int32 modifier = schoolMask == SPELL_SCHOOL_MASK_NORMAL ? 35 : 40;
            amount = CalculatePct(std::max<int32>(0, owner->GetResistance(schoolMask)), modifier);
        }
    }

    void CalculateStatAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
    {
        // xinef: shadowfiend inherits 30% of intellect and 65% of stamina (guessed)
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            Stats stat = Stats(aurEff->GetSpellInfo()->Effects[aurEff->GetEffIndex()].MiscValue);
            amount = CalculatePct(std::max<int32>(0, owner->GetStat(stat)), stat == STAT_STAMINA ? 65 : 30);
        }
    }

    void CalculateAPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // xinef: shadowfiend inherits 333% of SP as AP - 35.7% of damage increase per hit
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
            int32 spellPowerPCT = 300;

            if (Aura* runeAura = GetPowerfulShadowfiendAura(owner))
                AddPct(spellPowerPCT, runeAura->GetEffect(EFFECT_0)->GetAmount());

            amount = CalculatePct(std::max<int32>(0, shadow), 300); // xinef: deacrased to 300, including 15% from self buff           
        }
    }

    void CalculateSPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // xinef: shadowfiend inherits 30% of SP
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            int32 shadow = owner->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW);
            amount = CalculatePct(std::max<int32>(0, shadow), 30);

            if (Aura* runeAura = GetFiendFriendAura(owner))
                AddPct(amount, runeAura->GetEffect(EFFECT_0)->GetAmount());

            // xinef: Update appropriate player field
            if (owner->GetTypeId() == TYPEID_PLAYER)
                owner->SetUInt32Value(PLAYER_PET_SPELL_POWER, (uint32)amount);
        }
    }

    void HandleEffectApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        GetUnitOwner()->ApplySpellImmune(0, IMMUNITY_STATE, aurEff->GetAuraType(), true, SPELL_BLOCK_TYPE_POSITIVE);
        if (aurEff->GetAuraType() == SPELL_AURA_MOD_ATTACK_POWER)
            GetUnitOwner()->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_ATTACK_POWER_PCT, true, SPELL_BLOCK_TYPE_POSITIVE);
        else if (aurEff->GetAuraType() == SPELL_AURA_MOD_STAT)
            GetUnitOwner()->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE, true, SPELL_BLOCK_TYPE_POSITIVE);

        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            if (Aura* runeAura = GetPowerfulShadowfiendAura(owner))
            {
                int32 procSpell = runeAura->GetEffect(EFFECT_1)->GetAmount();
                owner->AddAura(procSpell, GetUnitOwner());
            }

            if (Aura* runeAura = GetRabidShadowsAura(owner))
            {
                int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
                owner->AddAura(procSpell, GetUnitOwner());
            }

            if (Aura* runeAura = GetPutrefyingClawsAura(owner))
            {
                int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
                owner->AddAura(procSpell, GetUnitOwner());
            }

            if (Aura* runeAura = GetEssenceDevourerAura(owner))
            {
                int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
                owner->AddAura(procSpell, GetUnitOwner());
            }
        }
    }

    void Register() override
    {
        if (m_scriptSpellId != 35661)
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_shadowfiend_scaling::CalculateResistanceAmount, EFFECT_ALL, SPELL_AURA_MOD_RESISTANCE);

        if (m_scriptSpellId == 35661 || m_scriptSpellId == 35662)
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_shadowfiend_scaling::CalculateStatAmount, EFFECT_ALL, SPELL_AURA_MOD_STAT);

        if (m_scriptSpellId == 35661)
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_shadowfiend_scaling::CalculateAPAmount, EFFECT_ALL, SPELL_AURA_MOD_ATTACK_POWER);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_shadowfiend_scaling::CalculateSPAmount, EFFECT_ALL, SPELL_AURA_MOD_DAMAGE_DONE);
        }

        OnEffectApply += AuraEffectApplyFn(spell_pri_shadowfiend_scaling::HandleEffectApply, EFFECT_ALL, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

// -34861 - Circle of Healing
class spell_pri_circle_of_healing : public SpellScript
{
    PrepareSpellScript(spell_pri_circle_of_healing);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_GLYPH_OF_CIRCLE_OF_HEALING });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::RaidCheck(GetCaster(), false));

        uint32 const maxTargets = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(GetCaster());

        if (targets.size() > maxTargets)
        {
            targets.sort(Acore::HealthPctOrderPred());
            targets.resize(maxTargets);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_circle_of_healing::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// -47509 - Divine Aegis
class spell_pri_divine_aegis : public AuraScript
{
    PrepareAuraScript(spell_pri_divine_aegis);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_DIVINE_AEGIS });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcTarget();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        int32 absorb = CalculatePct(int32(eventInfo.GetHealInfo()->GetHeal()), aurEff->GetAmount());

        // Multiple effects stack, so let's try to find this aura.
        if (AuraEffect const* aegis = eventInfo.GetProcTarget()->GetAuraEffect(SPELL_PRIEST_DIVINE_AEGIS, EFFECT_0))
            absorb += aegis->GetAmount();

        absorb = std::min(absorb, eventInfo.GetProcTarget()->getLevel() * 125);

        GetTarget()->CastCustomSpell(SPELL_PRIEST_DIVINE_AEGIS, SPELLVALUE_AURA_CHARGE, absorb, eventInfo.GetProcTarget(), true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pri_divine_aegis::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pri_divine_aegis::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 64844 - Divine Hymn
class spell_pri_divine_hymn : public SpellScript
{
    PrepareSpellScript(spell_pri_divine_hymn);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::RaidCheck(GetCaster(), false));
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_divine_hymn::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

// 55680 - Glyph of Prayer of Healing
class spell_pri_glyph_of_prayer_of_healing : public AuraScript
{
    PrepareAuraScript(spell_pri_glyph_of_prayer_of_healing);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        HealInfo* healInfo = eventInfo.GetHealInfo();
        if (!healInfo || !healInfo->GetHeal())
        {
            return;
        }

        SpellInfo const* triggeredSpellInfo = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL);
        int32 heal = int32(CalculatePct(int32(healInfo->GetHeal()), aurEff->GetAmount()) / triggeredSpellInfo->GetMaxTicks());
        GetTarget()->CastCustomSpell(SPELL_PRIEST_GLYPH_OF_PRAYER_OF_HEALING_HEAL, SPELLVALUE_BASE_POINT0, heal, eventInfo.GetProcTarget(), true, nullptr, aurEff);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_glyph_of_prayer_of_healing::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 47788 - Guardian Spirit
class spell_pri_guardian_spirit : public AuraScript
{
    PrepareAuraScript(spell_pri_guardian_spirit);

    uint32 healPct;

    Aura* GetGuardianAngelAura(Unit* caster)
    {
        for (size_t i = 901020; i < 901026; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetGuardiansoftheLightAura(Unit* caster)
    {
        for (size_t i = 901026; i < 901032; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL });
    }

    bool Load() override
    {
        healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue();
        return true;
    }

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* runeAura = GetGuardiansoftheLightAura(caster))
        {
            if (target != caster)
            {
                int32 procPct = runeAura->GetEffect(EFFECT_0)->GetAmount();
                int32 amount0 = CalculatePct(aurEff->GetAmount(), procPct);
                int32 amount1 = CalculatePct(GetEffect(EFFECT_1)->GetAmount(), procPct);

                caster->AddAura(SPELL_PRIEST_GUARDIAN_SPIRIT, caster);
                if (Aura* guardianAura = caster->GetAura(SPELL_PRIEST_GUARDIAN_SPIRIT))
                {
                    guardianAura->GetEffect(EFFECT_0)->ChangeAmount(amount0);
                    guardianAura->GetEffect(EFFECT_1)->ChangeAmount(amount1);
                }
            }
        }
    }

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void Absorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetTarget();

        if (!target || caster->isDead())
            return;

        if (dmgInfo.GetDamage() < target->GetHealth() || hasSavedTheTarget)
            return;

        int32 healAmount = int32(target->CountPctFromMaxHealth(healPct));
        // Remove the aura now, we don't want 40% healing bonus if you don't have the Guardian Angel Rune.
        if (!GetGuardianAngelAura(caster))
            Remove(AURA_REMOVE_BY_ENEMY_SPELL);

        target->CastCustomSpell(target, SPELL_PRIEST_GUARDIAN_SPIRIT_HEAL, &healAmount, nullptr, nullptr, true);
        absorbAmount = dmgInfo.GetDamage();
        hasSavedTheTarget = true;
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            // Reduce cooldown if you have the Guardian Angel Rune and Guardien Spirit hasn't saved the target.
            if (Aura* runeAura = GetGuardianAngelAura(caster))
                if (!hasSavedTheTarget)
                {
                    int32 cooldown = runeAura->GetEffect(EFFECT_0)->GetAmount();
                    int32 remainingCooldown = player->GetSpellCooldownDelay(SPELL_PRIEST_GUARDIAN_SPIRIT);
                    cooldown = remainingCooldown - cooldown;
                    player->ModifySpellCooldown(SPELL_PRIEST_GUARDIAN_SPIRIT, -cooldown);
                }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_guardian_spirit::HandleApply, EFFECT_0, SPELL_AURA_MOD_HEALING_PCT, AURA_EFFECT_HANDLE_REAL);
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_guardian_spirit::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_guardian_spirit::Absorb, EFFECT_1);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_guardian_spirit::HandleRemove, EFFECT_0, SPELL_AURA_MOD_HEALING_PCT, AURA_EFFECT_HANDLE_REAL);
    }
private:
    bool hasSavedTheTarget = false;
};

// 64904 - Hymn of Hope
class spell_pri_hymn_of_hope : public SpellScript
{
    PrepareSpellScript(spell_pri_hymn_of_hope);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::PowerCheck(POWER_MANA, false));
        targets.remove_if(Acore::RaidCheck(GetCaster(), false));

        uint32 const maxTargets = 3;

        if (targets.size() > maxTargets)
        {
            targets.sort(Acore::PowerPctOrderPred(POWER_MANA));
            targets.resize(maxTargets);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_hymn_of_hope::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

// 37594 - Greater Heal Refund
class spell_pri_item_greater_heal_refund : public AuraScript
{
    PrepareAuraScript(spell_pri_item_greater_heal_refund);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_ITEM_EFFICIENCY });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (HealInfo* healInfo = eventInfo.GetHealInfo())
            if (Unit* healTarget = healInfo->GetTarget())
                if (eventInfo.GetHitMask() & PROC_EX_NO_OVERHEAL && healTarget->IsFullHealth())
                    return true;
        return false;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(GetTarget(), SPELL_PRIEST_ITEM_EFFICIENCY, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pri_item_greater_heal_refund::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pri_item_greater_heal_refund::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};


class spell_pri_lightwell : public SpellScript
{
    PrepareSpellScript(spell_pri_lightwell);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::ObjectGUIDCheck(GetCaster()->GetGUID(), true));
        targets.remove_if([&](WorldObject* target) -> bool
            {
                return !target->ToUnit() || target->ToUnit()->HealthAbovePct(50) || target->ToUnit()->HasAura(SPELL_PRIEST_LIGHTWELL_RENEW);
            });

        if (!targets.empty())
        {
            Acore::Containers::RandomResize(targets, 1);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_lightwell::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

class spell_pri_lightwell_renew : public AuraScript
{
    PrepareAuraScript(spell_pri_lightwell_renew);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* aura = caster->GetAura(SPELL_PRIEST_LIGHTWELL_CHARGE)) {
            if (aura->GetCharges() <= 0)
                aura->Remove();
            else
                aura->SetCharges(aura->GetCharges() - 1);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_lightwell_renew::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

// 8129 - Mana Burn
class spell_pri_mana_burn : public SpellScript
{
    PrepareSpellScript(spell_pri_mana_burn);

    void HandleAfterHit()
    {
        if (Unit* unitTarget = GetHitUnit())
            unitTarget->RemoveAurasWithMechanic((1 << MECHANIC_FEAR) | (1 << MECHANIC_POLYMORPH));
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_pri_mana_burn::HandleAfterHit);
    }
};

// 28305 - Mana Leech (Passive) (Priest Pet Aura)
class spell_pri_mana_leech : public AuraScript
{
    PrepareAuraScript(spell_pri_mana_leech);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_MANA_LEECH_PROC });
    }

    bool Load() override
    {
        _procTarget = nullptr;
        return true;
    }

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        _procTarget = GetTarget()->GetOwner();
        return _procTarget;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(_procTarget, SPELL_PRIEST_MANA_LEECH_PROC, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pri_mana_leech::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pri_mana_leech::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }

private:
    Unit* _procTarget;
};

// -49821 - Mind Sear
class spell_pri_mind_sear : public SpellScript
{
    PrepareSpellScript(spell_pri_mind_sear);

    void FilterTargets(std::list<WorldObject*>& unitList)
    {
        unitList.remove_if(Acore::ObjectGUIDCheck(GetCaster()->GetGuidValue(UNIT_FIELD_CHANNEL_OBJECT), true));
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_mind_sear::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 47580-47582 - Pain and Suffering
class spell_pri_pain_and_suffering_proc : public AuraScript
{
    PrepareAuraScript(spell_pri_pain_and_suffering_proc);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        // Refresh Shadow Word: Pain and Vampiric Touch on target
        if (Unit* unitTarget = eventInfo.GetActionTarget())
        {
            if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_PRIEST_SHADOW_WORD_PAIN, EFFECT_0))
                aur->GetBase()->RefreshTimersWithMods();
            if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_PRIEST_VAMPIRIC_TOUCH, EFFECT_0))
                aur->GetBase()->RefreshTimersWithMods();
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_pain_and_suffering_proc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// -47540 - Penance
class spell_pri_penance : public SpellScript
{
    PrepareSpellScript(spell_pri_penance);

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    bool Validate(SpellInfo const* spellInfo) override
    {
        SpellInfo const* firstRankSpellInfo = sSpellMgr->GetSpellInfo(SPELL_PRIEST_PENANCE_R1);
        if (!firstRankSpellInfo)
            return false;

        // can't use other spell than this penance due to spell_ranks dependency
        if (!spellInfo->IsRankOf(firstRankSpellInfo))
            return false;

        uint8 rank = spellInfo->GetRank();
        if (!sSpellMgr->GetSpellWithRank(SPELL_PRIEST_PENANCE_PERIODIC_DAMAGE, rank, true))
            return false;
        if (!sSpellMgr->GetSpellWithRank(SPELL_PRIEST_PENANCE_PERIODIC_HEAL, rank, true))
            return false;

        return true;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (Unit* unitTarget = GetHitUnit())
        {
            if (!unitTarget->IsAlive())
                return;

            uint8 rank = GetSpellInfo()->GetRank();

            if (caster->IsFriendlyTo(unitTarget))
                caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PRIEST_PENANCE_PERIODIC_HEAL, rank), false);
            else
            {
                caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PRIEST_PENANCE_PERIODIC_DAMAGE, rank), false);
            }

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
        OnEffectHitTarget += SpellEffectFn(spell_pri_penance::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnCheckCast += SpellCheckCastFn(spell_pri_penance::CheckCast);
    }
};

// 47758 - Penance (damage periodic) / 47757 - Penance (heal periodic)
class spell_pri_penance_hit : public SpellScript
{
    PrepareSpellScript(spell_pri_penance_hit);

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!caster->HasAura(SPELL_PRIEST_PENANCE_PERIODIC_DAMAGE) && !caster->HasAura(SPELL_PRIEST_PENANCE_PERIODIC_HEAL))
        {
            // Remove Power of the Dark Side buff.
            for (size_t i = 900810; i < 900816; i++)
            {
                if (caster->HasAura(i))
                    caster->RemoveAura(i);
            }

            // Remove Resonating Penance buff.
            for (size_t i = 900834; i < 900840; i++)
            {
                if (caster->HasAura(i))
                    caster->RemoveAura(i);
            }
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_pri_penance_hit::HandleAfterHit);
    }
};

// -47540 - Penance Purge the Wicked
class spell_pri_penance_purge : public SpellScript
{
    PrepareSpellScript(spell_pri_penance_purge);

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* unitTarget = GetHitUnit();

        if (!unitTarget->IsAlive())
            return;

        if (unitTarget->HasAura(SPELL_PRIEST_PURGE_THE_WICKED))
            caster->CastSpell(unitTarget, SPELL_PRIEST_PURGE_THE_WICKED_AOE, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_penance_purge::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 48066 - Power Word: Shield
static int32 CalculateSpellAmount(Unit* caster, float ratio, int32 amount, SpellInfo const* spellInfo, const AuraEffect* aurEff)
{
    // ratio from sp bonus
    float bonus = ratio / 100;

    // Borrowed Time
    if (AuraEffect const* borrowedTime = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, PRIEST_ICON_ID_BORROWED_TIME, EFFECT_1))
        bonus += CalculatePct(1.0f, borrowedTime->GetAmount());

    bonus *= caster->SpellBaseHealingBonusDone(spellInfo->GetSchoolMask());

    // Improved PW: Shield: its weird having a SPELLMOD_ALL_EFFECTS here but its blizzards doing :)
    // Improved PW: Shield is only applied at the spell healing bonus because it was already applied to the base value in CalculateSpellDamage
    bonus = caster->ApplyEffectModifiers(spellInfo, aurEff->GetEffIndex(), bonus);
    bonus *= caster->CalculateLevelPenalty(spellInfo);

    amount += int32(bonus);

    // Rapture
    if (AuraEffect const* rapture = caster->GetAuraEffect(SPELL_PRIEST_RAPTURE, EFFECT_2))
        AddPct(amount, rapture->GetAmount());

    // Twin Disciplines
    if (AuraEffect const* twinDisciplines = caster->GetAuraEffect(SPELL_AURA_ADD_PCT_MODIFIER, SPELLFAMILY_PRIEST, 0x400000, 0, 0, caster->GetGUID()))
        AddPct(amount, twinDisciplines->GetAmount());

    // Focused Power, xinef: apply positive modifier only
    if (int32 healModifier = caster->GetMaxPositiveAuraModifier(SPELL_AURA_MOD_HEALING_DONE_PERCENT))
        AddPct(amount, healModifier);

    // Arena - Dampening
    if (AuraEffect const* arenaDampening = caster->GetAuraEffect(SPELL_GENERIC_ARENA_DAMPENING, EFFECT_0))
    {
        AddPct(amount, arenaDampening->GetAmount());
    }
    // Battleground - Dampening
    else if (AuraEffect const* bgDampening = caster->GetAuraEffect(SPELL_GENERIC_BATTLEGROUND_DAMPENING, EFFECT_0))
    {
        AddPct(amount, bgDampening->GetAmount());
    }

    // Weal and Woe Rune Buff
    for (size_t i = 900798; i < 900804; i++)
    {
        if (AuraEffect const* runeBuff = caster->GetAuraEffect(i, EFFECT_0))
        {
            AddPct(amount, runeBuff->GetAmount());
            caster->RemoveAura(i);
        }
    }

    return amount;
};

class spell_pri_power_word_shield_aura : public AuraScript
{
    PrepareAuraScript(spell_pri_power_word_shield_aura);

    Aura* GetBodyAndSoulAura(Unit* caster)
    {
        for (size_t i = 900336; i < 900342; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetCrystallineReflectionAura(Unit* caster)
    {
        for (size_t i = 900354; i < 900360; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetShieldDisciplineAura(Unit* caster)
    {
        for (size_t i = 900368; i < 900374; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetAegisOfWrathAura(Unit* caster)
    {
        for (size_t i = 900382; i < 900388; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetWordsOfThePiousAura(Unit* caster)
    {
        for (size_t i = 900388; i < 900394; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetIndemnityAura(Unit* caster)
    {
        for (size_t i = 900882; i < 900888; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_REFLECTIVE_SHIELD_TRIGGERED, SPELL_PRIEST_REFLECTIVE_SHIELD_R1 });
    }

    void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& canBeRecalculated)
    {
        canBeRecalculated = false;
        float ratio = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(GetCaster());
        if (Unit* caster = GetCaster())
        {
            amount = CalculateSpellAmount(caster, ratio, amount, GetSpellInfo(), aurEff);

            if (Aura* runeAura = GetAegisOfWrathAura(caster))
            {
                int32 increasePct = runeAura->GetEffect(EFFECT_0)->GetAmount();
                AddPct(amount, increasePct);
            }
        }
    }

    void ReflectDamage(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* caster = GetCaster();
        Unit* owner = GetUnitOwner();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetTarget();
        if (dmgInfo.GetAttacker() == target)
            return;

        if (owner)
            if (AuraEffect* talentAurEff = owner->GetAuraEffectOfRankedSpell(SPELL_PRIEST_REFLECTIVE_SHIELD_R1, EFFECT_0))
            {
                int32 bp = CalculatePct(absorbAmount, talentAurEff->GetAmount());
                // xinef: prevents infinite loop!
                if (!dmgInfo.GetSpellInfo() || dmgInfo.GetSpellInfo()->Id != SPELL_PRIEST_REFLECTIVE_SHIELD_TRIGGERED)
                    target->CastCustomSpell(dmgInfo.GetAttacker(), SPELL_PRIEST_REFLECTIVE_SHIELD_TRIGGERED, &bp, nullptr, nullptr, true, nullptr, aurEff);
            }

        if (Aura* runeAura = GetCrystallineReflectionAura(caster))
        {
            int32 damagePct = runeAura->GetEffect(EFFECT_0)->GetAmount();
            int32 amount = CalculatePct(absorbAmount, damagePct);

            caster->CastCustomSpell(RUNE_PRIEST_CRYSTALLINE_REFLECTION_DAMAGE, SPELLVALUE_BASE_POINT0, amount, dmgInfo.GetAttacker(), TRIGGERED_FULL_MASK);
        }

        if (Aura* runeAura = GetShieldDisciplineAura(caster))
            if (dmgInfo.GetUnmitigatedDamage() > aurEff->GetAmount())
            {
                int32 manaPct = runeAura->GetEffect(EFFECT_0)->GetAmount();
                int32 amount = CalculatePct(caster->GetMaxPower(POWER_MANA), manaPct) / 10;

                caster->CastCustomSpell(RUNE_PRIEST_SHIELD_DISCIPLINE_ENERGIZE, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
            }
    }

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();
        Unit* target = GetUnitOwner();

        if (!caster || caster->isDead())
            return;

        if (!target || target->isDead())
            return;

        if (caster->HasAura(SPELL_PRIEST_AUTONEMENT))
        {
            caster->AddAura(SPELL_PRIEST_AUTONEMENT_AURA, target);

            if (Aura* runeAura = GetIndemnityAura(caster))
            {
                int32 duration = runeAura->GetEffect(EFFECT_0)->GetAmount();

                if (Aura* atonement = target->GetAura(SPELL_PRIEST_AUTONEMENT_AURA))
                    atonement->SetDuration(atonement->GetDuration() + duration);
            }
        }

        if (Aura* runeAura = GetBodyAndSoulAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, target);
        }

        if (Aura* runeAura = GetCrystallineReflectionAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_1)->GetAmount();

            caster->CastSpell(target, procSpell, TRIGGERED_FULL_MASK);
        }

        if (Aura* runeAura = GetWordsOfThePiousAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, caster);
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

        if (Aura* runeAura = GetAegisOfWrathAura(caster))
        {
            int32 reducPct = runeAura->GetEffect(EFFECT_1)->GetAmount();
            int32 amount = GetEffect(EFFECT_0)->GetAmount();
            int32 reduction = CalculatePct(amount, reducPct);

            if (reduction > 0)
                GetEffect(EFFECT_0)->ChangeAmount(amount - reduction);
        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_power_word_shield_aura::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_pri_power_word_shield_aura::ReflectDamage, EFFECT_0);
        OnEffectApply += AuraEffectApplyFn(spell_pri_power_word_shield_aura::HandleProc, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_power_word_shield_aura::HandlePeriodic, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_pri_power_word_shield : public SpellScript
{
    PrepareSpellScript(spell_pri_power_word_shield);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        if (!target)
            return SPELL_FAILED_BAD_TARGETS;

        if (AuraEffect* aurEff = target->GetAuraEffect(SPELL_AURA_SCHOOL_ABSORB, (SpellFamilyNames)GetSpellInfo()->SpellFamilyName, GetSpellInfo()->SpellIconID, EFFECT_0))
        {
            int32 newAmount = GetSpellInfo()->Effects[EFFECT_0].CalcValue(caster, nullptr, nullptr);
            float ratio = GetSpellInfo()->Effects[EFFECT_1].CalcValue(caster, nullptr, nullptr);
            newAmount = CalculateSpellAmount(caster, ratio, newAmount, GetSpellInfo(), aurEff);

            if (aurEff->GetAmount() > newAmount)
                return SPELL_FAILED_AURA_BOUNCED;
        }

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pri_power_word_shield::CheckCast);
    }
};

//// 48066 - Power Word: Shield
//class spell_pri_power_word_shield_atonement : public AuraScript
//{
//    PrepareAuraScript(spell_pri_power_word_shield_atonement);
//
//    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
//    {
//        Unit* caster = GetCaster();
//        Unit* target = GetUnitOwner();
//
//        if (!caster || caster->isDead())
//            return;
//        if (!caster->HasAura(SPELL_PRIEST_AUTONEMENT))
//            return;
//        
//        caster->AddAura(SPELL_PRIEST_AUTONEMENT_AURA, target);
//    }
//
//    void Register() override
//    {
//        OnEffectApply += AuraEffectApplyFn(spell_pri_power_word_shield_atonement::HandleProc, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
//    }
//};

// 33110 - Prayer of Mending Heal
class spell_pri_prayer_of_mending_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_prayer_of_mending_heal);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_PRIEST_T9_HEALING_2P,
                SPELL_PRIEST_TWIN_DISCIPLINE_R1,
                SPELL_PRIEST_SPIRITUAL_HEALING_R1,
                SPELL_PRIEST_DIVINE_PROVIDENCE_R1
            });
    }

    void HandleHeal(SpellEffIndex /*effIndex*/)
    {
        if (Unit* caster = GetOriginalCaster())
        {
            int32 heal = GetEffectValue();
            if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_PRIEST_T9_HEALING_2P, EFFECT_0))
            {
                AddPct(heal, aurEff->GetAmount());
            }
            if (AuraEffect* aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_PRIEST_TWIN_DISCIPLINE_R1, EFFECT_0))
            {
                AddPct(heal, aurEff->GetAmount());
            }
            if (AuraEffect* aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_PRIEST_SPIRITUAL_HEALING_R1, EFFECT_0))
            {
                AddPct(heal, aurEff->GetAmount());
            }
            if (AuraEffect* aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_PRIEST_DIVINE_PROVIDENCE_R1, EFFECT_0))
            {
                AddPct(heal, aurEff->GetAmount());
            }
            SetEffectValue(heal);
        }
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_pri_prayer_of_mending_heal::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 48158 - Shadow Word: Death
class spell_pri_shadow_word_death : public SpellScript
{
    PrepareSpellScript(spell_pri_shadow_word_death);

    Aura* GetDeathspeakerBuff(Unit* caster)
    {
        for (size_t i = 900668; i < 900674; i++)
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

        target = GetHitUnit();

        if (!target || target->isDead())
            return;

        damage = GetHitDamage();

        if (target->HealthBelowPct(20) || GetDeathspeakerBuff(caster))
            damage *= GetSpellInfo()->GetEffect(EFFECT_1).BonusMultiplier;
        else if (target->HealthBelowPct(50))
            damage *= GetSpellInfo()->GetEffect(EFFECT_1).DamageMultiplier;

        SetHitDamage(damage);

        if (caster->HasAura(T1_PRIEST_SHADOW_2PC))
        {
            int32 amount = CalculatePct(damage, 30);
            caster->CastCustomSpell(T1_PRIEST_SHADOW_2PC_SHADOW_WORD_DEATH, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);

            if (GetDeathspeakerBuff(caster) || target->HealthBelowPct(20))
                caster->CastCustomSpell(T1_PRIEST_SHADOW_2PC_SHADOW_WORD_DEATH, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!target || target->isDead())
            return;

        if (Aura* buff = GetDeathspeakerBuff(caster))
            buff->Remove();
        else
        {
            if (Aura* painAndSuffering = caster->GetAuraOfRankedSpell(TALENT_PRIEST_PAIN_AND_SUFFERING))
                damage -= CalculatePct(damage, painAndSuffering->GetEffect(EFFECT_1)->GetAmount());

            caster->CastCustomSpell(SPELL_PRIEST_SHADOW_WORD_DEATH_SELFDAMAGE, SPELLVALUE_BASE_POINT0, damage, caster, TRIGGERED_FULL_MASK);

            if (caster->HasAura(T1_PRIEST_SHADOW_4PC))
                caster->CastSpell(caster, T1_PRIEST_SHADOW_4PC_BUFF, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_shadow_word_death::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_pri_shadow_word_death::HandleAfterHit);
    }

private:
    int32 damage = 0;
    Unit* target;
};

// -34914 - Vampiric Touch
class spell_pri_vampiric_touch : public AuraScript
{
    PrepareAuraScript(spell_pri_vampiric_touch);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PRIEST_VAMPIRIC_TOUCH_DISPEL });
    }

    Aura* GetMentalFortitudeAura(Unit* caster)
    {
        for (size_t i = 901150; i < 901156; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleDispel(DispelInfo* dispelInfo)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = dispelInfo->GetDispeller())
                caster->CastSpell(target, SPELL_PRIEST_VAMPIRIC_TOUCH_DISPEL, TRIGGERED_FULL_MASK);
    }

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetOwner()->ToUnit();

        if (!target || target->isDead())
            return;

        int32 damage = aurEff->GetAmount();
        int32 healPct = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(caster);

        damage = caster->SpellDamageBonusDone(target, GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE, EFFECT_0);
        damage = target->SpellDamageBonusTaken(GetCaster(), GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);

        int32 heal = int32(CalculatePct(damage, healPct));

        // Mental Fortitude rune, shield instead of healing if caster is at full health.
        if (Aura* runeAura = GetMentalFortitudeAura(caster))
            if (caster->GetHealthPct() == 100)
            {
                int32 maxAmount = CalculatePct(caster->GetMaxHealth(), runeAura->GetEffect(EFFECT_0)->GetAmount());

                if (Aura* shield = caster->GetAura(RUNE_PRIEST_MENTAL_FORTITUDE_SHIELD))
                {
                    int32 amount = std::min<int32>(shield->GetEffect(EFFECT_0)->GetAmount() + heal, maxAmount);
                    shield->GetEffect(EFFECT_0)->ChangeAmount(amount);
                    shield->RefreshDuration();
                }
                else
                {
                    int32 amount = std::min<int32>(heal, maxAmount);
                    caster->CastCustomSpell(RUNE_PRIEST_MENTAL_FORTITUDE_SHIELD, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
                }

                heal = 0;
            }

        if (heal > 0)
            caster->CastCustomSpell(SPELL_PRIEST_VAMPIRIC_TOUCH_HEAL, SPELLVALUE_BASE_POINT0, heal, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        AfterDispel += AuraDispelFn(spell_pri_vampiric_touch::HandleDispel);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_vampiric_touch::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 605 - Mind Control
class spell_pri_mind_control : public AuraScript
{
    PrepareAuraScript(spell_pri_mind_control);

    void HandleApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                uint32 duration = static_cast<uint32>(GetDuration());
                caster->SetInCombatWith(target, duration);
                target->SetInCombatWith(caster, duration);
            }
        }
    }

    void HandleRemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                caster->SetCombatTimer(0);
                target->SetCombatTimer(0);
            }
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_pri_mind_control::HandleApplyEffect, EFFECT_0, SPELL_AURA_MOD_POSSESS, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_pri_mind_control::HandleRemoveEffect, EFFECT_0, SPELL_AURA_MOD_POSSESS, AURA_EFFECT_HANDLE_REAL);
    }
};

// 48300 - Devouring Plague
class spell_pri_devouring_plague : public SpellScript
{
    PrepareSpellScript(spell_pri_devouring_plague);

    Aura* GetMentalFortitudeAura(Unit* caster)
    {
        for (size_t i = 901150; i < 901156; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleExtraDamage(SpellMissInfo missInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (target->isDead() || !target->HasAura(SPELL_PRIEST_DEVOURING_PLAGUE))
            return;

        Aura* devouring = target->GetAura(SPELL_PRIEST_DEVOURING_PLAGUE);
        AuraEffect* devouringEff = devouring->GetEffect(EFFECT_0);

        int32 healPct = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(caster);
        int32 remainingTicks = devouring->GetDuration() / devouringEff->GetAmplitude();
        uint32 damage = devouringEff->GetAmount();
        damage = target->SpellDamageBonusTaken(caster, GetSpellInfo(), damage, DOT);

        int32 amount = damage * (remainingTicks + 1);
        int32 heal = int32(CalculatePct(amount, healPct));

        // Mental Fortitude rune, shield instead of healing if caster is at full health.
        if (Aura* runeAura = GetMentalFortitudeAura(caster))
            if (caster->GetHealthPct() == 100)
            {
                int32 maxAmount = CalculatePct(caster->GetMaxHealth(), runeAura->GetEffect(EFFECT_0)->GetAmount());

                if (Aura* shield = caster->GetAura(RUNE_PRIEST_MENTAL_FORTITUDE_SHIELD))
                {
                    int32 amount = std::min<int32>(shield->GetEffect(EFFECT_0)->GetAmount() + heal, maxAmount);
                    shield->GetEffect(EFFECT_0)->ChangeAmount(amount);
                    shield->RefreshDuration();
                }
                else
                {
                    int32 amount = std::min<int32>(heal, maxAmount);
                    caster->CastCustomSpell(RUNE_PRIEST_MENTAL_FORTITUDE_SHIELD, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
                }

                heal = 0;
            }

        if (heal > 0)
            caster->CastCustomSpell(caster, SPELL_PRIEST_DEVOURING_PLAGUE_HEAL, &heal, nullptr, nullptr, true, nullptr, devouringEff);

        caster->CastCustomSpell(target, SPELL_PRIEST_DEVOURING_PLAGUE_EXTRA_DAMAGE, &amount, nullptr, nullptr, true, nullptr, devouringEff);
    }

    void HandleHealing()
    {
        Unit* caster = GetCaster();
        int32 damage = GetHitDamage();
        int32 healPct = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(caster);

        int32 heal = int32(CalculatePct(damage, healPct));

        GetCaster()->CastCustomSpell(SPELL_PRIEST_DEVOURING_PLAGUE_HEAL, SPELLVALUE_BASE_POINT0, heal, caster, TRIGGERED_FULL_MASK);

        if (Aura* voidform = caster->GetAura(SPELL_PRIEST_VOIDFORM))
        {
            int32 durationIncrease = voidform->GetEffect(EFFECT_0)->GetAmplitude();
            voidform->SetDuration(voidform->GetDuration() + durationIncrease);
        }
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Mind Devourer Rune Buff
        for (size_t i = 900286; i < 900292; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_pri_devouring_plague::HandleExtraDamage);
        OnHit += SpellHitFn(spell_pri_devouring_plague::HandleHealing);
        AfterHit += SpellHitFn(spell_pri_devouring_plague::HandleAfterHit);
    }
};

// 48300 - Devouring Plague
class spell_pri_devouring_plague_heal : public AuraScript
{
    PrepareAuraScript(spell_pri_devouring_plague_heal);

    Aura* GetMentalFortitudeAura(Unit* caster)
    {
        for (size_t i = 901150; i < 901156; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();
        int32 healPct = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(caster);
        int32 heal = int32(CalculatePct(aurEff->GetAmount(), healPct));

        // Mental Fortitude rune, shield instead of healing if caster is at full health.
        if (Aura* runeAura = GetMentalFortitudeAura(caster))
            if (caster->GetHealthPct() == 100)
            {
                int32 maxAmount = CalculatePct(caster->GetMaxHealth(), runeAura->GetEffect(EFFECT_0)->GetAmount());

                if (Aura* shield = caster->GetAura(RUNE_PRIEST_MENTAL_FORTITUDE_SHIELD))
                {
                    int32 amount = std::min<int32>(shield->GetEffect(EFFECT_0)->GetAmount() + heal, maxAmount);
                    shield->GetEffect(EFFECT_0)->ChangeAmount(amount);
                    shield->RefreshDuration();
                }
                else
                {
                    int32 amount = std::min<int32>(heal, maxAmount);
                    caster->CastCustomSpell(RUNE_PRIEST_MENTAL_FORTITUDE_SHIELD, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
                }

                heal = 0;
            }

        if (heal > 0)
            caster->CastCustomSpell(SPELL_PRIEST_DEVOURING_PLAGUE_HEAL, SPELLVALUE_BASE_POINT0, heal, caster, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_devouring_plague_heal::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
    }
};

// 81001 - Mass Resurrection
class spell_pri_mass_resurrection : public SpellScript
{
    PrepareSpellScript(spell_pri_mass_resurrection);

    std::list <Unit*> FindTargets()
    {
        std::list <Unit*> targetAvailable = {};

        if (Player* caster = GetCaster()->ToPlayer())
        {
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
        }

        return targetAvailable;
    }

    void HandleProc()
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            if (!player->GetGroup())
                return;

            for (auto const& target : FindTargets())
            {
                GetCaster()->CastSpell(target, SPELL_PRIEST_MASS_RESURRECTION, TRIGGERED_FULL_MASK);
            }
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_mass_resurrection::HandleProc);
    }
};

// 81003 - Leap of Faith
class spell_pri_leap_of_faith : public SpellScript
{
    PrepareSpellScript(spell_pri_leap_of_faith);

    Aura* GetBodyAndSoulAura(Unit* caster)
    {
        for (size_t i = 900336; i < 900342; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();

        //if (target->GetTypeId() != TYPEID_PLAYER)
        //    return SPELL_FAILED_TARGET_NOT_PLAYER;

        if (caster->HasUnitState(UNIT_STATE_JUMPING) || caster->HasUnitMovementFlag(MOVEMENTFLAG_FALLING))
            return SPELL_FAILED_MOVING;

        return SPELL_CAST_OK;
    }

    void HandleBaseDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        Unit* baseTarget = GetExplTargetUnit();
        Creature* targetCreature = GetHitCreature();

        if (caster != target)
        {
            caster->CastSpell(target, SPELL_PRIEST_LEAP_OF_FAITH_PROC, true);
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(1766); // Rogue kick
            if (!target->IsImmunedToSpellEffect(spellInfo, EFFECT_0))
                target->InterruptNonMeleeSpells(true);

            if (Aura* runeAura = GetBodyAndSoulAura(caster))
            {
                int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

                caster->AddAura(procSpell, target);
            }
        }
        else
            baseTarget->CastSpell(caster, SPELL_PRIEST_LEAP_OF_FAITH_PROC, true);
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        float casterZ = GetCaster()->GetPositionZ(); // for Ring of Valor
        WorldLocation gripPos = *GetExplTargetDest();
        if (Unit* target = GetHitUnit())
            if (!target->HasAuraType(SPELL_AURA_DEFLECT_SPELLS) || target->HasUnitState(UNIT_STATE_STUNNED)) // Deterrence
            {
                if (target != GetCaster())
                {
                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(1766); // Rogue kick
                    if (!target->IsImmunedToSpellEffect(spellInfo, EFFECT_0))
                        target->InterruptNonMeleeSpells(false, 0, false);
                }

                if (target->GetMapId() == 618) // for Ring of Valor
                    gripPos.m_positionZ = std::max(casterZ + 0.2f, 28.5f);

                target->CastSpell(gripPos.GetPositionX(), gripPos.GetPositionY(), gripPos.GetPositionZ(), SPELL_PRIEST_LEAP_OF_FAITH_GRAB, true);
            }
    }

    void Register() override
    {
        if (m_scriptSpellId == SPELL_PRIEST_LEAP_OF_FAITH)
        {
            OnCheckCast += SpellCheckCastFn(spell_pri_leap_of_faith::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_pri_leap_of_faith::HandleBaseDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
        else
            OnEffectHitTarget += SpellEffectFn(spell_pri_leap_of_faith::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 81006 - Power Word: Life
class spell_pri_power_word_life : public SpellScript
{
    PrepareSpellScript(spell_pri_power_word_life);

    void HandleHeal(SpellEffIndex effIndex)
    {
        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 heal = GetEffectValue();

        ApplyPct(heal, GetCaster()->SpellBaseHealingBonusDone(SPELL_SCHOOL_MASK_HOLY));

        heal = caster->SpellHealingBonusDone(target, GetSpellInfo(), uint32(heal), SPELL_DIRECT_DAMAGE, effIndex);
        heal = target->SpellHealingBonusTaken(caster, GetSpellInfo(), uint32(heal), SPELL_DIRECT_DAMAGE);

        int32 healthThreshold = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(caster);
        int32 healIncrease = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(caster);

        if (target->HealthBelowPct(healthThreshold))
        {
            ApplyPct(heal, healIncrease);
            caster->AddAura(SPELL_PRIEST_POWER_WORD_LIFE_LISTENER, caster);
        }

        SetHitHeal(heal);
    }

    void HandleProc()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!caster->HasAura(SPELL_PRIEST_POWER_WORD_LIFE_LISTENER))
            return;

        caster->ToPlayer()->ModifySpellCooldown(SPELL_PRIEST_POWER_WORD_LIFE, -GetSpellInfo()->GetEffect(EFFECT_1).Amplitude);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_power_word_life::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
        AfterHit += SpellHitFn(spell_pri_power_word_life::HandleProc);
    }
};

// 81008 - Void Shift
class spell_pri_void_shift : public SpellScript
{
    PrepareSpellScript(spell_pri_void_shift);

    void HandleProc(SpellEffIndex effIndex)
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();

        int32 minPct = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(caster);
        int32 targetHealthPct = std::max<int32>(target->GetHealthPct(), minPct);
        int32 casterHealthPct = std::max<int32>(caster->GetHealthPct(), minPct);

        caster->SetHealth(CalculatePct(targetHealthPct, caster->GetMaxHealth()));
        target->SetHealth(CalculatePct(casterHealthPct, target->GetMaxHealth()));
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_void_shift::HandleProc, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 81009 - Atonement
class spell_pri_atonement : public AuraScript
{
    PrepareAuraScript(spell_pri_atonement);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();
        Unit* target = eventInfo.GetProcTarget();

        if (!caster || caster->isDead())
            return;

        if (!target || target->isDead())
            return;

        if (!eventInfo.GetSpellInfo())
            return;

        if (eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_FLASH_HEAL || eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_RENEW)
        {
            if (!target->HasAura(SPELL_PRIEST_AUTONEMENT_AURA))
                caster->AddAura(SPELL_PRIEST_AUTONEMENT_AURA, target);

            if (Aura* atonementAura = target->GetAura(SPELL_PRIEST_AUTONEMENT_AURA))
                if (atonementAura->GetDuration() <= 8000)
                    atonementAura->RefreshDuration();

            return;
        }

        if (!eventInfo.GetDamageInfo() || eventInfo.GetDamageInfo()->GetDamage() <= 0)
            return;

        int32 damage = eventInfo.GetDamageInfo()->GetDamage();
        int32 amount = CalculatePct(damage, aurEff->GetAmount());
        GetAura()->GetEffect(EFFECT_1)->SetAmount(amount);

        caster->CastSpell(caster, SPELL_PRIEST_AUTONEMENT_AOE, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_atonement::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 81011 - Atonement AOE
class spell_pri_atonement_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_atonement_heal);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 amount = caster->GetAura(SPELL_PRIEST_AUTONEMENT)->GetEffect(EFFECT_1)->GetAmount();

        for (auto const& object : targets)
        {
            Unit* target = object->ToUnit();

            if (target->isDead() || !target->HasAura(SPELL_PRIEST_AUTONEMENT_AURA))
                continue;

            caster->CastCustomSpell(SPELL_PRIEST_AUTONEMENT_HEAL, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_atonement_heal::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 81013 - Power Word: Radiance
class spell_pri_power_word_radiance : public SpellScript
{
    PrepareSpellScript(spell_pri_power_word_radiance);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::RaidCheck(GetCaster(), false));

        uint32 const maxTargets = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(GetCaster());

        if (targets.size() > maxTargets)
        {
            targets.sort(Acore::HealthPctOrderPred());
            targets.resize(maxTargets);
        }
    }

    void HandleHit(SpellEffIndex effIndex)
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();

        int32 durationPct = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(caster);

        if (Aura* atonement = target->GetAura(SPELL_PRIEST_AUTONEMENT_AURA))
        {
            int32 duration = CalculatePct(atonement->GetMaxDuration(), durationPct);

            if (atonement->GetDuration() > duration)
                return;

            atonement->SetDuration(duration);
            return;
        }

        caster->AddAura(SPELL_PRIEST_AUTONEMENT_AURA, target);

        Aura* atonement = target->GetAura(SPELL_PRIEST_AUTONEMENT_AURA);
        int32 duration = CalculatePct(atonement->GetMaxDuration(), durationPct);

        // Add T1 4pc duration increase.
        if (Aura* set_T1_4pc = caster->GetAura(T1_PRIEST_DISCI_4PC))
            duration += set_T1_4pc->GetEffect(EFFECT_1)->GetAmount();

        atonement->SetDuration(duration);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_power_word_radiance::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        OnEffectHitTarget += SpellEffectFn(spell_pri_power_word_radiance::HandleHit, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 81015 - Power Word: Barrier
class spell_pri_power_word_barrier : public SpellScript
{
    PrepareSpellScript(spell_pri_power_word_barrier);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.clear();
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_power_word_barrier::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 81017 - Purge the Wicked
class spell_pri_purge_the_wicked_aura : public AuraScript
{
    PrepareAuraScript(spell_pri_purge_the_wicked_aura);

    Aura* GetWickedPainAura(Unit* caster)
    {
        for (size_t i = 900930; i < 900936; i++)
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

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* runeAura = GetWickedPainAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
            caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_purge_the_wicked_aura::HandleProc, EFFECT_2, SPELL_AURA_DUMMY);
    }
};

// 81018 - Purge the Wicked AOE
class spell_pri_purge_the_wicked : public SpellScript
{
    PrepareSpellScript(spell_pri_purge_the_wicked);

    Aura* GetRevelInPurityAura(Unit* caster)
    {
        for (size_t i = 900942; i < 900948; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        targets.remove(target);
        int32 maxTarget = 1;

        if (Aura* runeAura = GetRevelInPurityAura(caster))
            maxTarget++;

        std::list<Unit*> wickedTargets = {};

        for (auto const& object : targets)
        {
            Unit* victim = object->ToUnit();

            if (!victim || victim->isDead())
                return;
            // if the target is already affected by Purge the Wicked switch it to the second list.
            if (victim->HasAura(SPELL_PRIEST_PURGE_THE_WICKED) && victim->GetAura(SPELL_PRIEST_PURGE_THE_WICKED)->GetDuration() > 5000)
            {
                wickedTargets.emplace_back(victim);
                continue;
            }

            caster->AddAura(SPELL_PRIEST_PURGE_THE_WICKED, victim);
            maxTarget--;

            if (maxTarget <= 0)
                break;
        }
        // If there wasn't enough target without Purge the Wicked, cast it on the targets already affected by it
        if (maxTarget > 0)
        {
            for (auto const& victim : wickedTargets)
            {
                if (victim->isDead())
                    continue;

                caster->AddAura(SPELL_PRIEST_PURGE_THE_WICKED, victim);
                maxTarget--;

                if (maxTarget <= 0)
                    break;
            }
        }
        // No matter what refresh the duration of Purge the Wicked on the main target.
        if (Aura* aura = target->GetAura(SPELL_PRIEST_PURGE_THE_WICKED))
        {
            aura->RefreshDuration(true);
        } 
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_purge_the_wicked::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 81019 - Rapture
class spell_pri_rapture : public SpellScript
{
    PrepareSpellScript(spell_pri_rapture);

    void HandleProc()
    {
        if (Player* player = GetCaster()->ToPlayer())
            player->RemoveSpellCooldown(SPELL_PRIEST_POWER_WORD_SHIELD, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_rapture::HandleProc);
    }
};

// 81021 - Evangelism
class spell_pri_evangelism : public SpellScript
{
    PrepareSpellScript(spell_pri_evangelism);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 durationIncrease = GetSpellInfo()->GetEffect(EFFECT_0).CalcValue(caster);

        for (auto const& object : targets)
        {
            Unit* target = object->ToUnit();

            if (target->isDead())
                continue;

            if (Aura* atonement = target->GetAura(SPELL_PRIEST_AUTONEMENT_AURA))
                atonement->SetDuration(atonement->GetDuration() + durationIncrease);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_evangelism::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 81022 - Light's Wrath
class spell_pri_light_wrath : public SpellScript
{
    PrepareSpellScript(spell_pri_light_wrath);

    void HandleDamage(SpellEffIndex effIndex)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 damage = GetHitDamage();
        int32 atonementPct = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(player);
        int32 atonementTarget = 0;

        Group* group = player->GetGroup();

        if (!group)
            return;

        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
            if (Player* target = itr->GetSource())
                if (target->HasAura(SPELL_PRIEST_AUTONEMENT_AURA))
                    atonementTarget++;

        if (atonementTarget > 0)
            AddPct(damage, atonementPct * atonementTarget);

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_light_wrath::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 81025 - Holy Word: Serenity / 48071 - Flash Heal / 6064 - Heal
class spell_pri_holy_word_serenity_cooldown : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_serenity_cooldown);

    void HandleProc()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 cooldownReduction = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_HOLY_WORD_SERENITY)->GetEffect(EFFECT_1).CalcValue(player);

        player->ModifySpellCooldown(SPELL_PRIEST_HOLY_WORD_SERENITY, -cooldownReduction);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_holy_word_serenity_cooldown::HandleProc);
    }
};

// 81026 - Holy Word: Chastise / 48123 - Smite
class spell_pri_holy_word_chastise_cooldown : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_chastise_cooldown);

    void HandleProc()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 cooldownReduction = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_HOLY_WORD_CHASTISE)->GetEffect(EFFECT_2).CalcValue(player);

        player->ModifySpellCooldown(SPELL_PRIEST_HOLY_WORD_CHASTISE, -cooldownReduction);

        if (player->HasAura(SPELL_PRIEST_DIVINE_FAVOR_CHASTISE))
            player->ToPlayer()->RemoveSpellCooldown(SPELL_PRIEST_HOLY_FIRE, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_holy_word_chastise_cooldown::HandleProc);
    }
};

// 48135 - Holy Fire
class spell_pri_holy_fire : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_fire);

    void HandleProc(SpellMissInfo missInfo)
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();

        if (target->HasAura(SPELL_PRIEST_HOLY_FIRE) && caster->HasAura(SPELL_PRIEST_EMPYREAL_BLAZE_BUFF))
        {
            Aura* holyFire = target->GetAura(SPELL_PRIEST_HOLY_FIRE);
            int32 duration = holyFire->GetDuration();

            caster->AddAura(SPELL_PRIEST_EMPYREAL_BLAZE_LISTENER, target);
            target->GetAura(SPELL_PRIEST_EMPYREAL_BLAZE_LISTENER)->GetEffect(EFFECT_0)->SetAmount(duration);
        }
    }

    void HandleAfter()
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();

        if (target->HasAura(SPELL_PRIEST_HOLY_FIRE) && target->HasAura(SPELL_PRIEST_EMPYREAL_BLAZE_LISTENER))
        {
            Aura* holyFire = target->GetAura(SPELL_PRIEST_HOLY_FIRE);
            Aura* listenerAura = target->GetAura(SPELL_PRIEST_EMPYREAL_BLAZE_LISTENER);

            int32 duration = listenerAura->GetEffect(EFFECT_0)->GetAmount() + holyFire->GetMaxDuration();
            listenerAura->Remove();

            holyFire->SetMaxDuration(duration);
            holyFire->RefreshDuration();
        }
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_pri_holy_fire::HandleProc);
        AfterHit += SpellHitFn(spell_pri_holy_fire::HandleAfter);
    }
};

// 48135 - Holy Fire Aura
class spell_pri_holy_fire_aura : public AuraScript
{
    PrepareAuraScript(spell_pri_holy_fire_aura);

    Aura* GetHolyHellstoneAura(Unit* caster)
    {
        for (size_t i = 900200; i < 900206; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Unit* findNearestTarget(Unit* caster, Unit* target)
    {
        Unit* nearTarget = nullptr;
        auto const& threatList = caster->getAttackers();
        auto threatListCopy = threatList;

        if (threatListCopy.empty()) return nullptr;

        for (auto const& threat : threatListCopy)
            if (threat->IsAlive())
            {
                if (threat->HasAura(SPELL_PRIEST_HOLY_FIRE))
                    continue;

                if (threat == target)
                    continue;

                nearTarget = threat;
            }

        return nearTarget;
    }

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* runeAura = GetHolyHellstoneAura(caster))
            if (Unit* nearTarget = findNearestTarget(caster, target))
                if (GetAura()->GetEffect(EFFECT_2)->GetAmount() == 0)
                    if (Aura* newHolyFire = caster->AddAura(SPELL_PRIEST_HOLY_FIRE, nearTarget))
                        newHolyFire->GetEffect(EFFECT_2)->ChangeAmount(1);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_holy_fire_aura::HandleApply, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_holy_fire_aura::HandleRemove, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 81027 - Empyreal Blaze
class spell_pri_empyreal_blaze : public SpellScript
{
    PrepareSpellScript(spell_pri_empyreal_blaze);

    void HandleProc()
    {
        if (Player* player = GetCaster()->ToPlayer())
            player->RemoveSpellCooldown(SPELL_PRIEST_HOLY_FIRE, true);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_empyreal_blaze::HandleProc);
    }
};

// 81025 - Holy Word: Sanctify / 48072 - Prayer of Healing / 48068 - Renew
class spell_pri_holy_word_sanctify_cooldown : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_sanctify_cooldown);

    void HandleProc()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 cooldownReduction = 0;

        if (GetSpellInfo()->Id == SPELL_PRIEST_PRAYER_OF_HEALING)
            cooldownReduction = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_HOLY_WORD_SANCTIFY)->GetEffect(EFFECT_1).CalcValue(player);

        if (GetSpellInfo()->Id == SPELL_PRIEST_RENEW)
            cooldownReduction = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_HOLY_WORD_SANCTIFY)->GetEffect(EFFECT_2).CalcValue(player);

        player->ModifySpellCooldown(SPELL_PRIEST_HOLY_WORD_SANCTIFY, -cooldownReduction);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pri_holy_word_sanctify_cooldown::HandleProc);
    }
};

// 81030 - Apotheosis
class spell_pri_apotheosis : public SpellScript
{
    PrepareSpellScript(spell_pri_apotheosis);

    void HandleProc()
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            player->RemoveSpellCooldown(SPELL_PRIEST_HOLY_WORD_CHASTISE, true);
            player->RemoveSpellCooldown(SPELL_PRIEST_HOLY_WORD_SANCTIFY, true);
            player->RemoveSpellCooldown(SPELL_PRIEST_HOLY_WORD_SERENITY, true);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pri_apotheosis::HandleProc);
    }
};

// 81032 - Holy Word: Salvation
class spell_pri_holy_word_salvation : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_salvation);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::RaidCheck(GetCaster(), false));
    }

    void HandleProc(SpellEffIndex effIndex)
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();

        caster->CastSpell(target, SPELL_PRIEST_RENEW, true);
        caster->CastCustomSpell(SPELL_PRIEST_PRAYER_OF_MENDING, SPELLVALUE_AURA_CHARGE, 2, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_holy_word_salvation::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        OnEffectHitTarget += SpellEffectFn(spell_pri_holy_word_salvation::HandleProc, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 81032 - Holy Word: Salvation / 81025 - Holy Word: Serenity / 81029 - Holy Word: Sanctify / 81026 - Holy Word: Chastise
class spell_pri_holy_word_salvation_cooldown : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_word_salvation_cooldown);

    void HandleProc()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        int32 cooldownReduction = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_HOLY_WORD_SALVATION)->GetEffect(EFFECT_1).CalcValue(player);

        player->ModifySpellCooldown(SPELL_PRIEST_HOLY_WORD_SALVATION, -cooldownReduction);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_holy_word_salvation_cooldown::HandleProc);
    }
};

// 81034 - Divine Word Aura
class spell_pri_divine_word : public AuraScript
{
    PrepareAuraScript(spell_pri_divine_word);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;


        int32 spellID = eventInfo.GetSpellInfo()->Id;

        if (spellID == SPELL_PRIEST_HOLY_WORD_CHASTISE)
            caster->AddAura(SPELL_PRIEST_DIVINE_FAVOR_CHASTISE, caster);

        if (spellID == SPELL_PRIEST_HOLY_WORD_SANCTIFY) {
            if (Unit* selectedUnit = ObjectAccessor::GetUnit(*caster, caster->GetTarget()))
                caster->AddAura(SPELL_PRIEST_DIVINE_FAVOR_SANCTIFY, selectedUnit);
            else
                caster->AddAura(SPELL_PRIEST_DIVINE_FAVOR_SANCTIFY, caster);
        }

        if (spellID == SPELL_PRIEST_HOLY_WORD_SERENITY)
            caster->AddAura(SPELL_PRIEST_DIVINE_FAVOR_SERENITY, caster);
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_divine_word::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 81042 - Void Eruption 
class spell_pri_void_eruption : public SpellScript
{
    PrepareSpellScript(spell_pri_void_eruption);


    void HandleProc()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = ObjectAccessor::GetUnit(*caster, caster->GetTarget());

        if (!target || target->isDead())
            return;

        if (caster->HasAura(SPELL_PRIEST_VOIDFORM))
        {
            caster->CastSpell(target, SPELL_PRIEST_VOID_BOLT, TRIGGERED_FULL_MASK);
        }
        else
        {
            caster->AddAura(SPELL_PRIEST_VOIDFORM, caster);
            caster->CastSpell(target, SPELL_PRIEST_VOID_ERUPTION_DAMAGE, TRIGGERED_FULL_MASK);
            caster->CastSpell(target, SPELL_PRIEST_VOID_ERUPTION_DAMAGE, TRIGGERED_FULL_MASK);
            caster->ToPlayer()->RemoveSpellCooldown(SPELL_PRIEST_VOID_ERUPTION, true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_void_eruption::HandleProc);
    }
};

// 81044 - Voidform 
class spell_pri_void_eruption_cooldown : public AuraScript
{
    PrepareAuraScript(spell_pri_void_eruption_cooldown);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            int32 cooldownChange = 6000 - player->GetSpellCooldownDelay(SPELL_PRIEST_VOID_ERUPTION);
            player->SetSpellCooldown(SPELL_PRIEST_VOID_ERUPTION, cooldownChange);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (Player* player = GetCaster()->ToPlayer())
        {
            player->RemoveSpellCooldown(SPELL_PRIEST_VOID_ERUPTION, true);
            player->AddSpellCooldown(SPELL_PRIEST_VOID_ERUPTION, 0, 120000);
            player->SendSpellCooldown(SPELL_PRIEST_VOID_ERUPTION, 120000);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_void_eruption_cooldown::HandleProc, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_void_eruption_cooldown::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
    }
};

// All Insanity Generation EFFECT_1 On Cast
class spell_pri_insanity_on_cast : public SpellScript
{
    PrepareSpellScript(spell_pri_insanity_on_cast);

    void HandleProc()
    {
        Unit* caster = GetCaster();

        int32 insanityAmount = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(caster);

        caster->CastCustomSpell(SPELL_PRIEST_INSANITY_ENERGIZE, SPELLVALUE_BASE_POINT0, insanityAmount, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pri_insanity_on_cast::HandleProc);
    }
};

// All Insanity Generation EFFECT_1 On Periodic
class spell_pri_insanity_on_periodic : public AuraScript
{
    PrepareAuraScript(spell_pri_insanity_on_periodic);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 insanityAmount = aurEff->GetAmount();

        caster->CastCustomSpell(SPELL_PRIEST_INSANITY_ENERGIZE, SPELLVALUE_BASE_POINT0, insanityAmount, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_insanity_on_periodic::HandleProc, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 81083 - Shadowy Apparitions
class spell_pri_shadowy_apparitions : public AuraScript
{
    PrepareAuraScript(spell_pri_shadowy_apparitions);

    Aura* GetTormentedSpiritsAura(Unit* caster)
    {
        for (size_t i = 901360; i < 901366; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetProcTarget();

        if (!target || !caster)
            return;

        int32 procID = eventInfo.GetSpellInfo()->Id;

        // Return if Devouring Plague dot damage
        if (procID == SPELL_PRIEST_DEVOURING_PLAGUE && eventInfo.GetDamageInfo()->GetDamageType() == DOT)
            return;

        int32 shadowNbr = aurEff->GetAmount();

        if (eventInfo.GetHitMask() == PROC_EX_CRITICAL_HIT)
            shadowNbr = GetEffect(EFFECT_1)->GetAmount();

        if (procID == SPELL_PRIEST_SHADOW_WORD_PAIN)
        {
            int32 procChance = 0;

            if (Aura* runeAura = GetTormentedSpiritsAura(caster))
            {
                procChance += runeAura->GetEffect(EFFECT_0)->GetAmount();

                if (eventInfo.GetHitMask() == PROC_EX_CRITICAL_HIT)
                    procChance = GetEffect(EFFECT_1)->GetAmount();
            }

            if (!roll_chance_i(procChance))
                return;
        }

        GetEffect(EFFECT_2)->SetAmount(shadowNbr);
        caster->CastSpell(caster, SPELL_PRIEST_SHADOWY_APPARITIONS_AOE, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_pri_shadowy_apparitions::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pri_shadowy_apparitions::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 81085 - Shadowy Apparitions Aoe
class spell_pri_shadowy_apparitions_aoe : public SpellScript
{
    PrepareSpellScript(spell_pri_shadowy_apparitions_aoe);

    Aura* GetTalentAura()
    {
        for (size_t i = 81083; i < 81085; i++)
        {
            if (GetCaster()->HasAura(i))
                return GetCaster()->GetAura(i);
        }

        return nullptr;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();

        if (!GetTalentAura())
            return;

        int32 shadowNbr = GetTalentAura()->GetEffect(EFFECT_2)->GetAmount();

        for (auto const& object : targets)
        {
            Unit* target = object->ToUnit();

            if (target->isDead() || !target->HasAura(SPELL_PRIEST_VAMPIRIC_TOUCH))
                continue;

            int32 shadow = shadowNbr;

            while (shadow > 0)
            {
                Position pos = caster->GetNearPosition(urand(1, 5), urand(1, 5));
                SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);
                Creature* summon = caster->SummonCreature(900000, pos, TEMPSUMMON_MANUAL_DESPAWN, GetSpellInfo()->GetDuration(), 0, properties);

                if (!summon)
                    return;

                summon->SetOwnerGUID(caster->GetGUID());
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                summon->SetReactState(REACT_PASSIVE);
                summon->SetTarget(target->GetGUID());

                shadow--;
            }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_shadowy_apparitions_aoe::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 81086 - Shadowy Apparition Damage
class spell_pri_shadowy_apparitions_damage : public SpellScript
{
    PrepareSpellScript(spell_pri_shadowy_apparitions_damage);

    Aura* GetPhantasmalPathogenAura(Unit* caster)
    {
        for (size_t i = 901342; i < 901348; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleEffectHit(SpellEffIndex effIndex)
    {
        Unit* shadow = GetCaster();

        if (!shadow || shadow->isDead())
            return;

        Unit* caster = shadow->GetOwner();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        if (Aura* runeAura = GetPhantasmalPathogenAura(caster))
        {
            if (target->HasAura(SPELL_PRIEST_DEVOURING_PLAGUE))
            {
                int32 increasePct = runeAura->GetEffect(EFFECT_0)->GetAmount();
                AddPct(damage, increasePct);
            }
        }

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_shadowy_apparitions_damage::HandleEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// Shadowy Apparition Pet
class npc_pri_shadowy_apparitions : public CreatureScript
{
public:
    npc_pri_shadowy_apparitions() : CreatureScript("npc_pri_shadowy_apparitions") { }

    struct spell_pri_shadowy_apparitionsAI : public ScriptedAI
    {
        spell_pri_shadowy_apparitionsAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 update = 250;

        void Reset() override
        {
            me->CombatStop(true);
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 diff) override
        {
            if (update >= 250) {
                if (Unit* target = ObjectAccessor::GetCreature(*me, me->GetTarget()))
                {
                    Position pos = target->GetPosition();
                    me->GetMotionMaster()->MovePoint(0, pos);
                }
                else
                    me->DespawnOrUnsummon();

                update = 0;
            }

            update += diff;
        }

        void MovementInform(uint32 /*type*/, uint32 id) override {
            if (id == 0) {
                if (Unit* target = ObjectAccessor::GetCreature(*me, me->GetTarget()))
                    me->CastSpell(target, SPELL_PRIEST_SHADOWY_APPARITIONS_DAMAGE, TRIGGERED_FULL_MASK, nullptr, nullptr, me->GetOwnerGUID());

                me->DespawnOrUnsummon();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new spell_pri_shadowy_apparitionsAI(creature);
    }
};

// 48113 - Prayer of Mending
class spell_pri_prayer_of_mending : public AuraScript
{
    PrepareAuraScript(spell_pri_prayer_of_mending);

    Aura* GetRenewTheFaithAura(Unit* caster)
    {
        for (size_t i = 900100; i < 900106; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetHolyMendingAura(Unit* caster)
    {
        for (size_t i = 900456; i < 900462; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetBenedictionAura(Unit* caster)
    {
        for (size_t i = 900468; i < 900474; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetSayYourPrayersAura(Unit* caster)
    {
        for (size_t i = 900474; i < 900480; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Unit* findNearestTarget()
    {
        Unit* caster = GetCaster();
        std::list<Unit*> nearMembers;
        Group* group = caster->ToPlayer()->GetGroup();

        if (!group)
            return nullptr;

        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
            if (Player* Target = itr->GetSource())
            {
                if (!caster->IsWithinDistInMap(Target, 20.f))
                    continue;

                // IsHostileTo check duel and controlled by enemy
                if (Target->IsAlive() && !caster->IsHostileTo(Target))
                    nearMembers.push_back(Target);
            }

        if (!nearMembers.empty())
            nearMembers.sort(Acore::HealthPctOrderPred());

        return nearMembers.front();
    }

    void CastMendingToNearestTarget(Unit* target, Unit* caster, uint32 charges)
    {
        caster->CastSpell(target, SPELL_PRIEST_PRAYER_OF_MENDING_HEAL);
        Unit* nextTarget = findNearestTarget();
        if (nextTarget && charges > 0)
        {
            target->RemoveAura(SPELL_PRIEST_PRAYER_OF_MENDING);
            target->CastSpell(nextTarget, 41637 /*Dummy visual effect triggered by main spell cast*/, true);
            target->CastCustomSpell(SPELL_PRIEST_PRAYER_OF_MENDING, SPELLVALUE_AURA_CHARGE, charges, nextTarget, true, nullptr, nullptr, caster->GetGUID());

            // Check if new target has Renew, if so heal them
            if (Aura* runeAura = GetHolyMendingAura(caster))
                if (nextTarget->HasAura(SPELL_PRIEST_RENEW))
                {
                    int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
                    caster->CastSpell(nextTarget, procSpell, TRIGGERED_FULL_MASK);
                }

            // Check for chance to leave a renew on old target
            if (Aura* runeAura = GetBenedictionAura(caster))
            {
                int32 procChance = runeAura->GetEffect(EFFECT_0)->GetAmount();

                if (roll_chance_i(procChance))
                    caster->AddAura(SPELL_PRIEST_RENEW, target);
            }
        }
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        uint8 charges = aurEff->GetBase()->GetCharges() - 1;
        PreventDefaultAction();

        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (eventInfo.GetHealInfo() && eventInfo.GetSpellInfo() && eventInfo.GetHealInfo()->GetHeal() > 0)
            if (Aura* runeAura = GetRenewTheFaithAura(caster))
                if (eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_DIVINE_HYMN_HEAL)
                {
                    charges += 1;
                    CastMendingToNearestTarget(target, caster, charges);
                }

        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
        {
            // Chance to not consume any charge
            if (Aura* runeAura = GetSayYourPrayersAura(caster))
            {
                int32 procChance = runeAura->GetEffect(EFFECT_0)->GetAmount();

                if (roll_chance_i(procChance))
                    charges += 1;
            }

            CastMendingToNearestTarget(target, caster, charges);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_prayer_of_mending::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pri_holy_blossom : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_blossom);

    Aura* GetDreamofSpringAura(Unit* caster)
    {
        for (size_t i = 901466; i < 901472; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetInnerRadianceAura(Unit* caster)
    {
        for (size_t i = 901510; i < 901516; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            Group* group = player->GetGroup();

            if (!group)
                return;

            if (Aura* runeAura = GetDreamofSpringAura(caster))
            {
                auto const& allyList = group->GetMemberSlots();
                int32 durationIncrease = 1000;

                if (Aura* damage = caster->GetAura(SPELL_PRIEST_HOLY_MIGHT))
                    damage->SetDuration(std::min<int32>(damage->GetDuration() + durationIncrease, damage->GetMaxDuration()));

                if (player->GetGroup() && allyList.size() > 0) {
                    for (auto const& target : allyList)
                    {
                        Player* alliedPlayer = ObjectAccessor::FindPlayer(target.guid);

                        if (!alliedPlayer)
                            continue;

                        if (alliedPlayer->isDead())
                            continue;

                        if (Aura* strength = alliedPlayer->GetAura(SPELL_PRIEST_HOLY_MIGHT_STRENGTH))
                            strength->SetDuration(std::min<int32>(strength->GetDuration() + durationIncrease, strength->GetMaxDuration()));

                        if (Aura* agility = alliedPlayer->GetAura(SPELL_PRIEST_HOLY_MIGHT_AGILITY))
                            agility->SetDuration(std::min<int32>(agility->GetDuration() + durationIncrease, agility->GetMaxDuration()));

                        if (Aura* intellect = alliedPlayer->GetAura(SPELL_PRIEST_HOLY_MIGHT_INTELLECT))
                            intellect->SetDuration(std::min<int32>(intellect->GetDuration() + durationIncrease, intellect->GetMaxDuration()));

                        if (Aura* spirit = alliedPlayer->GetAura(SPELL_PRIEST_HOLY_MIGHT_SPIRIT))
                            spirit->SetDuration(std::min<int32>(spirit->GetDuration() + durationIncrease, spirit->GetMaxDuration()));
                    }
                }
            }
        }
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Acore::RaidCheck(GetCaster(), false));

        uint32 const maxTargets = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(GetCaster());

        if (targets.size() > maxTargets)
        {
            targets.sort(Acore::HealthPctOrderPred());
            targets.resize(maxTargets);
        }
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 heal = GetHitHeal();

        // apply Inner Radiance increase if used on himself
        if (Aura* runeAura = GetInnerRadianceAura(caster))
            if (target == caster)
            {
                int32 increase = runeAura->GetEffect(EFFECT_0)->GetAmount();
                AddPct(heal, increase);
            }

        SetHitHeal(heal);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pri_holy_blossom::HandleCast);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_holy_blossom::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        OnEffectHitTarget += SpellEffectFn(spell_pri_holy_blossom::HandleDummy, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

class spell_pri_holy_flame : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_flame);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (Unit* unitTarget = GetHitUnit())
        {
            if (!caster->IsFriendlyTo(unitTarget))
                caster->CastSpell(unitTarget, SPELL_PRIEST_HOLY_FLAME_DAMAGE, TRIGGERED_FULL_MASK);
            else
                caster->CastSpell(unitTarget, SPELL_PRIEST_HOLY_FLAME_HEAL, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_holy_flame::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

// 86207 - Holy Flame Heal
class spell_pri_holy_flame_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_flame_heal);

    Aura* GetInnerRadianceAura(Unit* caster)
    {
        for (size_t i = 901510; i < 901516; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 heal = GetHitHeal();

        // apply Inner Radiance increase if used on himself
        if (Aura* runeAura = GetInnerRadianceAura(caster))
            if (target == caster)
            {
                int32 increase = runeAura->GetEffect(EFFECT_0)->GetAmount();
                AddPct(heal, increase);
            }

        SetHitHeal(heal);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_holy_flame_heal::HandleDummy, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

class spell_pri_holy_might : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_might);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();

        targets.remove_if(Acore::RaidCheck(caster, false));
        targets.remove(caster);

        int32 statPct = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_HOLY_MIGHT)->GetEffect(EFFECT_0).CalcValue();

        int32 casterSTR = caster->GetStat(STAT_STRENGTH);
        int32 casterAGI = caster->GetStat(STAT_AGILITY);
        int32 casterINT = caster->GetStat(STAT_INTELLECT);
        int32 casterSPR = caster->GetStat(STAT_SPIRIT);

        int32 highestCasterStat = std::max({ casterSTR, casterAGI, casterINT, casterSPR });
        int32 buffAmount = CalculatePct(highestCasterStat, statPct);
        int32 speedAmount = 0;

        if (AuraEffect* aurEff = caster->GetAuraEffectOfRankedSpell(TALENT_PRIEST_CELERITY_R1, EFFECT_0))
            speedAmount = aurEff->GetAmount();

        for (auto const& object : targets)
        {
            Unit* target = object->ToUnit();
            if (!target || target->isDead())
                continue;

            int32 targetSTR = target->GetStat(STAT_STRENGTH);
            int32 targetAGI = target->GetStat(STAT_AGILITY);
            int32 targetINT = target->GetStat(STAT_INTELLECT);
            int32 targetSPR = target->GetStat(STAT_SPIRIT);
            int32 highestTargetStat = std::max({ targetSTR, targetAGI, targetINT, targetSPR });

            if (highestTargetStat == targetSTR)
                caster->CastCustomSpell(target, SPELL_PRIEST_HOLY_MIGHT_STRENGTH, &buffAmount, &speedAmount, nullptr, true, nullptr);
            else if (highestTargetStat == targetAGI)
                caster->CastCustomSpell(target, SPELL_PRIEST_HOLY_MIGHT_AGILITY, &buffAmount, &speedAmount, nullptr, true, nullptr);
            else if (highestTargetStat == targetINT)
                caster->CastCustomSpell(target, SPELL_PRIEST_HOLY_MIGHT_INTELLECT, &buffAmount, &speedAmount, nullptr, true, nullptr);
            else
                caster->CastCustomSpell(target, SPELL_PRIEST_HOLY_MIGHT_SPIRIT, &buffAmount, &speedAmount, nullptr, true, nullptr);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_holy_might::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

class spell_pri_holy_might_proc : public AuraScript
{
    PrepareAuraScript(spell_pri_holy_might_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return false;

        return caster->HasSpell(SPELL_PRIEST_HOLY_MIGHT);
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        GetCaster()->CastSpell(GetCaster(), SPELL_PRIEST_HOLY_MIGHT_AOE, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_holy_might_proc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pri_holy_might_increase : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_might_increase);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        int32 amount = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_HOLY_MIGHT)->GetEffect(EFFECT_2).CalcValue(caster);

        if (!caster || caster->isDead())
            return;

        if (Aura* aura = caster->GetAura(SPELL_PRIEST_HOLY_MIGHT))
            aura->SetDuration(aura->GetDuration() + amount);

        for (auto const& object : targets)
        {
            Unit* target = object->ToUnit();

            if (target->isDead() || !target->HasAura(SPELL_PRIEST_HOLY_MIGHT_STRENGTH) && !target->HasAura(SPELL_PRIEST_HOLY_MIGHT_AGILITY) && !target->HasAura(SPELL_PRIEST_HOLY_MIGHT_INTELLECT) && !target->HasAura(SPELL_PRIEST_HOLY_MIGHT_SPIRIT))
                continue;

            if (Aura* aura = target->GetAura(SPELL_PRIEST_HOLY_MIGHT_STRENGTH))
                aura->SetDuration(aura->GetDuration() + amount);
            else if (Aura* aura = target->GetAura(SPELL_PRIEST_HOLY_MIGHT_AGILITY))
                aura->SetDuration(aura->GetDuration() + amount);
            else if (Aura* aura = target->GetAura(SPELL_PRIEST_HOLY_MIGHT_INTELLECT))
                aura->SetDuration(aura->GetDuration() + amount);
            else if (Aura* aura = target->GetAura(SPELL_PRIEST_HOLY_MIGHT_SPIRIT))
                aura->SetDuration(aura->GetDuration() + amount);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_holy_might_increase::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 86220 - Wave of Light
class spell_pri_wave_of_light : public SpellScript
{
    PrepareSpellScript(spell_pri_wave_of_light);

    Aura* GetOverlordAura(Unit* caster)
    {
        for (size_t i = 901596; i < 901602; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* runeAura = GetOverlordAura(caster))
        {
            int32 targetNbr = runeAura->GetEffect(EFFECT_0)->GetAmount();
            for (auto const& object : targets)
            {
                Unit* target = object->ToUnit();

                if (target->isDead())
                    continue;

                caster->CastSpell(target, SPELL_PRIEST_HOLY_ERUPTION, TRIGGERED_FULL_MASK);
                targetNbr--;

                if (targetNbr <= 0)
                    break;
            }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_wave_of_light::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_pri_wave_of_light_absorb : public AuraScript
{
    PrepareAuraScript(spell_pri_wave_of_light_absorb);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        amount = CalculatePct(GetCaster()->SpellBaseHealingBonusDone(SPELL_SCHOOL_MASK_HOLY), amount);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pri_wave_of_light_absorb::CalculateAmount, EFFECT_2, SPELL_AURA_SCHOOL_ABSORB);
    }
};

class spell_pri_wave_of_light_accumulation : public AuraScript
{
    PrepareAuraScript(spell_pri_wave_of_light_accumulation);

    Aura* GetLightsWardAura(Unit* caster)
    {
        for (size_t i = 901614; i < 901620; i++)
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

        Unit* eventTarget = eventInfo.GetActor();
        if (!eventTarget || eventTarget->isDead() || !eventTarget->HasAura(SPELL_PRIEST_HOLY_MIGHT_STRENGTH) && !eventTarget->HasAura(SPELL_PRIEST_HOLY_MIGHT_AGILITY) && !eventTarget->HasAura(SPELL_PRIEST_HOLY_MIGHT_INTELLECT) && !eventTarget->HasAura(SPELL_PRIEST_HOLY_MIGHT_SPIRIT))
            return;

        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
        {
            if (SpellInfo const* spellInfo = eventInfo.GetSpellInfo())
                if (spellInfo->Id == SPELL_PRIEST_HOLY_WOUNDS_PROC)
                    return;

            Unit* target = GetUnitOwner();

            if (!target || target->isDead())
                return;

            int32 amount = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());

            if (Aura* runeAura = GetLightsWardAura(caster))
            {
                int32 procPct = runeAura->GetEffect(EFFECT_0)->GetAmount();
                int32 maxAmount = CalculatePct(caster->GetMaxHealth(), runeAura->GetEffect(EFFECT_1)->GetAmount());
                int32 shieldAmount = CalculatePct(amount, procPct);

                if (Aura* shieldAura = eventTarget->GetAura(RUNE_PRIEST_LIGHTS_WARD_SHIELD))
                    shieldAmount += shieldAura->GetEffect(EFFECT_0)->GetAmount();

                shieldAmount = std::min<int32>(shieldAmount, maxAmount);

                caster->CastCustomSpell(RUNE_PRIEST_LIGHTS_WARD_SHIELD, SPELLVALUE_BASE_POINT0, shieldAmount, eventTarget, TRIGGERED_FULL_MASK);
            }

            caster->CastCustomSpell(SPELL_PRIEST_HOLY_WOUNDS_PROC, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_wave_of_light_accumulation::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pri_holy_weaving : public AuraScript
{
    PrepareAuraScript(spell_pri_holy_weaving);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
        {
            GetCaster()->CastCustomSpell(TALENT_PRIEST_HOLY_WEAVING_PROC, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), eventInfo.GetActionTarget(), TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_holy_weaving::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pri_regenerative_barrier : public AuraScript
{
    PrepareAuraScript(spell_pri_regenerative_barrier);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (Aura* aura = GetCaster()->GetAura(SPELL_PRIEST_BLISTERING_BARRIER))
            aura->ModCharges(1);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_regenerative_barrier::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// Holy Burst
class spell_pri_surprise_burst : public AuraScript
{
    PrepareAuraScript(spell_pri_surprise_burst);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        int32 holyFlameChance = aurEff->GetAmount();
        int32 holyStrikeChance = aurEff->GetBase()->GetEffect(EFFECT_1)->GetAmount();

        int32 procSpell = eventInfo.GetProcSpell()->GetSpellInfo()->Id;

        if (procSpell == SPELL_PRIEST_HOLY_STRIKE)
        {
            if (roll_chance_i(holyStrikeChance))
            {
                caster->CastSpell(caster, TALENT_PRIEST_HOLY_BURST_PROC, TRIGGERED_FULL_MASK);
                caster->RemoveSpellCooldown(SPELL_PRIEST_HOLY_ERUPTION, true);
            }
        }
        else
        {
            if (roll_chance_i(holyFlameChance))
            {
                caster->CastSpell(caster, TALENT_PRIEST_HOLY_BURST_PROC, TRIGGERED_FULL_MASK);
                caster->RemoveSpellCooldown(SPELL_PRIEST_HOLY_ERUPTION, true);
            }
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_surprise_burst::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_pri_defy_fate : public AuraScript
{
    PrepareAuraScript(spell_pri_defy_fate);

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* victim = GetTarget();

        if (!victim || victim->isDead())
            return;

        int32 remainingHealth = victim->GetHealth() - dmgInfo.GetDamage();

        if (remainingHealth <= 0 && !victim->HasAura(TALENT_PRIEST_DEFY_FATE_COOLDOWN))
        {
            absorbAmount = dmgInfo.GetDamage();
            victim->CastSpell(victim, TALENT_PRIEST_DEFY_FATE_HEAL, TRIGGERED_FULL_MASK);
            victim->CastSpell(victim, TALENT_PRIEST_DEFY_FATE_COOLDOWN, TRIGGERED_FULL_MASK);
        }
        else
            absorbAmount = 0;
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_defy_fate::Absorb, EFFECT_0);
    }
};

class spell_pri_light_overload : public AuraScript
{
    PrepareAuraScript(spell_pri_light_overload);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
        {
            GetCaster()->CastSpell(eventInfo.GetActionTarget(), SPELL_PRIEST_HOLY_ERUPTION_LIGHT_OVERLOAD, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_light_overload::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 586 - Fade 
class spell_pri_fade : public AuraScript
{
    PrepareAuraScript(spell_pri_fade);

    Aura* GetFadedAura(Unit* caster)
    {
        for (size_t i = 900118; i < 900124; i++)
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

        if (Aura* runeAura = GetFadedAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_1)->GetAmount();
            caster->AddAura(procSpell, caster);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_fade::HandleApply, EFFECT_1, SPELL_AURA_MOD_DETECTED_RANGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_fade::HandleRemove, EFFECT_1, SPELL_AURA_MOD_DETECTED_RANGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 48071 - Flash Heal
class spell_pri_flash_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_flash_heal);

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove From Darkness Comes Light Rune Buff
        for (size_t i = 900168; i < 900174; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }

        // Remove Resonant Words Rune Buff
        for (size_t i = 901078; i < 901084; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_pri_flash_heal::HandleAfterHit);
    }
};

// 48076 - Holy Nova Heal
class spell_pri_holy_nova_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_nova_heal);

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Rhapsody Rune Buff
        for (size_t i = 900226; i < 900232; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_pri_holy_nova_heal::HandleAfterHit);
    }
};

// 48127 - Mind Blast
class spell_pri_mind_blast : public SpellScript
{
    PrepareSpellScript(spell_pri_mind_blast);

    void HandleHitDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        if (Aura* twistedFaith = caster->GetAuraOfRankedSpell(TALENT_PRIEST_TWISTED_FAITH))
            if (target->HasAura(SPELL_PRIEST_SHADOW_WORD_PAIN))
                damage += CalculatePct(damage, twistedFaith->GetEffect(EFFECT_1)->GetAmount());

        SetHitDamage(damage);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Shadowy Insight Rune Buff
        if (caster->HasAura(900250))
            caster->RemoveAura(900250);

        // Remove Anund's Shackles Rune Buff
        for (size_t i = 900266; i < 900272; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }

        // Remove Mind Melt Rune Buff
        for (size_t i = 901318; i < 901324; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_mind_blast::HandleHitDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_pri_mind_blast::HandleAfterHit);
    }
};

// 81041 - Mind Sear
class spell_pri_mind_sear_aura : public AuraScript
{
    PrepareAuraScript(spell_pri_mind_sear_aura);

    Aura* GetBurningSearAura(Unit* caster)
    {
        for (size_t i = 900318; i < 900324; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* runeAura = GetBurningSearAura(caster))
        {
            int32 procChance = runeAura->GetEffect(EFFECT_0)->GetAmount();

            if (target->HasAura(SPELL_PRIEST_SHADOW_WORD_PAIN) && target->HasAura(SPELL_PRIEST_VAMPIRIC_TOUCH))
            {
                auto const& threatList = caster->getAttackers();
                auto threatListCopy = threatList;

                for (auto const& victim : threatListCopy)
                    if (victim->IsAlive())
                    {
                        if (victim == target)
                            continue;

                        float distance = victim->GetDistance(target->GetPosition());

                        if (distance > 10)
                            continue;

                        if (!roll_chance_i(procChance))
                            continue;

                        caster->AddAura(SPELL_PRIEST_SHADOW_WORD_PAIN, victim);
                        caster->AddAura(SPELL_PRIEST_VAMPIRIC_TOUCH, victim);
                    }
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pri_mind_sear_aura::HandleProc, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 10060 - Power Infusion 
class spell_pri_power_infusion : public AuraScript
{
    PrepareAuraScript(spell_pri_power_infusion);

    Aura* GetTwinsoftheSunPriestessAura(Unit* caster)
    {
        for (size_t i = 900330; i < 900336; i++)
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

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* runeAura = GetTwinsoftheSunPriestessAura(caster))
        {
            if (target != caster)
            {
                int32 procPct = runeAura->GetEffect(EFFECT_0)->GetAmount();
                int32 amount = CalculatePct(aurEff->GetAmount(), procPct);

                caster->CastCustomSpell(SPELL_PRIEST_POWER_INFUSION, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
            }
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_power_infusion::HandleApply, EFFECT_0, SPELL_AURA_MOD_MELEE_RANGED_HASTE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_power_infusion::HandleRemove, EFFECT_0, SPELL_AURA_MOD_MELEE_RANGED_HASTE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 48072 - Prayer of Healing
class spell_pri_prayer_of_healing : public SpellScript
{
    PrepareSpellScript(spell_pri_prayer_of_healing);

    Aura* GetPrayerfulLitanyAura(Unit* caster)
    {
        for (size_t i = 900412; i < 900418; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        targets.remove_if(Acore::RaidCheck(GetCaster(), false));

        if (Aura* runeAura = GetPrayerfulLitanyAura(caster))
        {
            auto litanyTargets = targets;
            litanyTargets.sort(Acore::HealthPctOrderPred());
            litanyTargets.resize(1);

            for (auto const& object : litanyTargets)
            {
                Unit* target = object->ToUnit();
                caster->AddAura(RUNE_PRIEST_PRAYERFUL_LITANY_LISTENER, target);
            }
        }
    }

    void HandleEffectHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 heal = GetHitHeal();

        if (Aura* runeAura = GetPrayerfulLitanyAura(caster))
            if (target->HasAura(RUNE_PRIEST_PRAYERFUL_LITANY_LISTENER))
            {
                int32 amount = CalculatePct(heal, runeAura->GetEffect(EFFECT_0)->GetAmount());
                caster->CastCustomSpell(RUNE_PRIEST_PRAYERFUL_LITANY_HEAL, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
            }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pri_prayer_of_healing::FilterTargets, EFFECT_ALL, TARGET_UNIT_SRC_AREA_ALLY);
        OnEffectHitTarget += SpellEffectFn(spell_pri_prayer_of_healing::HandleEffectHit, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 48068 - Renew 
class spell_pri_renew : public AuraScript
{
    PrepareAuraScript(spell_pri_renew);

    Aura* GetSinsOfTheManyAura(Unit* caster)
    {
        for (size_t i = 900506; i < 900512; i++)
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

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* empoweredRenew = caster->GetAuraOfRankedSpell(TALENT_PRIEST_EMPOWERED_RENEW))
        {
            int32 healAmount = CalculatePct((aurEff->GetAmount() * aurEff->GetTotalTicks()), empoweredRenew->GetEffect(EFFECT_0)->GetAmount());
            caster->CastSpell(target, SPELL_PRIEST_EMPOWERED_RENEW, TRIGGERED_FULL_MASK);
        }

        if (Aura* runeAura = GetSinsOfTheManyAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();

            if (Aura* buff = caster->GetAura(procSpell))
                buff->ModStackAmount(1);
            else
                caster->AddAura(procSpell, caster);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Reduce Sins of the many stacks by 1.
        for (size_t i = 900512; i < 900518; i++)
        {
            if (Aura* buff = caster->GetAura(i))
                buff->ModStackAmount(-1);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_renew::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_renew::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
    }
};

// 48125 - Shadow Word: Pain  
class spell_pri_shadow_word_pain : public SpellScript
{
    PrepareSpellScript(spell_pri_shadow_word_pain);

    Aura* GetCatharstickAura(Unit* caster)
    {
        for (size_t i = 900650; i < 900656; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleHitDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 damage = GetHitDamage();

        if (Aura* runeAura = GetCatharstickAura(caster))
        {
            int32 increase = runeAura->GetEffect(EFFECT_2)->GetAmount();
            damage += increase;
            runeAura->GetEffect(EFFECT_2)->SetAmount(0);
        }

        SetHitDamage(damage);
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove T1 4pc buff
        if (caster->HasAura(T1_PRIEST_SHADOW_4PC_BUFF))
            caster->RemoveAura(T1_PRIEST_SHADOW_4PC_BUFF);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_shadow_word_pain::HandleHitDamage, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterCast += SpellCastFn(spell_pri_shadow_word_pain::HandleAfterCast);
    }
};

// 48125 - Shadow Word: Pain Aura
class spell_pri_shadow_word_pain_aura : public AuraScript
{
    PrepareAuraScript(spell_pri_shadow_word_pain_aura);

    Aura* GetSinsOfTheManyAura(Unit* caster)
    {
        for (size_t i = 900506; i < 900512; i++)
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

        if (Aura* runeAura = GetSinsOfTheManyAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_1)->GetAmount();

            if (Aura* buff = caster->GetAura(procSpell))
                buff->ModStackAmount(1);
            else
                caster->AddAura(procSpell, caster);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Reduce Sins of the many stacks by 1.
        for (size_t i = 900518; i < 900524; i++)
        {
            if (Aura* buff = caster->GetAura(i))
                buff->ModStackAmount(-1);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_shadow_word_pain_aura::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_shadow_word_pain_aura::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 33206 - Pain Suppression
class spell_pri_pain_suppression : public AuraScript
{
    PrepareAuraScript(spell_pri_pain_suppression);

    Aura* GetPainTransformationAura(Unit* caster)
    {
        for (size_t i = 900774; i < 900780; i++)
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

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* runeAura = GetPainTransformationAura(caster))
        {
            int32 procSpell = runeAura->GetEffect(EFFECT_0)->GetAmount();
            caster->CastSpell(target, procSpell, TRIGGERED_FULL_MASK);

            if (caster->HasAura(SPELL_PRIEST_AUTONEMENT))
                caster->AddAura(SPELL_PRIEST_AUTONEMENT_AURA, target);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_pain_suppression::HandleApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
    }
};

// 48123 - Smite
class spell_pri_smite : public SpellScript
{
    PrepareSpellScript(spell_pri_smite);

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Weal and Woe Rune Buff
        for (size_t i = 900792; i < 900798; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_pri_smite::HandleAfterHit);
    }
};

// 81016 - Power Word: Solace
class spell_pri_power_word_solace : public SpellScript
{
    PrepareSpellScript(spell_pri_power_word_solace);

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Weal and Woe Rune Buff
        for (size_t i = 900792; i < 900798; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_pri_power_word_solace::HandleAfterHit);
    }
};

// 6064 - Heal
class spell_pri_heal : public SpellScript
{
    PrepareSpellScript(spell_pri_heal);

    Aura* GetEverlastingLightAura(Unit* caster)
    {
        for (size_t i = 901046; i < 901052; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleEffectHit(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        int32 heal = GetHitHeal();

        if (Aura* runeAura = GetEverlastingLightAura(caster))
        {
            int32 manaPct = caster->GetPowerPct(POWER_MANA);
            int32 amountPct = runeAura->GetEffect(EFFECT_0)->GetAmount();
            int32 minimumThreshold = runeAura->GetEffect(EFFECT_1)->GetAmount();
            float effectiveness;

            if (manaPct <= minimumThreshold)
                effectiveness = 100;
            if (manaPct > minimumThreshold)
                effectiveness = 100 * (100 - manaPct) / (100 - minimumThreshold);

            int32 finalPct = CalculatePct(amountPct, effectiveness);
            AddPct(heal, finalPct);
        }

        SetHitHeal(heal);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Resonant Words Rune Buff
        for (size_t i = 901078; i < 901084; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }

        // Remove Lightweaver Rune Buff
        for (size_t i = 901090; i < 901096; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_heal::HandleEffectHit, EFFECT_0, SPELL_EFFECT_HEAL);
        AfterHit += SpellHitFn(spell_pri_heal::HandleAfterHit);
    }
};

// 48156 - Mind Flay
class spell_pri_mind_flay : public AuraScript
{
    PrepareAuraScript(spell_pri_mind_flay);

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Surge of Insanity Rune Buff
        for (size_t i = 901164; i < 901176; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_mind_flay::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pri_mind_flay_damage : public SpellScript
{
    PrepareSpellScript(spell_pri_mind_flay_damage);

    void HandleHitDamage(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        SpellInfo const* mindFlay = sSpellMgr->AssertSpellInfo(SPELL_PRIEST_MIND_FLAY_DAMAGE);
        caster->EnergizeBySpell(caster, SPELL_PRIEST_MIND_FLAY_DAMAGE, mindFlay->GetEffect(EFFECT_1).CalcValue(), POWER_RUNIC_POWER);

        int32 damage = GetHitDamage();

        if (Aura* twistedFaith = caster->GetAuraOfRankedSpell(TALENT_PRIEST_TWISTED_FAITH))
            if (target->HasAura(SPELL_PRIEST_SHADOW_WORD_PAIN))
                damage += CalculatePct(damage, twistedFaith->GetEffect(EFFECT_1)->GetAmount());

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pri_mind_flay_damage::HandleHitDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 81048 - Mind Spike
class spell_pri_mind_spike : public SpellScript
{
    PrepareSpellScript(spell_pri_mind_spike);

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Surge of Insanity Rune Buff
        for (size_t i = 901164; i < 901176; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_pri_mind_spike::HandleAfterHit);
    }
};

// 86200 - Blistering Barriers
class spell_pri_blistering_barriers : public AuraScript
{
    PrepareAuraScript(spell_pri_blistering_barriers);

    Aura* GetHolyBloodAura(Unit* caster)
    {
        for (size_t i = 901422; i < 901428; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* runeAura = GetHolyBloodAura(caster))
            if (!caster->HasSpellCooldown(RUNE_PRIEST_HOLY_BLOOD_SHIELD))
            {
                int32 healthPct = caster->GetHealthPct();
                int32 amountPct = runeAura->GetEffect(EFFECT_0)->GetAmount();
                int32 amount = CalculatePct(caster->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY), amountPct);
                int32 minimumThreshold = runeAura->GetEffect(EFFECT_1)->GetAmount();
                float effectiveness;

                if (healthPct <= minimumThreshold)
                    effectiveness = 100;
                if (healthPct > minimumThreshold)
                    effectiveness = 100 * (100 - healthPct) / (100 - minimumThreshold);

                ApplyPct(amount, effectiveness);

                caster->CastCustomSpell(RUNE_PRIEST_HOLY_BLOOD_SHIELD, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
                caster->AddSpellCooldown(RUNE_PRIEST_HOLY_BLOOD_SHIELD, 0, 12000);
            }
    }

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* victim = GetTarget();
        Player* caster = GetCaster()->ToPlayer();

        if (!victim || victim->isDead())
            return;

        if (!caster || caster->isDead())
            return;

        if (dmgInfo.GetAttackType() == BASE_ATTACK && dmgInfo.GetAttacker() != caster && !caster->HasSpellCooldown(SPELL_PRIEST_BLISTERING_BARRIER_PROC))
        {
            PreventDefaultAction();
            aurEff->GetBase()->ModCharges(-1);
            caster->AddSpellCooldown(SPELL_PRIEST_BLISTERING_BARRIER_PROC, 0, 3000);
            victim->CastSpell(victim, SPELL_PRIEST_BLISTERING_BARRIER_PROC, TRIGGERED_FULL_MASK, nullptr, nullptr, caster->GetGUID());
            caster->CastSpell(victim, SPELL_PRIEST_BLISTERING_BARRIER_PROC, TRIGGERED_FULL_MASK);
        }
        else
        {
            absorbAmount = 0;
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_blistering_barriers::HandleApply, EFFECT_1, SPELL_AURA_MOD_BASE_RESISTANCE_PCT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pri_blistering_barriers::Absorb, EFFECT_0);
    }
};

// 86217 - Prescience
class spell_pri_prescience_cast : public SpellScript
{
    PrepareSpellScript(spell_pri_prescience_cast);

    void HandleTarget(WorldObject*& target)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* targetUnit = target->ToUnit();

        if (!targetUnit || targetUnit->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            if (targetUnit != caster)
                return;

            if (Group* playerGroup = player->GetGroup())
            {
                Position casterPos = player->GetPosition();
                auto const& allyList = playerGroup->GetMemberSlots();
                int32 maxDistance = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(caster);

                for (auto const& allyDps : allyList)
                {
                    Player* ally = ObjectAccessor::FindPlayer(allyDps.guid);
                    if (ally && ally->IsAlive())
                    {
                        float distance = ally->GetDistance(casterPos);

                        if (distance > maxDistance && ally->HasAura(SPELL_PRIEST_PRESCIENCE_SPELL))
                            continue;

                        target = ally;
                        return;
                    }
                }
            }
        }
    }

    void Register() override
    {
        OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_pri_prescience_cast::HandleTarget, EFFECT_0, TARGET_UNIT_TARGET_ALLY);
    }
};

// 86217 - Prescience
class spell_pri_prescience : public AuraScript
{
    PrepareAuraScript(spell_pri_prescience);

    Aura* GetFateMirrorAura(Unit* caster)
    {
        for (size_t i = 901552; i < 901558; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetAnachronismAura(Unit* caster)
    {
        for (size_t i = 901566; i < 901572; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (Aura* timelyFaithTalent = caster->GetAuraOfRankedSpell(TALENT_PRIEST_TIMELY_FAITH))
        {
            int32 procChance = timelyFaithTalent->GetEffect(EFFECT_0)->GetAmount();

            if (roll_chance_i(procChance))
                caster->AddAura(TALENT_PRIEST_HOLY_BURST_PROC, caster);
        }

        if (Aura* runeAura = GetFateMirrorAura(caster))
        {
            int32 procAura = runeAura->GetEffect(EFFECT_0)->GetAmount();
            caster->AddAura(procAura, target);
        }

        if (Aura* runeAura = GetAnachronismAura(caster))
        {
            if (Aura* talent = caster->GetAuraOfRankedSpell(TALENT_PRIEST_HOLY_BURST))
            {
                int32 procChance = runeAura->GetEffect(EFFECT_0)->GetAmount();

                if (roll_chance_i(procChance))
                    caster->AddAura(TALENT_PRIEST_HOLY_BURST_PROC, caster);
            }
        }

        if (Aura* set_T1_2pc = caster->GetAura(T1_PRIEST_ABSOLUTION_2PC))
        {
            int32 totalNumber = set_T1_2pc->GetEffect(EFFECT_0)->GetAmount();
            int32 prescienceNumber = set_T1_2pc->GetEffect(EFFECT_2)->GetAmount() + 1;

            if (prescienceNumber < totalNumber)
                set_T1_2pc->GetEffect(EFFECT_2)->SetAmount(prescienceNumber);
            else
            {
                int32 duration = GetMaxDuration();
                int32 durationIncrease = set_T1_2pc->GetEffect(EFFECT_1)->GetAmount();
                AddPct(duration, durationIncrease);

                SetMaxDuration(duration);
                RefreshDuration();

                set_T1_2pc->GetEffect(EFFECT_2)->SetAmount(0);
            }
        }
    }

    void HandleRemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        // Remove Fate Mirror Rune Buff
        for (size_t i = 901558; i < 901564; i++)
        {
            if (target->HasAura(i))
                target->RemoveAura(i);
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_pri_prescience::HandleApplyEffect, EFFECT_0, SPELL_AURA_MOD_CRIT_PCT, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_pri_prescience::HandleRemoveEffect, EFFECT_0, SPELL_AURA_MOD_CRIT_PCT, AURA_EFFECT_HANDLE_REAL);
    }
};

// 86204 - Holy Eruption
class spell_pri_holy_eruption : public SpellScript
{
    PrepareSpellScript(spell_pri_holy_eruption);

    Aura* GetMomentumShiftAura(Unit* caster)
    {
        for (size_t i = 901484; i < 901490; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void HandleCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* runeAura = GetMomentumShiftAura(caster))
            if (caster->HasAura(TALENT_PRIEST_HOLY_BURST_PROC))
                caster->AddAura(runeAura->GetEffect(EFFECT_0)->GetAmount(), caster);
    }

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetHitUnit();

        if (!target || target->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            Unit* mainTarget = ObjectAccessor::GetUnit(*caster, caster->GetTarget());

            if (mainTarget && target == mainTarget)
            {
                if (Aura* tier1_4pc_buff = caster->GetAura(T1_PRIEST_ABSOLUTION_4PC_BUFF))
                {
                    int32 number = 0;
                    int32 cooldown = tier1_4pc_buff->GetEffect(EFFECT_0)->GetAmount();

                    if (caster->HasAura(SPELL_PRIEST_PRESCIENCE_SPELL))
                        number++;

                    if (Group* playerGroup = player->GetGroup())
                    {
                        Position casterPos = player->GetPosition();
                        auto const& allyList = playerGroup->GetMemberSlots();

                        for (auto const& target : allyList)
                        {
                            Player* ally = ObjectAccessor::FindPlayer(target.guid);
                            if (ally && ally->IsAlive())
                            {
                                float distance = ally->GetDistance(casterPos);

                                if (distance <= 60 && ally->HasAura(SPELL_PRIEST_PRESCIENCE_SPELL))
                                    number++;
                            }
                        }
                    }

                    while (number > 0)
                    {
                        caster->CastSpell(target, T1_PRIEST_ABSOLUTION_4PC_DAMAGE, TRIGGERED_FULL_MASK);
                        player->ModifySpellCooldown(SPELL_PRIEST_HOLY_MIGHT, -cooldown);
                        number--;
                    }

                    tier1_4pc_buff->Remove();
                }
            }
        }
    }

    void Register() override
    {
        BeforeCast += SpellCastFn(spell_pri_holy_eruption::HandleCast);
        OnEffectHitTarget += SpellEffectFn(spell_pri_holy_eruption::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 81051 - Shadow Crash damage  
class spell_pri_shadow_crash_damage : public SpellScript
{
    PrepareSpellScript(spell_pri_shadow_crash_damage);

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove T1 4pc buff
        if (caster->HasAura(T1_PRIEST_SHADOW_4PC_BUFF))
            caster->RemoveAura(T1_PRIEST_SHADOW_4PC_BUFF);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_pri_shadow_crash_damage::HandleAfterCast);
    }
};

class spell_pri_tome_of_sacred_virtues : public AuraScript
{
    PrepareAuraScript(spell_pri_tome_of_sacred_virtues);

    void HandleLearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->learnSpell(SPELL_PRIEST_PURGE_THE_WICKED);
        target->learnSpell(SPELL_PRIEST_POWER_WORD_SOLACE);
        target->learnSpell(SPELL_PRIEST_SHADOW_COVENANT);
        target->learnSpell(SPELL_PRIEST_EVANGELISM);
    }

    void HandleUnlearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->removeSpell(SPELL_PRIEST_PURGE_THE_WICKED, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_POWER_WORD_SOLACE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_SHADOW_COVENANT, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_EVANGELISM, SPEC_MASK_ALL, false);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_tome_of_sacred_virtues::HandleLearn, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_tome_of_sacred_virtues::HandleUnlearn, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pri_scroll_of_divine_grace : public AuraScript
{
    PrepareAuraScript(spell_pri_scroll_of_divine_grace);

    void HandleLearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->learnSpell(SPELL_PRIEST_GREATER_HEAL);
        target->learnSpell(SPELL_PRIEST_HOLY_WORD_CHASTITE);
        target->learnSpell(SPELL_PRIEST_HOLY_WORD_SERENITY);
        target->learnSpell(SPELL_PRIEST_DESPERATE_PRAYER);
    }

    void HandleUnlearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->removeSpell(SPELL_PRIEST_GREATER_HEAL, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_HOLY_WORD_CHASTITE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_HOLY_WORD_SERENITY, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_DESPERATE_PRAYER, SPEC_MASK_ALL, false);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_scroll_of_divine_grace::HandleLearn, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_scroll_of_divine_grace::HandleUnlearn, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_pri_codex_of_radiant_authority : public AuraScript
{
    PrepareAuraScript(spell_pri_codex_of_radiant_authority);

    void HandleLearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->learnSpell(SPELL_PRIEST_PRESCIENCE_SPELL);
        target->learnSpell(SPELL_PRIEST_LIGHTS_FADE);
        target->learnSpell(SPELL_PRIEST_HOLY_STRIKE);
        target->learnSpell(SPELL_PRIEST_HOLY_ERUPTION);
    }

    void HandleUnlearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->removeSpell(SPELL_PRIEST_PRESCIENCE_SPELL, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_LIGHTS_FADE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_HOLY_STRIKE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_PRIEST_HOLY_ERUPTION, SPEC_MASK_ALL, false);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pri_codex_of_radiant_authority::HandleLearn, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pri_codex_of_radiant_authority::HandleUnlearn, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// Death Tap
class spell_pri_death_tap : public AuraScript
{
    PrepareAuraScript(spell_pri_death_tap);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        caster->RemoveSpellCooldown(SPELL_PRIEST_SHADOW_WORD_DEATH, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_pri_death_tap::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

void AddSC_priest_spell_scripts()
{
    RegisterSpellScript(spell_pri_shadowfiend_scaling);
    RegisterSpellScript(spell_pri_circle_of_healing);
    RegisterSpellScript(spell_pri_divine_aegis);
    RegisterSpellScript(spell_pri_divine_hymn);
    RegisterSpellScript(spell_pri_glyph_of_prayer_of_healing);
    RegisterSpellScript(spell_pri_guardian_spirit);
    RegisterSpellScript(spell_pri_hymn_of_hope);
    RegisterSpellScript(spell_pri_item_greater_heal_refund);
    RegisterSpellScript(spell_pri_lightwell);
    RegisterSpellScript(spell_pri_lightwell_renew);
    RegisterSpellScript(spell_pri_mana_burn);
    RegisterSpellScript(spell_pri_mana_leech);
    RegisterSpellScript(spell_pri_mind_sear);
    RegisterSpellScript(spell_pri_pain_and_suffering_proc);
    RegisterSpellScript(spell_pri_penance);
    RegisterSpellScript(spell_pri_penance_hit);
    RegisterSpellScript(spell_pri_penance_purge);
    RegisterSpellAndAuraScriptPair(spell_pri_power_word_shield, spell_pri_power_word_shield_aura);
    RegisterSpellScript(spell_pri_prayer_of_mending_heal);
    RegisterSpellScript(spell_pri_shadow_word_death);
    RegisterSpellScript(spell_pri_vampiric_touch);
    RegisterSpellScript(spell_pri_mind_control);
    RegisterSpellScript(spell_pri_devouring_plague);
    RegisterSpellScript(spell_pri_devouring_plague_heal);
    RegisterSpellScript(spell_pri_mass_resurrection);
    RegisterSpellScript(spell_pri_leap_of_faith);
    RegisterSpellScript(spell_pri_power_word_life);
    RegisterSpellScript(spell_pri_void_shift);
    RegisterSpellScript(spell_pri_atonement);
    RegisterSpellScript(spell_pri_atonement_heal);
    RegisterSpellScript(spell_pri_power_word_radiance);
    RegisterSpellScript(spell_pri_power_word_barrier);
    RegisterSpellScript(spell_pri_purge_the_wicked_aura);
    RegisterSpellScript(spell_pri_purge_the_wicked);
    RegisterSpellScript(spell_pri_rapture);
    RegisterSpellScript(spell_pri_evangelism);
    RegisterSpellScript(spell_pri_light_wrath);
    RegisterSpellScript(spell_pri_holy_word_serenity_cooldown);
    RegisterSpellScript(spell_pri_holy_word_chastise_cooldown);
    RegisterSpellScript(spell_pri_holy_fire);
    RegisterSpellScript(spell_pri_holy_fire_aura);
    RegisterSpellScript(spell_pri_empyreal_blaze);
    RegisterSpellScript(spell_pri_holy_word_sanctify_cooldown);
    RegisterSpellScript(spell_pri_apotheosis);
    RegisterSpellScript(spell_pri_holy_word_salvation);
    RegisterSpellScript(spell_pri_holy_word_salvation_cooldown);
    RegisterSpellScript(spell_pri_divine_word);
    RegisterSpellScript(spell_pri_void_eruption);
    RegisterSpellScript(spell_pri_void_eruption_cooldown);
    RegisterSpellScript(spell_pri_insanity_on_cast);
    RegisterSpellScript(spell_pri_insanity_on_periodic);
    RegisterSpellScript(spell_pri_shadowy_apparitions);
    RegisterSpellScript(spell_pri_shadowy_apparitions_aoe);
    RegisterSpellScript(spell_pri_shadowy_apparitions_damage);
    RegisterSpellScript(spell_pri_prayer_of_mending);
    RegisterSpellScript(spell_pri_holy_blossom);
    RegisterSpellScript(spell_pri_holy_flame);
    RegisterSpellScript(spell_pri_holy_flame_heal);
    RegisterSpellScript(spell_pri_holy_might);
    RegisterSpellScript(spell_pri_holy_might_proc);
    RegisterSpellScript(spell_pri_holy_might_increase);
    RegisterSpellScript(spell_pri_wave_of_light);
    RegisterSpellScript(spell_pri_wave_of_light_accumulation);
    RegisterSpellScript(spell_pri_wave_of_light_absorb);
    RegisterSpellScript(spell_pri_holy_weaving);
    RegisterSpellScript(spell_pri_regenerative_barrier);
    RegisterSpellScript(spell_pri_surprise_burst);
    RegisterSpellScript(spell_pri_defy_fate);
    RegisterSpellScript(spell_pri_light_overload);
    RegisterSpellScript(spell_pri_fade);
    RegisterSpellScript(spell_pri_flash_heal);
    RegisterSpellScript(spell_pri_holy_nova_heal);
    RegisterSpellScript(spell_pri_mind_blast);
    RegisterSpellScript(spell_pri_mind_sear_aura);
    RegisterSpellScript(spell_pri_power_infusion);
    RegisterSpellScript(spell_pri_prayer_of_healing);
    RegisterSpellScript(spell_pri_renew);
    RegisterSpellScript(spell_pri_shadow_word_pain);
    RegisterSpellScript(spell_pri_shadow_word_pain_aura);
    RegisterSpellScript(spell_pri_pain_suppression);
    RegisterSpellScript(spell_pri_smite);
    RegisterSpellScript(spell_pri_power_word_solace);
    RegisterSpellScript(spell_pri_heal);
    RegisterSpellScript(spell_pri_mind_flay);
    RegisterSpellScript(spell_pri_mind_flay_damage);
    RegisterSpellScript(spell_pri_mind_spike);
    RegisterSpellScript(spell_pri_blistering_barriers);
    RegisterSpellScript(spell_pri_prescience_cast);
    RegisterSpellScript(spell_pri_prescience);
    RegisterSpellScript(spell_pri_holy_eruption); 
    RegisterSpellScript(spell_pri_shadow_crash_damage);
    RegisterSpellScript(spell_pri_tome_of_sacred_virtues);
    RegisterSpellScript(spell_pri_scroll_of_divine_grace);
    RegisterSpellScript(spell_pri_codex_of_radiant_authority);
    RegisterSpellScript(spell_pri_death_tap);


    new npc_pri_shadowy_apparitions();
}
