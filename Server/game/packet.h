//after:	
	HEADER_CG_MY_SHOP_EX			= 117,
//add:
	HEADER_CG_BIOLOGIST_MANAGER_OPEN	= 221,
	HEADER_CG_BIOLOGIST_MANAGER_DELIVER	= 222,

//after:
	HEADER_GC_AUTH_SUCCESS				= 150,
//add:
	HEADER_GC_BIOLOGIST_MANAGER_OPEN		= 221,
	HEADER_GC_BIOLOGIST_MANAGER_RESEARCH	= 222,

//at the bottom add, before:
#pragma pack()
#endif
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

#pragma pack()
#endif
