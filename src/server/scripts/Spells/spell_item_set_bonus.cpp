#include "PetDefines.h"
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
    SPELL_SET_GENERAL_VOLCANIC_ARMOR_DAMAGE = 9057,
    SPELL_SET_GENERAL_VESTMENTS_OF_THE_DEVOUT_SHIELD = 27779,

};

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



void AddSC_item_set_bonus_scripts()
{
    RegisterSpellScript(spell_set_prisoners_shackle);
    RegisterSpellScript(spell_set_vestments_of_the_devout);
    RegisterSpellScript(spell_set_volcanic_armor);
    RegisterSpellScript(spell_set_green_dragon_mail);
    RegisterSpellScript(spell_set_regalia_of_undead_cleansing);





}
