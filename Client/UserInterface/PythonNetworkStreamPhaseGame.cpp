//before:
			default:
				ret = RecvDefaultPacket(header);
				break;
//add:				
			case HEADER_GC_BIOLOGIST_MANAGER_OPEN:
				ret = RecvBiologistManagerOpen();
				break;

			case HEADER_GC_BIOLOGIST_MANAGER_RESEARCH:
				ret = RecvBiologistManagerResearch();


//at the bottom of the file add:
bool CPythonNetworkStream::RecvBiologistManagerOpen()
{
	TPacketGCBiologistManagerOpen packet;
	if (!Recv(sizeof(packet), &packet))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BiologistManagerOpen", Py_BuildValue("(iii)", packet.biologistQuestID, packet.remainingTime, packet.deliveredItems));
	return true;
}

bool CPythonNetworkStream::RecvBiologistManagerResearch()
{
	TPacketGCBiologistManagerSendResearch packet;
	if (!Recv(sizeof(packet), &packet))
		return false;
		
	switch (packet.subheader)
	{
		case SEND_RESEARCH_INFO:
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BiologistManagerResearch", Py_BuildValue("(iiiiiii)", packet.deliversCounter, packet.successDeliveries, packet.failedDeliveries, packet.timeDeleterUses, packet.elixirUses, packet.elixirPlusUses, packet.remainingTime));
		break;

		case SEND_RESEARCH_COMPLETE:
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_BiologistManagerResearchComplete", Py_BuildValue("()"));
		break;

		default:
			TraceError("CPythonNetworkStream::RecvBiologistManagerResearchPacket: Unknown subheader\n");
		break;
	}		
	return true;
}

bool CPythonNetworkStream::SendBiologistManagerOpenCommand()
{
	TPacketCGBiologistManagerOpen packet;
	packet.header = HEADER_CG_BIOLOGIST_MANAGER_OPEN;

	if (!Send(sizeof(packet), &packet))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::BiologistManagerDeliverItems(uint8_t questID, uint8_t itemWantedCount, uint8_t elixirCount, uint8_t elixirPlusCount, uint8_t timeDeleterCount)
{
	TPacketCGBiologistManagerDeliver packet;
	packet.header = HEADER_CG_BIOLOGIST_MANAGER_DELIVER;
	packet.questID = questID;
	packet.itemWantedCount = itemWantedCount;
	packet.elixirCount = elixirCount;
	packet.elixirPlusCount = elixirPlusCount;
	packet.timeDeleterCount = timeDeleterCount;
	
	if (!Send(sizeof(packet), &packet))
		return false;

	return SendSequence();
}
