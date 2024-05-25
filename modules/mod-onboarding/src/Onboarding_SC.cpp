/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "LuaEngine.h"
#include "Spell.h"
#include "OnboardingManager.h"

class Onboarding_PlayerScripts : public PlayerScript
{
public:
    Onboarding_PlayerScripts() : PlayerScript("Onboarding_PlayerScripts") { }

    void OnLogin(Player* player) override
    {
        if (!player)
            return;

        OnboardingManager::SendEventDependingOnTheProgression(player);
    }
};

// Add all scripts in one
void AddSC_Onboarding()
{
    new Onboarding_PlayerScripts();
}

