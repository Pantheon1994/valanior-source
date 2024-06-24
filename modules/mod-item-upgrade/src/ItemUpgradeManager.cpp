#include "ItemUpgradeManager.h"
#include "RunesManager.h"

std::vector<ItemUpgradeRequirement> ItemUpgradeManager::m_CostUpgrade = {};
std::map<uint32 /* itemLevel */, uint32> ItemUpgradeManager::m_ItemUpgradeConversion = {};

void ItemUpgradeManager::LoadCosts()
{
    m_CostUpgrade = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM item_upgrade_cost");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 itemLevel = fields[0].Get<uint32>();
        uint32 inventoryType = fields[1].Get<uint32>();
        uint32 cosmicEssenceCost = fields[2].Get<uint32>();
        uint32 requiredItemId1 = fields[3].Get<uint32>();
        uint32 requiredItemId2 = fields[4].Get<uint32>();
        uint32 requiredItemCount1 = fields[5].Get<uint32>();
        uint32 requiredItemCount2 = fields[6].Get<uint32>();
        uint32 quality = fields[7].Get<uint32>();

        ItemUpgradeRequirement upgrade = { itemLevel, inventoryType, cosmicEssenceCost, requiredItemId1, requiredItemId2, requiredItemCount1, requiredItemCount2, quality };
        m_CostUpgrade.push_back(upgrade);

    } while (result->NextRow());
}

void ItemUpgradeManager::LoadItemsUpgrade()
{
    m_ItemUpgradeConversion = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM item_upgrade");

    if (!result)
        return;

    do
    {

        Field* fields = result->Fetch();
        uint32 item1 = fields[0].Get<uint32>();
        uint32 item2 = fields[1].Get<uint32>();
        m_ItemUpgradeConversion[item1] = item2;

    } while (result->NextRow());
}

bool ItemUpgradeManager::IsThisItemUpgradable(uint32 itemId)
{
    const ItemTemplate* itemTemplate = sObjectMgr->GetItemTemplate(itemId);

    if ((itemTemplate->Class != ITEM_CLASS_WEAPON && itemTemplate->Class != ITEM_CLASS_ARMOR))
    {
        return false;
    }

    if (itemId < 100000)
    {
        auto itr = m_ItemUpgradeConversion.find(itemId + 1);
        if (itr == m_ItemUpgradeConversion.end())
            return false;
    }

    uint32 itemLevel = itemTemplate->ItemLevel;

    if (itemLevel == sWorld->GetValue("CONFIG_MAX_ITEM_LEVEL_UPGRADE"))
        return false;

    return true;
}

ItemUpgradeRequirement* ItemUpgradeManager::GetItemsRequierement(Player* player, uint32 nextEntry)
{
    ItemUpgradeRequirement* nextUpgrade = nullptr;

    const ItemTemplate* itemTemplate = sObjectMgr->GetItemTemplate(nextEntry);

    if (!itemTemplate)
        return nextUpgrade;

    for (auto& upgrade : m_CostUpgrade)
    {
        if (upgrade.itemLevel == itemTemplate->ItemLevel && upgrade.inventoryType == itemTemplate->InventoryType && upgrade.quality == itemTemplate->Quality) {
            nextUpgrade = &upgrade;
            break;
        }
    }

    return nextUpgrade;
}

void ItemUpgradeManager::SendItemToUpgradeWithRequierements(Player* player, uint32 itemId)
{
    const ItemTemplate* itemTemplate = sObjectMgr->GetItemTemplate(itemId);

    if (!itemTemplate)
        return RunesManager::SendChat(player, "This item is not upgradable.");

    if(!IsThisItemUpgradable(itemId))
        return RunesManager::SendChat(player, "This item is not upgradable.");

    uint32 nextEntry = 0;

    if (itemId >= 100000) {
        nextEntry = itemId + 1;
    }
    else {
        auto itr = m_ItemUpgradeConversion.find(nextEntry);
        if (itr != m_ItemUpgradeConversion.end())
        {
            nextEntry = itr->second;
        }
    }

    ItemUpgradeRequirement* itemRequierment = GetItemsRequierement(player, nextEntry);

    if(!itemRequierment)
        return RunesManager::SendChat(player, "This item is not upgradable anymore.");

    std::string fmt =
        std::to_string(nextEntry)
        + ";" + std::to_string(itemRequierment->cosmicEssenceCost)
        + ";" + std::to_string(itemRequierment->requiredItemId1)
        + ";" + std::to_string(itemRequierment->requiredItemId2)
        + ";" + std::to_string(itemRequierment->requiredItemCount1)
        + ";" + std::to_string(itemRequierment->requiredItemCount2);

    sEluna->SendItemForUpgrade(player, fmt);
}


void ItemUpgradeManager::UpgradeItem(Player* player, uint32 entry)
{
    const ItemTemplate* itemTemplate = sObjectMgr->GetItemTemplate(entry);

    if (!itemTemplate)
        return;

    if ((itemTemplate->Class != ITEM_CLASS_WEAPON && itemTemplate->Class != ITEM_CLASS_ARMOR))
    {
        RunesManager::SendChat(player, "This item is not upgradable.");
        return;
    }

    uint32 nextEntry = 0;

    if (entry >= 100000) {
        nextEntry = entry + 1;
    }
    else {
        auto itr = m_ItemUpgradeConversion.find(nextEntry);
        if (itr != m_ItemUpgradeConversion.end())
        {
            nextEntry = itr->second;
        }
        else {
            RunesManager::SendChat(player, "This item is not upgradable.");
            return;
        }
    }

    const ItemTemplate* itemUpgrade = sObjectMgr->GetItemTemplate(nextEntry);

    if (!itemUpgrade)
        return;

    uint32 itemLevel = itemUpgrade->ItemLevel;
    
    if (itemUpgrade->Name1 != itemTemplate->Name1)
    {
        RunesManager::SendChat(player, "You can't do that.");
        return;
    }

    ItemUpgradeRequirement* itemRequierment = GetItemsRequierement(player, nextEntry);

    if(!itemRequierment)
        return RunesManager::SendChat(player, "This item is not upgradable.");

    if (!HasEnoughItemToUpgrade(player, itemRequierment))
    {
        RunesManager::SendChat(player, "You don't have the required items to upgrade this item.");
        return;
    }

    RemoveRequieredItem(player, itemRequierment);

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

void ItemUpgradeManager::RemoveRequieredItem(Player* player, ItemUpgradeRequirement* upgrade)
{
    if(upgrade->requiredItemId1 > 0)
        player->DestroyItemCount(upgrade->requiredItemId1, upgrade->requiredItemCount1, true);

    if(upgrade->requiredItemId2 > 0)
        player->DestroyItemCount(upgrade->requiredItemId2, upgrade->requiredItemCount2, true);

    player->DestroyItemCount(70009, upgrade->cosmicEssenceCost, true);
}

bool ItemUpgradeManager::HasEnoughItemToUpgrade(Player* player, ItemUpgradeRequirement* upgrade)
{
    if (upgrade->requiredItemId1 > 0 && upgrade->requiredItemId2 == 0)
        return player->HasItemCount(upgrade->requiredItemId1, upgrade->requiredItemCount1)
            && player->HasItemCount(70009, upgrade->cosmicEssenceCost);

    if (upgrade->requiredItemId1 > 0 && upgrade->requiredItemId2 > 0)
        return player->HasItemCount(upgrade->requiredItemId1, upgrade->requiredItemCount1) &&
            player->HasItemCount(upgrade->requiredItemId2, upgrade->requiredItemCount2)
            && player->HasItemCount(70009, upgrade->cosmicEssenceCost);

    return false;
}
