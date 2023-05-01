#ifndef __BIOLOGIST_MANAGER_H__
#define __BIOLOGIST_MANAGER_H__
#include "stdafx.h"
#include "char.h"

#include <vector>
#include <map>
#include "utils.h"
#include "reminder_processor.h"

//relevant quest states
constexpr std::string_view BiologistQuestStateCollect = "finditem";
constexpr std::string_view BiologistQuestStateBack = "backtobio";
//relevant quest_flags
constexpr std::string_view BiologistQuestFlagTimer = ".collect_cd";
constexpr std::string_view BiologistQuestFlagItemsDeliveredCount = ".item_delivered_count";

class CBiologistManager : public singleton<CBiologistManager>, public ReminderProcessor
{
	public:
		CBiologistManager() = default;
		virtual ~CBiologistManager() = default;

		void 			ExecuteDeliveryRequest(LPCHARACTER ch, uint8_t questID, uint8_t itemWantedCount, uint8_t elixirCount, uint8_t elixirPlusCount, uint8_t timeDeleterCount);
		bool			CheckOpenInterface(LPCHARACTER ch);
		void			SendBiologistManagerOpenCommand(LPCHARACTER ch, const uint8_t questID);

//VARIABLES_SETTERS_GETTERS_START
		void			PopulateQuestNamesVector(std::string& quest_name);
		void			PopulateQuestItemVector(uint32_t quest_item);
		void			PopulateQuestCooldownsVector(uint32_t cooldown);
		void			PopulateQuestPCTsVector(uint32_t pct);
		void			PopulateQuestItemLimitsVector(uint32_t item_limit);
		
		void			SetBiologistPCTAdderVnum(uint32_t _biologistPCTAdderVnum) { biologistPCTAdderVnum = _biologistPCTAdderVnum; }
		void			SetBiologistPCTAdderPlusVnum(uint32_t _biologistPCTAdderPlusVnum) { biologistPCTAdderPlusVnum = _biologistPCTAdderPlusVnum; }
		void			SetBiologistPCTTimeDeleterVnum(uint32_t _biologistPCTTimeDeleterVnum) { biologistPCTTimeDeleterVnum = _biologistPCTTimeDeleterVnum; }
		void			SetBiologistQuestItemMaxNum(uint8_t _biologistQuestItemMaxNum) { biologistQuestItemMaxNum = _biologistQuestItemMaxNum; }
		void			SetBiologistPCTAdderValue(uint8_t _biologistPCTAdderValue) { biologistPCTAdderValue = _biologistPCTAdderValue; }
		void			SetBiologistPCTAdderPlusValue(uint8_t _biologistPCTAdderPlusValue) { biologistPCTAdderPlusValue = _biologistPCTAdderPlusValue; }
		
		uint32_t		GetBiologistPCTAdderVnum() { return biologistPCTAdderVnum; }
		uint32_t		GetBiologistPCTAdderPlusVnum() { return biologistPCTAdderPlusVnum; }
		uint32_t		GetBiologistPCTTimeDeleterVnum() { return biologistPCTTimeDeleterVnum; }
		uint8_t			GetBiologistQuestItemMaxNum() { return biologistQuestItemMaxNum; }
		uint8_t			GetBiologistPCTAdderValue() { return biologistPCTAdderValue; }
		uint8_t			GetBiologistPCTAdderPlusValue() { return biologistPCTAdderPlusValue; }

//VARIABLES_SETTERS_GETTERS_END

	private:
//INTERNAL_GENERAL_FUNCTIONS_START
		bool			IsQuestStatusFindItem(LPCHARACTER ch, const std::string& quest_name, uint8_t questID);
		void			SetQuestStateToBack(DWORD playerID, const uint8_t questID);
		size_t			GetBiologistQuestMaxNum() { return BiologistQuestNames.size(); }
		time_t			GetRemainingTime(LPCHARACTER ch, const uint8_t questID);
		uint8_t			GetDeliveredItems(LPCHARACTER ch, const uint8_t questID);
		bool			IsValidQuestID(LPCHARACTER ch, const uint8_t questID);	
		void 			ResearchPacket(LPCHARACTER ch, const uint8_t questID, uint8_t subheader, uint8_t deliversCounter, uint8_t successDeliveries,uint8_t failedDeliveries,uint8_t  timeDeleterUses,uint8_t elixirUses,uint8_t elixirPlusUses);
//INTERNAL_GENERAL_FUNCTIONS_END


	private:
		std::vector<std::string> BiologistQuestNames = {};
		std::vector<uint32_t> BiologistQuestItems = {};
		std::vector<uint32_t> BiologistQuestCooldowns = {};
		std::vector<uint8_t> BiologistQuestPCTs = {};
		std::vector<uint32_t> BiologistQuestItemLimits = {};
		
		uint32_t biologistPCTAdderVnum = 0;
		uint32_t biologistPCTAdderPlusVnum = 0;
		uint32_t biologistPCTTimeDeleterVnum = 0;	
		uint8_t biologistQuestItemMaxNum = 0;
		uint8_t biologistPCTAdderValue = 0;
		uint8_t biologistPCTAdderPlusValue = 0;
};
#endif