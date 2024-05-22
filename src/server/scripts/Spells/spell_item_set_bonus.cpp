#include "PetDefines.h"
#include "Pet.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Totem.h"
#include "UnitAI.h"
#include "Log.h"

enum SetSpells
{
    // Spells
    
    // Warrior
    SPELL_WARRIOR_ODYNS_FURY = 84507,
    SPELL_WARRIOR_LAST_STAND = 12975,
    SPELL_WARRIOR_LAST_STAND_AURA = 12976,
    SPELL_WARRIOR_SHIELD_VAULT = 84559,

    // Mage
    SPELL_MAGE_ICE_LANCE = 42914,
    SPELL_MAGE_WEAPON_ENCHANT_ARCANIZE_AURA = 81572,
    SPELL_MAGE_WEAPON_ENCHANT_CONDUIT_AURA = 81575,
    SPELL_MAGE_WEAPON_ENCHANT_DEFLECTION_AURA = 81578,
    SPELL_MAGE_WEAPON_ENCHANT_FORCE_AURA = 81580,
    SPELL_MAGE_WEAPON_ENCHANT_IGNIS_AURA = 81583,
    SPELL_MAGE_WEAPON_ENCHANT_SNOWBOUND_AURA = 81586,

    // Paladin
    SPELL_PALADIN_AVENGERS_SHIELD = 48827,
    SPELL_PALADIN_DIVINE_ZEAL = 86508,
    SPELL_PALADIN_JUDGEMENT_DAMAGE = 54158,
    SPELL_PALADIN_INSPIRING_VANGUARD = 80105,
    SPELL_PALADIN_INSPIRING_VANGUARD_BUFF = 80104,

    // Hunter
    SPELL_HUNTER_BESTIAL_WRATH = 80133,
    SPELL_HUNTER_TWILIGHT_PIERCER = 85006,

    // Death Knight
    SPELL_DEATHKNIGHT_NECROTIC_BLESSING = 87012,
    SPELL_DEATHKNIGHT_PILLAR_OF_FROST = 80303,
    SPELL_DEATHKNIGHT_VAMPIRIC_BLOOD = 55233,

    // Druid
    SPELL_DRUID_EFFLORESCENCE_HEAL = 80579,
    SPELL_DRUID_LIFEBLOOM = 48451,
    SPELL_DRUID_LIFEBLOOM_EXPIRE = 80588,
    SPELL_DRUID_NATURES_SWIFTNESS = 17116,
    SPELL_DRUID_RAGE_OF_THE_SLEEPER = 80570,
    SPELL_DRUID_STARFALL_DAMAGE = 53198,
    SPELL_DRUID_STARFIRE = 48465,

    // Warlock
    SPELL_WARLOCK_FIERY_SYMBOL = 83108,

    // Priest
    SPELL_PRIEST_ATONEMENT_HEAL = 81012,
    SPELL_PRIEST_HOLY_ERUPTION = 86204,
    SPELL_PRIEST_HOLY_MIGHT = 86208,
    SPELL_PRIEST_HOLY_WORD_SANCTIFY = 81029,
    SPELL_PRIEST_HOLY_WORD_SERENITY = 81025,
    SPELL_PRIEST_PRESCIENCE = 86217,
    SPELL_PRIEST_RENEW = 48068,
    SPELL_PALADIN_HAMMER_OF_WRATH = 48806,

    // Shaman
    SPELL_SHAMAN_EARTH_SHOCK = 49231,
    SPELL_SHAMAN_EARTHQUAKE = 84014,
    SPELL_SHAMAN_ELEMENTAL_BLAST = 84022,
    SPELL_SHAMAN_HEALING_SURGE = 84004,
    SPELL_SHAMAN_HEALING_WAVE = 49273,
    SPELL_SHAMAN_RIPTIDE = 61301,

    // ROGUE
    SPELL_ROGUE_OPPORTUNITY_BUFF = 82086,
    SPELL_ROGUE_RIPOSTE = 82064,


    // Sets
    SPELL_SET_GENERAL_VOLCANIC_ARMOR_DAMAGE = 9057,
    SPELL_SET_GENERAL_VESTMENTS_OF_THE_DEVOUT_SHIELD = 27779,

    // Warrior
    SPELL_SET_T1_WARRIOR_FURY_BONUS2_BUFF = 95101,
    SPELL_SET_T1_WARRIOR_FURY_BONUS2_VISUAL = 95102,

    // Mage
    SPELL_SET_T1_MAGE_ARCANE_4PC_LISTENER = 95503,
    SPELL_SET_T1_MAGE_ARCANE_4PC_DAMAGE = 95505,
    SPELL_SET_T1_MAGE_FROST_BONUS2_DAMAGE = 95701,

    // Paladin
    SPELL_SET_T1_PALADIN_PROT_BONUS2_DOT = 96101,
    SPELL_SET_T1_PALADIN_PROT_BONUS2_HEAL = 96102,
    SPELL_SET_T1_PALADIN_RET_4PC = 96201,
    SPELL_SET_T1_PALADIN_RET_4PC_HAMMER_OF_WRATH = 96203,

    // Hunter
    SPELL_SET_T1_HUNTER_MM_4PC_BUFF = 96602,
    SPELL_SET_T1_HUNTER_MM_2PC_DEBUFF = 96603,
    SPELL_SET_T1_HUNTER_SURV_2PC_BUFF = 96701,
    SPELL_SET_T1_HUNTER_SURV_4PC_BUFF = 96703,

    // Death Knight
    SPELL_SET_T1_DEATHKNIGHT_BLOOD_4PC_BUFF = 97002,
    SPELL_SET_T1_DEATHKNIGHT_FROST_4PC_BUFF = 97102,
    SPELL_SET_T1_DEATHKNIGHT_UNHOLY_2PC_PETBUFF = 97201,
    SPELL_SET_T1_DEATHKNIGHT_UNHOLY_4PC_PETBUFF = 97203,
    SPELL_SET_T1_DEATHKNIGHT_UNHOLY_4PC_BUFF = 97204,

    // Druid
    SPELL_SET_T1_DRUID_FERAL_2PC_BUFF = 97601,
    SPELL_SET_T1_DRUID_FERAL_4PC = 97602,
    SPELL_SET_T1_DRUID_FERAL_4PC_DOT = 97603,
    SPELL_SET_T1_DRUID_GUARDIAN_2PC = 97700,
    SPELL_SET_T1_DRUID_GUARDIAN_4PC_SHIELD = 97703,
    SPELL_SET_T1_DRUID_GUARDIAN_4PC_DAMAGE = 97704,
    SPELL_SET_T1_DRUID_RESTORATION_4PC_BUFF = 97802,

    // Warlock
    SPELL_SET_T1_WARLOCK_AFFLI_4PC_BUFF = 98002,
    SPELL_SET_T1_WARLOCK_AFFLI_4PC_LISTENER = 98003,
    SPELL_SET_T1_WARLOCK_DESTRU_4PC_DOT = 98204,

    // Priest
    SPELL_SET_T1_PRIEST_SHADOW_2PC_SHADOW_WORD_DEATH = 98701,
    SPELL_SET_T1_PRIEST_ABSOLUTION_4PC_HOLY_ERUPTION = 98803,

    // Shaman
    SPELL_SET_T1_SHAMAN_RESTORATION_2PC_BUFF = 99201,
    SPELL_SET_T1_SHAMAN_RESTORATION_2PC_HEAL = 99202,

    // Rogue
    SPELL_SET_T1_ROGUE_SUB_2PC_BUFF = 99701,
    SPELL_SET_T1_ROGUE_OUTLAW_2PC_BUFF = 99801,
};

// --------------------------------------------------------------------------- General Sets ---------------------------------------------------------------------------

// 41676 - Prisoner's Shackle
class spell_set_prisoners_shackle : public AuraScript
{
    PrepareAuraScript(spell_set_prisoners_shackle);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 absorbPct = GetEffect(EFFECT_1)->GetAmount();
        int32 absorb = std::min<int32>(dmgInfo.GetDamage(), CalculatePct(caster->GetStat(STAT_STAMINA), absorbPct));

        absorbAmount = absorb;
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_set_prisoners_shackle::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_set_prisoners_shackle::Absorb, EFFECT_0);
    }
};

// 27778 - Vestments of the Devout
class spell_set_vestments_of_the_devout : public AuraScript
{
    PrepareAuraScript(spell_set_vestments_of_the_devout);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHealInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetHealInfo()->GetTarget();

        if (!target || target->isDead())
            return;

        int32 ratio = aurEff->GetAmount();
        float amount = CalculatePct(caster->SpellBaseHealingBonusDone(GetSpellInfo()->GetSchoolMask()), ratio);

        // Improved PW: Shield: its weird having a SPELLMOD_ALL_EFFECTS here but its blizzards doing :)
        // Improved PW: Shield is only applied at the spell healing bonus because it was already applied to the base value in CalculateSpellDamage
        amount = caster->ApplyEffectModifiers(GetSpellInfo(), aurEff->GetEffIndex(), amount);
        amount *= caster->CalculateLevelPenalty(GetSpellInfo());

        caster->CastCustomSpell(SPELL_SET_GENERAL_VESTMENTS_OF_THE_DEVOUT_SHIELD, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_vestments_of_the_devout::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_vestments_of_the_devout::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};


// 9233 - Volcanic Armor Damage
class spell_set_volcanic_armor : public AuraScript
{
    PrepareAuraScript(spell_set_volcanic_armor);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetAttacker();

        if (!target || target->isDead())
            return;

        int32 amount = CalculatePct(caster->GetStat(STAT_STAMINA), aurEff->GetAmount());

        caster->CastCustomSpell(SPELL_SET_GENERAL_VOLCANIC_ARMOR_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_volcanic_armor::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_volcanic_armor::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 79413 - Green Dragon Mail
class spell_set_green_dragon_mail : public AuraScript
{
    PrepareAuraScript(spell_set_green_dragon_mail);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHealInfo();
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_green_dragon_mail::CheckProc);
    }
};

// 79415 - Regalia of Undead Cleansing
class spell_set_regalia_of_undead_cleansing : public AuraScript
{
    PrepareAuraScript(spell_set_regalia_of_undead_cleansing);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return false;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return false;

        return target->GetCreatureType() == CREATURE_TYPE_UNDEAD;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_regalia_of_undead_cleansing::CheckProc);
    }
};

// 41736 - Staff Intellect
class spell_set_staff_intellect : public AuraScript
{
    PrepareAuraScript(spell_set_staff_intellect);

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = 2 * IN_MILLISECONDS;
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            int32 value = aurEff->GetAmount();
            int32 amount = GetEffect(EFFECT_0)->GetAmount();

            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
            {
                if (item->IsFitToSpellRequirements(GetSpellInfo()))
                    if (amount == value)
                        return;
                    else
                        amount = value;
            }
            else
                if (amount == 0)
                    return;
                else
                    amount = 0;

            GetEffect(EFFECT_0)->ChangeAmount(amount);
            GetEffect(EFFECT_1)->ChangeAmount(amount);
        }
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_set_staff_intellect::CalcPeriodic, EFFECT_2, SPELL_AURA_ANY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_set_staff_intellect::HandlePeriodic, EFFECT_2, SPELL_AURA_ANY);
    }
};

// 41736 - Shield Intellect
class spell_set_shield_intellect : public AuraScript
{
    PrepareAuraScript(spell_set_shield_intellect);

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = 2 * IN_MILLISECONDS;
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            int32 value = aurEff->GetAmount();
            int32 amount = GetEffect(EFFECT_0)->GetAmount();

            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
            {
                if (item->IsFitToSpellRequirements(GetSpellInfo()))
                    if (amount == value)
                        return;
                    else
                        amount = value;
            }
            else
                if (amount == 0)
                    return;
                else
                    amount = 0;

            GetEffect(EFFECT_0)->ChangeAmount(amount);
            GetEffect(EFFECT_1)->ChangeAmount(amount);
        }
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_set_shield_intellect::CalcPeriodic, EFFECT_2, SPELL_AURA_ANY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_set_shield_intellect::HandlePeriodic, EFFECT_2, SPELL_AURA_ANY);
    }
};

// 79417 - Shard of the God
class spell_set_shard_of_the_god : public AuraScript
{
    PrepareAuraScript(spell_set_shard_of_the_god);

    void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
    {
        isPeriodic = true;
        amplitude = 2 * IN_MILLISECONDS;
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            int32 totalVersatility = player->GetUInt32Value(static_cast<uint16>(PLAYER_FIELD_COMBAT_RATING_1) + CR_EXPERTISE);
            int32 amount = CalculatePct(totalVersatility, aurEff->GetAmount());

            GetEffect(EFFECT_0)->ChangeAmount(amount);
        }
    }

    void Register() override
    {
        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_set_shard_of_the_god::CalcPeriodic, EFFECT_1, SPELL_AURA_ANY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_set_shard_of_the_god::HandlePeriodic, EFFECT_1, SPELL_AURA_ANY);
    }
};

// --------------------------------------------------------------------------- Warrior Sets ---------------------------------------------------------------------------

// 95100 - Battlegear of Rage Fury T1 Bonus 2
class spell_set_warrior_fury_T1_B2 : public AuraScript
{
    PrepareAuraScript(spell_set_warrior_fury_T1_B2);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_WARRIOR_ODYNS_FURY;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 stacks = aurEff->GetAmount();

        if (Aura* visualAura = caster->AddAura(SPELL_SET_T1_WARRIOR_FURY_BONUS2_VISUAL, caster))
            visualAura->SetStackAmount(stacks);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_warrior_fury_T1_B2::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_warrior_fury_T1_B2::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 95102 - Battlegear of Rage Fury T1 Bonus 2 Visual
class spell_set_warrior_fury_T1_B2_visual : public AuraScript
{
    PrepareAuraScript(spell_set_warrior_fury_T1_B2_visual);

    void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        caster->AddAura(SPELL_SET_T1_WARRIOR_FURY_BONUS2_BUFF, caster);
    }

    void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(SPELL_SET_T1_WARRIOR_FURY_BONUS2_BUFF))
            caster->RemoveAura(SPELL_SET_T1_WARRIOR_FURY_BONUS2_BUFF);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_set_warrior_fury_T1_B2_visual::ApplyEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_set_warrior_fury_T1_B2_visual::RemoveEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 95103 - Battlegear of Rage Fury T1 Bonus 4
class spell_set_warrior_fury_T1_B4 : public AuraScript
{
    PrepareAuraScript(spell_set_warrior_fury_T1_B4);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 cooldown = aurEff->GetAmount();

        if (Player* player = caster->ToPlayer())
            player->ModifySpellCooldown(SPELL_WARRIOR_ODYNS_FURY, -cooldown);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_warrior_fury_T1_B4::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_warrior_fury_T1_B4::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 95200 - Battlegear of Safeguard Prot T1 Bonus 2
class spell_set_warrior_prot_T1_B2 : public AuraScript
{
    PrepareAuraScript(spell_set_warrior_prot_T1_B2);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 cooldown = aurEff->GetAmount();

        if (caster->HasAura(SPELL_WARRIOR_LAST_STAND_AURA))
            cooldown *= 2;

        if (Player* player = caster->ToPlayer())
            player->ModifySpellCooldown(SPELL_WARRIOR_LAST_STAND, -cooldown);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_warrior_prot_T1_B2::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_warrior_prot_T1_B2::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 95302 - Battlegear of Tenacity Hoplite T1 Bonus 4
class spell_set_warrior_hoplite_T1_B4 : public AuraScript
{
    PrepareAuraScript(spell_set_warrior_hoplite_T1_B4);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 cooldown = aurEff->GetAmount();

        if (Player* player = caster->ToPlayer())
            player->ModifySpellCooldown(SPELL_WARRIOR_SHIELD_VAULT, -cooldown);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_warrior_hoplite_T1_B4::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_warrior_hoplite_T1_B4::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// --------------------------------------------------------------------------- Mage Sets ---------------------------------------------------------------------------

// 95504 - Arcanist Regalia Arcane T1 4pc buff
class spell_set_mage_arcane_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_mage_arcane_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        int32 amount = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());
        caster->CastCustomSpell(SPELL_SET_T1_MAGE_ARCANE_4PC_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_mage_arcane_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_mage_arcane_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 95505 - Arcanist Regalia Arcane T1 4pc damage
class spell_set_mage_arcane_T1_4pc_target : public SpellScript
{
    PrepareSpellScript(spell_set_mage_arcane_T1_4pc_target);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* target = ObjectAccessor::GetUnit(*GetCaster(), GetCaster()->GetTarget());

        if (!target || target->isDead())
            return;

        targets.remove(target);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_set_mage_arcane_T1_4pc_target::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 95700 - Frostweaver Regalia Frost T1 2pc
class spell_set_mage_frost_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_mage_frost_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        if (target->HasAuraState(AURA_STATE_FROZEN, sSpellMgr->AssertSpellInfo(SPELL_MAGE_ICE_LANCE), caster))
        {
            int32 amount = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());
            caster->CastCustomSpell(SPELL_SET_T1_MAGE_FROST_BONUS2_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_mage_frost_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_mage_frost_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_set_mage_frost_T1_2pc_target : public SpellScript
{
    PrepareSpellScript(spell_set_mage_frost_T1_2pc_target);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* target = ObjectAccessor::GetUnit(*GetCaster(), GetCaster()->GetTarget());

        if (!target || target->isDead())
            return;

        targets.remove(target);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_set_mage_frost_T1_2pc_target::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

// 95800 - Arcaneblade Regalia Spellblade T1 Bonus 2
class spell_set_mage_spellblade_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_mage_spellblade_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return false;

        if (Player* player = caster->ToPlayer())
        {
            return player->HasAura(SPELL_MAGE_WEAPON_ENCHANT_ARCANIZE_AURA)
                || player->HasAura(SPELL_MAGE_WEAPON_ENCHANT_CONDUIT_AURA)
                || player->HasAura(SPELL_MAGE_WEAPON_ENCHANT_DEFLECTION_AURA)
                || player->HasAura(SPELL_MAGE_WEAPON_ENCHANT_FORCE_AURA)
                || player->HasAura(SPELL_MAGE_WEAPON_ENCHANT_IGNIS_AURA)
                || player->HasAura(SPELL_MAGE_WEAPON_ENCHANT_SNOWBOUND_AURA);
        }

        return false;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_mage_spellblade_T1_2pc::CheckProc);
    }
};

// --------------------------------------------------------------------------- Paladin Sets ---------------------------------------------------------------------------

// 96100 - Holy Defender Armor Prot T1 Bonus 2
class spell_set_paladin_prot_T1_B2 : public AuraScript
{
    PrepareAuraScript(spell_set_paladin_prot_T1_B2);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        if (!eventInfo.GetSpellInfo())
            return false;

        /*if (eventInfo.GetDamageInfo()->GetDamageType() == DOT)
            return eventInfo.GetSpellInfo()->Id == SPELL_SET_T1_PALADIN_PROT_BONUS2_DOT;*/

        if (eventInfo.GetDamageInfo()->GetDamageType() == SPELL_DIRECT_DAMAGE)
            return eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_AVENGERS_SHIELD;

        return false;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        int32 damage = eventInfo.GetDamageInfo()->GetDamage();

        if (damage <= 0)
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;

        if (spellID == SPELL_PALADIN_AVENGERS_SHIELD)
        {
            int32 amount = CalculatePct(damage, aurEff->GetAmount());
            amount /= 5;
            caster->CastCustomSpell(SPELL_SET_T1_PALADIN_PROT_BONUS2_DOT, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }

        /*if (spellID == SPELL_SET_T1_PALADIN_PROT_BONUS2_DOT)
        {
            int32 amount = CalculatePct(damage, GetEffect(EFFECT_1)->GetAmount());
            caster->CastCustomSpell(SPELL_SET_T1_PALADIN_PROT_BONUS2_HEAL, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
        }*/
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_paladin_prot_T1_B2::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_paladin_prot_T1_B2::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 96103 - Holy Defender Armor Prot T1 Bonus 4
class spell_set_paladin_prot_T1_B4 : public AuraScript
{
    PrepareAuraScript(spell_set_paladin_prot_T1_B4);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() >= 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        int32 procChance = GetEffect(EFFECT_1)->GetAmount();

        if (roll_chance_i(procChance))
            if (Player* player = caster->ToPlayer())
            {
                player->RemoveSpellCooldown(SPELL_PALADIN_AVENGERS_SHIELD, true);

                if (player->HasAura(SPELL_PALADIN_INSPIRING_VANGUARD))
                    player->CastSpell(player, SPELL_PALADIN_INSPIRING_VANGUARD_BUFF, TRIGGERED_FULL_MASK);
            }

        int32 damage = eventInfo.GetDamageInfo()->GetDamage();
        int32 amount = CalculatePct(damage, aurEff->GetAmount());
        amount /= 5;

        caster->CastCustomSpell(SPELL_SET_T1_PALADIN_PROT_BONUS2_DOT, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_paladin_prot_T1_B4::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_paladin_prot_T1_B4::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 96200 - Avenger Armor Ret T1 Bonus 2 + Bonus 4
class spell_set_paladin_ret_T1_B2B4 : public AuraScript
{
    PrepareAuraScript(spell_set_paladin_ret_T1_B2B4);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetActionTarget() == GetCaster())
            return false;

        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() >= 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        caster->CastSpell(target, SPELL_PALADIN_JUDGEMENT_DAMAGE, TRIGGERED_FULL_MASK);

        if (Aura* bonus4 = caster->GetAura(SPELL_SET_T1_PALADIN_RET_4PC))
        {
            if (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HAMMER_OF_WRATH)
            {
                int32 damage = eventInfo.GetDamageInfo()->GetDamage();
                int32 amount = CalculatePct(damage, aurEff->GetAmount());
                int32 additionalTargets = bonus4->GetEffect(EFFECT_1)->GetAmount();

                auto const& threatList = caster->getAttackers();
                auto threatListCopy = threatList;

                if (threatListCopy.empty()) return;

                for (auto const& treathTarget : threatListCopy)
                {
                    if (treathTarget->IsAlive())
                    {
                        if (treathTarget == target)
                            continue;

                        float distance = treathTarget->GetDistance(target->GetPosition());

                        if (distance > 12)
                            continue;

                        caster->CastCustomSpell(SPELL_SET_T1_PALADIN_RET_4PC_HAMMER_OF_WRATH, SPELLVALUE_BASE_POINT0, amount, treathTarget, TRIGGERED_FULL_MASK);
                        additionalTargets--;

                        if (additionalTargets <= 0)
                            break;
                    }
                }
            }
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_paladin_ret_T1_B2B4::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_paladin_ret_T1_B2B4::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 96302 - Lawbringer Armor Inquisitor T1 4pc
class spell_set_paladin_inquisitor_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_paladin_inquisitor_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 cooldown = aurEff->GetAmount();

        if (Player* player = caster->ToPlayer())
            player->ModifySpellCooldown(SPELL_PALADIN_DIVINE_ZEAL, -cooldown);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_paladin_inquisitor_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_paladin_inquisitor_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// --------------------------------------------------------------------------- Hunter Sets ---------------------------------------------------------------------------

// 96501 - Giantstalker Armor BM T1 4pc
class spell_set_hunter_beast_mastery_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_hunter_beast_mastery_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 cooldown = aurEff->GetAmount();

        if (Player* player = caster->ToPlayer())
            player->ModifySpellCooldown(SPELL_HUNTER_BESTIAL_WRATH, -cooldown);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_hunter_beast_mastery_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_hunter_beast_mastery_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 96600 - Sharpshooter Armor Marksman T1 2pc
class spell_set_hunter_marksman_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_hunter_marksman_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return false;

        if (caster->HasAura(SPELL_SET_T1_HUNTER_MM_2PC_DEBUFF))
            return false;

        for (size_t i = 500512; i < 500518; i++)
            if (caster->HasAura(i))
            {
                caster->AddAura(96604, caster);
                return true;
            }

        return false;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_hunter_marksman_T1_2pc::CheckProc);
    }
};

// 96600 - Sharpshooter Armor Marksman T1 4pc
class spell_set_hunter_marksman_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_hunter_marksman_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (eventInfo.GetSpellInfo()->PowerType != POWER_FOCUS)
            return;

        int32 spellFocus = eventInfo.GetSpellInfo()->CalcPowerCost(caster, eventInfo.GetSchoolMask());

        if (spellFocus <= 0)
            return;

        int32 focusAccumulated = GetAura()->GetEffect(EFFECT_2)->GetAmount() + spellFocus;
        int32 focusThreshold = aurEff->GetAmount();
        int32 procChance = GetEffect(EFFECT_1)->GetAmount();

        for (focusAccumulated; focusAccumulated > focusThreshold; focusAccumulated -= focusThreshold)
            if (roll_chance_i(procChance))
                caster->AddAura(SPELL_SET_T1_HUNTER_MM_4PC_BUFF, caster);

        GetAura()->GetEffect(EFFECT_2)->SetAmount(focusAccumulated);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_hunter_marksman_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_hunter_marksman_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 96700 - Tracker Armor Survival T1 2pc
class spell_set_hunter_surv_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_hunter_surv_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            Pet* pet = player->GetPet();

            if (!pet || pet->isDead())
                return;

            player->AddAura(SPELL_SET_T1_HUNTER_SURV_2PC_BUFF, pet);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_hunter_surv_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_hunter_surv_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 96702 - Tracker Armor Survival T1 4pc
class spell_set_hunter_surv_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_hunter_surv_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return false;

        if (!eventInfo.GetSpellInfo() || eventInfo.GetSpellInfo()->Id != 80194)
            return false;

        if (Aura* buff = caster->AddAura(SPELL_SET_T1_HUNTER_SURV_4PC_BUFF, caster))
            return true;
        else
            return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_hunter_surv_T1_4pc::CheckProc);
    }
};

// 96803 - Shadowstalker Armor Dark Ranger T1 4pc Buff
class spell_set_hunter_dark_ranger_T1_4pc_buff : public AuraScript
{
    PrepareAuraScript(spell_set_hunter_dark_ranger_T1_4pc_buff);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 cooldown = aurEff->GetAmount();

        if (Player* player = caster->ToPlayer())
        {
            cooldown = CalculatePct(player->GetSpellCooldownDelay(SPELL_HUNTER_TWILIGHT_PIERCER), cooldown);
            player->ModifySpellCooldown(SPELL_HUNTER_TWILIGHT_PIERCER, -cooldown);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_hunter_dark_ranger_T1_4pc_buff::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_hunter_dark_ranger_T1_4pc_buff::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// --------------------------------------------------------------------------- Death Knight Sets ---------------------------------------------------------------------------

// 97000 - Bloodlord Plate Blood T1 2pc
class spell_set_deathknight_blood_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_deathknight_blood_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 duration = aurEff->GetAmount();

        if (Aura* vampiric = caster->GetAura(SPELL_DEATHKNIGHT_VAMPIRIC_BLOOD))
        {
            duration = std::min<int32>(vampiric->GetDuration() + duration, vampiric->GetMaxDuration());
            vampiric->SetDuration(duration);
        }
        else
            if (Aura* vampiric = caster->AddAura(SPELL_DEATHKNIGHT_VAMPIRIC_BLOOD, caster))
                vampiric->SetDuration(duration);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_deathknight_blood_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_deathknight_blood_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 97001 - Bloodlord Plate Blood T1 4pc
class spell_set_deathknight_blood_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_deathknight_blood_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 duration = aurEff->GetAmount();

        if (Aura* strength = caster->GetAura(SPELL_SET_T1_DEATHKNIGHT_BLOOD_4PC_BUFF))
            strength->SetDuration(strength->GetDuration() + duration);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_deathknight_blood_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_deathknight_blood_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 97100 - Frostreaper Plate Frost T1 2pc
class spell_set_deathknight_frost_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_deathknight_frost_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* pillar = caster->GetAura(SPELL_DEATHKNIGHT_PILLAR_OF_FROST))
        {
            if (eventInfo.GetSpellInfo()->PowerType != POWER_RUNIC_POWER)
                return;

            int32 spellRunicPower = eventInfo.GetSpellInfo()->CalcPowerCost(caster, eventInfo.GetSchoolMask());

            if (spellRunicPower <= 0)
                return;

            int32 runicAccumulated = GetAura()->GetEffect(EFFECT_2)->GetAmount() + spellRunicPower;
            int32 runicThreshold = aurEff->GetAmount();
            int32 duration = pillar->GetDuration() + GetEffect(EFFECT_1)->GetAmount();

            for (runicAccumulated; runicAccumulated > runicThreshold; runicAccumulated -= runicThreshold)
                pillar->SetDuration(duration);

            GetAura()->GetEffect(EFFECT_2)->SetAmount(runicAccumulated);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_deathknight_frost_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_deathknight_frost_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 97101 - Frostreaper Plate Frost T1 4pc
class spell_set_deathknight_frost_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_deathknight_frost_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        SpellRuneCostEntry const* src = sSpellRuneCostStore.LookupEntry(eventInfo.GetSpellInfo()->RuneCostID);

        if (!src)
            return;

        uint32 runeCost = src->RuneCost[RUNE_BLOOD];

        if (runeCost <= 0)
            return;

        int32 runicAccumulated = GetAura()->GetEffect(EFFECT_1)->GetAmount() + runeCost;
        int32 runicThreshold = aurEff->GetAmount();

        for (runicAccumulated; runicAccumulated > runicThreshold; runicAccumulated -= runicThreshold)
            caster->CastSpell(caster, SPELL_SET_T1_DEATHKNIGHT_FROST_4PC_BUFF, TRIGGERED_FULL_MASK);

        GetAura()->GetEffect(EFFECT_1)->SetAmount(runicAccumulated);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_deathknight_frost_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_deathknight_frost_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 97202 - Plaguebearer Plate Unholy T1 4pc
class spell_set_deathknight_unholy_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_deathknight_unholy_T1_4pc);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            Pet* pet = player->GetPet();

            if (!pet || pet->isDead())
                return;

            player->AddAura(SPELL_SET_T1_DEATHKNIGHT_UNHOLY_4PC_PETBUFF, pet);
        }
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            Pet* pet = player->GetPet();

            if (!pet || pet->isDead())
                return;

            if (!pet->HasAura(SPELL_SET_T1_DEATHKNIGHT_UNHOLY_4PC_PETBUFF))
                player->AddAura(SPELL_SET_T1_DEATHKNIGHT_UNHOLY_4PC_PETBUFF, pet);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            Pet* pet = player->GetPet();

            if (!pet || pet->isDead())
                return;

            if (pet->HasAura(SPELL_SET_T1_DEATHKNIGHT_UNHOLY_4PC_PETBUFF))
                pet->RemoveAura(SPELL_SET_T1_DEATHKNIGHT_UNHOLY_4PC_PETBUFF);
        }
    }

    void Register()
    {
        OnEffectApply += AuraEffectRemoveFn(spell_set_deathknight_unholy_T1_4pc::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_set_deathknight_unholy_T1_4pc::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(spell_set_deathknight_unholy_T1_4pc::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 97203 - Plaguebearer Plate Unholy T1 4pc proc
class spell_set_deathknight_unholy_T1_4pc_proc : public AuraScript
{
    PrepareAuraScript(spell_set_deathknight_unholy_T1_4pc_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* pet = GetUnitOwner();

        if (!pet || pet->isDead())
            return;

        int32 procChance = aurEff->GetAmount();

        if (pet->HasAura(SPELL_SET_T1_DEATHKNIGHT_UNHOLY_2PC_PETBUFF))
            procChance = GetEffect(EFFECT_1)->GetAmount();

        procChance += badLuckProtection;

        if (!roll_chance_i(procChance))
        {
            badLuckProtection++;
            return;
        }
        caster->AddAura(SPELL_SET_T1_DEATHKNIGHT_UNHOLY_4PC_BUFF, caster);
        badLuckProtection = 0;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_deathknight_unholy_T1_4pc_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_deathknight_unholy_T1_4pc_proc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
private:
    int32 badLuckProtection = 0;
};

// 97302 - Soulbinder Plate Soulweaver T1 4pc
class spell_set_deathknight_soulweaver_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_deathknight_soulweaver_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetHealInfo())
            return false;

        if (!eventInfo.GetSpellInfo() || eventInfo.GetSpellInfo()->Id != SPELL_DEATHKNIGHT_NECROTIC_BLESSING);
        return false;

        Unit* target = eventInfo.GetHealInfo()->GetTarget();

        if (!target || target->isDead())
            return false;

        int32 health = target->GetHealth() - eventInfo.GetHealInfo()->GetHeal();
        int32 healthThreshold = CalculatePct(target->GetMaxHealth(), GetEffect(EFFECT_0)->GetAmount());

        return health <= healthThreshold;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_deathknight_soulweaver_T1_4pc::CheckProc);
    }
};

// --------------------------------------------------------------------------- Druid Sets ---------------------------------------------------------------------------

// 97500 - Elune Raiment Balance T1 2pc
class spell_set_druid_balance_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_druid_balance_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id != SPELL_DRUID_STARFALL_DAMAGE;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_druid_balance_T1_2pc::CheckProc);
    }
};

// 97601 - Malfurion Raiment Feral T1 2pc buff
class spell_set_druid_feral_T1_2pc_buff : public AuraScript
{
    PrepareAuraScript(spell_set_druid_feral_T1_2pc_buff);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        if (Aura* set_4pc = caster->GetAura(SPELL_SET_T1_DRUID_FERAL_4PC))
        {
            int32 damage = eventInfo.GetDamageInfo()->GetDamage();
            int32 amount = CalculatePct(damage, set_4pc->GetEffect(EFFECT_0)->GetAmount());
            caster->CastCustomSpell(SPELL_SET_T1_DRUID_FERAL_4PC_DOT, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_druid_feral_T1_2pc_buff::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_druid_feral_T1_2pc_buff::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 97101 - Ursoc Raiment Guardian T1 2pc
class spell_set_druid_guardian_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_druid_guardian_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* rageofTheSleeper = caster->GetAura(SPELL_DRUID_RAGE_OF_THE_SLEEPER))
        {
            if (eventInfo.GetSpellInfo()->PowerType != POWER_RAGE)
                return;

            int32 spellRage = eventInfo.GetSpellInfo()->CalcPowerCost(caster, eventInfo.GetSchoolMask());

            if (spellRage <= 0)
                return;

            rageAccumulated += spellRage;
            int32 rageThreshold = aurEff->GetAmount();
            int32 attackPower = CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), GetEffect(EFFECT_1)->GetAmount());
            int32 currentMaxShield = GetEffect(EFFECT_2)->GetAmount();

            for (rageAccumulated; rageAccumulated > rageThreshold; rageAccumulated -= rageThreshold)
                currentMaxShield += attackPower;

            GetAura()->GetEffect(EFFECT_2)->SetAmount(currentMaxShield);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_druid_guardian_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_druid_guardian_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
private:
    int32 rageAccumulated = 0;
};

// 97701 - Ursoc Raiment Guardian T1 2pc Shield
class spell_set_druid_guardian_T1_2pc_shield : public AuraScript
{
    PrepareAuraScript(spell_set_druid_guardian_T1_2pc_shield);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        // Set absorbtion amount to unlimited
        amount = -1;
    }

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = dmgInfo.GetAttacker();

        if (!target || target->isDead())
            return;

        if (Aura* set2pc = caster->GetAura(SPELL_SET_T1_DRUID_GUARDIAN_2PC))
        {
            int32 absorbPct = GetEffect(EFFECT_1)->GetAmount();
            int32 absorb = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            int32 maxShield = set2pc->GetEffect(EFFECT_2)->GetAmount();

            if (maxShield <= absorb)
            {
                absorbAmount = maxShield;
                set2pc->GetEffect(EFFECT_2)->SetAmount(0);
                SetDuration(10);
            }
            else
            {
                absorbAmount = absorb;
                maxShield -= absorb;
                set2pc->GetEffect(EFFECT_2)->SetAmount(maxShield);
            }

            if (GetSpellInfo()->Id == SPELL_SET_T1_DRUID_GUARDIAN_4PC_SHIELD)
            {
                int32 amount = CalculatePct(absorbAmount, GetEffect(EFFECT_2)->GetAmount());
                caster->CastCustomSpell(SPELL_SET_T1_DRUID_GUARDIAN_4PC_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
            }

        }
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_set_druid_guardian_T1_2pc_shield::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_set_druid_guardian_T1_2pc_shield::Absorb, EFFECT_0);
    }
};

// 97702 - Ursoc Raiment Guardian T1 4pc
class spell_set_druid_guardian_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_druid_guardian_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* rageofTheSleeper = caster->GetAura(SPELL_DRUID_RAGE_OF_THE_SLEEPER))
        {
            if (eventInfo.GetSpellInfo()->PowerType != POWER_RAGE)
                return;

            int32 spellRage = eventInfo.GetSpellInfo()->CalcPowerCost(caster, eventInfo.GetSchoolMask());

            if (spellRage <= 0)
                return;

            int32 rageAccumulated = GetAura()->GetEffect(EFFECT_2)->GetAmount() + spellRage;
            int32 rageThreshold = aurEff->GetAmount();
            int32 duration = rageofTheSleeper->GetDuration() + GetEffect(EFFECT_1)->GetAmount();

            for (rageAccumulated; rageAccumulated > rageThreshold; rageAccumulated -= rageThreshold)
                rageofTheSleeper->SetDuration(duration);

            GetAura()->GetEffect(EFFECT_2)->SetAmount(rageAccumulated);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_druid_guardian_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_druid_guardian_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 97801 - Cenarion Raiment Resto T1 Bonus 4
class spell_set_druid_restoration_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_druid_restoration_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;
        int32 cooldown = aurEff->GetAmount();

        if (spellID == SPELL_DRUID_EFFLORESCENCE_HEAL)
            caster->CastSpell(caster, SPELL_SET_T1_DRUID_RESTORATION_4PC_BUFF, TRIGGERED_FULL_MASK);

        if (spellID == SPELL_DRUID_LIFEBLOOM || spellID == SPELL_DRUID_LIFEBLOOM_EXPIRE)
            if (Player* player = caster->ToPlayer())
                player->ModifySpellCooldown(SPELL_DRUID_NATURES_SWIFTNESS, -cooldown);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_druid_restoration_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_druid_restoration_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// --------------------------------------------------------------------------- Warlock Sets ---------------------------------------------------------------------------

// 98001 - Cursed Raiment Affli T1 Bonus 4
class spell_set_warlock_affliction_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_warlock_affliction_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 stacks = aurEff->GetAmount();

        caster->CastCustomSpell(SPELL_SET_T1_WARLOCK_AFFLI_4PC_LISTENER, SPELLVALUE_AURA_STACK, stacks, caster, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_warlock_affliction_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_warlock_affliction_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 98003 - Cursed Raiment Affli T1 Bonus 4
class spell_set_warlock_affliction_T1_4pc_visual : public AuraScript
{
    PrepareAuraScript(spell_set_warlock_affliction_T1_4pc_visual);

    void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        caster->AddAura(SPELL_SET_T1_WARLOCK_AFFLI_4PC_BUFF, caster);
    }

    void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(SPELL_SET_T1_WARLOCK_AFFLI_4PC_BUFF))
            caster->RemoveAura(SPELL_SET_T1_WARLOCK_AFFLI_4PC_BUFF);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_set_warlock_affliction_T1_4pc_visual::ApplyEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_set_warlock_affliction_T1_4pc_visual::RemoveEffect, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 98203 - Chaotic Raiment Destru T1 Bonus 4
class spell_set_warlock_destruction_T1_4pc_proc : public AuraScript
{
    PrepareAuraScript(spell_set_warlock_destruction_T1_4pc_proc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        int32 amount = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());
        amount /= 4;
        caster->CastCustomSpell(SPELL_SET_T1_WARLOCK_DESTRU_4PC_DOT, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_warlock_destruction_T1_4pc_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_warlock_destruction_T1_4pc_proc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 98300 - Felheart Raiment Demonbound T1 2pc
class spell_set_warlock_demonbound_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_warlock_demonbound_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return false;;

        if (!eventInfo.GetDamageInfo())
            return false;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return false;

        return target->HasAura(SPELL_WARLOCK_FIERY_SYMBOL);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_warlock_demonbound_T1_2pc::CheckProc);
    }
};

// 98302 - Felheart Raiment Demonbound T1 4pc
class spell_set_warlock_demonbound_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_warlock_demonbound_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            if (eventInfo.GetSpellInfo()->PowerType != POWER_ENERGY)
                return;

            int32 spellSoulPower = eventInfo.GetSpellInfo()->CalcPowerCost(caster, eventInfo.GetSchoolMask());

            if (spellSoulPower <= 0)
                return;
            soulPowerAccumulated += spellSoulPower;
            int32 soulPowerThreshold = aurEff->GetAmount();
            int32 cooldown = GetEffect(EFFECT_1)->GetAmount();
            for (soulPowerAccumulated; soulPowerAccumulated > soulPowerThreshold; soulPowerAccumulated -= soulPowerThreshold)
                player->ModifySpellCooldown(SPELL_WARLOCK_FIERY_SYMBOL, -cooldown);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_warlock_demonbound_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_warlock_demonbound_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
private:
    int32 soulPowerAccumulated = 0;
};

// --------------------------------------------------------------------------- Priest Sets ---------------------------------------------------------------------------

// 98501 - Vestments of Strictness Discipline T1 4pc
class spell_set_priest_discipline_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_priest_discipline_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id != SPELL_PRIEST_ATONEMENT_HEAL;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_priest_discipline_T1_4pc::CheckProc);
    }
};

// 98600 - Vestments of Light Holy T1 2pc
class spell_set_priest_holy_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_priest_holy_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetHealInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetHealInfo()->GetTarget();

        if (!target || target->isDead())
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;

        if (spellID == SPELL_PRIEST_HOLY_WORD_SANCTIFY)
        {
            int32 duration = aurEff->GetAmount();
            caster->CastCustomSpell(SPELL_PRIEST_RENEW, SPELLVALUE_AURA_DURATION, duration, target, TRIGGERED_FULL_MASK);
        }

        if (spellID == SPELL_PRIEST_HOLY_WORD_SERENITY)
            caster->CastSpell(target, SPELL_PRIEST_RENEW, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_priest_holy_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_priest_holy_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 98801 - Vestments of Prophecy Absolution T1 4pc
class spell_set_priest_absolution_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_priest_absolution_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_PRIEST_PRESCIENCE;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_priest_absolution_T1_4pc::CheckProc);
    }
};

// --------------------------------------------------------------------------- Shaman Sets ---------------------------------------------------------------------------

// 99003 - The Firerage Elemental T1 4pc
class spell_set_shaman_elemental_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_shaman_elemental_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        return eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_EARTH_SHOCK
            || eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_EARTHQUAKE
            || eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_ELEMENTAL_BLAST;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_shaman_elemental_T1_4pc::CheckProc);
    }
};

// 99200 - The Tidalsurge Restoration T1 2pc
class spell_set_shaman_restoration_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_shaman_restoration_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetHealInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetHealInfo()->GetTarget();

        if (!target || target->isDead())
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;

        if (spellID == SPELL_SHAMAN_HEALING_SURGE || spellID == SPELL_SHAMAN_HEALING_WAVE)
        {
            caster->CastSpell(target, SPELL_SET_T1_SHAMAN_RESTORATION_2PC_BUFF, TRIGGERED_FULL_MASK);
            return;
        }

        if (spellID != SPELL_SHAMAN_RIPTIDE || eventInfo.GetHealInfo()->GetHeal() <= 0)
            return;

        if (Player* player = caster->ToPlayer())
        {
            int32 amount = CalculatePct(eventInfo.GetHealInfo()->GetHeal(), aurEff->GetAmount());

            if (player->HasAura(SPELL_SET_T1_SHAMAN_RESTORATION_2PC_BUFF))
                caster->CastCustomSpell(SPELL_SET_T1_SHAMAN_RESTORATION_2PC_HEAL, SPELLVALUE_BASE_POINT0, amount, player, TRIGGERED_FULL_MASK);

            if (Group* playerGroup = player->GetGroup())
            {
                Position casterPos = target->GetPosition();
                auto const& allyList = playerGroup->GetMemberSlots();

                for (auto const& target : allyList)
                {
                    Player* ally = ObjectAccessor::FindPlayer(target.guid);
                    if (ally && ally->IsAlive())
                    {
                        float distance = ally->GetDistance(casterPos);

                        if (distance <= 60 && ally->HasAura(SPELL_SET_T1_SHAMAN_RESTORATION_2PC_BUFF))
                            caster->CastCustomSpell(SPELL_SET_T1_SHAMAN_RESTORATION_2PC_HEAL, SPELLVALUE_BASE_POINT0, amount, ally, TRIGGERED_FULL_MASK);
                    }
                }
            }
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_shaman_restoration_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_shaman_restoration_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 99202 - The Tidalsurge Restoration T1 4pc
class spell_set_shaman_restoration_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_shaman_restoration_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetHealInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetHealInfo()->GetTarget();

        if (!target || target->isDead())
            return;

        if (!target->HasAura(SPELL_SET_T1_SHAMAN_RESTORATION_2PC_BUFF))
            return;

        if (!roll_chance_i(aurEff->GetAmount()))
            return;

        if (Player* player = caster->ToPlayer())
        {
            int32 amount = CalculatePct(eventInfo.GetHealInfo()->GetHeal(), aurEff->GetAmount());

            if (Group* playerGroup = player->GetGroup())
            {
                std::list <Unit*> targetAvailable;
                Position casterPos = target->GetPosition();
                auto const& allyList = playerGroup->GetMemberSlots();

                for (auto const& target : allyList)
                {
                    Player* ally = ObjectAccessor::FindPlayer(target.guid);
                    if (ally && ally->IsAlive())
                    {
                        float distance = ally->GetDistance(casterPos);

                        if (distance <= 40)
                            targetAvailable.push_back(ally);
                    }
                }

                targetAvailable.sort(Acore::HealthPctOrderPred());

                for (auto const& riptTarget : targetAvailable)
                {
                    if (!riptTarget || riptTarget->isDead())
                        continue;

                    caster->AddAura(SPELL_SHAMAN_RIPTIDE, riptTarget);
                    break;
                }
            }
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_set_shaman_restoration_T1_4pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_shaman_restoration_T1_4pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// --------------------------------------------------------------------------- Rogue Sets ---------------------------------------------------------------------------

// 99600 - Bladeslayer Armor Combat T1 2pc
class spell_set_rogue_combat_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_rogue_combat_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
            player->RemoveSpellCooldown(SPELL_ROGUE_RIPOSTE, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_rogue_combat_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_rogue_combat_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 99700 - Nightslayer Armor Sublety T1 2pc
class spell_set_rogue_sublety_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_rogue_sublety_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 stacks = caster->GetComboPoints();
        caster->CastCustomSpell(SPELL_SET_T1_ROGUE_SUB_2PC_BUFF, SPELLVALUE_AURA_STACK, stacks, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_rogue_sublety_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_rogue_sublety_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 99800 - Crewslayer Armor Outlaw T1 2pc
class spell_set_rogue_outlaw_T1_2pc : public AuraScript
{
    PrepareAuraScript(spell_set_rogue_outlaw_T1_2pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 stacks = caster->GetComboPoints();
        caster->CastCustomSpell(SPELL_SET_T1_ROGUE_OUTLAW_2PC_BUFF, SPELLVALUE_AURA_STACK, stacks, caster, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_rogue_outlaw_T1_2pc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_set_rogue_outlaw_T1_2pc::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 99800 - Crewslayer Armor Outlaw T1 4pc
class spell_set_rogue_outlaw_T1_4pc : public AuraScript
{
    PrepareAuraScript(spell_set_rogue_outlaw_T1_4pc);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return false;

        return caster->HasAura(SPELL_ROGUE_OPPORTUNITY_BUFF);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_set_rogue_outlaw_T1_4pc::CheckProc);
    }
};



void AddSC_item_set_bonus_scripts()
{
    RegisterSpellScript(spell_set_prisoners_shackle);
    RegisterSpellScript(spell_set_vestments_of_the_devout);
    RegisterSpellScript(spell_set_volcanic_armor);
    RegisterSpellScript(spell_set_green_dragon_mail);
    RegisterSpellScript(spell_set_regalia_of_undead_cleansing);
    RegisterSpellScript(spell_set_staff_intellect);
    RegisterSpellScript(spell_set_shield_intellect);
    RegisterSpellScript(spell_set_shard_of_the_god);
    
    RegisterSpellScript(spell_set_warrior_fury_T1_B2);
    RegisterSpellScript(spell_set_warrior_fury_T1_B2_visual);
    RegisterSpellScript(spell_set_warrior_fury_T1_B4);
    RegisterSpellScript(spell_set_warrior_prot_T1_B2);
    RegisterSpellScript(spell_set_warrior_hoplite_T1_B4);

    RegisterSpellScript(spell_set_mage_arcane_T1_4pc);
    RegisterSpellScript(spell_set_mage_arcane_T1_4pc_target);
    RegisterSpellScript(spell_set_mage_frost_T1_2pc);
    RegisterSpellScript(spell_set_mage_frost_T1_2pc_target);
    RegisterSpellScript(spell_set_mage_spellblade_T1_2pc);

    RegisterSpellScript(spell_set_paladin_prot_T1_B2);
    RegisterSpellScript(spell_set_paladin_prot_T1_B4);
    RegisterSpellScript(spell_set_paladin_ret_T1_B2B4);
    RegisterSpellScript(spell_set_paladin_inquisitor_T1_4pc);

    RegisterSpellScript(spell_set_hunter_beast_mastery_T1_4pc);
    RegisterSpellScript(spell_set_hunter_marksman_T1_2pc);
    RegisterSpellScript(spell_set_hunter_marksman_T1_4pc);
    RegisterSpellScript(spell_set_hunter_surv_T1_2pc);
    RegisterSpellScript(spell_set_hunter_surv_T1_4pc);
    RegisterSpellScript(spell_set_hunter_dark_ranger_T1_4pc_buff);

    RegisterSpellScript(spell_set_deathknight_blood_T1_2pc);
    RegisterSpellScript(spell_set_deathknight_blood_T1_4pc);
    RegisterSpellScript(spell_set_deathknight_frost_T1_2pc);
    RegisterSpellScript(spell_set_deathknight_frost_T1_4pc);
    RegisterSpellScript(spell_set_deathknight_unholy_T1_4pc);
    RegisterSpellScript(spell_set_deathknight_unholy_T1_4pc_proc);
    RegisterSpellScript(spell_set_deathknight_soulweaver_T1_4pc);

    RegisterSpellScript(spell_set_druid_balance_T1_2pc);
    RegisterSpellScript(spell_set_druid_feral_T1_2pc_buff);
    RegisterSpellScript(spell_set_druid_guardian_T1_2pc);
    RegisterSpellScript(spell_set_druid_guardian_T1_2pc_shield);
    RegisterSpellScript(spell_set_druid_guardian_T1_4pc);
    RegisterSpellScript(spell_set_druid_restoration_T1_4pc);

    RegisterSpellScript(spell_set_warlock_affliction_T1_4pc);
    RegisterSpellScript(spell_set_warlock_affliction_T1_4pc_visual);
    RegisterSpellScript(spell_set_warlock_destruction_T1_4pc_proc);
    RegisterSpellScript(spell_set_warlock_demonbound_T1_2pc);
    RegisterSpellScript(spell_set_warlock_demonbound_T1_4pc);

    RegisterSpellScript(spell_set_priest_discipline_T1_4pc);
    RegisterSpellScript(spell_set_priest_holy_T1_2pc);
    RegisterSpellScript(spell_set_priest_absolution_T1_4pc);
    
    RegisterSpellScript(spell_set_shaman_elemental_T1_4pc);
    RegisterSpellScript(spell_set_shaman_restoration_T1_2pc);
    RegisterSpellScript(spell_set_shaman_restoration_T1_4pc);

    RegisterSpellScript(spell_set_rogue_combat_T1_2pc);
    RegisterSpellScript(spell_set_rogue_sublety_T1_2pc);
    RegisterSpellScript(spell_set_rogue_outlaw_T1_2pc);
    RegisterSpellScript(spell_set_rogue_outlaw_T1_4pc);



    

}
