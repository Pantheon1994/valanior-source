#include "ItemUpgradeManager.h"
#include "RunesManager.h"


std::map<uint32 /* itemLevel */, Upgrade> ItemUpgradeManager::m_CostUpgrade = {};


void ItemUpgradeManager::LoadCosts()
{
    m_CostUpgrade = {};

    QueryResult result = WorldDatabase.Query("SELECT * type FROM item_upgrade_cost");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 itemLevel = fields[0].Get<uint32>();
        uint32 runicEssenceCost = fields[1].Get<uint32>();
        uint32 requiredItemId1 = fields[2].Get<uint32>();
        uint32 requiredItemCount1 = fields[3].Get<uint32>();
        uint32 requiredItemId2 = fields[4].Get<uint32>();
        uint32 requiredItemCount2 = fields[5].Get<uint32>();

        Upgrade upgrade = { itemLevel, runicEssenceCost, requiredItemId1, requiredItemCount1, requiredItemId2, requiredItemCount2 };
        m_CostUpgrade[itemLevel] = upgrade;

    } while (result->NextRow());
}

void ItemUpgradeManager::UpgradeItem(Player* player, uint32 entry)
{
    const ItemTemplate* itemTemplate = sObjectMgr->GetItemTemplate(entry);

    if (entry < 100000 || itemTemplate->Class != ITEM_CLASS_WEAPON || itemTemplate->Class != ITEM_CLASS_ARMOR)
    {
        RunesManager::SendChat(player, "You can't upgrade this item.");
        return;
    }

    if (!itemTemplate)
        return;

    uint32 nextEntry = entry + 1;

    const ItemTemplate* itemUpgrade = sObjectMgr->GetItemTemplate(nextEntry);

    if (!itemUpgrade)
        return;

    uint32 itemLevel = itemUpgrade->ItemLevel;

    if (itemLevel > sWorld->GetValue("CONFIG_MAX_ITEM_LEVEL_UPGRADE"))
    {
        RunesManager::SendChat(player, "You can't upgrade this item anymore");
        return;
    }

    if (itemUpgrade->Name1 != itemTemplate->Name1)
    {
        RunesManager::SendChat(player, "You can't upgrade this item.");
        return;
    }

    auto find = m_CostUpgrade.find(itemLevel);

    if (find == m_CostUpgrade.end())
    {
        RunesManager::SendChat(player, "You can't upgrade this item.");
        return;
    }

    if (!HasEnoughItemToUpgrade(player, find->second))
    {
        RunesManager::SendChat(player, "You don't have the required items to upgrade this item.");
        return;
    }

    RemoveRequieredItem(player, find->second);

    Item* item = player->GetItemByEntry(entry);
    Item* nextItem = player->AddItem(nextEntry);

    for (uint32 j = 0; j < MAX_ENCHANTMENT_SLOT; ++j)
    {
        if (uint32 enchId = item->GetEnchantmentId(EnchantmentSlot(j)))
        {
            nextItem->SetEnchantment(EnchantmentSlot(j), enchId, 0, 0);
        }
    }

    player->DestroyItemCount(entry, 1, true);
    sEluna->UpgradeItemSuccess(player);
}

void ItemUpgradeManager::RemoveRequieredItem(Player* player, Upgrade upgrade)
{
    if(upgrade.requiredItemId1 > 0)
        player->DestroyItemCount(upgrade.requiredItemId1, upgrade.requiredItemCount1, true);

    if(upgrade.requiredItemId2 > 0)
        player->DestroyItemCount(upgrade.requiredItemId2, upgrade.requiredItemId2, true);

    player->DestroyItemCount(70009, upgrade.runicEssenceCost, true);
}

bool ItemUpgradeManager::HasEnoughItemToUpgrade(Player* player, Upgrade upgrade)
{
    if (upgrade.requiredItemId1 > 0 && upgrade.requiredItemId2 == 0)
        return player->HasItemCount(upgrade.requiredItemId1, upgrade.requiredItemCount1)
            && player->HasItemCount(70009, upgrade.runicEssenceCost);

    if (upgrade.requiredItemId1 > 0 && upgrade.requiredItemId2 > 0)
        return player->HasItemCount(upgrade.requiredItemId1, upgrade.requiredItemCount1) &&
            player->HasItemCount(upgrade.requiredItemId2, upgrade.requiredItemCount2)
            && player->HasItemCount(70009, upgrade.runicEssenceCost);

    return false;
}