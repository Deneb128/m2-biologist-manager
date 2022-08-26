//afterL
	Set(HEADER_CG_MALL_CHECKOUT				, sizeof(TPacketCGSafeboxCheckout)		, "MallCheckout"			, true , true);
//add
	Set(HEADER_CG_BIOLOGIST_MANAGER_OPEN	, sizeof(TPacketCGBiologistManagerOpen)	, "TPacketCGBiologistManagerOpen", true , true);
	Set(HEADER_CG_BIOLOGIST_MANAGER_DELIVER	, sizeof(TPacketCGBiologistManagerDeliver)	, "TPacketCGBiologistManagerDeliver", true , true);

//if you don't have too bool parameters at the end, just add a single true