#include "OnboardingManager.h"
#include "RunesManager.h"

OnboardingManager::accountOnboardingContainer OnboardingManager::AccountOnboardingStore = {};

void OnboardingManager::InitializeOnboardingAccountProgression()
{
    AccountOnboardingStore = {};

    QueryResult result = LoginDatabase.Query("SELECT id, progression FROM dungeon_mythic_bosses ORDER by `order` ASC");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 accountId = fields[0].Get<uint32>();
        uint32 progression = fields[1].Get<uint32>();
        AccountOnboardingStore[accountId] = OnboardingStep(progression);
    } while (result->NextRow());

}

void OnboardingManager::SendEventDependingOnTheProgression(Player* player)
{
    OnboardingStep step = OnboardingStep(GetOnboardingStep(player));

    if (step == 0)
        return;

    switch (step)
    {
        case STEP_FIRST_LOGIN:
            break;
        case STEP_GIFT_ACCEPTED:
            break;
        case STEP_EQUIP_A_RUNE:
            break;
        case STEP_REACH_LEVEL_6:
            break;
        case STEP_UPGRADE_A_RUNE:
            break;
        case STEP_DISCOVER_MORE_RUNE:
            break;
        case STEP_CHOOSE_LUCKY_RUNE:
            break;
        case STEP_CHOOSE_AUTO_REFUND_RUNE:
            break;
        case STEP_FINAL:
            break;
        default:
            break;
    }

    sEluna->SendProgressionOnboarding(player, step);
}

uint8 OnboardingManager::GetOnboardingStep(Player* player)
{
    auto it = AccountOnboardingStore.find(player->GetSession()->GetAccountId());

    if (it != AccountOnboardingStore.end())
        return it->second;

    return 0;
}

void OnboardingManager::UpdateProgression(Player* player)
{
    OnboardingStep step = OnboardingStep(GetOnboardingStep(player));

    if (step == 0)
        return;

    uint32 accountId = player->GetSession()->GetAccountId();
    AccountOnboardingStore[accountId] = OnboardingStep(step + 1);

    LoginDatabase.Query("UPDATE account SET progression = progression + 1 WHERE id = {}", accountId);
}

void OnboardingManager::OnClaimTheGift(Player* player)
{
    OnboardingStep step = OnboardingStep(GetOnboardingStep(player));

    if (step == 0)
        return;

    if (step >= STEP_GIFT_ACCEPTED)
        return;

    Rune rune = RunesManager::GetRuneBySpellId(100163);
    RunesManager::AddRunesPlayer(player, { rune });

    UpdateProgression(player);
    SendEventDependingOnTheProgression(player);
}

void OnboardingManager::OnReachLevel(Player* player)
{
    OnboardingStep step = OnboardingStep(GetOnboardingStep(player));

    if (step == 0)
        return;

    if (step >= STEP_REACH_LEVEL_6)
        return;

    Rune rune = RunesManager::GetRuneBySpellId(100163);
    RunesManager::AddRunesPlayer(player, { rune, rune });

    UpdateProgression(player);
    SendEventDependingOnTheProgression(player);
}

void OnboardingManager::OnEquipARune(Player* player)
{
    OnboardingStep step = OnboardingStep(GetOnboardingStep(player));

    if (step == 0)
        return;

    if (step >= STEP_EQUIP_A_RUNE)
        return;

    UpdateProgression(player);
    SendEventDependingOnTheProgression(player);
}

void OnboardingManager::OnUpgradeARune(Player* player)
{
    OnboardingStep step = OnboardingStep(GetOnboardingStep(player));

    if (step == 0)
        return;

    if (step >= STEP_UPGRADE_A_RUNE)
        return;

    player->AddItem(70008, 1000);

    UpdateProgression(player);
    SendEventDependingOnTheProgression(player);
}

void OnboardingManager::OnOpeningSealedCommonRune(Player* player)
{
    // Logic for the achievements

    OnboardingStep step = OnboardingStep(GetOnboardingStep(player));

    if (step == 0)
        return;

    if (step >= STEP_DISCOVER_MORE_RUNE)
        return;

    UpdateProgression(player);
    SendEventDependingOnTheProgression(player);
}
