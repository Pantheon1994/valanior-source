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
  * Scripts for spells with SPELLFAMILY_HUNTER, SPELLFAMILY_PET and SPELLFAMILY_GENERIC spells used by hunter players.
  * Ordered alphabetically using scriptname.
  * Scriptnames of files in this file should be prefixed with "spell_hun_".
  */

#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "Pet.h"
#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "Player.h"
#include <random>
#include "PetDefines.h"

  // TODO: this import is not necessary for compilation and marked as unused by the IDE
  //  however, for some reasons removing it would cause a damn linking issue
  //  there is probably some underlying problem with imports which should properly addressed
  //  see: https://github.com/azerothcore/azerothcore-wotlk/issues/9766
#include "GridNotifiersImpl.h"

enum HunterSpells
{
    // Theirs
    SPELL_HUNTER_ASPECT_OF_THE_BEAST = 49071,
    SPELL_HUNTER_ASPECT_OF_THE_BEAST_PET = 61669,
    SPELL_HUNTER_ASPECT_OF_THE_VIPER = 34074,
    SPELL_HUNTER_ASPECT_OF_THE_VIPER_ENERGIZE = 34075,
    SPELL_HUNTER_BESTIAL_WRATH = 19574,
    SPELL_HUNTER_CHIMERA_SHOT_SERPENT = 53353,
    SPELL_HUNTER_CHIMERA_SHOT_VIPER = 53358,
    SPELL_HUNTER_CHIMERA_SHOT_SCORPID = 53359,
    SPELL_HUNTER_GLYPH_OF_ASPECT_OF_THE_VIPER = 56851,
    SPELL_HUNTER_IMPROVED_MEND_PET = 24406,
    SPELL_HUNTER_INVIGORATION_TRIGGERED = 53398,
    SPELL_HUNTER_MASTERS_CALL_TRIGGERED = 62305,
    SPELL_HUNTER_MISDIRECTION_PROC = 35079,
    SPELL_HUNTER_PET_LAST_STAND_TRIGGERED = 53479,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX = 55709,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED = 54114,
    SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF = 55711,
    SPELL_HUNTER_PET_CARRION_FEEDER_TRIGGERED = 54045,
    SPELL_HUNTER_READINESS = 23989,
    SPELL_HUNTER_SNIPER_TRAINING_R1 = 53302,
    SPELL_HUNTER_SNIPER_TRAINING_BUFF_R1 = 64418,

    // Ours
    SPELL_HUNTER_CRESCENT_VEIL = 85009,
    SPELL_HUNTER_WYVERN_STING_DOT = 80156,
    SPELL_HUNTER_WILDFIRE_BOMB = 80188,
    SPELL_HUNTER_KILL_SHOT = 61006,
    SPELL_HUNTER_BESTIAL_WRATH_DAMAGE = 80229,
    SPELL_HUNTER_BESTIAL_WRATH_BUFF = 80132,
    SPELL_HUNTER_SPEARHEAD = 80206,
    SPELL_HUNTER_VICIOUS_VIPER = 61609,
    SPELL_HUNTER_VIPER_ATTACK_SPEED = 60144,
    SPELL_DRAENEI_GIFT_OF_THE_NAARU = 59543,
    SPELL_HUNTER_GLYPH_OF_ARCANE_SHOT = 61389,
    SPELL_LOCK_AND_LOAD_TRIGGER = 56453,
    SPELL_LOCK_AND_LOAD_MARKER = 67544,
    SPELL_HUNTER_MONGOOSE_FURY = 80144,
    SPELL_HUNTER_ANIMAL_COMPANION_TALENT = 80223,
    SPELL_HUNTER_ANIMAL_COMPANION = 80224,
    SPELL_HUNTER_KILL_COMMAND = 80141,
    SPELL_HUNTER_KILL_COMMAND_DAMAGE = 80142,
    SPELL_HUNTER_STAMPEDED_DAMAGE = 80166,
    SPELL_HUNTER_FURY_OF_THE_EAGLE = 80194,
    SPELL_HUNTER_TALENT_TIP_OF_SPEAR = 80232,
    SPELL_HUNTER_TALENT_TIP_OF_SPEAR_BUFF = 80233,
    SPELL_HUNTER_BACKSHOT = 85001,
    SPELL_HUNTER_WITHERING_FIRE = 85002,
    SPELL_HUNTER_WITHERING_FIRE_DAMAGE = 85003,
    SPELL_HUNTER_BLACK_CURSE = 85004,
    SPELL_HUNTER_BLACK_CURSE_HEAL = 85005,
    SPELL_HUNTER_TWILIGHT_PIERCER_STUN = 85007,
    SPELL_HUNTER_INVIS_ACTIVATOR = 85008,
    SPELL_HUNTER_CAMOUFLAGE = 80163,
    SPELL_HUNTER_BLEND = 85012,
    SPELL_HUNTER_SHADOW_SHOT = 85016,
    SPELL_VISUAL_TELEPORT_EFFECT = 82017,
    SPELL_HUNTER_INSTANT_DISMISS_PET = 85018,
    SPELL_HUNTER_BEAST_LORE = 1462,
    SPELL_HUNTER_CALL_PET = 883,
    SPELL_HUNTER_CALL_STABLED_PET = 62757,
    SPELL_HUNTER_DISMISS_PET = 2641,
    SPELL_HUNTER_FEED_PET = 6991,
    SPELL_HUNTER_MEND_PET = 48990,
    SPELL_HUNTER_REVIVE_PET = 982,
    SPELL_HUNTER_TAME_BEAST = 1515,
    SPELL_HUNTER_ARCANE_SHOT = 49045,
    SPELL_HUNTER_SPECTRAL_SHOT = 85019,
    SPELL_HUNTER_EVANESCENCE = 85020,
    SPELL_HUNTER_COBRA_SHOT = 80171,
    SPELL_HUNTER_LONE_WOLF_BUFF = 80182,
    SPELL_HUNTER_ASPECT_OF_THE_EAGLE = 80159,
    SPELL_HUNTER_DEATH_CHAKRAM = 80167,
    SPELL_HUNTER_COORDINATED_ASSAULT_BLEED = 80201,
    SPELL_HUNTER_COORDINATED_ASSAULT_BUFF = 80202,
    SPELL_HUNTER_COORDINATED_ASSAULT_PET_DAMAGE = 80203,
    SPELL_HUNTER_SPEARHEAD_PET_DAMAGE = 80207,
    SPELL_HUNTER_SPEARHEAD_BUFF = 80208,
    SPELL_HUNTER_FLANKING_STRIKE_PET_DAMAGE = 80198,
    SPELL_HUNTER_TWILIGHT_PIERCER = 85006,
    SPELL_HUNTER_ASPECT_OF_THE_BEAST_BUFF = 80247,

    // Talents
    TALENT_HUNTER_SHADOW_CLOAK = 85034,
    TALENT_HUNTER_SHADOW_CLOAK_BUFF = 85037,
    TALENT_HUNTER_IMPROVED_BLEND_PROC = 85053,
    TALENT_HUNTER_BRING_ME_TO_LIFE_PROC = 85086,
    TALENT_HUNTER_BRING_ME_TO_LIFE_COOLDOWN = 85087,
    TALENT_HUNTER_IMPROVED_BLACK_CURSE_HEAL = 85108,
    TALENT_HUNTER_CALCULATED_SHOT = 80231,
    TALENT_HUNTER_CAREFUL_AIM_DAMAGE = 80228,

    // Runes
    RUNE_HUNTER_EVASIVE_MANEUVERS_SHIELD = 501732,

    // Sets
    T1_HUNTER_SURVIVAL_4PC_BUFF = 96704,
    T1_HUNTER_DARKRANGER_2PC_BUFF = 96801,
    T1_HUNTER_DARKRANGER_4PC = 96802,
    T1_HUNTER_DARKRANGER_4PC_BUFF = 96803,
};

class spell_hun_check_pet_los : public SpellScript
{
    PrepareSpellScript(spell_hun_check_pet_los);

    SpellCastResult CheckCast()
    {
        Unit* pet = GetCaster()->GetGuardianPet();
        if (!pet)
            pet = GetCaster()->GetCharm();

        if (!pet)
            return SPELL_FAILED_NO_PET;

        if (!pet->IsAlive())
        {
            SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_PET_IS_DEAD);
            return SPELL_FAILED_CUSTOM_ERROR;
        }

        if (!GetCaster()->IsWithinLOSInMap(pet))
            return SPELL_FAILED_LINE_OF_SIGHT;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_hun_check_pet_los::CheckCast);
    }
};

class spell_hun_cower : public AuraScript
{
    PrepareAuraScript(spell_hun_cower);

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (AuraEffect* aurEff = GetUnitOwner()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_PET, GetSpellInfo()->SpellIconID, EFFECT_0))
            AddPct(amount, aurEff->GetAmount());
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_cower::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_DECREASE_SPEED);
    }
};

class spell_hun_wyvern_sting : public AuraScript
{
    PrepareAuraScript(spell_hun_wyvern_sting)

        void HandleEffectRemove(AuraEffect const*  /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->CastSpell(GetTarget(), SPELL_HUNTER_WYVERN_STING_DOT, true);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_wyvern_sting::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_animal_handler : public AuraScript
{
    PrepareAuraScript(spell_hun_animal_handler);

    void CalculateAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        amount = 0;
        if (Unit* owner = GetUnitOwner()->GetOwner())
            if (AuraEffect const* animalHandlerEff = owner->GetDummyAuraEffect(SPELLFAMILY_HUNTER, 2234, EFFECT_1))
                amount = animalHandlerEff->GetAmount();
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_animal_handler::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_ATTACK_POWER_PCT);
    }
};

class spell_hun_generic_scaling : public AuraScript
{
    PrepareAuraScript(spell_hun_generic_scaling);

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
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            // xinef: by default pet inherits 45% of stamina
            int32 modifier = 45;

            // xinef: Wild Hunt bonus for stamina
            if (AuraEffect* wildHuntEff = GetUnitOwner()->GetDummyAuraEffect(SPELLFAMILY_PET, 3748, EFFECT_0))
                AddPct(modifier, wildHuntEff->GetAmount());

            amount = CalculatePct(std::max<int32>(0, owner->GetStat(Stats(aurEff->GetSpellInfo()->Effects[aurEff->GetEffIndex()].MiscValue))), modifier);
        }
    }

    void CalculateAPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            // xinef: by default 22% of RAP
            int32 modifier = 22;

            // xinef: Wild Hunt bonus for AP
            if (AuraEffect* wildHuntEff = GetUnitOwner()->GetDummyAuraEffect(SPELLFAMILY_PET, 3748, EFFECT_1))
                AddPct(modifier, wildHuntEff->GetAmount());

            float ownerAP = owner->GetTotalAttackPowerValue(RANGED_ATTACK);

            // Xinef: Hunter vs. Wild
            if (AuraEffect* HvWEff = owner->GetAuraEffect(SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT, SPELLFAMILY_HUNTER, 3647, EFFECT_0))
                ownerAP += CalculatePct(owner->GetStat(STAT_STAMINA), HvWEff->GetAmount());

            amount = CalculatePct(std::max<int32>(0, ownerAP), modifier);
        }
    }

    void CalculateSPAmount(AuraEffect const*  /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
    {
        if (Unit* owner = GetUnitOwner()->GetOwner())
        {
            // xinef: by default 12.87% of RAP
            float modifier = 12.87f;

            // xinef: Wild Hunt bonus for AP
            if (AuraEffect* wildHuntEff = GetUnitOwner()->GetDummyAuraEffect(SPELLFAMILY_PET, 3748, EFFECT_1))
                AddPct(modifier, wildHuntEff->GetAmount());

            amount = CalculatePct(std::max<int32>(0, owner->GetTotalAttackPowerValue(RANGED_ATTACK)), modifier);

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
        if (aurEff->GetAuraType() == SPELL_AURA_MOD_STAT && (aurEff->GetMiscValue() == STAT_STAMINA || aurEff->GetMiscValue() == STAT_INTELLECT))
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
        if (m_scriptSpellId != 34902)
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_generic_scaling::CalculateResistanceAmount, EFFECT_ALL, SPELL_AURA_MOD_RESISTANCE);
        else
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_generic_scaling::CalculateStatAmount, EFFECT_ALL, SPELL_AURA_MOD_STAT);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_generic_scaling::CalculateAPAmount, EFFECT_ALL, SPELL_AURA_MOD_ATTACK_POWER);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_hun_generic_scaling::CalculateSPAmount, EFFECT_ALL, SPELL_AURA_MOD_DAMAGE_DONE);
        }

        DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_hun_generic_scaling::CalcPeriodic, EFFECT_ALL, SPELL_AURA_ANY);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hun_generic_scaling::HandlePeriodic, EFFECT_ALL, SPELL_AURA_ANY);
    }
};

// Taming the Beast quests (despawn creature after dismiss)
class spell_hun_taming_the_beast : public AuraScript
{
    PrepareAuraScript(spell_hun_taming_the_beast);

    void HandleOnEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
        {
            if (Creature* creature = target->ToCreature())
            {
                creature->GetThreatMgr().ClearAllThreat();
            }
        }
    }

    void HandleOnEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
            if (Creature* creature = target->ToCreature())
                creature->DespawnOrUnsummon(1);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_taming_the_beast::HandleOnEffectApply, EFFECT_0, SPELL_AURA_MOD_CHARM, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_taming_the_beast::HandleOnEffectRemove, EFFECT_0, SPELL_AURA_MOD_CHARM, AURA_EFFECT_HANDLE_REAL);
    }
};

// 13161 Aspect of the Beast
class spell_hun_aspect_of_the_beast : public AuraScript
{
    PrepareAuraScript(spell_hun_aspect_of_the_beast);

    bool Load() override
    {
        return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_ASPECT_OF_THE_BEAST_PET });
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
            if (Player* caster = GetCaster()->ToPlayer())
                if (Pet* pet = caster->GetPet())
                    pet->RemoveAurasDueToSpell(SPELL_HUNTER_ASPECT_OF_THE_BEAST_PET);
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
            if (Player* caster = GetCaster()->ToPlayer())
                if (caster->GetPet())
                    caster->CastSpell(caster, SPELL_HUNTER_ASPECT_OF_THE_BEAST_PET, true);
    }

    void OnPetApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* pet = GetUnitOwner();
        if (Unit* owner = pet->GetOwner())
            if (owner->HasAura(SPELL_HUNTER_ASPECT_OF_THE_BEAST))
                return;

        SetDuration(0);
    }

    void Register() override
    {
        if (m_scriptSpellId == 49071)
        {
            AfterEffectApply += AuraEffectApplyFn(spell_hun_aspect_of_the_beast::OnApply, EFFECT_0, SPELL_AURA_UNTRACKABLE, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_hun_aspect_of_the_beast::OnRemove, EFFECT_0, SPELL_AURA_UNTRACKABLE, AURA_EFFECT_HANDLE_REAL);
        }
        else
            AfterEffectApply += AuraEffectApplyFn(spell_hun_aspect_of_the_beast::OnPetApply, EFFECT_0, SPELL_AURA_UNTRACKABLE, AURA_EFFECT_HANDLE_REAL);
    }
};

// 34074 - Aspect of the Viper
class spell_hun_ascpect_of_the_viper : public AuraScript
{
    PrepareAuraScript(spell_hun_ascpect_of_the_viper);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_HUNTER_ASPECT_OF_THE_VIPER_ENERGIZE,
                SPELL_HUNTER_GLYPH_OF_ASPECT_OF_THE_VIPER,
                SPELL_HUNTER_VIPER_ATTACK_SPEED,
                SPELL_HUNTER_VICIOUS_VIPER
            });
    }

    bool CheckProc(ProcEventInfo& procInfo)
    {
        SpellInfo const* spellInfo = procInfo.GetSpellInfo();
        // Xinef: cannot proc from volley damage
        if (spellInfo && (spellInfo->SpellFamilyFlags[0] & 0x2000) && spellInfo->Effects[EFFECT_0].Effect == SPELL_EFFECT_SCHOOL_DAMAGE)
            return false;
        return true;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo&  /*eventInfo*/)
    {
        PreventDefaultAction();

        uint32 maxMana = GetTarget()->GetMaxPower(POWER_MANA);
        int32 mana = CalculatePct(maxMana, GetTarget()->GetAttackTime(RANGED_ATTACK) / 1000.0f);

        if (AuraEffect const* glyph = GetTarget()->GetAuraEffect(SPELL_HUNTER_GLYPH_OF_ASPECT_OF_THE_VIPER, EFFECT_0))
            AddPct(mana, glyph->GetAmount());

        GetTarget()->CastCustomSpell(SPELL_HUNTER_ASPECT_OF_THE_VIPER_ENERGIZE, SPELLVALUE_BASE_POINT0, mana, GetTarget(), true, nullptr, aurEff);
    }

    void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        // Hunter T7 4P Bonus
        if (GetTarget()->HasAura(SPELL_HUNTER_VIPER_ATTACK_SPEED))
            GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_VICIOUS_VIPER, true, nullptr, aurEff);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // Hunter T7 4P Bonus
        if (GetTarget()->HasAura(SPELL_HUNTER_VIPER_ATTACK_SPEED))
            GetTarget()->RemoveAurasDueToSpell(SPELL_HUNTER_VICIOUS_VIPER);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_ascpect_of_the_viper::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hun_ascpect_of_the_viper::HandleProc, EFFECT_2, SPELL_AURA_DUMMY);
        AfterEffectApply += AuraEffectApplyFn(spell_hun_ascpect_of_the_viper::OnApply, EFFECT_0, SPELL_AURA_OBS_MOD_POWER, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_ascpect_of_the_viper::OnRemove, EFFECT_0, SPELL_AURA_OBS_MOD_POWER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 53209 Chimera Shot
class spell_hun_chimera_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_chimera_shot);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_CHIMERA_SHOT_SERPENT, SPELL_HUNTER_CHIMERA_SHOT_VIPER, SPELL_HUNTER_CHIMERA_SHOT_SCORPID });
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (Unit* unitTarget = GetHitUnit())
        {
            uint32 spellId = 0;
            int32 basePoint = 0;
            Unit::AuraApplicationMap& Auras = unitTarget->GetAppliedAuras();
            for (Unit::AuraApplicationMap::iterator i = Auras.begin(); i != Auras.end(); ++i)
            {
                Aura* aura = i->second->GetBase();
                if (aura->GetCasterGUID() != caster->GetGUID())
                    continue;

                // Search only Serpent Sting, Viper Sting, Scorpid Sting auras
                flag96 familyFlag = aura->GetSpellInfo()->SpellFamilyFlags;
                if (!(familyFlag[1] & 0x00000080 || familyFlag[0] & 0x0000C000))
                    continue;
                if (AuraEffect* aurEff = aura->GetEffect(0))
                {
                    // Serpent Sting - Instantly deals 40% of the damage done by your Serpent Sting.
                    // 1 8
                    if (familyFlag[0] & 0x4000)
                    {
                        int32 TickCount = aurEff->GetTotalTicks();
                        spellId = SPELL_HUNTER_CHIMERA_SHOT_SERPENT;
                        basePoint = aurEff->GetAmount();
                        ApplyPct(basePoint, TickCount * 40);
                        basePoint = unitTarget->SpellDamageBonusTaken(caster, aura->GetSpellInfo(), basePoint, DOT, aura->GetStackAmount());
                    }
                    // Viper Sting - Instantly restores mana to you equal to 60% of the total amount drained by your Viper Sting.
                    else if (familyFlag[1] & 0x00000080)
                    {
                        int32 TickCount = aura->GetEffect(0)->GetTotalTicks();
                        spellId = SPELL_HUNTER_CHIMERA_SHOT_VIPER;

                        // Amount of one aura tick
                        basePoint = int32(CalculatePct(unitTarget->GetMaxPower(POWER_MANA), aurEff->GetAmount()));
                        int32 casterBasePoint = aurEff->GetAmount() * unitTarget->GetMaxPower(POWER_MANA) / 50; // TODO: Caster uses unitTarget?
                        if (basePoint > casterBasePoint)
                            basePoint = casterBasePoint;
                        ApplyPct(basePoint, TickCount * 60);
                    }
                    // Scorpid Sting - Attempts to Disarm the target for 10 sec. This effect cannot occur more than once per 1 minute.
                    else if (familyFlag[0] & 0x00008000)
                    {
                        if (caster->ToPlayer()) // Scorpid Sting - Add 1 minute cooldown
                        {
                            if (caster->ToPlayer()->HasSpellCooldown(SPELL_HUNTER_CHIMERA_SHOT_SCORPID))
                                break;

                            caster->ToPlayer()->AddSpellCooldown(SPELL_HUNTER_CHIMERA_SHOT_SCORPID, 0, 60000);
                        }

                        spellId = SPELL_HUNTER_CHIMERA_SHOT_SCORPID;
                    }

                    // Refresh aura duration
                    aura->RefreshDuration();
                    aurEff->ChangeAmount(aurEff->CalculateAmount(caster), false);
                }
                break;
            }

            if (spellId)
                caster->CastCustomSpell(unitTarget, spellId, &basePoint, 0, 0, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_chimera_shot::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// -19572 - Improved Mend Pet
class spell_hun_improved_mend_pet : public AuraScript
{
    PrepareAuraScript(spell_hun_improved_mend_pet);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_IMPROVED_MEND_PET });
    }

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        return roll_chance_i(GetEffect(EFFECT_0)->GetAmount());
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_IMPROVED_MEND_PET, true, nullptr, aurEff);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_improved_mend_pet::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hun_improved_mend_pet::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 53412 - Invigoration
class spell_hun_invigoration : public SpellScript
{
    PrepareSpellScript(spell_hun_invigoration);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_INVIGORATION_TRIGGERED });
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* unitTarget = GetHitUnit())
            if (AuraEffect* aurEff = unitTarget->GetDummyAuraEffect(SPELLFAMILY_HUNTER, 3487, 0))
                if (roll_chance_i(aurEff->GetAmount()))
                    unitTarget->CastSpell(unitTarget, SPELL_HUNTER_INVIGORATION_TRIGGERED, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_invigoration::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 53478 - Last Stand Pet
class spell_hun_last_stand_pet : public SpellScript
{
    PrepareSpellScript(spell_hun_last_stand_pet);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_PET_LAST_STAND_TRIGGERED });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        int32 healthModSpellBasePoints0 = int32(caster->CountPctFromMaxHealth(30));
        caster->CastCustomSpell(caster, SPELL_HUNTER_PET_LAST_STAND_TRIGGERED, &healthModSpellBasePoints0, nullptr, nullptr, true, nullptr);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_last_stand_pet::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 53271 - Masters Call
class spell_hun_masters_call : public SpellScript
{
    PrepareSpellScript(spell_hun_masters_call);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_MASTERS_CALL_TRIGGERED });
    }

    SpellCastResult DoCheckCast()
    {
        Pet* pet = GetCaster()->ToPlayer()->GetPet();
        if (!pet || !pet->IsAlive())
            return SPELL_FAILED_NO_PET;

        // Do a mini Spell::CheckCasterAuras on the pet, no other way of doing this
        SpellCastResult result = SPELL_CAST_OK;
        uint32 const unitflag = pet->GetUnitFlags();
        if (pet->GetCharmerGUID())
            result = SPELL_FAILED_CHARMED;
        else if (unitflag & UNIT_FLAG_STUNNED)
            result = SPELL_FAILED_STUNNED;
        else if (unitflag & UNIT_FLAG_FLEEING)
            result = SPELL_FAILED_FLEEING;
        else if (unitflag & UNIT_FLAG_CONFUSED)
            result = SPELL_FAILED_CONFUSED;

        if (result != SPELL_CAST_OK)
            return result;

        Unit* target = GetExplTargetUnit();
        if (!target)
            return SPELL_FAILED_BAD_TARGETS;

        if (!pet->IsWithinLOSInMap(target))
            return SPELL_FAILED_LINE_OF_SIGHT;

        return SPELL_CAST_OK;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->ToPlayer()->GetPet()->CastSpell(GetHitUnit(), GetEffectValue(), true);
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        GetHitUnit()->CastSpell((Unit*)nullptr, SPELL_HUNTER_MASTERS_CALL_TRIGGERED, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_hun_masters_call::DoCheckCast);

        OnEffectHitTarget += SpellEffectFn(spell_hun_masters_call::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnEffectHitTarget += SpellEffectFn(spell_hun_masters_call::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 23989 - Readiness
class spell_hun_readiness : public SpellScript
{
    PrepareSpellScript(spell_hun_readiness);

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Player* caster = GetCaster()->ToPlayer();
        // immediately finishes the cooldown on your other Hunter abilities except Bestial Wrath

        // force removal of the disarm cooldown
        caster->RemoveSpellCooldown(SPELL_HUNTER_CHIMERA_SHOT_SCORPID);

        SpellCooldowns& cooldowns = caster->GetSpellCooldownMap();

        std::set<std::pair<uint32, bool>> spellsToRemove;
        std::set<uint32> categoriesToRemove;

        for (const auto& [spellId, cooldown] : cooldowns)
        {
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
            if (spellInfo
                && spellInfo->SpellFamilyName == SPELLFAMILY_HUNTER
                && spellInfo->Id != SPELL_HUNTER_READINESS
                && spellInfo->Id != SPELL_HUNTER_BESTIAL_WRATH
                && spellInfo->Id != SPELL_DRAENEI_GIFT_OF_THE_NAARU)
            {
                if (spellInfo->RecoveryTime > 0)
                    spellsToRemove.insert(std::make_pair(spellInfo->Id, cooldown.needSendToClient));

                if (spellInfo->CategoryRecoveryTime > 0)
                    categoriesToRemove.insert(spellInfo->GetCategory());
            }
        }

        // we can't remove spell cooldowns while iterating.
        for (const auto& [spellId, sendToClient] : spellsToRemove)
            caster->RemoveSpellCooldown(spellId, sendToClient);
        for (const auto& category : categoriesToRemove)
            caster->RemoveCategoryCooldown(category);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_readiness::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 37506 - Scatter Shot
class spell_hun_scatter_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_scatter_shot);

    bool Load() override
    {
        return GetCaster()->GetTypeId() == TYPEID_PLAYER;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Player* caster = GetCaster()->ToPlayer();
        // break Auto Shot and autohit
        caster->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
        caster->AttackStop();
        caster->SendAttackSwingCancelAttack();
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_scatter_shot::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// -53302 - Sniper Training
class spell_hun_sniper_training : public AuraScript
{
    PrepareAuraScript(spell_hun_sniper_training);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_SNIPER_TRAINING_R1, SPELL_HUNTER_SNIPER_TRAINING_BUFF_R1 });
    }

    void HandlePeriodic(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (aurEff->GetAmount() <= 0)
        {
            if (!GetCaster() || !GetTarget())
                return;

            Unit* target = GetTarget();

            if (!target || target->isDead())
                return;

            uint32 spellId = SPELL_HUNTER_SNIPER_TRAINING_BUFF_R1 + GetId() - SPELL_HUNTER_SNIPER_TRAINING_R1;
            if (SpellInfo const* triggeredSpellInfo = sSpellMgr->GetSpellInfo(spellId))
            {
                Unit* triggerCaster = triggeredSpellInfo->NeedsToBeTriggeredByCaster(GetSpellInfo()) ? GetCaster() : target;
                triggerCaster->CastSpell(target, triggeredSpellInfo, true, 0, aurEff);
            }
        }
    }

    void HandleUpdatePeriodic(AuraEffect* aurEff)
    {
        if (Player* playerTarget = GetUnitOwner()->ToPlayer())
        {
            int32 baseAmount = aurEff->GetBaseAmount();
            int32 amount = playerTarget->isMoving() || aurEff->GetAmount() <= 0 ?
                playerTarget->CalculateSpellDamage(playerTarget, GetSpellInfo(), aurEff->GetEffIndex(), &baseAmount) :
                aurEff->GetAmount() - 1;
            aurEff->SetAmount(amount);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hun_sniper_training::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_hun_sniper_training::HandleUpdatePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

// 55709 - Pet Heart of the Phoenix
class spell_hun_pet_heart_of_the_phoenix : public SpellScript
{
    PrepareSpellScript(spell_hun_pet_heart_of_the_phoenix);

    bool Load() override
    {
        if (!GetCaster()->IsPet())
            return false;
        return true;
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED, SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF });
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (caster->IsAlive())
            return SPELL_FAILED_TARGET_NOT_DEAD;
        if (caster->HasAura(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF))
            return SPELL_FAILED_CASTER_AURASTATE;
        return SPELL_CAST_OK;
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (Unit* owner = caster->GetOwner())
            if (!caster->HasAura(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF))
            {
                owner->CastCustomSpell(SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_TRIGGERED, SPELLVALUE_BASE_POINT0, 100, caster, true);
                caster->CastSpell(caster, SPELL_HUNTER_PET_HEART_OF_THE_PHOENIX_DEBUFF, true);
            }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_hun_pet_heart_of_the_phoenix::CheckCast);
        OnEffectHitTarget += SpellEffectFn(spell_hun_pet_heart_of_the_phoenix::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

// 54044 - Pet Carrion Feeder
class spell_hun_pet_carrion_feeder : public SpellScript
{
    PrepareSpellScript(spell_hun_pet_carrion_feeder);

    bool Load() override
    {
        if (!GetCaster()->IsPet())
            return false;
        return true;
    }

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_PET_CARRION_FEEDER_TRIGGERED });
    }

    SpellCastResult CheckIfCorpseNear()
    {
        Unit* caster = GetCaster();
        float max_range = GetSpellInfo()->GetMaxRange(false);
        WorldObject* result = nullptr;
        // search for nearby enemy corpse in range
        Acore::AnyDeadUnitSpellTargetInRangeCheck check(caster, max_range, GetSpellInfo(), TARGET_CHECK_ENEMY);
        Acore::WorldObjectSearcher<Acore::AnyDeadUnitSpellTargetInRangeCheck> searcher(caster, result, check);
        Cell::VisitWorldObjects(caster, searcher, max_range);
        if (!result)
        {
            Cell::VisitGridObjects(caster, searcher, max_range);
        }
        if (!result)
        {
            return SPELL_FAILED_NO_EDIBLE_CORPSES;
        }
        return SPELL_CAST_OK;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        caster->CastSpell(caster, SPELL_HUNTER_PET_CARRION_FEEDER_TRIGGERED, false);
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_hun_pet_carrion_feeder::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        OnCheckCast += SpellCheckCastFn(spell_hun_pet_carrion_feeder::CheckIfCorpseNear);
    }
};

// 34477 - Misdirection
class spell_hun_misdirection : public AuraScript
{
    PrepareAuraScript(spell_hun_misdirection);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_MISDIRECTION_PROC });
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEFAULT || !GetTarget()->HasAura(SPELL_HUNTER_MISDIRECTION_PROC))
            GetTarget()->ResetRedirectThreat();
    }

    bool CheckProc(ProcEventInfo& /*eventInfo*/)
    {
        return GetTarget()->GetRedirectThreatTarget();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();
        GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_MISDIRECTION_PROC, true, nullptr, aurEff);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_misdirection::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        DoCheckProc += AuraCheckProcFn(spell_hun_misdirection::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hun_misdirection::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
    }
};

// 35079 - Misdirection (Proc)
class spell_hun_misdirection_proc : public AuraScript
{
    PrepareAuraScript(spell_hun_misdirection_proc);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->ResetRedirectThreat();
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_misdirection_proc::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 781 - Disengage
class spell_hun_disengage : public SpellScript
{
    PrepareSpellScript(spell_hun_disengage);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (caster->GetTypeId() == TYPEID_PLAYER && !caster->IsInCombat())
            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_hun_disengage::CheckCast);
    }
};

// 1515 - Tame Beast
class spell_hun_tame_beast : public SpellScript
{
    PrepareSpellScript(spell_hun_tame_beast);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (caster->GetTypeId() != TYPEID_PLAYER)
            return SPELL_FAILED_DONT_REPORT;

        Player* player = GetCaster()->ToPlayer();

        if (!GetExplTargetUnit())
        {
            player->SendTameFailure(PET_TAME_INVALID_CREATURE);
            return SPELL_FAILED_DONT_REPORT;
        }

        if (Creature* target = GetExplTargetUnit()->ToCreature())
        {
            if (target->getLevel() > player->getLevel())
            {
                player->SendTameFailure(PET_TAME_TOO_HIGHLEVEL);
                return SPELL_FAILED_DONT_REPORT;
            }

            if (target->GetCreatureTemplate()->IsExotic() && !player->CanTameExoticPets())
            {
                player->SendTameFailure(PET_TAME_CANT_CONTROL_EXOTIC);
                return SPELL_FAILED_DONT_REPORT;
            }

            if (!target->GetCreatureTemplate()->IsTameable(player->CanTameExoticPets()))
            {
                player->SendTameFailure(PET_TAME_NOT_TAMEABLE);
                return SPELL_FAILED_DONT_REPORT;
            }

            PetStable const* petStable = player->GetPetStable();
            if (petStable)
            {
                if (petStable->CurrentPet)
                    return SPELL_FAILED_ALREADY_HAVE_SUMMON;

                if (petStable->GetUnslottedHunterPet())
                {
                    caster->SendTameFailure(PET_TAME_TOO_MANY);
                    return SPELL_FAILED_DONT_REPORT;
                }
            }

            if (player->GetCharmGUID())
            {
                player->SendTameFailure(PET_TAME_ANOTHER_SUMMON_ACTIVE);
                return SPELL_FAILED_DONT_REPORT;
            }

            if (target->GetOwnerGUID())
            {
                player->SendTameFailure(PET_TAME_CREATURE_ALREADY_OWNED);
                return SPELL_FAILED_DONT_REPORT;
            }
        }
        else
        {
            player->SendTameFailure(PET_TAME_INVALID_CREATURE);
            return SPELL_FAILED_DONT_REPORT;
        }

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_hun_tame_beast::CheckCast);
    }
};

// 60144 - Viper Attack Speed
class spell_hun_viper_attack_speed : public AuraScript
{
    PrepareAuraScript(spell_hun_viper_attack_speed);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_ASPECT_OF_THE_VIPER, SPELL_HUNTER_VICIOUS_VIPER });
    }

    void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (GetTarget()->HasAura(SPELL_HUNTER_ASPECT_OF_THE_VIPER))
            GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_VICIOUS_VIPER, true, nullptr, aurEff);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        // possible exploit
        GetTarget()->RemoveAurasDueToSpell(SPELL_HUNTER_VICIOUS_VIPER);
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_hun_viper_attack_speed::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_viper_attack_speed::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 56841 - Glyph of Arcane Shot
class spell_hun_glyph_of_arcane_shot : public AuraScript
{
    PrepareAuraScript(spell_hun_glyph_of_arcane_shot);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_HUNTER_GLYPH_OF_ARCANE_SHOT });
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Unit* procTarget = eventInfo.GetProcTarget())
        {
            // Find Serpent Sting, Viper Sting, Scorpid Sting, Wyvern Sting
            const auto found = std::find_if(std::begin(procTarget->GetAppliedAuras()), std::end(procTarget->GetAppliedAuras()),
                [&](std::pair<uint32, AuraApplication*> pair)
                {
                    Aura const* aura = pair.second->GetBase();
            return ((aura->GetCasterGUID() == GetTarget()->GetGUID())
                && aura->GetSpellInfo()->SpellFamilyName == SPELLFAMILY_HUNTER
                && aura->GetSpellInfo()->SpellFamilyFlags.HasFlag(0xC000, 0x1080));
                });

            if (found != std::end(procTarget->GetAppliedAuras()))
            {
                return true;
            }
        }
        return false;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        SpellInfo const* procSpell = eventInfo.GetSpellInfo();
        if (!procSpell)
        {
            return;
        }

        int32 mana = procSpell->CalcPowerCost(GetTarget(), procSpell->GetSchoolMask());
        ApplyPct(mana, aurEff->GetAmount());

        GetTarget()->CastCustomSpell(SPELL_HUNTER_GLYPH_OF_ARCANE_SHOT, SPELLVALUE_BASE_POINT0, mana, GetTarget());
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_glyph_of_arcane_shot::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hun_glyph_of_arcane_shot::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// -42243 - Volley (Trigger one)
class spell_hun_volley_trigger : public SpellScript
{
    PrepareSpellScript(spell_hun_volley_trigger);

    void SelectTarget(std::list<WorldObject*>& targets)
    {
        // It's here because Volley is an AOE spell so there is no specific target to be attacked
        // Let's select one of our targets
        if (!targets.empty())
        {
            _target = *(targets.begin());
        }
    }

    void HandleFinish()
    {
        if (!_target)
        {
            return;
        }

        Unit* caster = GetCaster();
        if (!caster || !caster->IsPlayer())
        {
            return;
        }

        for (Unit::ControlSet::iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
        {
            if (Unit* pet = *itr)
            {
                if (pet->IsAlive() && pet->GetTypeId() == TYPEID_UNIT)
                {
                    pet->ToCreature()->AI()->OwnerAttacked(_target->ToUnit());
                }
            }
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hun_volley_trigger::SelectTarget, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        AfterCast += SpellCastFn(spell_hun_volley_trigger::HandleFinish);
    }

private:
    WorldObject* _target = nullptr;
};

enum LocknLoadSpells
{
    SPELL_FROST_TRAP_SLOW = 67035
};

// -56342 - Lock and Load
class spell_hun_lock_and_load : public AuraScript
{
    PrepareAuraScript(spell_hun_lock_and_load);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo({ SPELL_LOCK_AND_LOAD_TRIGGER, SPELL_LOCK_AND_LOAD_MARKER, SPELL_FROST_TRAP_SLOW });
    }

    bool CheckTrapProc(ProcEventInfo& eventInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return false;

        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
        if (!spellInfo || !eventInfo.GetActor())
        {
            return false;
        }

        // Black Arrow and Fire traps may trigger on periodic tick only.
        if (spellInfo->Effects[0].ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE || spellInfo->Effects[1].ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE)
        {
            return true;
        }

        return IsTargetValid(spellInfo, eventInfo.GetProcTarget()) && !eventInfo.GetActor()->HasAura(SPELL_LOCK_AND_LOAD_MARKER);
    }

    bool IsTargetValid(SpellInfo const* spellInfo, Unit* target)
    {
        if (!spellInfo || !target)
        {
            return false;
        }

        // Don't check it for fire traps and black arrow, they proc on periodic only and not spell hit.
        // So it's wrong to check for immunity, it was already checked when the spell was applied.
        if ((spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_FIRE) || (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_SHADOW) || (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_NATURE || (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_NORMAL)))
        {
            return false;
        }

        // HitMask for Frost Trap can't be checked correctly as it is.
        // That's because the talent is triggered by the spell that fires the trap (63487)...
        // ...and not the actual spell that applies the slow effect (67035).
        // So the IMMUNE result is never sent by the spell that triggers this.
        if (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_NATURE)
        {
            if (SpellInfo const* triggerSpell = sSpellMgr->GetSpellInfo(SPELL_FROST_TRAP_SLOW))
            {
                return !target->IsImmunedToSpell(triggerSpell);
            }
        }

        return true;
    }

    template <uint32 mask>
    void HandleProcs(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        SpellInfo const* spellInfo = eventInfo.GetSpellInfo();

        if (!(eventInfo.GetTypeMask() & mask) || !spellInfo)
        {
            return;
        }

        // Also check if the proc from the fire traps and black arrow actually comes from the periodic ticks here.
        // Normally this wouldn't be required, but we are circumventing the current proc system limitations.
        if (((spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_FIRE) || (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_SHADOW) || (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_NATURE) || (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_NORMAL))
            && (spellInfo->Effects[0].ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE || spellInfo->Effects[1].ApplyAuraName == SPELL_AURA_PERIODIC_DAMAGE)
            && !(mask & PROC_FLAG_DONE_PERIODIC))
        {
            return;
        }

        if (!roll_chance_i(aurEff->GetAmount()))
        {
            return;
        }

        Unit* caster = eventInfo.GetActor();

        if (!caster || caster->isDead())
            return;

        caster->CastSpell(caster, SPELL_LOCK_AND_LOAD_TRIGGER, true);
    }

    void ApplyMarker(ProcEventInfo& eventInfo)
    {
        if (IsTargetValid(eventInfo.GetSpellInfo(), eventInfo.GetProcTarget()))
        {
            Unit* caster = eventInfo.GetActor();
            caster->CastSpell(caster, SPELL_LOCK_AND_LOAD_MARKER, true);
        }
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_lock_and_load::CheckTrapProc);

        OnEffectProc += AuraEffectProcFn(spell_hun_lock_and_load::HandleProcs<PROC_FLAG_DONE_TRAP_ACTIVATION>, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        OnEffectProc += AuraEffectProcFn(spell_hun_lock_and_load::HandleProcs<PROC_FLAG_DONE_PERIODIC>, EFFECT_1, SPELL_AURA_DUMMY);

        AfterProc += AuraProcFn(spell_hun_lock_and_load::ApplyMarker);
    }
};

// 19577 - Intimidation
class spell_hun_intimidation : public AuraScript
{
    PrepareAuraScript(spell_hun_intimidation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (SpellInfo const* spellInfo = eventInfo.GetSpellInfo())
        {
            return !spellInfo->IsPositive();
        }

        return true;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_intimidation::CheckProc);
    }
};

// 19574 - Bestial Wrath
class spell_hun_bestial_wrath : public SpellScript
{
    PrepareSpellScript(spell_hun_bestial_wrath);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
        {
            return SPELL_FAILED_NO_VALID_TARGETS;
        }

        Pet* pet = caster->ToPlayer()->GetPet();
        if (!pet)
        {
            return SPELL_FAILED_NO_PET;
        }

        if (!pet->IsAlive())
        {
            SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_PET_IS_DEAD);
            return SPELL_FAILED_CUSTOM_ERROR;
        }

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_hun_bestial_wrath::CheckCast);
    }
};

class spell_hun_predators_thirst : public AuraScript
{
    PrepareAuraScript(spell_hun_predators_thirst);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0) {
            Unit* pet = GetCaster();

            if (!pet || pet->isDead())
                return;

            Unit* master = GetCaster()->GetOwner();

            if (!master || master->isDead())
                return;

            int32 damage = eventInfo.GetDamageInfo()->GetDamage();
            Unit* target = eventInfo.GetDamageInfo()->GetAttacker()->IsPlayer() ? master : pet;
            int32 healPct = aurEff->GetAmount();

            if (master->HasAura(13161))
                healPct += 5;

            int32 healAmount = CalculatePct(damage, healPct);

            target->CastCustomSpell(80124, SPELLVALUE_BASE_POINT0, healAmount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_predators_thirst::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_aspect_cheetah : public AuraScript
{
    PrepareAuraScript(spell_hun_aspect_cheetah);

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        GetCaster()->CastSpell(GetCaster(), 80129, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_aspect_cheetah::HandleRemove, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_bestial_apply : public SpellScript
{
    PrepareSpellScript(spell_hun_bestial_apply);

    void HandleBuff()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        Unit* pet = player->GetPet();

        if (!pet || pet->isDead())
            return;

        float ap = GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK);
        int32 ratio = sSpellMgr->AssertSpellInfo(SPELL_HUNTER_BESTIAL_WRATH_DAMAGE)->GetEffect(EFFECT_0).CalcValue(player);
        int32 damage = CalculatePct(ap, ratio);

        player->AddAura(SPELL_HUNTER_BESTIAL_WRATH_BUFF, pet);
        player->AddAura(SPELL_HUNTER_BESTIAL_WRATH_BUFF, player);

        pet->CastCustomSpell(SPELL_HUNTER_BESTIAL_WRATH_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, true, nullptr, nullptr);

        auto summonedUnits = player->m_Controlled;
        for (auto const& unit : summonedUnits)
        {
            if (!unit || unit->isDead())
                return;

            if (unit->GetCharmInfo() && unit->GetEntry() == 600612)
            {
                player->AddAura(SPELL_HUNTER_BESTIAL_WRATH_BUFF, unit);
                unit->CastCustomSpell(SPELL_HUNTER_BESTIAL_WRATH_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, true, nullptr, nullptr);
            }
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_bestial_apply::HandleBuff);
    }
};

class spell_hun_black_arrow_reset : public SpellScript
{
    PrepareSpellScript(spell_hun_black_arrow_reset);

    void HandleProc()
    {
        if (Player* caster = GetCaster()->ToPlayer())
            if (caster->IsAlive() && caster->HasSpell(63672))
                caster->RemoveSpellCooldown(63672, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_black_arrow_reset::HandleProc);
    }
};

class spell_hun_chimaera_trigger : public SpellScript
{
    PrepareSpellScript(spell_hun_chimaera_trigger);

    void HandleBuff()
    {
        if (Unit* unit = GetExplTargetUnit()) {
            Spell* spell = GetSpell();
            std::list<WorldObject*> targets;
            spell->SearchAreaTargets(targets, 7.5f, unit, GetCaster(), TARGET_OBJECT_TYPE_UNIT, TARGET_CHECK_ENEMY, nullptr);
            targets.remove(unit);
            if (targets.size() == 0)
                GetCaster()->CastSpell(unit, 80136, TRIGGERED_FULL_MASK);
            else
                if (Creature* creature = targets.front()->ToCreature())
                    GetCaster()->CastSpell(creature, 80136, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_chimaera_trigger::HandleBuff);
    }
};

class spell_hun_steady_shot_concussive : public SpellScript
{
    PrepareSpellScript(spell_hun_steady_shot_concussive);

    void HandleBuff()
    {
        Unit* target = GetExplTargetUnit();

        if (!target || !target->IsAlive())
            return;

        if (Aura* aura = target->GetAura(5116))
        {
            if (aura->GetCasterGUID() == GetCaster()->GetGUID()) {
                // aura->SetDuration(aura->GetDuration() + aura->GetEffect(EFFECT_1)->GetAmount());
            }
        }
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_hun_steady_shot_concussive::HandleBuff);
    }
};

class spell_hun_explosive_shot : public AuraScript
{
    PrepareAuraScript(spell_hun_explosive_shot);

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* target = GetTarget();

        if (!GetCaster() || GetCaster()->isDead())
            return;

        if (!target || !target->IsAlive())
            return;

        GetCaster()->CastSpell(target, 80137, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_explosive_shot::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_kill_command : public SpellScript
{
    PrepareSpellScript(spell_hun_kill_command);

    Aura* GetDeadlyDuoRune()
    {
        for (size_t i = 501484; i < 501490; i++)
        {
            if (GetCaster()->HasAura(i))
                return GetCaster()->GetAura(i);
        }

        return nullptr;
    }

    void HandleCast()
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        Unit* pet = caster->GetPet();

        if (!pet || pet->isDead())
            return;

        float ap = GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK);
        int32 ratio = sSpellMgr->AssertSpellInfo(SPELL_HUNTER_KILL_COMMAND_DAMAGE)->GetEffect(EFFECT_1).CalcValue(caster);
        int32 damage = CalculatePct(ap, ratio);

        pet->Attack(target, true);
        pet->CastCustomSpell(SPELL_HUNTER_KILL_COMMAND_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, true, nullptr, nullptr);

        auto summonedUnits = caster->m_Controlled;

        for (auto const& unit : summonedUnits)
            if (unit->GetCharmInfo() && unit->GetEntry() == 600612)
                unit->CastCustomSpell(SPELL_HUNTER_KILL_COMMAND_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, true, nullptr, nullptr);

        if (Aura* aura = caster->GetAura(SPELL_HUNTER_TALENT_TIP_OF_SPEAR))
            caster->CastSpell(caster, SPELL_HUNTER_TALENT_TIP_OF_SPEAR_BUFF, true);

        if (caster->HasSpell(SPELL_HUNTER_FURY_OF_THE_EAGLE))
            caster->ModifySpellCooldown(SPELL_HUNTER_FURY_OF_THE_EAGLE, -3000);
    }

    void HandleAfterCast()
    {
        Player* caster = GetCaster()->ToPlayer();
        int32 procChance = sSpellMgr->AssertSpellInfo(80141)->GetEffect(EFFECT_2).CalcValue(caster);
        int32 duration = 0;

        if (Aura* aura = caster->GetAura(SPELL_HUNTER_SPEARHEAD))
        {
            procChance += aura->GetEffect(EFFECT_2)->GetAmount();
            duration = aura->GetDuration();
        }

        if (GetDeadlyDuoRune())
            if (Aura* aura = caster->GetAura(GetDeadlyDuoRune()->GetSpellInfo()->GetEffect(EFFECT_0).TriggerSpell))
            {
                procChance += aura->GetEffect(EFFECT_1)->GetAmount();
                caster->RemoveAura(aura);
            }

        if (roll_chance_i(procChance))
        {
            caster->RemoveSpellCooldown(SPELL_HUNTER_KILL_COMMAND, true);

            if (!GetDeadlyDuoRune() || duration == 0)
                return;

            int32 amount = GetDeadlyDuoRune()->GetEffect(EFFECT_1)->GetAmount();
            caster->GetAura(80208)->SetDuration(duration + amount);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_kill_command::HandleCast);
        AfterCast += SpellCastFn(spell_hun_kill_command::HandleAfterCast);
    }
};

class spell_hun_mongoose_fury : public SpellScript
{
    PrepareSpellScript(spell_hun_mongoose_fury);

    void HandleBuff()
    {
        Unit* player = GetCaster();
        Aura* mongooseBuff = player->GetAura(SPELL_HUNTER_MONGOOSE_FURY);
        SpellValue const* value = GetSpellValue();

        if (!mongooseBuff)
            player->AddAura(SPELL_HUNTER_MONGOOSE_FURY, player);

        if (mongooseBuff)
        {
            int32 maxStack = value->EffectBasePoints[EFFECT_1];
            int32 stackCount = mongooseBuff->GetStackAmount();
            if (stackCount == maxStack)
                return;
            player->SetAuraStack(SPELL_HUNTER_MONGOOSE_FURY, player, stackCount + 1);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_mongoose_fury::HandleBuff);
    }
};

class spell_hun_readiness_trigger : public AuraScript
{
    PrepareAuraScript(spell_hun_readiness_trigger);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Player* caster = GetTarget()->ToPlayer();

        if (!caster || !caster->IsAlive())
            return;

        if (caster)
        {
            caster->RemoveSpellCooldown(80146, true);
            caster->AddAura(80152, caster);
        }
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_readiness_trigger::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_trueshot : public SpellScript
{
    PrepareSpellScript(spell_hun_trueshot);

    void HandleBuff()
    {
        GetCaster()->CastSpell(GetExplTargetUnit(), 80154, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_trueshot::HandleBuff);
    }
};

class spell_hun_bear_applier : public AuraScript
{
    PrepareAuraScript(spell_hun_bear_applier);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || !player->IsAlive())
            return;

        Unit* pet = player->GetPet();

        if (!pet || pet->isDead())
            return;

        auto summonedUnits = player->m_Controlled;

        for (auto const& unit : summonedUnits)
        {
            if (!unit->IsInWorld())
                continue;

            if (unit->isDead())
                continue;

            float ap = unit->GetTotalAttackPowerValue(BASE_ATTACK);
            unit->SetInt32Value(UNIT_FIELD_ATTACK_POWER, CalculatePct(ap, 10.0f));
            unit->UpdateDamagePhysical(BASE_ATTACK);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || !player->IsAlive())
            return;

        Unit* pet = player->GetPet();

        if (!pet || pet->isDead())
            return;

        auto summonedUnits = player->m_Controlled;

        for (auto const& unit : summonedUnits)
        {
            if (!unit->IsInWorld())
                continue;

            if (unit->isDead())
                continue;
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_bear_applier::HandleProc, EFFECT_1, SPELL_AURA_MOD_ATTACK_POWER_PCT, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_bear_applier::HandleRemove, EFFECT_1, SPELL_AURA_MOD_ATTACK_POWER_PCT, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_beast_applier : public AuraScript
{
    PrepareAuraScript(spell_hun_beast_applier);

    void HandleApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || !player->IsAlive())
            return;

        Unit* pet = player->GetPet();

        if (!pet || pet->isDead())
            return;

        player->AddAura(SPELL_HUNTER_ASPECT_OF_THE_BEAST_BUFF, pet);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || !player->IsAlive())
            return;

        Unit* pet = player->GetPet();

        if (!pet || pet->isDead())
            return;

        if (Aura* aura = pet->GetAura(SPELL_HUNTER_ASPECT_OF_THE_BEAST_BUFF))
            aura->Remove();
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_beast_applier::HandleApply, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_beast_applier::HandleRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_aspect_turtle : public SpellScript
{
    PrepareSpellScript(spell_hun_aspect_turtle);

    void HandleBuff()
    {
        GetCaster()->CastSpell(GetCaster(), 80158, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_aspect_turtle::HandleBuff);
    }
};

class spell_hun_survival_fittest : public AuraScript
{
    PrepareAuraScript(spell_hun_survival_fittest);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* player = GetCaster()->ToPlayer();
        Unit* pet = player->GetPet();

        if (!pet)
            return;

        if (!player || !player->IsAlive())
            return;

        player->AddAura(80162, pet);

        auto summonedUnits = player->m_Controlled;

        for (auto const& unit : summonedUnits)
        {
            if (!unit->IsInWorld())
                continue;

            if (unit->isDead())
                continue;

            player->CastSpell(unit, 80162);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* pet = player->GetPet();

        if (!pet || pet->isDead())
            return;

        pet->RemoveAura(80162);

        auto summonedUnits = player->m_Controlled;

        for (auto const& unit : summonedUnits)
        {
            if (!unit->IsInWorld())
                continue;

            if (unit->isDead())
                continue;

            unit->RemoveAura(80162);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_survival_fittest::HandleProc, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_survival_fittest::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_camouflage : public AuraScript
{
    PrepareAuraScript(spell_hun_camouflage);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* player = GetCaster();

        if (!player)
            return;

        auto summonedUnits = player->m_Controlled;

        for (auto const& unit : summonedUnits) {

            if (!unit || unit->isDead())
                continue;

            player->AddAura(80175, unit);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* pet = player->GetPet();

        if (!pet || pet->isDead())
            return;

        pet->RemoveAura(80163);

        auto summonedUnits = player->m_Controlled;

        for (auto const& unit : summonedUnits)
        {
            if (unit->isDead())
                continue;

            unit->RemoveAura(80175);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_camouflage::HandleProc, EFFECT_0, SPELL_AURA_MOD_STEALTH, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_camouflage::HandleRemove, EFFECT_0, SPELL_AURA_MOD_STEALTH, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_death_chakram : public SpellScript
{
    PrepareSpellScript(spell_hun_death_chakram);

    void HandleHit(SpellEffIndex effIndex)
    {
        if (!GetCaster() || GetCaster()->isDead())
            return;

        int32 energizeAmount = sSpellMgr->AssertSpellInfo(SPELL_HUNTER_DEATH_CHAKRAM)->GetEffect(EFFECT_2).CalcValue();
        GetCaster()->EnergizeBySpell(GetCaster(), SPELL_HUNTER_DEATH_CHAKRAM, energizeAmount, POWER_FOCUS);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_death_chakram::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_hun_cobra_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_cobra_shot);

    void HandleCast()
    {
        Player* target = GetCaster()->ToPlayer();

        if (!target || !target->IsAlive())
            return;

        int32 amount = sSpellMgr->GetSpellInfo(SPELL_HUNTER_COBRA_SHOT)->GetEffect(EFFECT_1).CalcValue(target);
        target->ModifySpellCooldown(SPELL_HUNTER_KILL_COMMAND, amount);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_cobra_shot::HandleCast);
    }
};

class spell_hun_barbed_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_barbed_shot);

    void HandleBuff()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* pet = player->GetPet();

        if (!pet || pet->isDead())
            return;

        player->AddAura(80174, pet);
    }

    void HandleEnergy(SpellEffIndex effIndex)
    {
        GetCaster()->CastSpell(GetCaster(), 80173, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_barbed_shot::HandleBuff);
        OnEffectHit += SpellEffectFn(spell_hun_barbed_shot::HandleEnergy, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_hun_murder_crows_check : public AuraScript
{
    PrepareAuraScript(spell_hun_murder_crows_check);

    bool HandleProc(ProcEventInfo& eventInfo)
    {
        if (Unit* target = eventInfo.GetActionTarget())
            if (Aura* aura = target->GetAura(80176))
                if (aura->GetCasterGUID() == GetCaster()->GetGUID())
                    return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_murder_crows_check::HandleProc);
    }
};

class spell_hun_murder_crows_reset : public SpellScript
{
    PrepareSpellScript(spell_hun_murder_crows_reset);

    void HandleProc()
    {
        Unit* caster = GetCaster();
        if (Player* player = caster->ToPlayer()) {
            player->RemoveSpellCooldown(80176, true);
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_murder_crows_reset::HandleProc);
    }
};

class spell_hun_bloodshed : public SpellScript
{
    PrepareSpellScript(spell_hun_bloodshed);

    void HandleBuff()
    {
        Player* player = GetCaster()->ToPlayer();

        if (!player || player->isDead())
            return;

        Unit* pet = player->GetPet();

        if (!pet || player->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        float ap = GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK);
        int32 ratio = sSpellMgr->AssertSpellInfo(80179)->GetEffect(EFFECT_2).CalcValue(GetCaster());
        int32 damage = CalculatePct(ap, ratio);

        pet->CastCustomSpell(80179, SPELLVALUE_BASE_POINT0, damage, target, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_bloodshed::HandleBuff);
    }
};

class spell_hun_lone_wolf : public AuraScript
{
    PrepareAuraScript(spell_hun_lone_wolf);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        Pet* pet = GetCaster()->ToPlayer()->GetPet();

        if (!pet)
            GetCaster()->AddAura(SPELL_HUNTER_LONE_WOLF_BUFF, GetCaster());
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hun_lone_wolf::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_hun_dire_beast : public SpellScript
{
    PrepareSpellScript(spell_hun_dire_beast);

    void HandleSummon()
    {
        Unit* caster = GetCaster();
        if (!caster || caster->isDead())
            return;

        std::vector<int32> summons = { 400000,400001,400002 };
        int32 summonId = summons[rand() % summons.size()];

        Position const& pos = caster->GetPosition();
        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);
        int32 duration = GetSpellInfo()->GetDuration();

        Creature* summon = caster->SummonCreature(summonId, pos, TEMPSUMMON_TIMED_DESPAWN, duration, 0, properties);

        summon->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(summon->getLevel() - (summon->getLevel() / 8) + caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.05f));
        summon->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(summon->getLevel() + (summon->getLevel() / 8) + caster->GetTotalAttackPowerValue(RANGED_ATTACK) * 0.05f));
        caster->AddAura(34902, summon);
        caster->AddAura(34903, summon);
        caster->AddAura(34904, summon);

        if (summon && summon->IsAlive())
            if (Unit* target = ObjectAccessor::GetUnit(*GetCaster(), GetCaster()->GetTarget()))
                summon->AI()->AttackStart(target);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_dire_beast::HandleSummon);
    }
};

class spell_hun_call_of_wild : public SpellScript
{
    PrepareSpellScript(spell_hun_call_of_wild);

    void HandlePet()
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        Position const& pos = GetCaster()->GetPosition();
        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(63);
        int32 duration = GetSpellInfo()->GetDuration();

        PetStable* petStable = caster->GetPetStable();

        if (!petStable)
            return;

        int32 totalSummon = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(caster);

        for (size_t i = 0; i < totalSummon; i++)
        {
            if (!petStable->StabledPets.at(i))
                continue;

            uint32 displayId = petStable->StabledPets.at(i)->DisplayId;

            Creature* pet = caster->SummonCreatureGuardian(600613, caster, caster->ToPlayer(), duration, SECOND_PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);

            if (pet && pet->IsAlive())
            {
                pet->SetDisplayId(displayId);

                if (CreatureDisplayInfoEntry const* displayInfo = sCreatureDisplayInfoStore.LookupEntry(displayId))
                    if (displayInfo->scale > 1)
                        pet->SetObjectScale((1 / (displayInfo->scale)) - 0.2);
            }
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_call_of_wild::HandlePet);
    }
};

class spell_hun_call_of_wild_periodic : public SpellScript
{
    PrepareSpellScript(spell_hun_call_of_wild_periodic);

    void HandleSummon()
    {
        PetStable* petStable = GetCaster()->ToPlayer()->GetPetStable();

        if (!petStable)
            return;

        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        Position const& pos = GetCaster()->GetPosition();
        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(63);
        int32 duration = GetSpellInfo()->GetDuration();

        int32 petQuantity = -1;

        for (size_t i = 0; i < petStable->StabledPets.size(); i++)
        {
            if (!petStable->StabledPets.at(i))
                continue;

            petQuantity++;
        }

        if (petQuantity < 0)
            return;

        uint32 random = urand(0, petQuantity);

        uint32 displayId = petStable->StabledPets.at(random)->DisplayId;

        Creature* pet = GetCaster()->SummonCreatureGuardian(600613, GetCaster(), GetCaster()->ToPlayer(), duration, SECOND_PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);

        if (pet && pet->IsAlive())
        {
            pet->SetDisplayId(displayId);

            if (CreatureDisplayInfoEntry const* displayInfo = sCreatureDisplayInfoStore.LookupEntry(displayId)) {
                if (displayInfo->scale > 1.0f) {
                    pet->SetObjectScale((1 / (displayInfo->scale)) - 0.2);
                }
            }

            pet->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, float(pet->getLevel() - (pet->getLevel() / 8)));
            pet->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, float(pet->getLevel() + (pet->getLevel() / 8)));
            pet->AddAura(34902, GetCaster());
            pet->AddAura(34903, GetCaster());
            pet->AddAura(34904, GetCaster());
        }
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_call_of_wild_periodic::HandleSummon);
    }
};

class spell_hun_harpoon : public SpellScript
{
    PrepareSpellScript(spell_hun_harpoon);

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();

        if (target && target->GetTypeId() == TYPEID_PLAYER && caster->GetExactDist(target) < 8.0f)
            return SPELL_FAILED_TOO_CLOSE;

        return SPELL_CAST_OK;
    }

    void HandleCast()
    {
        if (AuraEffect const* aurEff = GetCaster()->GetAuraEffectOfRankedSpell(19295, EFFECT_0))
        {
            Unit* caster = GetCaster();
            if (Unit* target = GetExplTargetUnit()) {

                float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);

                int32 damageRatio = aurEff->GetBase()->GetEffect(EFFECT_0)->GetAmount();
                int32 focusAmount = aurEff->GetBase()->GetEffect(EFFECT_1)->GetAmount();

                int32 damage = CalculatePct(ap, damageRatio);
                int32 maxTicks = sSpellMgr->AssertSpellInfo(80235)->GetMaxTicks();

                int32 newFocusAmount = focusAmount / maxTicks;
                caster->CastCustomSpell(target, 80235, &damage, &newFocusAmount, nullptr, true, nullptr, nullptr);
            }
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_hun_harpoon::CheckCast);
        OnCast += SpellCastFn(spell_hun_harpoon::HandleCast);
    }
};

class spell_hun_fury_eagle : public SpellScript
{
    PrepareSpellScript(spell_hun_fury_eagle);

    void HandleHit(SpellMissInfo missInfo)
    {
        Unit* target = GetExplTargetUnit();

        if (!target)
            return;

        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        int32 targetHealthPct = target->GetHealthPct();
        int32 hpThreshold = sSpellMgr->GetSpellInfo(80194)->GetEffect(EFFECT_2).CalcValue(GetCaster());

        if (targetHealthPct < hpThreshold)
        {
            GetCaster()->CastSpell(GetCaster(), 80196, true);
        }
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_hun_fury_eagle::HandleHit);
    }
};

class spell_hun_flanking_strike : public SpellScript
{
    PrepareSpellScript(spell_hun_flanking_strike);

    void HandleBuff()
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        Unit* pet = caster->GetPet();

        if (!pet || pet->isDead())
            return;

        float ap = GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK);
        int32 ratio = sSpellMgr->AssertSpellInfo(80198)->GetEffect(EFFECT_0).CalcValue(caster);
        int32 damage = CalculatePct(ap, ratio);

        Position targetPos = GetExplTargetUnit()->GetPosition();

        pet->CastCustomSpell(SPELL_HUNTER_FLANKING_STRIKE_PET_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_flanking_strike::HandleBuff);
    }
};

class spell_hun_coordinated_assault : public SpellScript
{
    PrepareSpellScript(spell_hun_coordinated_assault);

    void HandleBuff()
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        Unit* pet = caster->GetPet();

        if (!pet || pet->isDead())
            return;

        float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
        int32 ratio = sSpellMgr->AssertSpellInfo(SPELL_HUNTER_COORDINATED_ASSAULT_PET_DAMAGE)->GetEffect(EFFECT_0).CalcValue(caster);
        int32 damage = CalculatePct(ap, ratio);

        pet->Attack(target, true);
        pet->CastCustomSpell(SPELL_HUNTER_COORDINATED_ASSAULT_PET_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, TRIGGERED_FULL_MASK);
        caster->AddAura(SPELL_HUNTER_COORDINATED_ASSAULT_BUFF, caster);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_coordinated_assault::HandleBuff);
    }
};

class spell_hun_coordinated_bleed : public AuraScript
{
    PrepareAuraScript(spell_hun_coordinated_bleed);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetDamageInfo())
            return false;

        if (eventInfo.GetDamageInfo()->GetDamage() <= 0)
            return false;

        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo()->Id == SPELL_HUNTER_KILL_SHOT)
        {
            Unit* target = eventInfo.GetActionTarget();

            if (!target || target->isDead())
                return;

            Unit* caster = GetCaster();

            if (!caster || caster->isDead())
                return;

            int32 damage = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount()) / 6;

            caster->CastCustomSpell(SPELL_HUNTER_COORDINATED_ASSAULT_BLEED, SPELLVALUE_BASE_POINT0, damage, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_coordinated_bleed::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_spearhead : public SpellScript
{
    PrepareSpellScript(spell_hun_spearhead);

    void HandleBuff()
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        Unit* pet = caster->GetPet();

        if (!pet || pet->isDead())
            return;

        float ap = GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK);
        int32 ratio = sSpellMgr->AssertSpellInfo(SPELL_HUNTER_SPEARHEAD_PET_DAMAGE)->GetEffect(EFFECT_0).CalcValue(caster);
        int32 damage = CalculatePct(ap, ratio);

        pet->CastCustomSpell(SPELL_HUNTER_SPEARHEAD_PET_DAMAGE, SPELLVALUE_BASE_POINT0, damage, target, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_spearhead::HandleBuff);
    }
};

class spell_hun_spearhead_buff : public SpellScript
{
    PrepareSpellScript(spell_hun_spearhead_buff);

    void HandleProc()
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        Unit* pet = GetCaster()->ToPlayer()->GetPet();

        if (!pet || pet->isDead())
            return;

        GetCaster()->AddAura(SPELL_HUNTER_SPEARHEAD_BUFF, GetCaster());
    }

    void Register()
    {
        OnCast += SpellCastFn(spell_hun_spearhead_buff::HandleProc);
    }
};

class spell_hun_cobra_sting : public SpellScript
{
    PrepareSpellScript(spell_hun_cobra_sting);

    void HandleAfterCast()
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        if (Aura* aura = caster->GetAura(24443))
        {
            int32 procChance = aura->GetEffect(EFFECT_0)->GetAmount();
            bool didProc = roll_chance_i(procChance);
            if (didProc)
                caster->RemoveSpellCooldown(80172, true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_hun_cobra_sting::HandleAfterCast);
    }
};

class spell_hun_aspect_mastery_crit : public AuraScript
{
    PrepareAuraScript(spell_hun_aspect_mastery_crit);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(53265))
            caster->AddAura(80213, caster);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(80213))
            caster->RemoveAura(80213);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_aspect_mastery_crit::HandleProc, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_aspect_mastery_crit::HandleRemove, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_aspect_mastery_ranged_damage : public AuraScript
{
    PrepareAuraScript(spell_hun_aspect_mastery_ranged_damage);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (caster->HasAura(53265))
            caster->AddAura(80214, caster);
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(80214))
            caster->RemoveAura(80214);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_aspect_mastery_ranged_damage::HandleProc, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_aspect_mastery_ranged_damage::HandleRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_wild_call : public AuraScript
{
    PrepareAuraScript(spell_hun_wild_call);

    void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || !caster->IsAlive())
            return;

        if (caster)
            caster->RemoveSpellCooldown(80172, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_wild_call::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_beast_within : public AuraScript
{
    PrepareAuraScript(spell_hun_beast_within);

    void HandleProc(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        if (GetCaster()->HasAura(80221))
            GetCaster()->AddAura(80222, GetCaster());
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        if (GetCaster()->HasAura(80222))
            GetCaster()->RemoveAura(80222);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_beast_within::HandleProc, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_beast_within::HandleRemove, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
    }
};

static bool IsSecondaryPetAlreadySummoned(Unit* caster, uint32 petId) {

    auto summonedUnits = caster->ToPlayer()->m_Controlled;

    if (summonedUnits.size() == 0)
        return false;

    for (const auto& unit : summonedUnits)
        if (unit->GetCharmInfo() && unit->GetEntry() == 600612)
            return true;

    return false;
}

static void ApplySecondaryPet(Creature* summon, auto firstPet, Unit* caster)
{
    summon->GetMotionMaster()->MoveFollow(summon->GetCharmerOrOwner(), SECOND_PET_FOLLOW_DIST, summon->GetFollowAngle());
    summon->InitCharmInfo();
    ((Guardian*)summon)->InitStatsForLevel(caster->getLevel());

    summon->GetCharmInfo()->SetPetNumber(firstPet->PetNumber, false);
    summon->SetDisplayId(firstPet->DisplayId);
    summon->setPowerType(POWER_FOCUS);
    summon->SetNativeDisplayId(firstPet->DisplayId);
    summon->SetName(firstPet->Name);

    PetLevelInfo const* pInfo = sObjectMgr->GetPetLevelInfo(firstPet->CreatureId, caster->getLevel());
    if (pInfo)
    {
        summon->SetCreateHealth(pInfo->health);
        summon->SetModifierValue(UNIT_MOD_HEALTH, BASE_VALUE, (float)pInfo->health);
        if (pInfo->armor > 0)
            summon->SetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE, float(pInfo->armor));

        for (uint8 stat = 0; stat < MAX_STATS; ++stat)
            summon->SetCreateStat(Stats(stat), float(pInfo->stats[stat]));
    }

    if (CreatureDisplayInfoEntry const* displayInfo = sCreatureDisplayInfoStore.LookupEntry(summon->GetNativeDisplayId())) {
        if (displayInfo->scale > 1)
            summon->SetObjectScale((1 / (displayInfo->scale)) - 0.2);
    }
}

/*class Hunter_AllMapScript : public AllMapScript
{
public:
    Hunter_AllMapScript() : AllMapScript("Hunter_AllMapScript") { }

    // Handle the secondary pet if the player has the talent when the hunter enter in any maps.
    void OnPlayerEnterAll(Map* map, Player* player)
    {
        if (player->getClass() == CLASS_HUNTER && player->HasAura(SPELL_HUNTER_ANIMAL_COMPANION_TALENT))
        {
            PetStable* petStable = player->GetPetStable();

            if (!petStable)
                return;

            auto firstPet = petStable->StabledPets.at(0);

            if (!firstPet)
                return;

            if (IsSecondaryPetAlreadySummoned(player, firstPet->PetNumber))
                return;

            Position const& pos = player->GetPosition();
            SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);
            uint32 displayId = firstPet->DisplayId;
            Creature* summon = player->SummonCreature(600612, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60 * IN_MILLISECONDS, 0, properties);
            summon->SetDisplayId(displayId);
            ApplySecondaryPet(summon, firstPet, player);
        }
    }
};*/

/*class spell_hun_animal_companion : public SpellScript
{
    PrepareSpellScript(spell_hun_animal_companion);

    void HandleBuff()
    {
        Player* caster = GetCaster()->ToPlayer();

        if (!caster || !caster->IsAlive())
            return;

        if (!caster->HasAura(SPELL_HUNTER_ANIMAL_COMPANION_TALENT))
            return;

        PetStable* petStable = caster->GetPetStable();

        if (!petStable)
            return;

        auto firstPet = petStable->StabledPets.at(0);

        if (!firstPet)
            return;


        Position const& pos = caster->GetPosition();
        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);
        Creature* summon = caster->SummonCreature(600612, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60 * IN_MILLISECONDS, 0, properties);
        uint32 displayId = firstPet->DisplayId;
        summon->SetDisplayId(displayId);
        ApplySecondaryPet(summon, firstPet, caster);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_hun_animal_companion::HandleBuff);
    }
};*/

/*class spell_hun_animal_companion_dismiss_pet : public SpellScript
{
    PrepareSpellScript(spell_hun_animal_companion_dismiss_pet);

    void HandleBuff()
    {
        Player* caster = GetCaster()->ToPlayer();

        auto summonedUnits = caster->ToPlayer()->m_Controlled;

        for (const auto& pet : summonedUnits)
            if (pet->GetCharmInfo())
                pet->ToTempSummon()->DespawnOrUnsummon();
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_hun_animal_companion_dismiss_pet::HandleBuff);
    }
};*/

class spell_hun_arctic_bola : public AuraScript
{
    PrepareAuraScript(spell_hun_arctic_bola);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        Unit* target = procInfo.GetActionTarget();

        if (!target || !target->IsAlive())
            return;

        Player* caster = GetCaster()->ToPlayer();

        if (!caster || caster->isDead())
            return;

        caster->CastSpell(target, 80227, true);
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_arctic_bola::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_careful_aim : public AuraScript
{
    PrepareAuraScript(spell_hun_careful_aim);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* target = eventInfo.GetActionTarget();

        if (!target || target->isDead())
            return;

        float damageDealt = eventInfo.GetDamageInfo()->GetDamage();

        if (damageDealt <= 0)
            return;

        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        AuraEffect const* currentAura = GetCaster()->GetDummyAuraEffect(SPELLFAMILY_HUNTER, 2222, 0);

        float damage = CalculatePct(int32(damageDealt), currentAura->GetAmount());
        int32 maxTicks = sSpellMgr->GetSpellInfo(80228)->GetMaxTicks();
        int32 amount = damage / maxTicks;

        GetCaster()->CastCustomSpell(TALENT_HUNTER_CAREFUL_AIM_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_careful_aim::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hun_careful_aim::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_aimed_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_aimed_shot);

    void HandleDamage(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetExplTargetUnit();

        if (!target || target->isDead())
            return;

        int32 damage = GetHitDamage();

        if (Aura* calculated = target->GetAura(TALENT_HUNTER_CALCULATED_SHOT))
            if (target->GetHealthPct() >= calculated->GetEffect(EFFECT_1)->GetAmount())
                damage += CalculatePct(damage, calculated->GetEffect(EFFECT_0)->GetAmount());

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_aimed_shot::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_hun_rabid_mongoose : public AuraScript
{
    PrepareAuraScript(spell_hun_rabid_mongoose);

    void HandleLearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();
        if (target->HasSpell(48996))
        {
            target->removeSpell(48996, SPEC_MASK_ALL, false);
            target->learnSpell(53339);
        }
    }

    void HandleUnlearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();
        target->removeSpell(53339, SPEC_MASK_ALL, false);
        target->learnSpell(48996);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_rabid_mongoose::HandleLearn, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_rabid_mongoose::HandleUnlearn, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_harpoon_reset : public AuraScript
{
    PrepareAuraScript(spell_hun_harpoon_reset);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (AuraEffect const* aurEff = GetCaster()->GetAuraEffectOfRankedSpell(19295, EFFECT_0))
            return true;
        return false;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        if (Player* caster = GetCaster()->ToPlayer())
            if (caster->IsAlive())
                caster->RemoveSpellCooldown(80190, true);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_harpoon_reset::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_hun_harpoon_reset::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_hunters_prey : public AuraScript
{
    PrepareAuraScript(spell_hun_hunters_prey);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        GetCaster()->ToPlayer()->RemoveSpellCooldown(61006, true);
        GetCaster()->ToPlayer()->AddAura(80220, GetCaster());
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_hunters_prey::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_thrill_of_hunt : public AuraScript
{
    PrepareAuraScript(spell_hun_thrill_of_hunt);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        Pet* pet = GetCaster()->ToPlayer()->GetPet();

        if (!pet || pet->isDead())
            return;

        GetCaster()->AddAura(80239, pet);
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_thrill_of_hunt::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

class spell_hun_noxious_stings : public AuraScript
{
    PrepareAuraScript(spell_hun_noxious_stings);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        int32 buffAmount = aurEff->GetAmount();

        GetCaster()->CastCustomSpell(80240, SPELLVALUE_BASE_POINT0, buffAmount, GetCaster());
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_noxious_stings::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_hunting_party : public AuraScript
{
    PrepareAuraScript(spell_hun_hunting_party);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        if (!GetCaster() || !GetCaster()->IsAlive())
            return;

        int32 focusAmount = aurEff->GetBase()->GetEffect(EFFECT_2)->GetAmount();

        GetCaster()->CastCustomSpell(80241, SPELLVALUE_BASE_POINT0, focusAmount, GetCaster());

        Pet* pet = GetCaster()->ToPlayer()->GetPet();

        if (!pet || pet->isDead())
            return;

        GetCaster()->CastCustomSpell(80241, SPELLVALUE_BASE_POINT0, focusAmount, pet);
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_hunting_party::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hunter_stampeded : public AuraScript
{
    PrepareAuraScript(spell_hunter_stampeded);

    void HandleDummyTick(AuraEffect const* /*aurEff*/)
    {
        Unit* target = GetTarget();
        Position position = target->GetPosition();
        if (GetAura()->GetDuration() % 2 == 0)
            position.m_positionX += 2.5f;
        else
            position.m_positionX -= 2.5f;
        SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);
        TempSummon* summon = target->GetOwner()->SummonCreature(600609, position, TEMPSUMMON_TIMED_DESPAWN, 10000, 0, properties);
        summon->SetSummonerGUID(target->GetOwnerGUID());
        summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        summon->SetReactState(REACT_PASSIVE);
        summon->SetTarget();
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hunter_stampeded::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class npc_hunter_spell_stampeded : public CreatureScript
{
public:
    npc_hunter_spell_stampeded() : CreatureScript("npc_hunter_spell_stampeded") { }

    struct npc_hunter_spell_stampededAI : public ScriptedAI
    {
        npc_hunter_spell_stampededAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 update = 750;

        void Reset() override
        {
            Position pos = me->GetFirstCollisionPosition(40.f, 0);
            me->GetMotionMaster()->MovePoint(0, pos);
            me->CombatStop(true);
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 diff) override
        {
            if (update >= 750) {
                if (Unit* owner = me->ToTempSummon()->GetSummonerUnit()) {
                    me->CastSpell(me, SPELL_HUNTER_STAMPEDED_DAMAGE, true, nullptr, nullptr, owner->GetGUID());
                    me->CastSpell(me, 80242, true, nullptr, nullptr, owner->GetGUID());
                }
                update = 0;
            }
            update += diff;
        }

        void MovementInform(uint32 /*type*/, uint32 id) override {
            if (id == 0) {
                me->DespawnOrUnsummon();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hunter_spell_stampededAI(creature);
    }
};

class spell_hun_backshot : public SpellScript
{
    PrepareSpellScript(spell_hun_backshot);

    Aura* GetTormentingShadowsAura(Unit* caster)
    {
        for (size_t i = 501586; i < 501592; i++)
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

        float ap = CalculatePct(int32(GetCaster()->GetTotalAttackPowerValue(RANGED_ATTACK)), GetEffectValue());
        int32 sp = CalculatePct(int32(GetCaster()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW)), GetEffectValue());
        int32 damage = std::max<int32>(0, int32(ap + sp));

        damage = GetCaster()->SpellDamageBonusDone(target, GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE, effIndex);
        damage = target->SpellDamageBonusTaken(GetCaster(), GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);

        if (!target->HasInArc(M_PI, caster))
        {
            uint32 damageBonus = GetSpellInfo()->GetEffect(EFFECT_1).CalcValue(caster);

            AddPct(damage, damageBonus);

            if (Player* player = caster->ToPlayer())
            {
                uint32 reduction = GetSpellInfo()->GetEffect(EFFECT_2).CalcValue(caster);
                player->ModifySpellCooldown(SPELL_HUNTER_WITHERING_FIRE, reduction);
            }

            if (GetTormentingShadowsAura(caster))
            {
                int32 damagePct = GetTormentingShadowsAura(caster)->GetEffect(EFFECT_0)->GetAmount();
                int32 procSpell = GetTormentingShadowsAura(caster)->GetEffect(EFFECT_1)->GetAmount();

                AddPct(damage, damagePct);

                caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
            }
        }

        SetHitDamage(damage);
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove Vein Burst rune Buff
        for (size_t i = 501672; i < 501678; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_backshot::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_hun_backshot::HandleAfterHit);
    }
};

class spell_hun_withering_fire_energy : public SpellScript
{
    PrepareSpellScript(spell_hun_withering_fire_energy);

    void HandleBuff()
    {
        int32 energizeAmount = sSpellMgr->AssertSpellInfo(SPELL_HUNTER_WITHERING_FIRE_DAMAGE)->GetEffect(EFFECT_1).CalcValue();
        GetCaster()->EnergizeBySpell(GetCaster(), SPELL_HUNTER_WITHERING_FIRE, energizeAmount, POWER_FOCUS);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_hun_withering_fire_energy::HandleBuff);
    }
};

class spell_hun_black_curse_reset : public AuraScript
{
    PrepareAuraScript(spell_hun_black_curse_reset);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        Player* caster = GetCaster()->ToPlayer();
        caster->RemoveSpellCooldown(SPELL_HUNTER_BLACK_CURSE, true);

        if (caster->IsAlive())
            caster->CastSpell(caster, SPELL_HUNTER_BLACK_CURSE_HEAL, true);
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_black_curse_reset::HandleProc, EFFECT_2, SPELL_AURA_DUMMY);
    }
};

class spell_hun_twilight_piercer : public SpellScript
{
    PrepareSpellScript(spell_hun_twilight_piercer);

    void HandleProc()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(SPELL_HUNTER_INVIS_ACTIVATOR))
            caster->CastSpell(GetExplTargetUnit(), SPELL_HUNTER_TWILIGHT_PIERCER_STUN, TRIGGERED_FULL_MASK);
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 energizeAmount = sSpellMgr->AssertSpellInfo(SPELL_HUNTER_TWILIGHT_PIERCER)->GetEffect(EFFECT_2).CalcValue();
        caster->EnergizeBySpell(caster, SPELL_HUNTER_TWILIGHT_PIERCER, energizeAmount, POWER_FOCUS);

        if (Player* player = caster->ToPlayer())
        {
            if (caster->HasAura(T1_HUNTER_DARKRANGER_2PC_BUFF))
            {
                caster->RemoveAura(T1_HUNTER_DARKRANGER_2PC_BUFF);

                if (Aura* T1_4pc = caster->GetAura(T1_HUNTER_DARKRANGER_4PC))
                {
                    int32 cooldown = T1_4pc->GetEffect(EFFECT_0)->GetAmount();

                    if (caster->HasAura(SPELL_HUNTER_CRESCENT_VEIL))
                        cooldown *= 2;

                    player->ModifySpellCooldown(SPELL_HUNTER_CRESCENT_VEIL, -cooldown);
                }
            }
        }
    }

    void Register() override
    {
        BeforeCast += SpellCastFn(spell_hun_twilight_piercer::HandleProc);
        AfterHit += SpellHitFn(spell_hun_twilight_piercer::HandleAfterCast);
    }
};

// 85006 - Twilight Piercer Aura
class spell_hun_twilight_piercer_aura : public AuraScript
{
    PrepareAuraScript(spell_hun_twilight_piercer_aura);

    Aura* GetEphemeralStrikeAura(Unit* caster)
    {
        for (size_t i = 501824; i < 501830; i++)
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
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = GetUnitOwner();

        if (!target || target->isDead())
            return;

        if (GetEphemeralStrikeAura(caster))
        {
            int32 procSpell = GetEphemeralStrikeAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->CastSpell(target, procSpell, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_twilight_piercer_aura::HandleApply, EFFECT_1, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_twilight_piercer_aura::HandleRemove, EFFECT_1, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_invis_activator : public AuraScript
{
    PrepareAuraScript(spell_hun_invis_activator);

    void OnApply(AuraEffect const*  /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        caster->CastSpell(caster, SPELL_HUNTER_INVIS_ACTIVATOR, TRIGGERED_FULL_MASK);

        if (AuraEffect* shadowCloak = caster->GetAuraEffectOfRankedSpell(TALENT_HUNTER_SHADOW_CLOAK, EFFECT_0))
            caster->CastCustomSpell(TALENT_HUNTER_SHADOW_CLOAK_BUFF, SPELLVALUE_BASE_POINT0, shadowCloak->GetAmount(), caster, TRIGGERED_FULL_MASK);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (Aura* aura = caster->GetAura(SPELL_HUNTER_INVIS_ACTIVATOR))
            aura->SetDuration(500);

        if (Aura* talentAura = caster->GetAura(TALENT_HUNTER_SHADOW_CLOAK_BUFF))
            talentAura->SetDuration(5000);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_invis_activator::OnApply, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_invis_activator::OnRemove, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_shadow_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_shadow_shot);

    void HandleDamage(SpellEffIndex effIndex)
    {
        Player* caster = GetCaster()->ToPlayer();
        if (Unit* target = GetHitUnit())
        {
            SpellInfo const* value = GetSpellInfo();
            uint32 reduction = value->GetEffect(EFFECT_2).CalcValue(caster);
            caster->ModifySpellCooldown(SPELL_HUNTER_WITHERING_FIRE, reduction);

            int32 damage = GetEffectValue();
            float ap = CalculatePct(int32(GetCaster()->GetTotalAttackPowerValue(RANGED_ATTACK)), damage);
            int32 sp = CalculatePct(int32(GetCaster()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW)), damage);
            int32 sum = std::max<int32>(0, int32(ap + sp));

            damage = GetCaster()->SpellDamageBonusDone(target, GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE, effIndex);
            damage = target->SpellDamageBonusTaken(GetCaster(), GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);

            SetHitDamage(sum);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_shadow_shot::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_hun_shadow_movement : public SpellScript
{
    PrepareSpellScript(spell_hun_shadow_movement);

    void HandleCast()
    {
        Unit* caster = GetCaster();
        Position pos = GetExplTargetUnit()->GetPosition();
        caster->NearTeleportTo(pos);
        caster->CastSpell(caster, SPELL_VISUAL_TELEPORT_EFFECT, TRIGGERED_FULL_MASK);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_hun_shadow_movement::HandleCast);
    }
};

class spell_hun_shadow_stalker_replacer : public AuraScript
{
    PrepareAuraScript(spell_hun_shadow_stalker_replacer);

    void HandleLearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->removeSpell(SPELL_HUNTER_BEAST_LORE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_CALL_PET, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_CALL_STABLED_PET, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_DISMISS_PET, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_FEED_PET, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_MEND_PET, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_REVIVE_PET, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_TAME_BEAST, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_CAMOUFLAGE, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_ARCANE_SHOT, SPEC_MASK_ALL, false);
        target->learnSpell(SPELL_HUNTER_BLEND);
        target->learnSpell(SPELL_HUNTER_SPECTRAL_SHOT);
        target->learnSpell(SPELL_HUNTER_EVANESCENCE);

        if (Pet* pet = target->GetPet())
            target->CastSpell(target, SPELL_HUNTER_INSTANT_DISMISS_PET, TRIGGERED_FULL_MASK);
    }

    void HandleUnlearn(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Player* target = GetCaster()->ToPlayer();

        target->removeSpell(SPELL_HUNTER_BLEND, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_SPECTRAL_SHOT, SPEC_MASK_ALL, false);
        target->removeSpell(SPELL_HUNTER_EVANESCENCE, SPEC_MASK_ALL, false);
        target->learnSpell(SPELL_HUNTER_BEAST_LORE);
        target->learnSpell(SPELL_HUNTER_CALL_PET);
        target->learnSpell(SPELL_HUNTER_CALL_STABLED_PET);
        target->learnSpell(SPELL_HUNTER_DISMISS_PET);
        target->learnSpell(SPELL_HUNTER_FEED_PET);
        target->learnSpell(SPELL_HUNTER_MEND_PET);
        target->learnSpell(SPELL_HUNTER_REVIVE_PET);
        target->learnSpell(SPELL_HUNTER_TAME_BEAST);
        target->learnSpell(SPELL_HUNTER_CAMOUFLAGE);
        target->learnSpell(SPELL_HUNTER_ARCANE_SHOT);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_shadow_stalker_replacer::HandleLearn, EFFECT_0, SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_shadow_stalker_replacer::HandleUnlearn, EFFECT_0, SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_spectral_shot : public SpellScript
{
    PrepareSpellScript(spell_hun_spectral_shot);

    void HandleDamage(SpellEffIndex effIndex)
    {
        Player* caster = GetCaster()->ToPlayer();
        if (Unit* target = GetHitUnit())
        {
            SpellInfo const* value = sSpellMgr->AssertSpellInfo(SPELL_HUNTER_SPECTRAL_SHOT);
            uint32 reduction = value->GetEffect(EFFECT_2).CalcValue(caster);
            uint32 focus = value->GetEffect(EFFECT_1).CalcValue(caster);
            caster->ModifySpellCooldown(SPELL_HUNTER_WITHERING_FIRE, reduction);
            caster->EnergizeBySpell(caster, SPELL_HUNTER_SPECTRAL_SHOT, focus, POWER_FOCUS);


            int32 damage = GetEffectValue();
            float ap = CalculatePct(int32(GetCaster()->GetTotalAttackPowerValue(RANGED_ATTACK)), damage);
            int32 sp = CalculatePct(int32(GetCaster()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_SHADOW)), damage);
            int32 sum = std::max<int32>(0, int32(ap + sp));

            damage = GetCaster()->SpellDamageBonusDone(target, GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE, effIndex);
            damage = target->SpellDamageBonusTaken(GetCaster(), GetSpellInfo(), uint32(damage), SPELL_DIRECT_DAMAGE);

            SetHitDamage(sum);
        }
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_spectral_shot::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_hun_spectral_shot::HandleAfterHit);
    }
};

class spell_hun_relentless_curse : public AuraScript
{
    PrepareAuraScript(spell_hun_relentless_curse);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (Unit* target = eventInfo.GetActionTarget())
            if (Aura* aura = target->GetAura(SPELL_HUNTER_BLACK_CURSE))
                if (aura->GetCasterGUID() == GetCaster()->GetGUID())
                    return true;

        return false;
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_hun_relentless_curse::CheckProc);
    }
};

class spell_hun_improved_blend : public AuraScript
{
    PrepareAuraScript(spell_hun_improved_blend);

    void HandleDummyTick(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Aura* aura = caster->GetAura(SPELL_HUNTER_INVIS_ACTIVATOR))
        {
            int32 health = aurEff->GetAmount();
            int32 focus = aurEff->GetBase()->GetEffect(EFFECT_1)->GetAmount();

            caster->CastCustomSpell(caster, TALENT_HUNTER_IMPROVED_BLEND_PROC, &health, &focus, nullptr, true, nullptr, nullptr);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_hun_improved_blend::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_hun_bring_me_to_life : public AuraScript
{
    PrepareAuraScript(spell_hun_bring_me_to_life);

    void Absorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
    {
        if (roll_chance_i(GetAura()->GetEffect(EFFECT_1)->GetAmount()))
        {
            Unit* target = GetTarget();

            if (!target || target->isDead())
                return;

            int32 remainingHealth = target->GetHealth() - dmgInfo.GetDamage();
            int32 healPct = GetAura()->GetEffect(EFFECT_2)->GetAmount();

            if (remainingHealth <= 0 && !target->HasAura(TALENT_HUNTER_BRING_ME_TO_LIFE_COOLDOWN))
            {
                absorbAmount = dmgInfo.GetDamage();
                int32 healAmount = int32(target->CountPctFromMaxHealth(healPct));

                target->CastSpell(target, TALENT_HUNTER_BRING_ME_TO_LIFE_PROC, TRIGGERED_FULL_MASK);
                target->CastCustomSpell(TALENT_HUNTER_BRING_ME_TO_LIFE_COOLDOWN, SPELLVALUE_BASE_POINT0, healAmount, target, true, nullptr, aurEff);
            }
            else
                absorbAmount = 0;
        }
    }

    void Register() override
    {
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_hun_bring_me_to_life::Absorb, EFFECT_0);
    }
};

class spell_hun_focused_shots : public AuraScript
{
    PrepareAuraScript(spell_hun_focused_shots);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
    {
        GetCaster()->ToPlayer()->ModifySpellCooldown(SPELL_HUNTER_WITHERING_FIRE, aurEff->GetAmount());
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_focused_shots::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class spell_hun_improved_black_curse : public AuraScript
{
    PrepareAuraScript(spell_hun_improved_black_curse);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        if (GetCaster()->IsAlive() && eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0)
        {
            int32 damage = eventInfo.GetDamageInfo()->GetDamage();
            if (damage)
            {
                int32 healPct = aurEff->GetAmount();
                int32 healAmount = CalculatePct(damage, healPct);
                GetCaster()->CastCustomSpell(TALENT_HUNTER_IMPROVED_BLACK_CURSE_HEAL, SPELLVALUE_BASE_POINT0, healAmount, GetCaster(), TRIGGERED_FULL_MASK);
            }
        }
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(spell_hun_improved_black_curse::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 85013 - Lord of Shadows
class spell_hun_lord_of_shadows : public AuraScript
{
    PrepareAuraScript(spell_hun_lord_of_shadows);

    Aura* GetTormentingShadowsAura(Unit* caster)
    {
        for (size_t i = 501572; i < 501578; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetShadowMasteryAura(Unit* caster)
    {
        for (size_t i = 501734; i < 501740; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetTheLastDanceAura(Unit* caster)
    {
        for (size_t i = 501800; i < 501806; i++)
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

        if (GetShadowMasteryAura(caster))
        {
            int32 procSpell = GetShadowMasteryAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, caster);
        }

        if (GetTheLastDanceAura(caster))
        {
            int32 procSpell = GetTheLastDanceAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (GetTormentingShadowsAura(caster))
        {
            int32 procSpell = GetTormentingShadowsAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, caster);
            caster->GetAura(procSpell)->SetStackAmount(20);
        }

    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_lord_of_shadows::HandleApply, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_lord_of_shadows::HandleRemove, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 85010 - Desecrating Shots
class spell_hun_desecrating_shots : public AuraScript
{
    PrepareAuraScript(spell_hun_desecrating_shots);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove Silent Death rune Buff
        for (size_t i = 501640; i < 501646; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_desecrating_shots::OnRemove, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 85009 - Crescent Veil
class spell_hun_crescent_veil : public AuraScript
{
    PrepareAuraScript(spell_hun_crescent_veil);

    Aura* GetMoonlessSkyAura(Unit* caster)
    {
        for (size_t i = 501684; i < 501690; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetVeilOfRenewalAura(Unit* caster)
    {
        for (size_t i = 501702; i < 501708; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetVeiledAmbushAura(Unit* caster)
    {
        for (size_t i = 501714; i < 501720; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    void OnApply(AuraEffect const*  /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (GetMoonlessSkyAura(caster))
        {
            int32 procSpell = GetMoonlessSkyAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, caster);
        }

        if (GetVeilOfRenewalAura(caster))
        {
            int32 procSpell = GetVeilOfRenewalAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
        }

        if (GetVeiledAmbushAura(caster))
        {
            int32 procSpell = GetVeiledAmbushAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, caster);
        }

        // Grant T1 4pc buff
        if (caster->HasAura(T1_HUNTER_DARKRANGER_4PC))
            caster->AddAura(T1_HUNTER_DARKRANGER_4PC_BUFF, caster);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // remove Moonless Night rune Buff
        for (size_t i = 501690; i < 501696; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }

        // remove Veiled Ambush rune Buff
        for (size_t i = 501720; i < 501726; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }

        // Remove T1 4pc buff
        if (caster->HasAura(T1_HUNTER_DARKRANGER_4PC_BUFF))
            caster->RemoveAura(T1_HUNTER_DARKRANGER_4PC_BUFF);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_crescent_veil::OnApply, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_crescent_veil::OnRemove, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 85012 - Blend
class spell_hun_blend : public AuraScript
{
    PrepareAuraScript(spell_hun_blend);

    Aura* GetEvasiveManeuversAura(Unit* caster)
    {
        for (size_t i = 501726; i < 501732; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetShadowMasteryAura(Unit* caster)
    {
        for (size_t i = 501734; i < 501740; i++)
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

        if (GetEvasiveManeuversAura(caster))
        {
            int32 shieldPct = GetEvasiveManeuversAura(caster)->GetEffect(EFFECT_0)->GetAmount();
            int32 maxhealth = caster->GetMaxHealth();
            int32 amount = CalculatePct(maxhealth, shieldPct);

            caster->CastCustomSpell(RUNE_HUNTER_EVASIVE_MANEUVERS_SHIELD, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
        }

        if (GetShadowMasteryAura(caster))
        {
            int32 procSpell = GetShadowMasteryAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, caster);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Handle Evasive Maneuvers' shield duration
        if (Aura* evasiveShield = caster->GetAura(RUNE_HUNTER_EVASIVE_MANEUVERS_SHIELD))
        {
            int32 duration = 0;

            if (GetEvasiveManeuversAura(caster))
                duration = GetEvasiveManeuversAura(caster)->GetEffect(EFFECT_1)->GetAmount();

            evasiveShield->SetDuration(duration);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_blend::HandleApply, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_blend::HandleRemove, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 85014 - Shadow Empowerment
class spell_hun_shadow_empowerment : public AuraScript
{
    PrepareAuraScript(spell_hun_shadow_empowerment);

    Aura* GetShadowGlideAura(Unit* caster)
    {
        for (size_t i = 501882; i < 501888; i++)
        {
            if (caster->HasAura(i))
                return caster->GetAura(i);
        }

        return nullptr;
    }

    Aura* GetGLoomAura(Unit* caster)
    {
        for (size_t i = 501894; i < 501900; i++)
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

        if (GetShadowGlideAura(caster))
        {
            int32 procSpell = GetShadowGlideAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, caster);
        }

        if (GetGLoomAura(caster))
        {
            int32 procSpell = GetGLoomAura(caster)->GetEffect(EFFECT_0)->GetAmount();

            caster->AddAura(procSpell, caster);
        }
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Shadow Glide Rune Buff
        for (size_t i = 501888; i < 501894; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }

        // Remove Gloom Rune Buff
        for (size_t i = 501900; i < 501906; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_shadow_empowerment::HandleApply, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_shadow_empowerment::HandleRemove, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 85002 - Withering Fire Aura
class spell_hun_withering_fire_aura : public AuraScript
{
    PrepareAuraScript(spell_hun_withering_fire_aura);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        // Remove Echoing Fire Rune Buff
        for (size_t i = 501924; i < 501930; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_withering_fire_aura::HandleApply, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_hun_withering_fire_aura::HandleRemove, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 80188 - Wildfire Bomb
class spell_hun_wildfire_bomb : public SpellScript
{
    PrepareSpellScript(spell_hun_wildfire_bomb);

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
        if (Aura* buff = caster->GetAura(T1_HUNTER_SURVIVAL_4PC_BUFF))
        {
            Unit* mainTarget = ObjectAccessor::GetUnit(*caster, caster->GetTarget());

            if (mainTarget && target == mainTarget)
            {
                int32 damageIncrease = buff->GetEffect(EFFECT_0)->GetAmount();
                AddPct(damage, damageIncrease);
            }
        }

        SetHitDamage(damage);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_hun_wildfire_bomb::HandleHit, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_hun_animal_companion_check : public AuraScript
{
    PrepareAuraScript(spell_hun_animal_companion_check);

    void HandleOnEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Pet* pet = GetUnitOwner()->ToPet();

        if (!pet)
            return;

        Player* player = pet->GetOwner();

        if (!player)
            return;

        if (player->getClass() == CLASS_HUNTER && player->HasAura(SPELL_HUNTER_ANIMAL_COMPANION_TALENT))
        {
            PetStable* petStable = player->GetPetStable();

            if (!petStable)
                return;

            auto firstPet = petStable->StabledPets.at(0);

            if (!firstPet)
                return;

            Position const& pos = player->GetPosition();
            SummonPropertiesEntry const* properties = sSummonPropertiesStore.LookupEntry(61);
            uint32 displayId = firstPet->DisplayId;
            Creature* summon = player->SummonCreature(600612, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60 * IN_MILLISECONDS, 0, properties);
            summon->SetDisplayId(displayId);
            ApplySecondaryPet(summon, firstPet, player);
        }
    }

    void HandleOnEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Pet* pet = GetUnitOwner()->ToPet();

        if (!pet)
            return;

        Player* player = pet->GetOwner();

        if (!player)
            return;

        if (player->getClass() == CLASS_HUNTER && player->HasAura(SPELL_HUNTER_ANIMAL_COMPANION_TALENT))
        {
            auto summonedUnits = player->m_Controlled;

            for (const auto& unit : summonedUnits)
                if (unit->GetCharmInfo() && unit->GetEntry() == 600612)
                    unit->ToCreature()->DespawnOrUnsummon();
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_animal_companion_check::HandleOnEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_animal_companion_check::HandleOnEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_hun_expert_of_the_wilds : public AuraScript
{
    PrepareAuraScript(spell_hun_expert_of_the_wilds);

    void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* caster = GetUnitOwner()->ToPlayer();

        caster->learnSpell(SPELL_HUNTER_WILDFIRE_BOMB);
        caster->learnSpell(SPELL_HUNTER_ASPECT_OF_THE_EAGLE);
        caster->learnSpell(SPELL_HUNTER_DEATH_CHAKRAM);
    }

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Player* caster = GetUnitOwner()->ToPlayer();

        caster->removeSpell(SPELL_HUNTER_WILDFIRE_BOMB, SPEC_MASK_ALL, false);
        caster->removeSpell(SPELL_HUNTER_ASPECT_OF_THE_EAGLE, SPEC_MASK_ALL, false);
        caster->removeSpell(SPELL_HUNTER_DEATH_CHAKRAM, SPEC_MASK_ALL, false);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_hun_expert_of_the_wilds::HandleApply, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_hun_expert_of_the_wilds::HandleRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_hunter_spell_scripts()
{
    RegisterSpellScript(spell_hun_check_pet_los);
    RegisterSpellScript(spell_hun_cower);
    RegisterSpellScript(spell_hun_wyvern_sting);
    RegisterSpellScript(spell_hun_animal_handler);
    RegisterSpellScript(spell_hun_generic_scaling);
    RegisterSpellScript(spell_hun_taming_the_beast);
    RegisterSpellScript(spell_hun_glyph_of_arcane_shot);
    //RegisterSpellScript(spell_hun_aspect_of_the_beast);
    RegisterSpellScript(spell_hun_ascpect_of_the_viper);
    RegisterSpellScript(spell_hun_chimera_shot);
    RegisterSpellScript(spell_hun_disengage);
    RegisterSpellScript(spell_hun_improved_mend_pet);
    RegisterSpellScript(spell_hun_invigoration);
    RegisterSpellScript(spell_hun_last_stand_pet);
    RegisterSpellScript(spell_hun_masters_call);
    RegisterSpellScript(spell_hun_misdirection);
    RegisterSpellScript(spell_hun_misdirection_proc);
    RegisterSpellScript(spell_hun_pet_carrion_feeder);
    RegisterSpellScript(spell_hun_pet_heart_of_the_phoenix);
    RegisterSpellScript(spell_hun_readiness);
    RegisterSpellScript(spell_hun_scatter_shot);
    RegisterSpellScript(spell_hun_sniper_training);
    RegisterSpellScript(spell_hun_tame_beast);
    RegisterSpellScript(spell_hun_viper_attack_speed);
    RegisterSpellScript(spell_hun_volley_trigger);
    RegisterSpellScript(spell_hun_lock_and_load);
    RegisterSpellScript(spell_hun_intimidation);
    RegisterSpellScript(spell_hun_bestial_wrath);
    RegisterSpellScript(spell_hun_predators_thirst);
    RegisterSpellScript(spell_hun_aspect_cheetah);
    RegisterSpellScript(spell_hun_bestial_apply);
    RegisterSpellScript(spell_hun_black_arrow_reset);
    RegisterSpellScript(spell_hun_chimaera_trigger);
    RegisterSpellScript(spell_hun_steady_shot_concussive);
    RegisterSpellScript(spell_hun_explosive_shot);
    RegisterSpellScript(spell_hun_kill_command);
    RegisterSpellScript(spell_hun_mongoose_fury);
    RegisterSpellScript(spell_hun_readiness_trigger);
    RegisterSpellScript(spell_hun_trueshot);
    //RegisterSpellScript(spell_hun_bear_applier);
    RegisterSpellScript(spell_hun_aspect_turtle);
    RegisterSpellScript(spell_hun_survival_fittest);
    RegisterSpellScript(spell_hun_camouflage);
    RegisterSpellScript(spell_hun_death_chakram);
    RegisterSpellScript(spell_hun_cobra_shot);
    RegisterSpellScript(spell_hun_barbed_shot);
    RegisterSpellScript(spell_hun_murder_crows_reset);
    RegisterSpellScript(spell_hun_murder_crows_check);
    RegisterSpellScript(spell_hun_bloodshed);
    RegisterSpellScript(spell_hun_lone_wolf);
    RegisterSpellScript(spell_hun_dire_beast);
    RegisterSpellScript(spell_hun_call_of_wild);
    RegisterSpellScript(spell_hun_call_of_wild_periodic);
    RegisterSpellScript(spell_hun_harpoon);
    RegisterSpellScript(spell_hun_fury_eagle);
    RegisterSpellScript(spell_hun_flanking_strike);
    RegisterSpellScript(spell_hun_coordinated_assault);
    RegisterSpellScript(spell_hun_coordinated_bleed);
    RegisterSpellScript(spell_hun_spearhead);
    RegisterSpellScript(spell_hun_spearhead_buff);
    RegisterSpellScript(spell_hun_cobra_sting);
    RegisterSpellScript(spell_hun_aspect_mastery_crit);
    RegisterSpellScript(spell_hun_aspect_mastery_ranged_damage);
    RegisterSpellScript(spell_hun_wild_call);
    RegisterSpellScript(spell_hun_beast_within);
    //RegisterSpellScript(spell_hun_animal_companion);
    //RegisterSpellScript(spell_hun_animal_companion_dismiss_pet);
    RegisterSpellScript(spell_hun_arctic_bola);
    RegisterSpellScript(spell_hun_careful_aim);
    RegisterSpellScript(spell_hun_aimed_shot);
    RegisterSpellScript(spell_hun_rabid_mongoose);
    RegisterSpellScript(spell_hun_harpoon_reset);
    RegisterSpellScript(spell_hun_hunters_prey);
    RegisterSpellScript(spell_hun_thrill_of_hunt);
    RegisterSpellScript(spell_hun_noxious_stings);
    RegisterSpellScript(spell_hun_hunting_party);
    RegisterSpellScript(spell_hunter_stampeded);
    RegisterSpellScript(spell_hun_backshot);
    RegisterSpellScript(spell_hun_black_curse_reset);
    RegisterSpellScript(spell_hun_twilight_piercer);
    RegisterSpellScript(spell_hun_twilight_piercer_aura);
    RegisterSpellScript(spell_hun_invis_activator);
    RegisterSpellScript(spell_hun_shadow_shot);
    RegisterSpellScript(spell_hun_shadow_movement);
    RegisterSpellScript(spell_hun_shadow_stalker_replacer);
    RegisterSpellScript(spell_hun_spectral_shot);
    RegisterSpellScript(spell_hun_relentless_curse);
    RegisterSpellScript(spell_hun_improved_blend);
    RegisterSpellScript(spell_hun_bring_me_to_life);
    RegisterSpellScript(spell_hun_focused_shots);
    RegisterSpellScript(spell_hun_improved_black_curse);
    RegisterSpellScript(spell_hun_lord_of_shadows);
    RegisterSpellScript(spell_hun_desecrating_shots);
    RegisterSpellScript(spell_hun_crescent_veil);
    RegisterSpellScript(spell_hun_blend);
    RegisterSpellScript(spell_hun_shadow_empowerment);
    RegisterSpellScript(spell_hun_withering_fire_aura);
    RegisterSpellScript(spell_hun_wildfire_bomb);
    RegisterSpellScript(spell_hun_animal_companion_check);
    RegisterSpellScript(spell_hun_expert_of_the_wilds);
    RegisterSpellScript(spell_hun_withering_fire_energy);
    RegisterSpellScript(spell_hun_beast_applier);

    //new Hunter_AllMapScript();
    new npc_hunter_spell_stampeded();
}
