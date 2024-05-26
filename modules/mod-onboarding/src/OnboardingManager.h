#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "RunesManager.h"
#include "LuaEngine.h"
#include "Spell.h"


enum OnboardingStep {

    STEP_FIRST_LOGIN = 1,
    STEP_GIFT_ACCEPTED,
    STEP_EQUIP_A_RUNE,
    STEP_REACH_LEVEL_6,
    STEP_UPGRADE_A_RUNE,
    STEP_DISCOVER_MORE_RUNE,
    STEP_CHOOSE_LUCKY_RUNE,
    STEP_CHOOSE_AUTO_REFUND_RUNE,
    STEP_FINAL,
};


class OnboardingManager
{
public:

    static uint8 GetOnboardingStep(Player* player);
    static void InitializeOnboardingAccountProgression();
    static void SendEventDependingOnTheProgression(Player* player);
    static void UpdateProgression(Player* player);


    // Onboarding Event;
    static void AcceptGift(Player* player);
    static void OnReachLevel(Player* player);
    static void OnEquipARune(Player* player);
    static void OnUpgradeARune(Player* player);
    static void OnOpeningSealedCommonRune(Player* player);
    static void ApplyLuckyRune(Player* player);
    static void OnSelectAutoRefundRune(Player* player);

private:
    typedef std::map<uint32, OnboardingStep> accountOnboardingContainer;
    static accountOnboardingContainer AccountOnboardingStore;
};
