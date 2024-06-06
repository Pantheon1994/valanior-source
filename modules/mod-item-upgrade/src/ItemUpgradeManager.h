
#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "RunesManager.h"
#include "LuaEngine.h"
#include "Spell.h"

struct ItemUpgradeRequirement {
    uint32 itemLevel;
    uint32 inventoryType;
    uint32 cosmicEssenceCost;
    uint32 requiredItemId1;
    uint32 requiredItemId2;
    uint32 requiredItemCount1;
    uint32 requiredItemCount2;
    uint32 quality;
};

class ItemUpgradeManager {

public:
    static void LoadCosts();
    static void LoadItemsUpgrade();
    static bool IsThisItemUpgradable(uint32 itemId);
    static ItemUpgradeRequirement* GetItemsRequierement(Player* player, uint32 itemId);
    static void SendItemToUpgradeWithRequierements(Player* player, uint32 itemId);
    static void UpgradeItem(Player* player, uint32 itemId);
    static void RemoveRequieredItem(Player* player, ItemUpgradeRequirement* upgrade);
    static bool HasEnoughItemToUpgrade(Player* player, ItemUpgradeRequirement* upgrade);

private:
    static std::vector<ItemUpgradeRequirement> m_CostUpgrade;
    static std::map<uint32 /* item1 */, uint32 /* item1 */> m_ItemUpgradeConversion;


};
