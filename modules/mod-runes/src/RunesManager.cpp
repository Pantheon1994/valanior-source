#include "RunesManager.h"
#include "boost/bind.hpp"
#include "Config.h"
#include "ElunaIncludes.h"
#include "LuaEngine.h"
#include "boost/iterator/counting_iterator.hpp"

std::map<uint32 /* SpellId */, Rune> RunesManager::m_Runes = {};
std::map<uint32 /* accountId */, std::vector<KnownRune>> RunesManager::m_KnownRunes = {};
std::map<uint64 /* guid */, std::vector<Loadout>> RunesManager::m_Loadout = {};
std::map<uint64 /* LoadoutId */, std::vector<SlotRune>> RunesManager::m_SlotRune = {};
std::map<uint32 /* accountId */, AccountProgression> RunesManager::m_Progression = {};
std::vector<SpellRuneConversion> RunesManager::m_SpellRuneConversion = {};

RuneConfig RunesManager::config = {};

void RunesManager::SetupConfig()
{
    config.enabled = sConfigMgr->GetOption<bool>("RuneManager.enabled", true);
    config.debug = false;
    config.maxSlots  = 18;
    config.defaultSlot = sConfigMgr->GetOption<uint32>("RuneManager.defaultSlot", 8);
    config.chanceDropRuneQualityWhite = sConfigMgr->GetOption<float>("RuneManager.chanceDropRuneQualityWhite", 90.0f);
    config.chanceDropRuneQualityGreen = sConfigMgr->GetOption<float>("RuneManager.chanceDropRuneQualityGreen", 10.0f);
    config.chanceDropRuneQualityBlue = sConfigMgr->GetOption<float>("RuneManager.chanceDropRuneQualityBlue", 0.2f);
    config.chanceDropRuneQualityEpic = sConfigMgr->GetOption<float>("RuneManager.chanceDropRuneQualityEpic", 0);
    config.chanceDropRuneQualityLegendary = sConfigMgr->GetOption<float>("RuneManager.chanceDropRuneQualityLegendary", 0);
    config.chanceDropRuneQualityRed = sConfigMgr->GetOption<float>("RuneManager.chanceDropRuneQualityRed", 0);
}

void RunesManager::LoadAllRunes()
{

    RunesManager::m_Runes = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM runes");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 id = fields[0].Get<uint32>();
        uint32 groupId = fields[1].Get<uint32>();
        int32 allowableClass = fields[2].Get<int32>();
        int32 allowableRace = fields[3].Get<int32>();
        int8 quality = fields[4].Get<int8>();
        int8 maxStacks = fields[5].Get<int8>();
        uint32 refundItemId = fields[6].Get<uint32>();
        uint32 refundDusts = fields[7].Get<uint32>();
        std::string keywords = fields[8].Get<std::string>();
        Rune rune = { id, groupId, allowableClass, allowableRace, quality, maxStacks, refundItemId, refundDusts, keywords };
        m_Runes.insert(std::make_pair(id, rune));
    } while (result->NextRow());

}

void RunesManager::SpellConversion(uint32 runeId, Player* player, bool apply)
{
    for (auto const& spell : m_SpellRuneConversion)
        if (spell.runeSpellId == runeId) {
            if (apply) {
                player->learnSpell(spell.newSpellId, false, false, true);
                player->removeSpell(spell.oldSpellId, SPEC_MASK_ALL, false, true);
            }   
            else {
                player->learnSpell(spell.oldSpellId, false, false, true);
                player->removeSpell(spell.newSpellId, SPEC_MASK_ALL, false, true);
            }
        }

}

void RunesManager::SendPlayerMessage(Player* player, std::string msg)
{
    player->GetSession()->SendAreaTriggerMessage(msg.c_str());
}

void RunesManager::LoadSpellsConversion()
{

    RunesManager::m_SpellRuneConversion = {};

    QueryResult result = WorldDatabase.Query("SELECT * FROM runes_spell_switch");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 runeSpellId = fields[0].Get<uint32>();
        uint32 oldSpellId = fields[1].Get<uint32>();
        uint32 newSpellId = fields[2].Get<int32>();
        SpellRuneConversion s = { runeSpellId, oldSpellId, newSpellId };
        m_SpellRuneConversion.push_back(s);
    } while (result->NextRow());

}

void RunesManager::LoadAccountsRunes()
{
    RunesManager::m_KnownRunes = {};

    QueryResult result = CharacterDatabase.Query("SELECT * FROM account_know_runes");

    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 accountId = fields[0].Get<uint32>();
        uint32 id = fields[1].Get<uint32>();
        uint32 runeId = fields[2].Get<uint32>();
        Rune rune = GetRuneBySpellId(runeId);
        KnownRune knowRune = { accountId, id, rune, 1 };
        m_KnownRunes[accountId].push_back(knowRune);
    } while (result->NextRow());


    for (auto& accountRunes : m_KnownRunes) {

        std::vector<KnownRune> newRunesForAccount = {};

        for (const auto& accountRune : accountRunes.second) {
            uint32 spellIdToFind = accountRune.rune.spellId; // ID du spell à rechercher
            int8 qualityToFind = accountRune.rune.quality;  // Qualité à rechercher

            auto ij = std::find_if(newRunesForAccount.begin(), newRunesForAccount.end(),
                [&](const KnownRune& accountRune) {
                return accountRune.rune.quality == qualityToFind && accountRune.rune.spellId == spellIdToFind;
            });

            if (ij != newRunesForAccount.end())
                ij->count += 1;
            else {
                newRunesForAccount.push_back(accountRune);
            }
        }

        m_KnownRunes[accountRunes.first] = newRunesForAccount;
    }

}

void RunesManager::LoadAllLoadout()
{

    RunesManager::m_Loadout = {};

    QueryResult result = CharacterDatabase.Query("SELECT * FROM character_rune_loadout ORDER BY `active` DESC");
    if (!result)
        return;
    do
    {
        Field* fields = result->Fetch();
        uint64 guid = fields[0].Get<uint64>();
        uint64 id = fields[1].Get<uint64>();
        std::string title = fields[2].Get<std::string>();
        bool active = fields[3].Get<bool>();
        Loadout loadout = { guid, id, title, active };
       m_Loadout[guid].push_back(loadout);
    } while (result->NextRow());
}

void RunesManager::LoadAllSlotRune()
{

    RunesManager::m_SlotRune = {};

    QueryResult result = CharacterDatabase.Query("SELECT * FROM character_rune_slots ORDER BY `order` DESC");
    if (!result)
        return;
    do
    {
        Field* fields = result->Fetch();
        uint64 loadoutId = fields[0].Get<uint64>();
        uint64 runeId = fields[1].Get<uint64>();
        uint64 runeSpellId = fields[2].Get<uint64>();
        uint32 order = fields[3].Get<uint32>();
        SlotRune slot = { loadoutId, runeId, runeSpellId, order };
        m_SlotRune[loadoutId].push_back(slot);
    } while (result->NextRow());
}

void RunesManager::LoadAllProgression()
{

    RunesManager::m_Progression = {};

    QueryResult result = CharacterDatabase.Query("SELECT * FROM character_rune_progression");
    if (!result)
        return;
    do
    {
        Field* fields = result->Fetch();
        uint32 accountId = fields[0].Get<uint32>();
        uint32 dusts  = fields[1].Get<uint32>();
        uint32 loadoutUnlocked  = fields[2].Get<uint32>();
        uint32 slotsUnlocked = fields[3].Get<uint32>();
        AccountProgression progression = { dusts, loadoutUnlocked, slotsUnlocked };
        m_Progression.insert(std::make_pair(accountId, progression));
    } while (result->NextRow());
}

void RunesManager::CreateDefaultCharacter(Player* player)
{
    CharacterDatabasePreparedStatement* stmt = nullptr;
    uint64 startIdSlot = 1;
    bool active = true;
    std::string slotDefault = "Default";
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_MAXID_LOADOUT);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        Field* fields = result->Fetch();
        startIdSlot = fields[0].Get<uint64>();
    }

    uint64 guid = player->GetGUID().GetCounter();
    uint32 accountId = player->GetSession()->GetAccountId();
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_FIRST_LOADOUT);
    stmt->SetData(0, guid);
    stmt->SetData(1, startIdSlot);
    stmt->SetData(2, slotDefault);
    stmt->SetData(3, active);

    CharacterDatabase.Execute(stmt);

    Loadout loadout = { guid, startIdSlot, slotDefault, true };
    m_Loadout[guid].push_back(loadout);

    CharacterDatabase.Query("INSERT INTO character_rune_progression (accountId, dusts, loadoutUnlocked, slotsUnlocked) VALUES ({}, 0, 0, 40) ", accountId);

    auto progression = m_Progression.find(player->GetSession()->GetAccountId());

    if (progression == m_Progression.end()) {
        AccountProgression progression = { 0, 0, 40 };
        m_Progression[accountId] = { progression };
    }

}


std::vector<std::string> RunesManager::RunesForClient(Player* player)
{
    std::vector<uint32> runeIds = {};
    std::vector<std::string > elements = {};
    auto known = m_KnownRunes.find(player->GetSession()->GetAccountId());
    auto pushRune = [&](Rune rune, uint32 id, bool known, uint32 count) {
        std::string fmt = 
                    std::to_string(rune.spellId)
            + ";" + std::to_string(rune.quality)
            + ";" + std::to_string(rune.maxStack)
            + ";" + std::to_string(rune.refundItemId)
            + ";" + std::to_string(rune.refundDusts)
            + ";" + rune.keywords
            + ";" + std::to_string(config.debug ? rune.spellId : id)
            + ";" + std::to_string(rune.allowableClass)
            + ";" + std::to_string(config.debug ? 1 : count)
        +";" + std::to_string(config.debug ? true : known);
        elements.push_back(fmt);
    };

    if (known != m_KnownRunes.end())
        for (auto const& kwownRune : known->second) {
            runeIds.push_back(kwownRune.rune.spellId);
            pushRune(kwownRune.rune, kwownRune.id, true, kwownRune.count);
        }

    for (auto it = m_Runes.begin(); it != m_Runes.end(); it++)
    {
        Rune rune = it->second;
        if (std::find(runeIds.begin(), runeIds.end(), rune.spellId) == runeIds.end()) {
            pushRune(rune, rune.spellId, false, 0);
        }
    }
    return elements;
}

std::vector<std::string> RunesManager::LoadoutCachingForClient(Player* player)
{
    std::vector<std::string> elements = {};

    auto match = m_Loadout.find(player->GetGUID().GetCounter());

    if (match != m_Loadout.end()) {
        for (auto const& loadout : match->second) {
            std::stringstream fmt;
            fmt << loadout.id << ";" << loadout.title << ";" << loadout.active;
            elements.push_back(fmt.str());
        }
    }
    return elements;
}

std::vector<std::string> RunesManager::SlotsCachingForClient(Player* player)
{
    std::vector<std::string> elements = {};
    uint64 activeId = GetActiveLoadoutId(player);

    if (activeId <= 0)
        return elements;

    auto match = m_SlotRune.find(activeId);

    if (match != m_SlotRune.end())
        for (auto const& slot : match->second) {
            Rune rune = GetRuneBySpellId(slot.runeSpellId);
            std::stringstream fmt;
            fmt << slot.id << ";" << slot.runeId << ";" << slot.runeSpellId << ";" << slot.order << ";" << std::to_string(rune.quality);
            elements.push_back(fmt.str());
        }

    return elements;
}


std::string RunesManager::ProgressionCachingForClient(Player* player)
{
    std::string value = "";
    auto progression = m_Progression.find(player->GetSession()->GetAccountId());

    if (progression != m_Progression.end()) {
        std::stringstream fmt;
        fmt << progression->second.dusts << ";" << progression->second.unlockedLoadoutCount << ";" << progression->second.unlockedSlotRunes << ";" << config.maxSlots;
        value = fmt.str();
    }
    return value;
}


Rune RunesManager::GetRuneBySpellId(uint32 runeId)
{
    auto it = m_Runes.find(runeId);

    if (it != m_Runes.end())
        return it->second;

    return {};
}

bool RunesManager::KnowRuneId(Player* player, uint64 runeId)
{
    if (!player)
        return false;

    auto it = m_KnownRunes.find(player->GetSession()->GetAccountId());

    if (it != m_KnownRunes.end()) {
        auto match = std::find_if(it->second.begin(), it->second.end(), [runeId](const KnownRune& account) {
            return account.id == runeId;
        });
        if (match != it->second.end())
            return true;
        else
            return false;
    }
    return false;
}

void RunesManager::RemoveSlotsOnCharacterDel(ObjectGuid guid)
{
    auto match = m_Loadout.find(guid.GetCounter());

    if (match != m_Loadout.end())
        for (auto const& loadout : match->second)
            if (loadout.active)
                CharacterDatabase.Query("DELETE FROM character_rune_slots WHERE id = {}", loadout.id);


    CharacterDatabase.Query("DELETE FROM character_rune_loadout WHERE guid = {}", guid.GetCounter());
}

void RunesManager::ApplyRunesOnLogin(Player* player)
{
    uint64 activeId = GetActiveLoadoutId(player);

    if (activeId <= 0)
        return;

    auto match = m_SlotRune.find(activeId);

    if (match != m_SlotRune.end())
        for (auto const& slot : match->second)
            if (!player->HasAura(slot.runeSpellId) && slot.id)
                player->AddAura(slot.runeSpellId, player);
}

Rune RunesManager::GetRuneById(Player* player, uint64 id)
{
    if (!player)
        return {};

    auto it = m_KnownRunes.find(player->GetSession()->GetAccountId());

    if (it != m_KnownRunes.end()) {
        auto match = std::find_if(it->second.begin(), it->second.end(), [id](const KnownRune& account) {
            return account.id == id;
        });
        if (match != it->second.end())
            return match->rune;
        else
            return {};
    }
    return {};
}

bool RunesManager::RuneAlreadyActivated(Player* player, uint64 runeId)
{
    uint64 activeId = GetActiveLoadoutId(player);

    if (activeId <= 0)
        return false;

    auto match = m_SlotRune.find(activeId);

    if (match != m_SlotRune.end())
        for (auto const& slot : match->second)
            if (slot.runeId == runeId)
                return true;

    return false;
}

uint64 RunesManager::GetActiveLoadoutId(Player* player)
{
    auto match = m_Loadout.find(player->GetGUID().GetCounter());

    if (match != m_Loadout.end())
        for (auto const& loadout: match->second)
            if (loadout.active)
                return loadout.id;

    return 0;
}

uint32 RunesManager::GetCoutSameGroupRune(Player* player, uint32 spellId)
{
    uint64 activeId = GetActiveLoadoutId(player);
    uint32 count = 0;

    if (activeId <= 0)
        return count;

    auto match = m_SlotRune.find(activeId);

    if (match != m_SlotRune.end()) {
        Rune rune = GetRuneBySpellId(spellId);
        count = std::count_if(match->second.begin(), match->second.end(),
            [&](const SlotRune& s)
        {
            Rune runeToCompare = GetRuneBySpellId(s.runeSpellId);
            return runeToCompare.groupId == rune.groupId;
        });
    }
    return count;
}

bool RunesManager::HasEnoughToUpgrade(Player* player, uint32 spellId)
{
    if (!player)
        return false;

    auto it = m_KnownRunes.find(player->GetSession()->GetAccountId());

    if (it != m_KnownRunes.end())
    {
        auto count = std::count_if(it->second.begin(), it->second.end(), [&](const KnownRune& account) {
            return account.rune.spellId == spellId;
        });
        return count >= 3;
    }

    return false;
}

uint32 RunesManager::GetCountActivatedRune(Player* player)
{
    uint64 activeId = GetActiveLoadoutId(player);
    uint32 count = 0;

    if (activeId <= 0)
        return count;

    auto match = m_SlotRune.find(activeId);

    if (match != m_SlotRune.end())
        count = match->second.size();

    return count;
}

void RunesManager::ActivateRune(Player* player, uint32 index, uint64 runeId)
{
    if (!player)
        return;

    if (player->isDead())
        return;

    if (!player->HasPlayerFlag(PLAYER_FLAGS_RESTING) || player->getLevel() <= 10) {
        SendPlayerMessage(player, "You can change only your rune inside resting area or under level 10.");
        return;
    }

    Rune rune = GetRuneById(player, runeId);

    if (config.debug)
        rune = GetRuneBySpellId(runeId);

    if (!rune) {
        SendPlayerMessage(player, "You don't have this rune.");
        return;
    }

    if((rune.allowableClass & player->getClassMask()) == 0)
    {
        SendPlayerMessage(player, "You can't activate this rune.");
        return;
    }

    /*if (RuneAlreadyActivated(player, runeId))
    {
        SendPlayerMessage(player, "This rune is already activated.");
        return;
    }*/

    auto progression = m_Progression.find(player->GetSession()->GetAccountId());

    if (GetCountActivatedRune(player) >= progression->second.unlockedSlotRunes)
    {
        SendPlayerMessage(player, "You have reach the maximum rune.");
        return;
    }

    const uint32 count = GetCoutSameGroupRune(player, rune.spellId);
    bool tooMuchStack = count >= rune.maxStack;

    if (tooMuchStack)
    {
        SendPlayerMessage(player, "You can't activate more of this rune.");
        return;
    }

    player->CastCustomSpell(79850, SPELLVALUE_BASE_POINT0, runeId, player, TRIGGERED_NONE);
}


void RunesManager::ResetAllSlots(Player* player)
{
    if (!player)
        return;

    uint64 activeId = GetActiveLoadoutId(player);

    if (activeId <= 0)
        return;

    CharacterDatabase.Query("DELETE FROM character_rune_slots WHERE id = {}", activeId);

    auto match = m_SlotRune.find(activeId);
    if (match != m_SlotRune.end()) {
        for (auto& slot : match->second) {
            player->RemoveAura(slot.runeSpellId);
        }
        match->second.clear();
    }

    sEluna->RefreshSlotsRune(player);
}

void RunesManager::ActivateLoadout(Player* player, uint64 newLoadoutId)
{
    uint32 activeId = GetActiveLoadoutId(player);

    if (activeId == newLoadoutId)
        return;

    auto match = m_Loadout.find(player->GetGUID().GetCounter());

    auto it = m_SlotRune.find(activeId);
    if (it != m_SlotRune.end()) {
        for (auto& slot : it->second) {
            player->RemoveAura(slot.runeSpellId);
            SpellConversion(slot.runeId, player, false);
        }
    }

    auto ij = m_SlotRune.find(newLoadoutId);
    if (ij != m_SlotRune.end()) {
        for (auto& slot : ij->second) {
            player->AddAura(slot.runeSpellId, player);
            SpellConversion(slot.runeId, player, true);
        }
    }

    if (match != m_Loadout.end())
        for (auto& loadout : match->second) {
            if (loadout.id == newLoadoutId)
                loadout.active = true;
            if (loadout.id == activeId)
                loadout.active = false;
        }

    sEluna->RefreshSlotsRune(player);
}

void RunesManager::DisableRune(Player* player, uint64 runeId)
{
    if (!player)
        return;

    if (player->isDead())
        return;

    if (!player->HasPlayerFlag(PLAYER_FLAGS_RESTING) || player->getLevel() <= 10) {
        SendPlayerMessage(player, "You can change only your rune inside resting area or under level 10.");
        return;
    }

    Rune rune = GetRuneById(player, runeId);

    if (config.debug)
        rune = GetRuneBySpellId(runeId);

    if (!rune)
    {
        SendPlayerMessage(player, "You don't have this rune.");
        return;
    }

    if (!RuneAlreadyActivated(player, runeId))
    {
        SendPlayerMessage(player, "This rune is not activated.");
        return;
    }

    RemoveRuneFromSlots(player, rune);
}

void RunesManager::RefundRune(Player* player, uint64 runeId)
{
    Rune rune = GetRuneById(player, runeId);

    if (!rune) {
        SendPlayerMessage(player, "You don't have this rune.");
        return;
    }

    RemoveRuneFromSlots(player, rune);
    player->AddItem(1000000, rune.refundDusts);
}

void RunesManager::UpgradeRune(Player* player, uint64 runeId)
{
    Rune rune = GetRuneById(player, runeId);

    if (!rune) {
        SendPlayerMessage(player, "You don't have this rune.");
        return;
    }

    if (!HasEnoughToUpgrade(player, rune.spellId)) {
        SendPlayerMessage(player, "You don't have enough of this similar rune to upgrade.");
        return;
    }
}

void RunesManager::AddRuneToSlot(Player* player, Rune rune, uint64 runeId)
{
    uint64 activeId = GetActiveLoadoutId(player);

    if (activeId <= 0)
        return;

    auto match = m_SlotRune.find(activeId);
    SlotRune slot = { activeId, runeId, rune.spellId, 1 };

    if (match != m_SlotRune.end()) {
        if (match->second.size() > 0) {
            slot.order = GetMissingSlotNumber(match->second, player);
        }
        match->second.push_back(slot);
    }
    else
        m_SlotRune[activeId].push_back(slot);


    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_RUNE_SLOT);
    stmt->SetData(0, slot.id);
    stmt->SetData(1, slot.runeId);
    stmt->SetData(2, slot.runeSpellId);
    stmt->SetData(3, slot.order);
    trans->Append(stmt);
    CharacterDatabase.CommitTransaction(trans);
    sEluna->RefreshSlotsRune(player);
}


void RunesManager::RemoveRuneFromSlots(Player* player, Rune rune)
{
    uint64 activeId = GetActiveLoadoutId(player);

    if (activeId <= 0)
        return;

    auto match = m_SlotRune.find(activeId);

    if (match == m_SlotRune.end())
        return;

    auto it = std::find_if(match->second.begin(),
        match->second.end(),
        [&]
    (const SlotRune& slot) -> bool { return slot.runeId == rune.spellId; });

    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_SLOT);
    stmt->SetData(0, uint32(it->order));
    stmt->SetData(1, uint32(activeId));
    CharacterDatabase.Execute(stmt);

    SpellConversion(rune.spellId, player, false);
    player->RemoveAura(rune.spellId);
    match->second.erase(it);

    sEluna->RefreshSlotsRune(player);
}

uint32 RunesManager::GetMissingSlotNumber(std::vector<SlotRune> slots, Player* p) {

    std::list<uint32> usedOrders;
    for (auto& slot : slots)
        usedOrders.push_back(slot.order);

    for (uint32 order = 1; order < config.maxSlots; order++)
        if (std::find(usedOrders.begin(), usedOrders.end(), order) == usedOrders.end())
            return order;


    return 1;
}
