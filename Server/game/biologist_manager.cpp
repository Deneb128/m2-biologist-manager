#include "biologist_manager.h"
#include "packet.h"
#include "questmanager.h"
#include "desc.h"
#include "item.h"
namespace utils{
	std::string string_view_concat(std::string_view a, std::string_view b){

		std::string rv(a.size() + b.size(), '\0');

		std::copy(b.begin(), b.end(),
				std::copy(a.begin(), a.end(), rv.begin()));

		return rv;
	}

	std::string view_to_string(std::string_view a){
		std::string st = {a.begin(), a.end()};
		return st;
	}
}

bool CBiologistManager::IsValidQuestID(LPCHARACTER ch, const uint8_t questID)
{
	if(questID > this->GetBiologistQuestMaxNum())
		return false;

	auto pPC = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());
	if(pPC == nullptr){
		return false;
	}	
	std::string questName = BiologistQuestNames.at(questID);
	std::string questState = utils::view_to_string(BiologistQuestStateCollect);
	auto findItemValue = quest::CQuestManager::Instance().GetQuestStateIndex(questName, questState);

	std::string questFlag = BiologistQuestNames.at(questID) + ".__status";
	int questStateValue = pPC->GetFlag(questFlag);

	if(findItemValue != questStateValue)
		return false;
	return true;
}

bool CBiologistManager::IsQuestStatusFindItem(LPCHARACTER ch,const std::string& quest_name, uint8_t questID)
{

	auto pPC = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());
	if(pPC == nullptr){
		return false;
	}

	std::string questState = utils::view_to_string(BiologistQuestStateCollect);
	auto findItemValue = quest::CQuestManager::Instance().GetQuestStateIndex(quest_name, questState);
	std::string questFlag = quest_name + ".__status";
	std::string questFlagItem = (quest_name + utils::view_to_string(BiologistQuestFlagItemsDeliveredCount));

	const int questStateValue = pPC->GetFlag(questFlag);
	const uint32_t questFlagItemCount = pPC->GetFlag(questFlagItem);

	//if the quest has not started yet, the status can be 0
	//therefore if 0, the interface cannot be opened
	if(questStateValue == 0)
		return false;
	//if it's not at finditem state, it cannot open the interface, it's in a
	//backtobio or __COMPLETE__ or whatever else state
	if(questStateValue != findItemValue)
		return false;
	//otherwise it's in a "finditem" state,

	if(questFlagItemCount >= BiologistQuestItemLimits[questID])
		return false;

	return true;
}

void CBiologistManager::SetQuestStateToBack(DWORD playerID, const uint8_t questID)
{
	auto pPC = quest::CQuestManager::instance().GetPC(playerID);
	if(pPC == nullptr){
		return;
	}	
	std::string questName = BiologistQuestNames.at(questID);
	std::string questState =  utils::view_to_string(BiologistQuestStateBack);

	pPC->SetQuestState(questName, questState);
	pPC->DoQuestStateChange();
}

bool CBiologistManager::CheckOpenInterface(LPCHARACTER ch)
{
	uint8_t iterVal = 0;
	for(const auto& val : BiologistQuestNames)
	{
		if(IsQuestStatusFindItem(ch, val) == true){
			SendBiologistManagerOpenCommand(ch, iterVal);
			return true;
		}
		++iterVal;
	}
	return false;
}

void CBiologistManager::SendBiologistManagerOpenCommand(LPCHARACTER ch, const uint8_t questID)
{
	time_t remainingTime = GetRemainingTime(ch, questID);

	TPacketGCBiologistManagerOpen p;
	p.header = HEADER_GC_BIOLOGIST_MANAGER_OPEN;
	p.biologistQuestID = questID;
	p.remainingTime = remainingTime <= 0 ? 0 : remainingTime;
	p.deliveredItems = GetDeliveredItems(ch, questID);


	ch->GetDesc()->Packet(&p, sizeof(TPacketGCBiologistManagerOpen));
}

time_t CBiologistManager::GetRemainingTime(LPCHARACTER ch, const uint8_t questID)
{
	auto pPC = quest::CQuestManager::instance().GetPCForce(ch->GetPlayerID());
	std::string questName = utils::string_view_concat(BiologistQuestNames.at(questID), BiologistQuestFlagTimer);
	return floor(pPC->GetFlag(questName) - get_global_time());
}

time_t CBiologistManager::GetRemainingTime(LPCHARACTER ch, const uint8_t questID)
{
	auto pPC = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());
	std::string questName = BiologistQuestNames.at(questID) + utils::view_to_string(BiologistQuestFlagTimer);
	return floor(pPC->GetFlag(questName) - get_global_time());
}

void CBiologistManager::ExecuteDeliveryRequest(LPCHARACTER ch, uint8_t questID, uint8_t itemWantedCount,  uint8_t elixirCount, uint8_t elixirPlusCount, uint8_t timeDeleterCount)
{
	if (ch->GetDesc() == nullptr) {
		return;
	}

	if (!IsValidQuestID(ch,questID)) {
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("An error occurred. Please contact an admin %s."), "[ERROR: 3009]");
		ch->ChatPacket(CHAT_TYPE_INFO, "questID: %d", questID);
		ch->UpdateBiologistRequestPulse();
		return;
	}
	//double checks
	uint8_t _itemWantedCount = itemWantedCount > this->GetBiologistQuestMaxNum() ? this->GetBiologistQuestMaxNum() : itemWantedCount;
	uint8_t _elixirCount = elixirCount > _itemWantedCount ? _itemWantedCount : elixirCount;
	uint8_t _elixirPlusCount = elixirPlusCount > _itemWantedCount ? _itemWantedCount : elixirPlusCount;
	uint8_t _timeDeleterCount = timeDeleterCount > _itemWantedCount ? _itemWantedCount : timeDeleterCount;

	auto pPC = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());
	if(pPC == nullptr){
		return;
	}	
	std::string timerFlag = BiologistQuestNames.at(questID) + utils::view_to_string(BiologistQuestFlagTimer);
	uint32_t timerFlagValue = 0;

	std::string quantityDeliveredFlag = BiologistQuestNames.at(questID) + utils::view_to_string(BiologistQuestFlagItemsDeliveredCount);
	uint8_t quantityDeliveredFlagValue = pPC->GetFlag(quantityDeliveredFlag);

	//for idiots
	const uint8_t pctThreshold = 100 + this->GetBiologistPCTAdderValue();
	const uint8_t pctThresholdPlus = 100 + this->GetBiologistPCTAdderPlusValue();

	//system message
	uint8_t successDeliveries = 0;
	uint8_t failedDeliveries = 0;
	uint8_t timeDeleterUses = 0;
	uint8_t elixirUses = 0;
	uint8_t elixirPlusUses = 0;
	
	uint8_t deliversCounter = 0;
	
	for(; deliversCounter <= _itemWantedCount; deliversCounter++)
	{
		auto itemToDeliver = ch->FindSpecifyItem(BiologistQuestItems.at(questID)); //check item to deliver

		timerFlagValue = pPC->GetFlag(timerFlag);
		if(static_cast<time_t>(timerFlagValue) > get_global_time()) //check quest_cooldown
		{
			if(_timeDeleterCount > 0)
			{
				auto itemTimeDeleter = ch->FindSpecifyItem(this->GetBiologistPCTTimeDeleterVnum()); // check time deleter item
				if(itemTimeDeleter != nullptr){
					itemTimeDeleter->SetCount(itemTimeDeleter->GetCount() - 1); //remove the item
					pPC->SetFlag(timerFlag, 0); //remove cooldown
					++timeDeleterUses;
					--_timeDeleterCount;
				}
				else{
					//send packet result
					ResearchPacket(ch, questID, SEND_RESEARCH_INFO, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses);
					ch->UpdateBiologistRequestPulse();
					return;
				}
			}
			else{
				//send packet result
				ResearchPacket(ch, questID, SEND_RESEARCH_INFO, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses);
				ch->UpdateBiologistRequestPulse();
				return;
			}
		}
		//all items delivered, but we need to pass once again
		//to check for the latest time deleter item
		if(deliversCounter == _itemWantedCount){
			ResearchPacket(ch, questID, SEND_RESEARCH_INFO, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses);
			ch->UpdateBiologistRequestPulse();
			return;
		}

		if(itemToDeliver == nullptr){
			ResearchPacket(ch, questID, SEND_RESEARCH_INFO, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses);
			ch->UpdateBiologistRequestPulse();
			return;
		}
		uint8_t pct = BiologistQuestPCTs.at(questID);
		if(_elixirCount > 0) //looking if to add pct
		{
			auto itemPctAdder = ch->FindSpecifyItem(this->GetBiologistPCTAdderVnum()); // check elixir
			if(itemPctAdder != nullptr)
			{			
				//if base pct is 99 and someone wants to make it 100%, then, sure, by all means. 
				//But if it goes higher than that, it means that idiot just went ahead anyway
				//so, let's try to save them from their stupidity
				//LEGIT IDIOT PROOF
				if((pct + this->GetBiologistPCTAdderValue()) < pctThreshold){
					pct += this->GetBiologistPCTAdderValue();
					itemPctAdder->SetCount(itemPctAdder->GetCount() - 1);
					--_elixirCount;
					++elixirUses;
				}
			}
		}
		if(_elixirPlusCount > 0) //looking if to add more pct
		{
			auto itemPctAdderPlus = ch->FindSpecifyItem(this->GetBiologistPCTAdderPlusVnum()); // check elixir
			if(itemPctAdderPlus != nullptr)
			{			
				//if base pct is 99 and someone wants to make it 100%, then, sure, by all means. 
				//But if it goes higher than that, it means that idiot just went ahead anyway
				//so, let's try to save them from their stupidity
				//LEGIT IDIOT PROOF, AGAIN
				if((pct + this->GetBiologistPCTAdderPlusValue()) < pctThresholdPlus){
					pct += this->GetBiologistPCTAdderPlusValue();
					itemPctAdderPlus->SetCount(itemPctAdderPlus->GetCount() - 1);
					--_elixirPlusCount;
					++elixirPlusUses;
				}
			}			
		}

		if(number(1, 100) <= pct) //success
		{
			++quantityDeliveredFlagValue;
			pPC->SetFlag(quantityDeliveredFlag, quantityDeliveredFlagValue); //set the delivered items flag count
			itemToDeliver->SetCount(itemToDeliver->GetCount() - 1); //remove the item to deliver
			if(quantityDeliveredFlagValue >= BiologistQuestItemLimits.at(questID)){ // no more items to deliver
				pPC->SetFlag(timerFlag, 0); //remove cooldown
				SetQuestStateToBack(ch->GetPlayerID(), questID);
				ResearchPacket(ch, questID, SEND_RESEARCH_COMPLETE, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses);
				ch->UpdateBiologistRequestPulse();
				return;
			}
			else{ //set cooldown for success delivery
				pPC->SetFlag(timerFlag, get_global_time() + BiologistQuestCooldowns.at(questID));
				++successDeliveries;
			}
		}
		else{ //fail, but we don't set the cooldown for failing
			itemToDeliver->SetCount(itemToDeliver->GetCount() - 1); //remove the item to deliver
			pPC->SetFlag(timerFlag, 0);
			++failedDeliveries;
		}
	}
	//send packet research with result
	ResearchPacket(ch, questID, SEND_RESEARCH_INFO, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses);
	ch->UpdateBiologistRequestPulse();
	
}

void CBiologistManager::ResearchPacket(LPCHARACTER ch, const uint8_t questID, uint8_t subheader, uint8_t deliversCounter, uint8_t successDeliveries, uint8_t failedDeliveries, uint8_t  timeDeleterUses, uint8_t elixirUses, uint8_t elixirPlusUses)
{
	if(ch == nullptr)
		return;

	if(ch->GetDesc() == nullptr)
		return;

	time_t remainingTime = GetRemainingTime(ch, questID);

	TPacketGCBiologistManagerSendResearch p;
	p.header = HEADER_GC_BIOLOGIST_MANAGER_RESEARCH;
	p.subheader = subheader;
	p.deliversCounter = deliversCounter;
	p.successDeliveries = successDeliveries;
	p.failedDeliveries = failedDeliveries;
	p.elixirUses = elixirUses;
	p.elixirPlusUses = elixirPlusUses;
	p.timeDeleterUses = timeDeleterUses;
	p.remainingTime = remainingTime <= 0 ? 0 : remainingTime;

	ch->GetDesc()->Packet(&p, sizeof(TPacketGCBiologistManagerSendResearch));
}

void CBiologistManager::PopulateQuestNamesVector(std::string& quest_name)
{
	BiologistQuestNames.emplace_back(quest_name);
}

void CBiologistManager::PopulateQuestItemVector(uint32_t quest_item)
{
	BiologistQuestItems.emplace_back(quest_item);
}

void CBiologistManager::PopulateQuestCooldownsVector(uint32_t cooldown)
{
	BiologistQuestCooldowns.emplace_back(cooldown);
}

void CBiologistManager::PopulateQuestPCTsVector(uint32_t pct)
{
	BiologistQuestPCTs.emplace_back(pct);
}

void CBiologistManager::PopulateQuestItemLimitsVector(uint32_t item_limit)
{
	BiologistQuestItemLimits.emplace_back(item_limit);
}