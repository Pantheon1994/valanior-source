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

enum ShamanSpells
{
    // Spells
    SPELL_SHAMAN_ANCESTRAL_GUIDANCE = 84010,
    SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM = 84079,
    SPELL_SHAMAN_ASCENDANCE_AIR = 84035,
    SPELL_SHAMAN_ASCENDANCE_AIR_AURA = 84036,
    SPELL_SHAMAN_ASCENDANCE_EARTH = 84113,
    SPELL_SHAMAN_ASCENDANCE_FLAME = 84019,
    SPELL_SHAMAN_ASCENDANCE_WATER = 84040,
    SPELL_SHAMAN_ASCENDANCE_WATER_AURA = 84041,
    SPELL_SHAMAN_ASTRAL_RECALL = 556,
    SPELL_SHAMAN_ASTRAL_SHIFT = 84007,
    SPELL_SHAMAN_BLOODLUST = 2825,
    SPELL_SHAMAN_CAPACITOR_TOTEM = 84069,
    SPELL_SHAMAN_CHAIN_HEAL = 55459,
    SPELL_SHAMAN_CHAIN_LIGHTNING = 49271,
    SPELL_SHAMAN_CHAIN_LIGHTNING_OVERLOAD = 84056,
    SPELL_SHAMAN_CLOUDBURST_TOTEM = 84082,
    SPELL_SHAMAN_CRASH_LIGHTNING = 84032,
    SPELL_SHAMAN_DOOM_WINDS = 84029,
    SPELL_SHAMAN_DOWNPOUR = 84046,
    SPELL_SHAMAN_EARTH_ELEMENTAL = 2062,
    SPELL_SHAMAN_EARTH_SHOCK = 49231,
    SPELL_SHAMAN_EARTHEN_SHIELD = 49284,
    SPELL_SHAMAN_EARTHEN_SHIELD_HEAL = 379,
    SPELL_SHAMAN_EARTHBIND_TOTEM = 2484,
    SPELL_SHAMAN_EARTHQUAKE = 84014,
    SPELL_SHAMAN_EARTHQUAKE_DAMAGE = 84015,
    SPELL_SHAMAN_ELEMENTAL_BLAST = 84022,
    SPELL_SHAMAN_ELEMENTAL_MASTERY = 16166,
    SPELL_SHAMAN_FERAL_SPIRIT = 51533,
    SPELL_SHAMAN_FIERY_STAMP = 84121,
    SPELL_SHAMAN_FIRE_ELEMENTAL = 2894,
    SPELL_SHAMAN_FLAME_SHOCK = 49233,
    SPELL_SHAMAN_FOCUS_FOE = 84116,
    SPELL_SHAMAN_FOCUS_FOE_STORM = 84117,
    SPELL_SHAMAN_FURY_OF_THE_ELEMENTS = 84106,
    SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_EARTH = 84110,
    SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_EARTH_GRIP = 84111,
    SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_FIRE = 84107,
    SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_STORM = 84108,
    SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_STORM_ECHO = 84109,
    SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_WATER = 84112,
    SPELL_SHAMAN_GHOST_WOLF = 2645,
    SPELL_SHAMAN_GROUNDING_TOTEM = 8177,
    SPELL_SHAMAN_GUST_OF_WIND = 84061,
    SPELL_SHAMAN_HEALING_RAIN = 84037,
    SPELL_SHAMAN_HEALING_SURGE = 84004,
    SPELL_SHAMAN_HEALING_TIDE_TOTEM = 84076,
    SPELL_SHAMAN_HEALING_WAVE = 49273,
    SPELL_SHAMAN_HEX = 51514,
    SPELL_SHAMAN_INVOKE_ESSENCE = 84102,
    SPELL_SHAMAN_INVOKE_ESSENCE_EARTH = 84104,
    SPELL_SHAMAN_INVOKE_ESSENCE_FIRE = 84103,
    SPELL_SHAMAN_INVOKE_ESSENCE_WATER = 84105,
    SPELL_SHAMAN_LAVA_BURST = 60043,
    SPELL_SHAMAN_LAVA_LASH = 60103,
    SPELL_SHAMAN_LIGHTNING_BOLT = 49238,
    SPELL_SHAMAN_LIGHTNING_BOLT_OVERLOAD = 84057,
    SPELL_SHAMAN_LAVA_BEAM_OVERLOAD = 84058,
    SPELL_SHAMAN_LIGHTNING_LASSO = 84013,
    SPELL_SHAMAN_LIGHTNING_SHIELD = 49281,
    SPELL_SHAMAN_MANA_TIDE_TOTEM = 16190,
    SPELL_SHAMAN_NATURES_SWIFTNESS = 16188,
    SPELL_SHAMAN_OVERCHARGE = 84128,
    SPELL_SHAMAN_REINCARNATION = 20608,
    SPELL_SHAMAN_RIPTIDE = 61301,
    SPELL_SHAMAN_SPIRIT_LINK_TOTEM = 84073,
    SPELL_SHAMAN_SPIRIT_WALK = 84008,
    SPELL_SHAMAN_STONECLAW_TOTEM = 58582,
    SPELL_SHAMAN_STORM_ELEMENTAL = 84084,
    SPELL_SHAMAN_STORMBRAND_TOTEM = 84244,
    SPELL_SHAMAN_STORMKEEPER = 84018,
    SPELL_SHAMAN_STORMSTRIKE = 17364,
    SPELL_SHAMAN_STORMSTRIKE_PHYSICAL = 32175,
    SPELL_SHAMAN_STORMSTRIKE_NATURE = 32176,
    SPELL_SHAMAN_THUNDERSTORM = 59159,
    SPELL_SHAMAN_TIDAL_FORCE = 55198,
    SPELL_SHAMAN_WATER_SHIELD = 57960,
    SPELL_SHAMAN_WATERY_GRAVE = 84125,
    SPELL_SHAMAN_WELLSPRING = 84044,
    SPELL_SHAMAN_WIND_SHEAR = 57994,
    SPELL_SHAMAN_WINDFURY_WEAPON_MAINHAND = 25504,
    SPELL_SHAMAN_WINDFURY_WEAPON_OFFHAND = 33750,

    // Forms
    SPELL_SHAMAN_SPIRIT_OF_FIRE = 84089,
    SPELL_SHAMAN_SPIRIT_OF_FIRE_PASSIVE = 84136,
    SPELL_SHAMAN_SPIRIT_OF_STORM = 84090,
    SPELL_SHAMAN_SPIRIT_OF_STORM_HASTE = 84096,
    SPELL_SHAMAN_SPIRIT_OF_STORM_PASSIVE = 84137,
    SPELL_SHAMAN_SPIRIT_OF_EARTH = 84091,
    SPELL_SHAMAN_SPIRIT_OF_EARTH_PASSIVE = 84138,
    SPELL_SHAMAN_SPIRIT_OF_WATER = 84092,
    SPELL_SHAMAN_SPIRIT_OF_WATER_PASSIVE = 84139,
    SPELL_SHAMAN_SPIRIT_OF_STORM_PROC = 84095,
    SPELL_SHAMAN_SPIRIT_OF_WATER_SHIELD = 84098,
    SPELL_SHAMAN_SPIRIT_OF_WATER_REGEN = 84100,

    // Passive
    SPELL_SHAMAN_MAELSTROM_WEAPON = 84053,
    SPELL_SHAMAN_MAELSTROM_WEAPON_PROC = 53817,

    // Talents
    TALENT_SHAMAN_TIDAL_WAVES_BUFF = 53390,

    // Runes
    RUNE_SHAMAN_VOLCANIC_INFERNO_DOT = 1000178,
    RUNE_SHAMAN_RESURGENCE_ENERGIZE = 1000342,
    RUNE_SHAMAN_IMPROVED_EARTHLIVING_WEAPON_HEAL = 1000454,
    RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_FIRE = 1000462,
    RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_FROST = 1000463,
    RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_NATURE = 1000464,
    RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_DEBUFF = 1000465,
    RUNE_SHAMAN_FORCEFUL_WINDS_BUFF = 1000484,
    RUNE_SHAMAN_FORCEFUL_WINDS_DEBUFF = 1000485,
    RUNE_SHAMAN_LIGHTNING_ROD_AOE = 1000528,
    RUNE_SHAMAN_LIGHTNING_ROD_DAMAGE = 1000529,
    RUNE_SHAMAN_AFTERSHOCK_ENERGIZE = 1000622,
    RUNE_SHAMAN_MOLTEN_ASSAULT_AOE = 1000668,
    RUNE_SHAMAN_LASHING_FLAMES_DAMAGE = 1000706,
    RUNE_SHAMAN_LEGACY_OF_THE_FROST_WITCH_LISTENER = 1000816,
    RUNE_SHAMAN_STORMBLAST_DAMAGE = 1000842,
    RUNE_SHAMAN_ELEMENTAL_SPIRITS_MOLTEN_WEAPON_DOT = 1000910,
    RUNE_SHAMAN_EARTHEN_WALL_SHIELD = 1000966,
    RUNE_SHAMAN_PRIMAL_TIDE_CORE_LISTENER = 1001016,
    RUNE_SHAMAN_PRIMAL_TIDE_CORE_AOE = 1001017,
    RUNE_SHAMAN_DELUGE_HEAL = 1001050,
    RUNE_SHAMAN_THUNDER_ROD_AOE = 1001206,
    RUNE_SHAMAN_THUNDER_ROD_DAMAGE = 1001207,
    RUNE_SHAMAN_ELEMENTAL_CLEANSING_DOT = 1001352,

    // Summons
    SUMMON_SHAMAN_EARTH_ELEMENTAL = 15352,
    SUMMON_SHAMAN_FIRE_ELEMENTAL = 15438,
    SUMMON_SHAMAN_STORM_ELEMENTAL = 400408,
    SUMMON_SHAMAN_FERAL_SPIRITS = 29264,
};

class rune_sha_tidebringer : public AuraScript
{
    PrepareAuraScript(rune_sha_tidebringer);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 procSpell = GetSpellInfo()->GetEffect(EFFECT_0).TriggerSpell;
        int32 maxCharges = aurEff->GetAmount();

        if (Aura* proc = caster->GetAura(procSpell))
        {
            int32 currentCharges = proc->GetCharges();
            proc->Remove();
            caster->AddAura(procSpell, caster);
        }
        else
        {
            caster->AddAura(procSpell, caster);
            caster->GetAura(procSpell)->ModCharges(-1);
        }
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_tidebringer::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class rune_sha_lava_surge : public AuraScript
{
    PrepareAuraScript(rune_sha_lava_surge);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
            player->RemoveSpellCooldown(SPELL_SHAMAN_LAVA_BURST, true);
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(rune_sha_lava_surge::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

class rune_sha_fiery_demise : public AuraScript
{
    PrepareAuraScript(rune_sha_fiery_demise);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            player->ModifySpellCooldown(SPELL_SHAMAN_FIRE_ELEMENTAL, -aurEff->GetAmount());
            player->ModifySpellCooldown(SPELL_SHAMAN_STORM_ELEMENTAL, -aurEff->GetAmount());
        }

    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(rune_sha_fiery_demise::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_volcanic_inferno : public AuraScript
{
    PrepareAuraScript(rune_sha_volcanic_inferno);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
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

        if (damage == 0)
            return;

        float amount = CalculatePct(damage, aurEff->GetAmount());
        int32 totalTick = sSpellMgr->AssertSpellInfo(RUNE_SHAMAN_VOLCANIC_INFERNO_DOT)->GetMaxTicks();
        amount /= totalTick;

        caster->CastCustomSpell(RUNE_SHAMAN_VOLCANIC_INFERNO_DOT, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_volcanic_inferno::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_volcanic_inferno::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_magma_burst : public AuraScript
{
    PrepareAuraScript(rune_sha_magma_burst);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        if (Aura* flameShock = target->GetAura(SPELL_SHAMAN_FLAME_SHOCK))
        {
            int32 newDuration = std::min<int32>(flameShock->GetMaxDuration(), flameShock->GetDuration() + aurEff->GetAmount());
            flameShock->SetDuration(newDuration);
            flameShock->GetEffect(EFFECT_1)->ResetPeriodic();
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_magma_burst::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_magma_burst::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_flash_of_lightning : public AuraScript
{
    PrepareAuraScript(rune_sha_flash_of_lightning);

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 cooldownReduction = aurEff->GetAmount();

        if (Player* player = caster->ToPlayer())
        {
            std::vector<uint32> natureSpells =
            {
                SPELL_SHAMAN_ASTRAL_RECALL, SPELL_SHAMAN_BLOODLUST,SPELL_SHAMAN_CHAIN_LIGHTNING, SPELL_SHAMAN_EARTH_ELEMENTAL, SPELL_SHAMAN_EARTHBIND_TOTEM,
                SPELL_SHAMAN_GROUNDING_TOTEM, SPELL_SHAMAN_HEX, SPELL_SHAMAN_REINCARNATION, SPELL_SHAMAN_STONECLAW_TOTEM, SPELL_SHAMAN_WIND_SHEAR,
                SPELL_SHAMAN_ELEMENTAL_MASTERY, SPELL_SHAMAN_THUNDERSTORM, SPELL_SHAMAN_FERAL_SPIRIT, SPELL_SHAMAN_MANA_TIDE_TOTEM, SPELL_SHAMAN_NATURES_SWIFTNESS,
                SPELL_SHAMAN_TIDAL_FORCE, SPELL_SHAMAN_ANCESTRAL_GUIDANCE, SPELL_SHAMAN_ASTRAL_SHIFT, SPELL_SHAMAN_CAPACITOR_TOTEM, SPELL_SHAMAN_GUST_OF_WIND,
                SPELL_SHAMAN_LIGHTNING_LASSO, SPELL_SHAMAN_SPIRIT_WALK, SPELL_SHAMAN_ELEMENTAL_BLAST, SPELL_SHAMAN_STORM_ELEMENTAL, SPELL_SHAMAN_STORMKEEPER,
                SPELL_SHAMAN_CRASH_LIGHTNING, SPELL_SHAMAN_DOOM_WINDS, SPELL_SHAMAN_ASCENDANCE_WATER, SPELL_SHAMAN_ANCESTRAL_PROTECTION_TOTEM, SPELL_SHAMAN_CLOUDBURST_TOTEM,
                SPELL_SHAMAN_DOWNPOUR, SPELL_SHAMAN_HEALING_RAIN, SPELL_SHAMAN_HEALING_TIDE_TOTEM, SPELL_SHAMAN_SPIRIT_LINK_TOTEM, SPELL_SHAMAN_WELLSPRING,
                SPELL_SHAMAN_FOCUS_FOE, SPELL_SHAMAN_FURY_OF_THE_ELEMENTS, SPELL_SHAMAN_OVERCHARGE, SPELL_SHAMAN_STORMBRAND_TOTEM, SPELL_SHAMAN_WATERY_GRAVE
            };

            for (uint32 spellId : natureSpells)
            {
                if (!player->HasSpell(spellId))
                    continue;

                player->ModifySpellCooldown(spellId, -cooldownReduction);
            }
        }
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(rune_sha_flash_of_lightning::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_pulsating_lightning : public AuraScript
{
    PrepareAuraScript(rune_sha_pulsating_lightning);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!caster->HasAura(SPELL_SHAMAN_LIGHTNING_SHIELD))
            return;

        if (!caster->IsInCombat())
            return;

        caster->CastSpell(caster, aurEff->GetAmount(), TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_pulsating_lightning::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class rune_sha_flowing_streams : public AuraScript
{
    PrepareAuraScript(rune_sha_flowing_streams);

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

        caster->CastSpell(target, SPELL_SHAMAN_HEALING_SURGE, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_flowing_streams::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_flowing_streams::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_undulation : public AuraScript
{
    PrepareAuraScript(rune_sha_undulation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetProcSpell();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (healingWaveQte == 3)
            healingWaveQte = 0;

        if (healingSurgeQte == 3)
            healingSurgeQte = 0;

        int32 procSpell = eventInfo.GetProcSpell()->GetSpellInfo()->Id;

        if (procSpell == SPELL_SHAMAN_HEALING_WAVE)
        {
            healingWaveQte++;

            if (healingWaveQte == 2)
                caster->AddAura(GetEffect(EFFECT_1)->GetAmount(), caster);
        }

        if (procSpell == SPELL_SHAMAN_HEALING_SURGE)
        {
            healingSurgeQte++;

            if (healingSurgeQte == 2)
                caster->AddAura(GetEffect(EFFECT_2)->GetAmount(), caster);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_undulation::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_undulation::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
private:
    int32 healingWaveQte = 0;
    int32 healingSurgeQte = 0;
};

class rune_sha_resurgence : public AuraScript
{
    PrepareAuraScript(rune_sha_resurgence);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->HasAttribute(SPELL_ATTR4_ALLOW_CAST_WHILE_CASTING))
            return false;

        return eventInfo.GetProcSpell();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 manaPct = 0;
        int32 procSpell = eventInfo.GetProcSpell()->GetSpellInfo()->Id;

        if (procSpell == SPELL_SHAMAN_HEALING_WAVE)
            manaPct = aurEff->GetAmount();

        if (procSpell == SPELL_SHAMAN_HEALING_SURGE || procSpell == SPELL_SHAMAN_RIPTIDE)
            manaPct = GetEffect(EFFECT_1)->GetAmount();

        if (procSpell == SPELL_SHAMAN_CHAIN_HEAL)
            manaPct = GetEffect(EFFECT_2)->GetAmount();

        if (manaPct == 0)
            return;

        int32 maxMana = caster->GetMaxPower(POWER_MANA);
        float amount = CalculatePct(maxMana, manaPct);
        amount /= 100;

        caster->CastCustomSpell(RUNE_SHAMAN_RESURGENCE_ENERGIZE, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_resurgence::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_resurgence::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_high_tide : public AuraScript
{
    PrepareAuraScript(rune_sha_high_tide);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (eventInfo.GetSpellInfo()->PowerType != POWER_MANA)
            return;

        int32 manaThreshold = aurEff->GetAmount();
        int32 procSpell = GetEffect(EFFECT_1)->GetAmount();
        manaSpent += eventInfo.GetSpellInfo()->CalcPowerCost(caster, eventInfo.GetSchoolMask());

        if (manaSpent < manaThreshold)
            return;

        manaSpent -= manaThreshold;
        caster->AddAura(procSpell, caster);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_high_tide::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_high_tide::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
private:
    int32 manaSpent = 0;
};

class rune_sha_spirit_wolf : public AuraScript
{
    PrepareAuraScript(rune_sha_spirit_wolf);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!caster->HasAura(SPELL_SHAMAN_GHOST_WOLF))
            return;

        caster->CastSpell(caster, aurEff->GetAmount(), TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_spirit_wolf::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class rune_sha_rejuvenating_wolf : public AuraScript
{
    PrepareAuraScript(rune_sha_rejuvenating_wolf);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!caster->HasAura(SPELL_SHAMAN_GHOST_WOLF))
            return;

        caster->CastSpell(caster, aurEff->GetAmount(), TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_rejuvenating_wolf::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class rune_sha_regenerating_wolf : public AuraScript
{
    PrepareAuraScript(rune_sha_regenerating_wolf);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!caster->HasAura(SPELL_SHAMAN_GHOST_WOLF))
            return;

        caster->CastSpell(caster, aurEff->GetAmount(), TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_regenerating_wolf::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class rune_sha_brimming_with_life : public AuraScript
{
    PrepareAuraScript(rune_sha_brimming_with_life);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->GetHealthPct() < 100)
            return;

        if (Player* player = caster->ToPlayer())
        {
            if (!player->HasSpellCooldown(SPELL_SHAMAN_REINCARNATION))
                return;

            player->ModifySpellCooldown(SPELL_SHAMAN_REINCARNATION, -aurEff->GetAmount());
        }
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_brimming_with_life::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class rune_sha_elemental_equilibrium : public AuraScript
{
    PrepareAuraScript(rune_sha_elemental_equilibrium);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (eventInfo.GetDamageInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_FIRE)
            caster->AddAura(RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_FIRE, caster);

        if (eventInfo.GetDamageInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_FROST)
            caster->AddAura(RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_FROST, caster);

        if (eventInfo.GetDamageInfo()->GetSchoolMask() == SPELL_SCHOOL_MASK_NATURE)
            caster->AddAura(RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_NATURE, caster);

        if (!caster->HasAura(RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_FIRE) ||
            !caster->HasAura(RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_FROST) ||
            !caster->HasAura(RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_NATURE))
            return;

        if (caster->HasAura(RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_DEBUFF))
            return;

        caster->AddAura(aurEff->GetAmount(), caster);
        caster->AddAura(RUNE_SHAMAN_ELEMENTAL_EQUILIBRIUM_DEBUFF, caster);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_elemental_equilibrium::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_elemental_equilibrium::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_forceful_winds : public AuraScript
{
    PrepareAuraScript(rune_sha_forceful_winds);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(RUNE_SHAMAN_FORCEFUL_WINDS_DEBUFF))
            return;

        if (!caster->HasAura(RUNE_SHAMAN_FORCEFUL_WINDS_BUFF))
            caster->CastSpell(caster, RUNE_SHAMAN_FORCEFUL_WINDS_BUFF, TRIGGERED_FULL_MASK);

        
        
        caster->CastSpell(caster, aurEff->GetAmount(), TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_forceful_winds::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_forceful_winds::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_forceful_winds_remove : public AuraScript
{
    PrepareAuraScript(rune_sha_forceful_winds_remove);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        caster->AddAura(RUNE_SHAMAN_FORCEFUL_WINDS_DEBUFF, caster);

        for (size_t i = 1000478; i < 1000484; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(rune_sha_forceful_winds_remove::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class rune_sha_primordial_bond : public AuraScript
{
    PrepareAuraScript(rune_sha_primordial_bond);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        hasElemental = false;

        for (Unit::ControlSet::iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
        {
            if ((*itr)->GetEntry() == SUMMON_SHAMAN_FIRE_ELEMENTAL ||
                (*itr)->GetEntry() == SUMMON_SHAMAN_EARTH_ELEMENTAL ||
                (*itr)->GetEntry() == SUMMON_SHAMAN_STORM_ELEMENTAL &&
                (*itr)->IsAlive())
                hasElemental = true;
        }

        int32 buffAura = aurEff->GetAmount();

        if (hasElemental == false)
        {
            if (caster->HasAura(buffAura))
                caster->RemoveAura(buffAura);
        }
        else
        {
            if (!caster->HasAura(buffAura))
                caster->AddAura(buffAura, caster);
        }

    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        for (size_t i = 1000498; i < 1000504; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_primordial_bond::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(rune_sha_primordial_bond::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
private:
    bool hasElemental = false;
};

class rune_sha_pulsating_water : public AuraScript
{
    PrepareAuraScript(rune_sha_pulsating_water);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!caster->HasAura(SPELL_SHAMAN_WATER_SHIELD))
            return;

        caster->CastSpell(caster, aurEff->GetAmount(), TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_pulsating_water::HandleProc, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class rune_sha_lightning_rod : public AuraScript
{
    PrepareAuraScript(rune_sha_lightning_rod);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetSpellInfo();
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

        if (damage == 0)
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;
        int32 LightningRod = aurEff->GetAmount();

        if (spellID == SPELL_SHAMAN_EARTH_SHOCK || spellID == SPELL_SHAMAN_EARTHQUAKE_DAMAGE || spellID == SPELL_SHAMAN_ELEMENTAL_BLAST)
            caster->CastSpell(target, LightningRod, TRIGGERED_FULL_MASK);

        else if (spellID == SPELL_SHAMAN_LIGHTNING_BOLT || spellID == SPELL_SHAMAN_CHAIN_LIGHTNING)
        {
            GetEffect(EFFECT_1)->SetAmount(eventInfo.GetDamageInfo()->GetDamage());
            caster->CastSpell(caster, RUNE_SHAMAN_LIGHTNING_ROD_AOE, TRIGGERED_FULL_MASK);
        }

    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_lightning_rod::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_lightning_rod::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_lightning_rod_aoe : public SpellScript
{
    PrepareSpellScript(rune_sha_lightning_rod_aoe);

    Aura* GetRuneAura(Unit* caster)
    {
        for (size_t i = 1000516; i < 1000522; i++)
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

        if (!GetRuneAura(caster))
            return;

        int32 lightningRod = GetRuneAura(caster)->GetEffect(EFFECT_0)->GetAmount();
        int32 damage = GetRuneAura(caster)->GetEffect(EFFECT_1)->GetAmount();

        for (auto const& object : targets)
        {
            Unit* target = object->ToUnit();

            if (target->isDead() || !target->HasAura(lightningRod))
                continue;

            int32 damagePct = target->GetAura(lightningRod)->GetEffect(EFFECT_0)->GetAmount();
            int32 amount = CalculatePct(damage, damagePct);

            caster->CastCustomSpell(RUNE_SHAMAN_LIGHTNING_ROD_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(rune_sha_lightning_rod_aoe::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class rune_sha_echoes_of_the_great_sundering : public AuraScript
{
    PrepareAuraScript(rune_sha_echoes_of_the_great_sundering);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;
        int32 earthShockBuff = aurEff->GetAmount();
        int32 elementalBlastBuff = GetEffect(EFFECT_1)->GetAmount();

        if (spellID == SPELL_SHAMAN_EARTH_SHOCK)
            caster->AddAura(earthShockBuff, caster);
        else if (spellID == SPELL_SHAMAN_ELEMENTAL_BLAST)
            caster->AddAura(elementalBlastBuff, caster);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_echoes_of_the_great_sundering::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_echoes_of_the_great_sundering::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_electrified_shocks_remove : public AuraScript
{
    PrepareAuraScript(rune_sha_electrified_shocks_remove);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        for (size_t i = 1000586; i < 1000592; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(rune_sha_electrified_shocks_remove::OnRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
    }
};

class rune_sha_aftershock : public AuraScript
{
    PrepareAuraScript(rune_sha_aftershock);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 amount = eventInfo.GetSpellInfo()->CalcPowerCost(caster, eventInfo.GetSpellInfo()->GetSchoolMask());

        caster->CastCustomSpell(RUNE_SHAMAN_AFTERSHOCK_ENERGIZE, SPELLVALUE_BASE_POINT0, amount, caster, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_aftershock::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_aftershock::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_deeply_rooted_fire : public AuraScript
{
    PrepareAuraScript(rune_sha_deeply_rooted_fire);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 baseDuration = GetEffect(EFFECT_1)->GetAmount();
        int32 increasedDuration = GetEffect(EFFECT_2)->GetAmount();

        if (Aura* ascendance = caster->GetAura(SPELL_SHAMAN_ASCENDANCE_FLAME))
        {
            int32 newDuration = std::min<int32>(ascendance->GetMaxDuration(), ascendance->GetDuration() + increasedDuration);
            ascendance->SetDuration(newDuration);
        }
        else
        {
            caster->AddAura(SPELL_SHAMAN_ASCENDANCE_FLAME, caster);
            caster->GetAura(SPELL_SHAMAN_ASCENDANCE_FLAME)->SetDuration(baseDuration);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_deeply_rooted_fire::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_deeply_rooted_fire::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_further_beyond : public AuraScript
{
    PrepareAuraScript(rune_sha_further_beyond);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 durationIncrease = 0;

        if (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_EARTH_SHOCK || eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_EARTHQUAKE)
            durationIncrease = GetEffect(EFFECT_1)->GetAmount();
        else if (eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_ELEMENTAL_BLAST)
            durationIncrease = GetEffect(EFFECT_2)->GetAmount();
        else
            return;

        int32 ascendanceSpell = 0;

        if (caster->HasSpell(SPELL_SHAMAN_ASCENDANCE_AIR))
            ascendanceSpell = SPELL_SHAMAN_ASCENDANCE_AIR_AURA;
        else if (caster->HasSpell(SPELL_SHAMAN_ASCENDANCE_EARTH))
            ascendanceSpell = SPELL_SHAMAN_ASCENDANCE_EARTH;
        else if (caster->HasSpell(SPELL_SHAMAN_ASCENDANCE_FLAME))
            ascendanceSpell = SPELL_SHAMAN_ASCENDANCE_FLAME;
        else if (caster->HasSpell(SPELL_SHAMAN_ASCENDANCE_WATER))
            ascendanceSpell = SPELL_SHAMAN_ASCENDANCE_WATER_AURA;
        else
            return;

        if (Aura* ascendance = caster->GetAura(ascendanceSpell))
        {
            int32 newDuration = std::min<int32>(ascendance->GetMaxDuration(), ascendance->GetDuration() + durationIncrease);
            ascendance->SetDuration(newDuration);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_further_beyond::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_further_beyond::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_molten_assault : public AuraScript
{
    PrepareAuraScript(rune_sha_molten_assault);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        if (Aura* flameShock = target->GetAura(SPELL_SHAMAN_FLAME_SHOCK))
        {
            flameShock->RefreshDuration();
            flameShock->GetEffect(EFFECT_1)->ResetPeriodic();
            caster->CastSpell(target, RUNE_SHAMAN_MOLTEN_ASSAULT_AOE, TRIGGERED_FULL_MASK);
        }

    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_molten_assault::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_molten_assault::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_molten_assault_aoe : public SpellScript
{
    PrepareSpellScript(rune_sha_molten_assault_aoe);

    Aura* GetRuneAura(Unit* caster)
    {
        for (size_t i = 1000662; i < 1000668; i++)
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

        if (!GetRuneAura(caster))
            return;

        int32 maxTargets = GetRuneAura(caster)->GetEffect(EFFECT_0)->GetAmount();
        int32 targetNbr = 0;

        for (auto const& object : targets)
        {
            Unit* target = object->ToUnit();

            if (targetNbr == maxTargets)
                return;

            if (target->isDead() || target->HasAura(SPELL_SHAMAN_FLAME_SHOCK))
                continue;

            caster->AddAura(SPELL_SHAMAN_FLAME_SHOCK, target);
            targetNbr++;
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(rune_sha_molten_assault_aoe::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class rune_sha_hot_hand : public AuraScript
{
    PrepareAuraScript(rune_sha_hot_hand);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            if (!caster->HasSpell(SPELL_SHAMAN_LAVA_LASH) || !caster->HasSpellCooldown(SPELL_SHAMAN_LAVA_LASH))
                return;

            int32 cooldown = CalculatePct(player->GetSpellCooldownDelay(SPELL_SHAMAN_LAVA_LASH), aurEff->GetAmount());
            player->ModifySpellCooldown(SPELL_SHAMAN_LAVA_LASH, -cooldown);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_hot_hand::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_hot_hand::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

class rune_sha_ashen_catalyst : public AuraScript
{
    PrepareAuraScript(rune_sha_ashen_catalyst);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            if (!caster->HasSpell(SPELL_SHAMAN_LAVA_LASH) || !caster->HasSpellCooldown(SPELL_SHAMAN_LAVA_LASH))
                return;

            player->ModifySpellCooldown(SPELL_SHAMAN_LAVA_LASH, -aurEff->GetAmount());
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_ashen_catalyst::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_ashen_catalyst::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

class rune_sha_lashing_flames : public AuraScript
{
    PrepareAuraScript(rune_sha_lashing_flames);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;
        int32 buffAura = aurEff->GetAmount();

        if (spellID == SPELL_SHAMAN_LAVA_LASH)
            target->AddAura(buffAura, target);

        if (spellID == SPELL_SHAMAN_FLAME_SHOCK)
        {
            if (!target->HasAura(buffAura))
                return;

            int32 damagePct = target->GetAura(buffAura)->GetEffect(EFFECT_0)->GetAmount();
            int32 damage = eventInfo.GetDamageInfo()->GetDamage();
            int32 amount = CalculatePct(damage, damagePct);

            caster->CastCustomSpell(RUNE_SHAMAN_LASHING_FLAMES_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_lashing_flames::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_lashing_flames::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_stormflurry : public AuraScript
{
    PrepareAuraScript(rune_sha_stormflurry);


    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetActionTarget() && eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* player = GetCaster();

        if (!player || player->isDead())
            return;

        Unit* target = eventInfo.GetActionTarget();

        if (!target || target->isDead())
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;

        if (spellID != SPELL_SHAMAN_STORMSTRIKE)
            return;

        player->CastSpell(target, spellID, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_stormflurry::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_stormflurry::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_static_accumulation_periodic : public AuraScript
{
    PrepareAuraScript(rune_sha_static_accumulation_periodic);

    void HandleProc(AuraEffect const* aurEff)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(SPELL_SHAMAN_ASCENDANCE_AIR_AURA))
            caster->CastSpell(caster, SPELL_SHAMAN_MAELSTROM_WEAPON_PROC, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_static_accumulation_periodic::HandleProc, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectPeriodic += AuraEffectPeriodicFn(rune_sha_static_accumulation_periodic::HandleProc, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class rune_sha_static_accumulation_proc : public SpellScript
{
    PrepareSpellScript(rune_sha_static_accumulation_proc);

    Aura* GetRuneAura(Unit* caster)
    {
        for (size_t i = 1000798; i < 1000804; i++)
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

        if (!GetRuneAura(caster))
            return;

        if (Aura* maelstromWeaponsAura = caster->GetAura(SPELL_SHAMAN_MAELSTROM_WEAPON_PROC))
        {
            maelstromWeaponspStacks = maelstromWeaponsAura->GetStackAmount();
        }
    }

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (!GetRuneAura(caster))
            return;

        if (maelstromWeaponspStacks == 0)
            return;

        int32 procChance = GetRuneAura(caster)->GetEffect(EFFECT_0)->GetAmount();

        if (roll_chance_i(procChance))
        {
            caster->CastSpell(caster, SPELL_SHAMAN_MAELSTROM_WEAPON_PROC, TRIGGERED_FULL_MASK);
            caster->GetAura(SPELL_SHAMAN_MAELSTROM_WEAPON_PROC)->SetStackAmount(maelstromWeaponspStacks);
        }

        maelstromWeaponspStacks = 0;
    }

    void Register() override
    {
        BeforeCast += SpellCastFn(rune_sha_static_accumulation_proc::HandleBeforeCast);
        AfterCast += SpellCastFn(rune_sha_static_accumulation_proc::HandleAfterCast);
    }
private:
    int32 maelstromWeaponspStacks = 0;
};

class rune_sha_legacy_of_the_frost_witch : public AuraScript
{
    PrepareAuraScript(rune_sha_legacy_of_the_frost_witch);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(RUNE_SHAMAN_LEGACY_OF_THE_FROST_WITCH_LISTENER))
            caster->RemoveAura(RUNE_SHAMAN_LEGACY_OF_THE_FROST_WITCH_LISTENER);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(rune_sha_legacy_of_the_frost_witch::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class rune_sha_stormblast : public AuraScript
{
    PrepareAuraScript(rune_sha_stormblast);


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

        if (!target|| target->isDead())
            return;

        int32 damage = eventInfo.GetDamageInfo()->GetDamage();

        int32 amount = CalculatePct(damage, aurEff->GetAmount());

        caster->CastCustomSpell(RUNE_SHAMAN_STORMBLAST_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_stormblast::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_stormblast::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_stormblast_remove : public SpellScript
{
    PrepareSpellScript(rune_sha_stormblast_remove);

    void HandleAfterCast()
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        for (size_t i = 1000836; i < 1000842; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(rune_sha_stormblast_remove::HandleAfterCast);
    }
};

class rune_sha_deeply_rooted_air : public AuraScript
{
    PrepareAuraScript(rune_sha_deeply_rooted_air);

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
            int32 baseDuration = GetEffect(EFFECT_1)->GetAmount();
            int32 increasedDuration = GetEffect(EFFECT_2)->GetAmount();

            if (Aura* ascendance = caster->GetAura(SPELL_SHAMAN_ASCENDANCE_AIR_AURA))
            {
                int32 newDuration = std::min<int32>(ascendance->GetMaxDuration(), ascendance->GetDuration() + increasedDuration);
                ascendance->SetDuration(newDuration);
            }
            else
            {
                caster->AddAura(SPELL_SHAMAN_ASCENDANCE_AIR_AURA, caster);
                caster->GetAura(SPELL_SHAMAN_ASCENDANCE_AIR_AURA)->SetDuration(baseDuration);
                player->RemoveSpellCooldown(SPELL_SHAMAN_STORMSTRIKE, true);
            }
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_deeply_rooted_air::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_deeply_rooted_air::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_thorims_invocation : public AuraScript
{
    PrepareAuraScript(rune_sha_thorims_invocation);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;

        if (spellID == SPELL_SHAMAN_CHAIN_LIGHTNING)
        {
            lastSpellID = SPELL_SHAMAN_CHAIN_LIGHTNING;
            return;
        }

        if (spellID == SPELL_SHAMAN_LIGHTNING_BOLT)
        {
            lastSpellID = SPELL_SHAMAN_LIGHTNING_BOLT;
            return;
        }

        Unit* target = eventInfo.GetActionTarget();

        if (!target || target->isDead())
            return;

        if (!caster->HasAura(SPELL_SHAMAN_ASCENDANCE_AIR_AURA))
            return;

        if (Aura* maelstromBuff = caster->GetAura(SPELL_SHAMAN_MAELSTROM_WEAPON_PROC))
        {
            int32 stacks = maelstromBuff->GetStackAmount();
            int32 threshold = aurEff->GetAmount();

            if (stacks - threshold > 0)
                maelstromBuff->ModStackAmount(-threshold);
            else
                maelstromBuff->Remove();

            caster->CastSpell(target, lastSpellID, TRIGGERED_FULL_MASK);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_thorims_invocation::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_thorims_invocation::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
private:
    int32 lastSpellID = SPELL_SHAMAN_LIGHTNING_BOLT;
};

class rune_sha_elemental_spirits : public AuraScript
{
    PrepareAuraScript(rune_sha_elemental_spirits);

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        for (size_t i = 1000868; i < 1000910; i++)
        {
            if (caster->HasAura(i))
                caster->RemoveAura(i);
        }
    }

    void Register()
    {
        OnEffectRemove += AuraEffectRemoveFn(rune_sha_elemental_spirits::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class rune_sha_elemental_spirits_molten_weapon : public AuraScript
{
    PrepareAuraScript(rune_sha_elemental_spirits_molten_weapon);

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

        int32 damage = eventInfo.GetDamageInfo()->GetDamage();
        int32 damagePct = aurEff->GetAmount();

        int32 amount = CalculatePct(damage, damagePct);

        caster->CastCustomSpell(RUNE_SHAMAN_ELEMENTAL_SPIRITS_MOLTEN_WEAPON_DOT, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_elemental_spirits_molten_weapon::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_elemental_spirits_molten_weapon::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_elemental_spirits_icy_edge : public AuraScript
{
    PrepareAuraScript(rune_sha_elemental_spirits_icy_edge);

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

        int32 procSpell = GetEffect(EFFECT_1)->GetAmount();
        int32 damage = eventInfo.GetDamageInfo()->GetDamage();
        int32 damagePct = aurEff->GetAmount();

        int32 amount = CalculatePct(damage, damagePct);

        caster->CastCustomSpell(procSpell, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_elemental_spirits_icy_edge::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_elemental_spirits_icy_edge::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_wind_wolfs : public AuraScript
{
    PrepareAuraScript(rune_sha_wind_wolfs);

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
            int32 duration = aurEff->GetAmount();
            player->ModifySpellCooldown(SPELL_SHAMAN_FERAL_SPIRIT, -duration);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_wind_wolfs::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_wind_wolfs::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_alpha_wolf : public AuraScript
{
    PrepareAuraScript(rune_sha_alpha_wolf);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        int32 procSpell = aurEff->GetAmount();

        for (Unit::ControlSet::iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
            if ((*itr)->GetEntry() == SUMMON_SHAMAN_FERAL_SPIRITS && (*itr)->IsAlive())
                caster->AddAura(procSpell, (*itr));
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_alpha_wolf::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_alpha_wolf::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_earthen_wall : public AuraScript
{
    PrepareAuraScript(rune_sha_earthen_wall);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetHealInfo()->GetTarget();

        if (!target || target->isDead())
            return;

        int32 heal = eventInfo.GetHealInfo()->GetHeal();
        int32 healPct = aurEff->GetAmount();

        int32 amount = CalculatePct(heal, healPct);

        caster->CastCustomSpell(RUNE_SHAMAN_EARTHEN_WALL_SHIELD, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_earthen_wall::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_earthen_wall::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_earthen_wave : public AuraScript
{
    PrepareAuraScript(rune_sha_earthen_wave);

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

        int32 chargeIncrease = aurEff->GetAmount();

        if (Aura* earthenShield = target->GetAura(SPELL_SHAMAN_EARTHEN_SHIELD))
            earthenShield->ModCharges(chargeIncrease);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_earthen_wave::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_earthen_wave::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_primal_tide_core : public AuraScript
{
    PrepareAuraScript(rune_sha_primal_tide_core);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetActor() || eventInfo.GetActor()->isDead())
            return false;

        if (!eventInfo.GetActionTarget() || eventInfo.GetActionTarget()->isDead())
            return false;

        return true;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = eventInfo.GetActor();
        Unit* target = eventInfo.GetActionTarget();

        if (!caster->HasSpellCooldown(RUNE_SHAMAN_PRIMAL_TIDE_CORE_AOE))
        {
            caster->CastSpell(caster, RUNE_SHAMAN_PRIMAL_TIDE_CORE_LISTENER, TRIGGERED_FULL_MASK);

            if (caster->GetAura(RUNE_SHAMAN_PRIMAL_TIDE_CORE_LISTENER)->GetStackAmount() < aurEff->GetAmount())
                return;

            caster->CastSpell(target, RUNE_SHAMAN_PRIMAL_TIDE_CORE_AOE);
            caster->RemoveAura(RUNE_SHAMAN_PRIMAL_TIDE_CORE_LISTENER);
        }
    }

    void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (caster->HasAura(RUNE_SHAMAN_PRIMAL_TIDE_CORE_LISTENER))
            caster->RemoveAura(RUNE_SHAMAN_PRIMAL_TIDE_CORE_LISTENER);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_primal_tide_core::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_primal_tide_core::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        OnEffectRemove += AuraEffectRemoveFn(rune_sha_primal_tide_core::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class rune_sha_primal_tide_core_proc : public SpellScript
{
    PrepareSpellScript(rune_sha_primal_tide_core_proc);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        uint32 const maxTargets = 1;

        if (targets.size() > maxTargets)
        {
            targets.sort(Acore::HealthPctOrderPred());
            targets.resize(maxTargets);
        }

        for (auto const& healTarget : targets)
        {
            Unit* target = healTarget->ToUnit();

            if (target->isDead())
                continue;

            GetCaster()->AddAura(SPELL_SHAMAN_RIPTIDE, target);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(rune_sha_primal_tide_core_proc::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

class rune_sha_nazjatar_molting : public AuraScript
{
    PrepareAuraScript(rune_sha_nazjatar_molting);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetHealInfo())
            return false;

        if (Unit* target = eventInfo.GetHealInfo()->GetTarget())
            return target->GetHealthPct() < GetEffect(EFFECT_0)->GetAmount();
        else
            return false;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_nazjatar_molting::CheckProc);
    }
};

class rune_sha_deluge : public AuraScript
{
    PrepareAuraScript(rune_sha_deluge);


    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetHealInfo() && eventInfo.GetHealInfo()->GetHeal() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetHealInfo()->GetTarget();

        if (!target || target->isDead())
            return;

        int32 heal = eventInfo.GetHealInfo()->GetHeal();

        if (!target->HasAura(SPELL_SHAMAN_RIPTIDE) && !target->HasAura(SPELL_SHAMAN_HEALING_RAIN))
            return;

        int32 amount = CalculatePct(heal, aurEff->GetAmount());

        caster->CastCustomSpell(RUNE_SHAMAN_DELUGE_HEAL, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_deluge::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_deluge::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_deeply_rooted_water : public AuraScript
{
    PrepareAuraScript(rune_sha_deeply_rooted_water);

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
            int32 baseDuration = GetEffect(EFFECT_1)->GetAmount();
            int32 increasedDuration = GetEffect(EFFECT_2)->GetAmount();

            if (Aura* ascendance = caster->GetAura(SPELL_SHAMAN_ASCENDANCE_WATER_AURA))
            {
                int32 newDuration = std::min<int32>(ascendance->GetMaxDuration(), ascendance->GetDuration() + increasedDuration);
                ascendance->SetDuration(newDuration);
            }
            else
            {
                caster->AddAura(SPELL_SHAMAN_ASCENDANCE_WATER_AURA, caster);
                caster->GetAura(SPELL_SHAMAN_ASCENDANCE_WATER_AURA)->SetDuration(baseDuration);
            }
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_deeply_rooted_water::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_deeply_rooted_water::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_everlasting_stamp : public AuraScript
{
    PrepareAuraScript(rune_sha_everlasting_stamp);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        if (Aura* fieryStamp = target->GetAura(SPELL_SHAMAN_FIERY_STAMP))
        {
            int32 newDuration = std::min<int32>(fieryStamp->GetMaxDuration(), fieryStamp->GetDuration() + aurEff->GetAmount());
            fieryStamp->SetDuration(newDuration);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_everlasting_stamp::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_everlasting_stamp::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_deadly_stamp : public AuraScript
{
    PrepareAuraScript(rune_sha_deadly_stamp);

    Aura* GetRuneAura(Unit* caster)
    {
        for (size_t i = 1001160; i < 1001166; i++)
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

        if (Player* player = caster->ToPlayer())
            player->ModifySpellCooldown(SPELL_SHAMAN_FIERY_STAMP, -GetRuneAura(caster)->GetEffect(EFFECT_0)->GetAmount());
    }

    void Register()
    {
        OnEffectProc += AuraEffectProcFn(rune_sha_deadly_stamp::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_fiery_furor : public AuraScript
{
    PrepareAuraScript(rune_sha_fiery_furor);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        ShapeshiftForm form = caster->GetShapeshiftForm();

        if (form != FORM_SPIRIT_OF_FIRE)
            return;

        int32 procSpell = aurEff->GetAmount();

        caster->CastSpell(target, procSpell, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_fiery_furor::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_fiery_furor::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_thunder_rod : public AuraScript
{
    PrepareAuraScript(rune_sha_thunder_rod);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetSpellInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        ShapeshiftForm form = caster->GetShapeshiftForm();

        if (form != FORM_SPIRIT_OF_STORM)
            return;

        Unit* target = eventInfo.GetDamageInfo()->GetVictim();

        if (!target || target->isDead())
            return;

        int32 damage = eventInfo.GetDamageInfo()->GetDamage();

        if (damage == 0)
            return;

        int32 spellID = eventInfo.GetSpellInfo()->Id;
        int32 thunderRod = aurEff->GetAmount();

        if (spellID == SPELL_SHAMAN_FOCUS_FOE || spellID == SPELL_SHAMAN_FOCUS_FOE_STORM)
            caster->CastSpell(target, thunderRod, TRIGGERED_FULL_MASK);
        else if (spellID == SPELL_SHAMAN_INVOKE_ESSENCE || spellID == SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_STORM || spellID == SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_STORM_ECHO)
        {
            GetEffect(EFFECT_1)->SetAmount(eventInfo.GetDamageInfo()->GetDamage());
            caster->CastSpell(caster, RUNE_SHAMAN_THUNDER_ROD_AOE, TRIGGERED_FULL_MASK);
        }

    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_thunder_rod::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_thunder_rod::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_thunder_rod_aoe : public SpellScript
{
    PrepareSpellScript(rune_sha_thunder_rod_aoe);

    Aura* GetRuneAura(Unit* caster)
    {
        for (size_t i = 1001194; i < 1001200; i++)
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

        if (!GetRuneAura(caster))
            return;

        ShapeshiftForm form = caster->GetShapeshiftForm();

        if (form != FORM_SPIRIT_OF_STORM)
            return;

        int32 thunderRod = GetRuneAura(caster)->GetEffect(EFFECT_0)->GetAmount();
        int32 damage = GetRuneAura(caster)->GetEffect(EFFECT_1)->GetAmount();

        for (auto const& object : targets)
        {
            Unit* target = object->ToUnit();

            if (target->isDead() || !target->HasAura(thunderRod))
                continue;

            int32 damagePct = target->GetAura(thunderRod)->GetEffect(EFFECT_0)->GetAmount();
            int32 amount = CalculatePct(damage, damagePct);

            caster->CastCustomSpell(RUNE_SHAMAN_THUNDER_ROD_DAMAGE, SPELLVALUE_BASE_POINT0, amount, target, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(rune_sha_thunder_rod_aoe::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class rune_sha_focus_wave : public AuraScript
{
    PrepareAuraScript(rune_sha_focus_wave);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        ShapeshiftForm form = caster->GetShapeshiftForm();

        if (form != FORM_SPIRIT_OF_WATER)
            return;

        int32 procSpell = aurEff->GetAmount();

        caster->CastSpell(caster, procSpell, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_focus_wave::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_focus_wave::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_lasting_water : public AuraScript
{
    PrepareAuraScript(rune_sha_lasting_water);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id == SPELL_SHAMAN_FURY_OF_THE_ELEMENTS_WATER;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_lasting_water::CheckProc);
    }
};

class rune_sha_elemental_cleansing : public AuraScript
{
    PrepareAuraScript(rune_sha_elemental_cleansing);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo() && eventInfo.GetDamageInfo()->GetDamage() > 0;
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        Unit* victim = eventInfo.GetDamageInfo()->GetVictim();

        if (!victim || victim->isDead())
            return;

        float damage = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount()));
        int32 amount = damage / 6;

        caster->CastCustomSpell(RUNE_SHAMAN_ELEMENTAL_CLEANSING_DOT, SPELLVALUE_BASE_POINT0, amount, victim, TRIGGERED_FULL_MASK);
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_elemental_cleansing::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_elemental_cleansing::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_impactful_storm : public AuraScript
{
    PrepareAuraScript(rune_sha_impactful_storm);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return false;

        ShapeshiftForm form = caster->GetShapeshiftForm();

        return form == FORM_SPIRIT_OF_STORM;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_impactful_storm::CheckProc);
    }
};

class rune_sha_elemental_essence : public AuraScript
{
    PrepareAuraScript(rune_sha_elemental_essence);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            int32 cooldown = aurEff->GetAmount();
            player->ModifySpellCooldown(SPELL_SHAMAN_OVERCHARGE, -cooldown);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_elemental_essence::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_elemental_essence::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_invoke_elements : public AuraScript
{
    PrepareAuraScript(rune_sha_invoke_elements);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            int32 cooldown = aurEff->GetAmount();
            player->ModifySpellCooldown(SPELL_SHAMAN_FURY_OF_THE_ELEMENTS, -cooldown);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_invoke_elements::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_invoke_elements::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_deeply_rooted_earth : public AuraScript
{
    PrepareAuraScript(rune_sha_deeply_rooted_earth);

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
            int32 baseDuration = GetEffect(EFFECT_1)->GetAmount();
            int32 increasedDuration = GetEffect(EFFECT_2)->GetAmount();

            if (Aura* ascendance = caster->GetAura(SPELL_SHAMAN_ASCENDANCE_EARTH))
            {
                int32 newDuration = std::min<int32>(ascendance->GetMaxDuration(), ascendance->GetDuration() + increasedDuration);
                ascendance->SetDuration(newDuration);
            }
            else
            {
                caster->AddAura(SPELL_SHAMAN_ASCENDANCE_EARTH, caster);
                caster->GetAura(SPELL_SHAMAN_ASCENDANCE_EARTH)->SetDuration(baseDuration);
            }
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_deeply_rooted_earth::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_deeply_rooted_earth::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_charging_attacks : public AuraScript
{
    PrepareAuraScript(rune_sha_charging_attacks);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        return eventInfo.GetDamageInfo();
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (!caster || caster->isDead())
            return;

        if (Player* player = caster->ToPlayer())
        {
            int32 cooldown = aurEff->GetAmount();
            player->ModifySpellCooldown(SPELL_SHAMAN_OVERCHARGE, -cooldown);
        }
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_charging_attacks::CheckProc);
        OnEffectProc += AuraEffectProcFn(rune_sha_charging_attacks::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

class rune_sha_power_of_the_maelstrom : public AuraScript
{
    PrepareAuraScript(rune_sha_power_of_the_maelstrom);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        if (!eventInfo.GetSpellInfo())
            return false;

        int32 spellID = eventInfo.GetSpellInfo()->Id;

        if (!spellID)
            return false;

        if (spellID == SPELL_SHAMAN_LIGHTNING_BOLT_OVERLOAD || spellID == SPELL_SHAMAN_CHAIN_LIGHTNING_OVERLOAD || spellID == SPELL_SHAMAN_LAVA_BEAM_OVERLOAD)
            return false;

        return true;
    }

    void Register()
    {
        DoCheckProc += AuraCheckProcFn(rune_sha_power_of_the_maelstrom::CheckProc);
    }
};

void AddSC_shaman_perks_scripts()
{
    RegisterSpellScript(rune_sha_tidebringer);
    RegisterSpellScript(rune_sha_lava_surge);
    RegisterSpellScript(rune_sha_fiery_demise);
    RegisterSpellScript(rune_sha_volcanic_inferno);
    RegisterSpellScript(rune_sha_magma_burst);
    RegisterSpellScript(rune_sha_flash_of_lightning);
    RegisterSpellScript(rune_sha_pulsating_lightning);
    RegisterSpellScript(rune_sha_flowing_streams);
    RegisterSpellScript(rune_sha_undulation);
    RegisterSpellScript(rune_sha_resurgence);
    RegisterSpellScript(rune_sha_high_tide);
    RegisterSpellScript(rune_sha_spirit_wolf);
    RegisterSpellScript(rune_sha_rejuvenating_wolf);
    RegisterSpellScript(rune_sha_regenerating_wolf);
    RegisterSpellScript(rune_sha_elemental_equilibrium);
    RegisterSpellScript(rune_sha_forceful_winds);
    RegisterSpellScript(rune_sha_forceful_winds_remove);
    RegisterSpellScript(rune_sha_primordial_bond);
    RegisterSpellScript(rune_sha_pulsating_water);
    RegisterSpellScript(rune_sha_lightning_rod);
    RegisterSpellScript(rune_sha_lightning_rod_aoe);
    RegisterSpellScript(rune_sha_echoes_of_the_great_sundering);
    RegisterSpellScript(rune_sha_electrified_shocks_remove);
    RegisterSpellScript(rune_sha_aftershock);
    RegisterSpellScript(rune_sha_deeply_rooted_fire);
    RegisterSpellScript(rune_sha_further_beyond);
    RegisterSpellScript(rune_sha_molten_assault);
    RegisterSpellScript(rune_sha_molten_assault_aoe);
    RegisterSpellScript(rune_sha_hot_hand);
    RegisterSpellScript(rune_sha_ashen_catalyst);
    RegisterSpellScript(rune_sha_lashing_flames);
    RegisterSpellScript(rune_sha_stormflurry);
    RegisterSpellScript(rune_sha_static_accumulation_periodic);
    RegisterSpellScript(rune_sha_static_accumulation_proc);
    RegisterSpellScript(rune_sha_legacy_of_the_frost_witch);
    RegisterSpellScript(rune_sha_stormblast);
    RegisterSpellScript(rune_sha_deeply_rooted_air);
    RegisterSpellScript(rune_sha_thorims_invocation);
    RegisterSpellScript(rune_sha_elemental_spirits);
    RegisterSpellScript(rune_sha_elemental_spirits_molten_weapon);
    RegisterSpellScript(rune_sha_elemental_spirits_icy_edge);
    RegisterSpellScript(rune_sha_wind_wolfs);
    RegisterSpellScript(rune_sha_alpha_wolf);
    RegisterSpellScript(rune_sha_earthen_wall);
    RegisterSpellScript(rune_sha_earthen_wave);
    RegisterSpellScript(rune_sha_primal_tide_core);
    RegisterSpellScript(rune_sha_primal_tide_core_proc);
    RegisterSpellScript(rune_sha_nazjatar_molting);
    RegisterSpellScript(rune_sha_deluge);
    RegisterSpellScript(rune_sha_deeply_rooted_water);
    RegisterSpellScript(rune_sha_everlasting_stamp);
    RegisterSpellScript(rune_sha_deadly_stamp);
    RegisterSpellScript(rune_sha_fiery_furor);
    RegisterSpellScript(rune_sha_thunder_rod);
    RegisterSpellScript(rune_sha_thunder_rod_aoe);
    RegisterSpellScript(rune_sha_focus_wave);
    RegisterSpellScript(rune_sha_lasting_water);
    RegisterSpellScript(rune_sha_elemental_cleansing);
    RegisterSpellScript(rune_sha_impactful_storm);
    RegisterSpellScript(rune_sha_elemental_essence);
    RegisterSpellScript(rune_sha_invoke_elements);
    RegisterSpellScript(rune_sha_deeply_rooted_earth);
    RegisterSpellScript(rune_sha_charging_attacks);
    RegisterSpellScript(rune_sha_power_of_the_maelstrom);
}

