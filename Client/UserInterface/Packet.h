//before 	HEADER_CG_KEY_AGREEMENT = 0xfb, // _IMPROVED_PACKET_ENCRYPTION_
add:
	HEADER_CG_BIOLOGIST_MANAGER_OPEN 			= 221,
	HEADER_CG_BIOLOGIST_MANAGER_DELIVER			= 222,


//before 	HEADER_GC_KEY_AGREEMENT_COMPLETED = 0xfa, // _IMPROVED_PACKET_ENCRYPTION_
add:
	HEADER_GC_BIOLOGIST_MANAGER_OPEN	= 221,
	HEADER_GC_BIOLOGIST_MANAGER_RESEARCH	= 222,


//At the bottom of the file, before #pragma pack(pop)
//add:
typedef struct SPacketGCBiologistManagerOpen
{
	BYTE			header;
	BYTE			biologistQuestID;
	unsigned int	remainingTime;
	uint8_t			deliveredItems;
} TPacketGCBiologistManagerOpen;

typedef struct SPacketCGBiologistManagerOpen
{
	BYTE	header;
} TPacketCGBiologistManagerOpen;

typedef struct SPacketCGBiologistManagerDeliver
{
	BYTE	header;
	uint8_t	questID;
	uint8_t	itemWantedCount;
	uint8_t	elixirCount;
	uint8_t	elixirPlusCount;
	uint8_t	timeDeleterCount;
} TPacketCGBiologistManagerDeliver;

enum BiologistManagerResearchSubheaders
{
	SEND_RESEARCH_INFO,
	SEND_RESEARCH_COMPLETE,
};
typedef struct SPacketGCBiologistManagerSendResearch
{
	BYTE			header;
	BYTE			subheader;
	uint8_t			deliversCounter;
	uint8_t			successDeliveries;
	uint8_t			failedDeliveries;
	uint8_t			timeDeleterUses;
	uint8_t			elixirUses;
	uint8_t 		elixirPlusUses;
	unsigned int	remainingTime;
} TPacketGCBiologistManagerSendResearch;
