//after:
			Set(HEADER_GC_AFFECT_REMOVE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCAffectRemove), STATIC_SIZE_PACKET));
//add:
			Set(HEADER_GC_BIOLOGIST_MANAGER_OPEN,	CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCBiologistManagerOpen), STATIC_SIZE_PACKET));
			Set(HEADER_GC_BIOLOGIST_MANAGER_RESEARCH,	CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCBiologistManagerSendResearch), STATIC_SIZE_PACKET));
			
