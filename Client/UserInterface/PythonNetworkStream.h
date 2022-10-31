
After:
		// Mall
		bool RecvMallOpenPacket();
		bool RecvMallItemSetPacket();
		bool RecvMallItemDelPacket();
Add:

		bool RecvBiologistManagerOpen();
		bool RecvBiologistManagerResearch();


		
After:

		// Handshake
		bool RecvHandshakePacket();
		bool RecvHandshakeOKPacket();

Add:
		// Biologist Manager
		bool SendBiologistManagerOpenCommand();
		bool BiologistManagerDeliverItems(uint8_t questID, uint8_t itemWantedCount, uint8_t elixirCount, uint8_t elixirPlusCount, uint8_t timeDeleterCount);
