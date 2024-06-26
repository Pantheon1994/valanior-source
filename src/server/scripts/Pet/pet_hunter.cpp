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
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "npc_pet_hun_".
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum HunterSpells
{
    SPELL_HUNTER_CRIPPLING_POISON       = 30981, // Viper
    SPELL_HUNTER_DEADLY_POISON_PASSIVE  = 34657, // Venomous Snake
    SPELL_HUNTER_MIND_NUMBING_POISON    = 25810, // Viper
    SPELL_HUNTER_GLYPH_OF_SNAKE_TRAP    = 56849,
    SPELL_HUNTER_PET_SCALING            = 62915
};

struct npc_pet_hunter_snake_trap : public ScriptedAI
{
    npc_pet_hunter_snake_trap(Creature* creature) : ScriptedAI(creature) { _init = false; }

    void Reset() override
    {
        _spellTimer = urand(1500, 3000);

        // Start attacking attacker of owner on first ai update after spawn - move in line of sight may choose better target
        if (!me->GetVictim())
            if (Unit* tgt = me->SelectNearestTarget(10.0f))
            {
                me->AddThreat(tgt, 100000.0f);
                AttackStart(tgt);
            }
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
        // _EnterEvadeMode();
        me->GetThreatMgr().ClearAllThreat();
        me->CombatStop(true);
        me->LoadCreaturesAddon(true);
        me->SetLootRecipient(nullptr);
        me->ResetPlayerDamageReq();
        me->SetLastDamagedTime(0);

        me->AddUnitState(UNIT_STATE_EVADE);
        me->GetMotionMaster()->MoveTargetedHome();

        Reset();
    }

    //Redefined for random target selection:
    void MoveInLineOfSight(Unit* who) override
    {
        if (!me->GetVictim() && who->isTargetableForAttack() && (me->IsHostileTo(who)) && who->isInAccessiblePlaceFor(me))
        {
            if (me->GetDistanceZ(who) > CREATURE_Z_ATTACK_RANGE)
                return;

            if (me->IsWithinDistInMap(who, 10.0f))
            {
                me->AddThreat(who, 100000.0f);
                AttackStart(who);
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (me->GetVictim()->HasBreakableByDamageCrowdControlAura(me))
        {
            me->InterruptNonMeleeSpells(false);
            return;
        }

        if (!_init)
        {
            _init = true;

            CreatureTemplate const* Info = me->GetCreatureTemplate();
            CreatureBaseStats const* stats = sObjectMgr->GetCreatureBaseStats(me->getLevel(), Info->unit_class);
            uint32 health = uint32(107 * (me->getLevel() - 40) * 0.025f);
            me->SetCreateHealth(health);

            for (uint8 stat = 0; stat < MAX_STATS; ++stat)
            {
                me->SetStat(Stats(stat), 0);
                me->SetCreateStat(Stats(stat), 0);
            }

            me->SetModifierValue(UNIT_MOD_HEALTH, BASE_VALUE, (float)health);
            me->SetMaxHealth(health);
            //Add delta to make them not all hit the same time
            uint32 delta = urand(0, 700);
            me->SetAttackTime(BASE_ATTACK, Info->BaseAttackTime + delta);
            me->SetStatFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER, float(stats->AttackPower));
            me->CastSpell(me, SPELL_HUNTER_DEADLY_POISON_PASSIVE, true);

            // Glyph of Snake Trap
            if (Unit* owner = me->GetOwner())
                if (owner->GetAuraEffectDummy(SPELL_HUNTER_GLYPH_OF_SNAKE_TRAP))
                    me->CastSpell(me, SPELL_HUNTER_PET_SCALING, true);
        }

        _spellTimer += diff;
        if (_spellTimer >= 3000)
        {
            if (urand(0, 2) == 0) // 33% chance to cast
                DoCastVictim(RAND(SPELL_HUNTER_MIND_NUMBING_POISON, SPELL_HUNTER_CRIPPLING_POISON));

            _spellTimer = 0;
        }

        DoMeleeAttackIfReady();
    }

private:
    bool _init;
    uint32 _spellTimer;
};

struct npc_hunter_wild_pet : public ScriptedAI
{
    npc_hunter_wild_pet(Creature* creature) : ScriptedAI(creature), _initAttack(true) { }

    void InitializeAI() override
    {
        _events.Reset();
        _events.ScheduleEvent(0, 1500);
    }

    void AttackTarget(Unit* target)
    {
        me->JumpTo(target, 9.375f);
        AttackStart(target);
    }

    void UpdateAI(uint32 diff) override
    {
        if (_initAttack)
        {
            if (Player* owner = me->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                if (Unit* target = owner->GetSelectedUnit())
                {
                    if (me->CanCreatureAttack(target) && owner->IsInCombat())
                    {
                        AttackTarget(target);
                        _initAttack = false;
                    }
                }
            }
        }

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case 0:
                if (Player* owner = me->GetCharmerOrOwnerPlayerOrPlayerItself())
                {
                    if (Unit* newTarget = owner->GetSelectedUnit())
                    {
                        if (Unit* victim = me->GetVictim()) {
                            if (victim->GetGUID() != newTarget->GetGUID())
                            {
                                if (me->CanCreatureAttack(newTarget) && owner->IsInCombat())
                                    AttackTarget(newTarget);
                            }
                        }
                    }
                }
                _events.ScheduleEvent(0, 1500);
                break;
            }
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    bool _initAttack;
    Player* owner;
    int32 shadow;
};


struct pet_companion : public ScriptedAI
{
    pet_companion(Creature* creature) : ScriptedAI(creature) { }


    struct SpellGuardian {
        uint32 spellId;
        uint32 recoveryTime;
    };

    void InitializeAI() override
    {
        _events.Reset();
        _events.ScheduleEvent(0, 1500);
        _events.ScheduleEvent(1, 1500);
        _events.ScheduleEvent(2, 1500);
        _events.ScheduleEvent(3, 1500);
        _events.ScheduleEvent(4, 1000);
    }

    void EnterCombat(Unit* victim)
    {

        _events.Reset();
        std::vector<SpellInfo const*> mSpells = {};
        std::array<uint32_t, MAX_CREATURE_SPELL_DATA_SLOT> petSpells;

        if (Guardian* gardian = ((Guardian*)me)) {
            petSpells = gardian->GetSpellIds();
            for (uint8 j = 0; j < MAX_CREATURE_SPELL_DATA_SLOT; ++j)
            {
                if (uint32 spellId = petSpells[j]) {
                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);

                    if (!spellInfo)
                        continue;

                    mSpells.push_back(spellInfo);
                }
            }
        }

        for (SpellInfo const*& spell : mSpells) {
            if (spell->GetDuration() == 0) {
                mSpellGuardian.push_back({ spell->Id, spell->RecoveryTime == 0 ? urand(1500, 2000) : spell->RecoveryTime });
            }
        }

        for (SpellGuardian spell : mSpellGuardian) {
            _events.ScheduleEvent(index, spell.recoveryTime);
            index += 1;
        }

    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case 0: {
                SpellGuardian* spell = &mSpellGuardian[0];

                if (!spell)
                    return;

                 me->CastSpell(me->GetVictim(), spell->spellId);
                _events.ScheduleEvent(0, spell->recoveryTime);
                break;
            }

            case 1: {
                SpellGuardian* spell = &mSpellGuardian[1];

                if (!spell)
                    return;

                me->CastSpell(me->GetVictim(), spell->spellId);
                _events.ScheduleEvent(1, spell->recoveryTime);
                break;
            }
               

            case 2: {
                SpellGuardian* spell = &mSpellGuardian[2];

                if (!spell)
                    return;

                 me->CastSpell(me->GetVictim(), spell->spellId);
                _events.ScheduleEvent(2, spell->recoveryTime);
                break;
            }
                
            case 3:
            {
                SpellGuardian* spell = &mSpellGuardian[3];

                if (!spell)
                    return;
                 me->CastSpell(me->GetVictim(), spell->spellId);
                _events.ScheduleEvent(3, spell->recoveryTime);
                break;
            }

            case 4:
            {
                uint32 curValue = me->GetPower(POWER_FOCUS);
                uint32 maxValue = me->GetMaxPower(POWER_FOCUS);

                if (curValue >= maxValue)
                    return;

                uint32 addvalue = 24 * sWorld->getRate(RATE_POWER_FOCUS);
                me->ModifyPower(POWER_FOCUS, int32(addvalue));
                break;
            }
               
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    uint32 index = 0;
    std::vector<SpellGuardian> mSpellGuardian;
    bool _initAttack = false;
};
void AddSC_hunter_pet_scripts()
{
    RegisterCreatureAI(npc_pet_hunter_snake_trap);
    RegisterCreatureAI(npc_hunter_wild_pet);
    RegisterCreatureAI(pet_companion);
}
