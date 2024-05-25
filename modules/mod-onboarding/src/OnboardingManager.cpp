#include "OnboardingManager.h"


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
    auto it = AccountOnboardingStore.find(player->GetSession()->GetAccountId());

    if (it == AccountOnboardingStore.end())
        return;

    OnboardingStep step = it->second;

    if (step >= STEP_FINAL)
        return;

    sEluna->SendProgressionOnboarding(player, step);
}

void OnboardingManager::UpdateProgression(Player* player)
{

}
