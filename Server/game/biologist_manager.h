#ifndef __BIOLOGIST_MANAGER_H__
#define __BIOLOGIST_MANAGER_H__
#include "stdafx.h"
#include "char.h"

#include <string_view>
#include <array>
#include <map>

//quest_names
constexpr std::array<std::string_view,12> BiologistQuestNames = {
	"ue_collect_item_lv30",
	"ue_collect_item_lv40",
	"ue_collect_item_lv50",
	"ue_collect_item_lv60",
	"ue_collect_item_lv70",
	"ue_collect_item_lv75",
	"ue_collect_item_lv80",
	"ue_collect_item_lv90",
	"ue_collect_item_lv95",
	"ue_collect_item_lv100",
	"ue_collect_item_lv105",
};
//items
constexpr std::array<uint32_t,12> BiologistQuestItems = {
	30006, 30055, 30047, 30324, 30015, 30050, 30198, 30166, 30495, 100029, 30329, 100039
};
//cooldowns
constexpr std::array<uint32_t,12> BiologistQuestCooldowns = {
	3600, 0, 0, 0, 0, 3600, 7200, 10800, 10800, 14400, 14400, 18000
};
//pcts
constexpr std::array<uint32_t,12> BiologistQuestPCTs = {
	90, 90, 90, 90, 90, 90, 44, 42, 30, 38, 36, 34
};
//requested item limits
constexpr std::array<uint32_t,12> BiologistQuestItemLimits = {
	20, 20, 20, 25, 20, 25, 30, 35, 15, 40, 45, 50
};
//relevant quest_state
constexpr std::string_view BiologistQuestStateCollect = "finditem";
constexpr std::string_view BiologistQuestStateBack = "backtobio";
//special items
constexpr uint32_t BIOLOGIST_PCT_ADDER_VNUM = 102529;
constexpr uint32_t BIOLOGIST_PCT_ADDER_PLUS_VNUM = 102616;
constexpr uint32_t BIOLOGIST_TIME_DELETER_VNUM = 102517;
//relevant quest_flags
constexpr std::string_view BiologistQuestFlagTimer = ".collect_cd";
constexpr std::string_view BiologistQuestFlagItemsDeliveredCount = ".item_delivered_count";
//item limit
constexpr uint8_t BIOLOGIST_QUEST_ITEM_MAX_NUM = 5;
//quest max num
constexpr uint8_t BIOLOGIST_QUEST_MAX_NUM = 11;
//PCT ADDER VALUES
constexpr uint8_t BIOLOGIST_PCT_ADDER_VALUE = 10;
constexpr uint8_t BIOLOGIST_PCT_ADDER_PLUS_VALUE = 30;

class CBiologistManager : public singleton<CBiologistManager>
{
	public:
		CBiologistManager() = default;
		virtual ~CBiologistManager() = default;

		bool	IsQuestStatusFindItem(LPCHARACTER ch, std::string_view quest_name);
		void	SetQuestStateToBack(DWORD playerID, const uint8_t questID);
		void	SendBiologistManagerOpenCommand(LPCHARACTER ch, const uint8_t questID);
		bool	CheckOpenInterface(LPCHARACTER ch);
		time_t	GetRemainingTime(LPCHARACTER ch, const uint8_t questID);
		uint8_t	GetDeliveredItems(LPCHARACTER ch, const uint8_t questID);
		bool	IsValidQuestID(LPCHARACTER ch, const uint8_t questID);	
		void 	ExecuteDeliveryRequest(LPCHARACTER ch, uint8_t questID, uint8_t itemWantedCount, uint8_t elixirCount, uint8_t elixirPlusCount, uint8_t timeDeleterCount);
		void 	ResearchPacket(LPCHARACTER ch, const uint8_t questID, uint8_t subheader, uint8_t deliversCounter, uint8_t successDeliveries,uint8_t failedDeliveries,uint8_t  timeDeleterUses,uint8_t elixirUses,uint8_t elixirPlusUses);
};
#endif