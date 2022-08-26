//add the biologist manager include
#include "biologist_manager.h"

//after:
		case HEADER_CG_REFINE:
			Refine(ch, c_pData);
			break;
//add:
		case HEADER_CG_BIOLOGIST_MANAGER_OPEN:
			if(!ch->IsObserverMode())
				SendBiologistManagerOpenCommand(ch, c_pData);
			break;
		case HEADER_CG_BIOLOGIST_MANAGER_DELIVER:
			if(!ch->IsObserverMode())
				BiologistManagerDeliverItems(ch, c_pData);			
			break;
//at the bottom of the file add:

void CInputMain::SendBiologistManagerOpenCommand(LPCHARACTER ch, const char * data)
{
	if(ch != nullptr){ //paranoid
		if(!CBiologistManager::instance().CheckOpenInterface(ch)){
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You don't have any biologist quest active."));
			return;
		}
	}
}

void CInputMain::BiologistManagerDeliverItems(LPCHARACTER ch, const char * data)
{
	TPacketCGBiologistManagerDeliver * pinfo = (TPacketCGBiologistManagerDeliver *) data;
	uint8_t questID = pinfo->questID;
	uint8_t itemWantedCount = pinfo->itemWantedCount;
	uint8_t elixirCount = pinfo->elixirCount;
	uint8_t elixirPlusCount = pinfo->elixirPlusCount;
	uint8_t timeDeleterCount = pinfo->timeDeleterCount;
	if(ch != nullptr){
		CBiologistManager::instance().ExecuteDeliveryRequest(ch, questID, itemWantedCount, elixirCount, elixirPlusCount, timeDeleterCount);
	}
}
