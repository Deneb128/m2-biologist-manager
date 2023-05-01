//add above void RegisterGlobalFunctionTable(lua_State* L)
	int _add_biologist_info(lua_State* L)
	{
		std::string biologistQuestName = "";
		uint32_t biologistQuestItem = 0;
		uint32_t biologistQuestCooldowns = 0;
		uint32_t biologistQuestPCTs = 0;
		uint32_t biologistQuestItemLimits = 0;

		if(!lua_isstring(L, 1))
		{
			sys_err("_add_biologist_info first argument (biologistQuestName) is invalid (not a string)");
			return 0;
		}
		biologistQuestName = lua_tostring(L,1);

		if(biologistQuestName.empty())
		{
			sys_err("_add_biologist_info first argument (biologistQuestName) is an empty string");
			return 0;
		}

		if(!lua_isnumber(L, 2))
		{
			sys_err("_add_biologist_info second argument (biologistQuestItem) is invalid (not a number)");
			return 0;
		}
		biologistQuestItem = static_cast<uint32_t>(lua_tonumber(L, 2));

		if(!lua_isnumber(L, 3))
		{
			sys_err("_add_biologist_info third argument (biologistQuestCooldowns) is invalid (not a number)");
			return 0;			
		}

		biologistQuestCooldowns = static_cast<uint32_t>(lua_tonumber(L, 3));

		if(!lua_isnumber(L, 4))
		{
			sys_err("_add_biologist_info fourth argument (biologistQuestPCTs) is invalid (not a number)");
			return 0;			
		}

		biologistQuestPCTs = static_cast<uint32_t>(lua_tonumber(L, 4));		
		
		
		if(!lua_isnumber(L, 5))
		{
			sys_err("_add_biologist_info fifth argument (biologistQuestItemLimits) is invalid (not a number)");
			return 0;			
		}

		biologistQuestItemLimits = static_cast<uint32_t>(lua_tonumber(L, 5));

		CBiologistManager::instance().PopulateQuestNamesVector(biologistQuestName);
		CBiologistManager::instance().PopulateQuestItemVector(biologistQuestItem);
		CBiologistManager::instance().PopulateQuestCooldownsVector(biologistQuestCooldowns);
		CBiologistManager::instance().PopulateQuestPCTsVector(biologistQuestPCTs);
		CBiologistManager::instance().PopulateQuestItemLimitsVector(biologistQuestItemLimits);
		return 1;
	}

	int _add_biologist_globals(lua_State* L)
	{
		uint32_t biologistPCTAdderVnum = 0;
		uint32_t biologistPCTAdderPlusVnum = 0;
		uint32_t biologistPCTTimeDeleterVnum = 0;
		
		uint8_t biologistQuestItemMaxNum = 0;
		uint8_t biologistPCTAdderValue = 0;
		uint8_t biologistPCTAdderPlusValue = 0;

		if(!lua_isnumber(L, 1))
		{
			sys_err("_add_biologist_global first argument (biologistPCTAdderVnum) is invalid (not a number)");
			return 0;
		}
		biologistPCTAdderVnum = static_cast<uint32_t>(lua_tonumber(L, 1));

		if(!lua_isnumber(L, 2))
		{
			sys_err("_add_biologist_global second argument (biologistPCTAdderPlusVnum) is invalid (not a number)");
			return 0;
		}
		biologistPCTAdderPlusVnum = static_cast<uint32_t>(lua_tonumber(L, 2));

		if(!lua_isnumber(L, 3))
		{
			sys_err("_add_biologist_global third argument (biologistPCTTimeDeleterVnum) is invalid (not a number)");
			return 0;			
		}

		biologistPCTTimeDeleterVnum = static_cast<uint32_t>(lua_tonumber(L, 3));

		if(!lua_isnumber(L, 4))
		{
			sys_err("_add_biologist_global fourth argument (biologistQuestItemMaxNum) is invalid (not a number)");
			return 0;			
		}
		biologistQuestItemMaxNum = static_cast<uint8_t>(lua_tonumber(L, 4));

		if(!lua_isnumber(L, 5))
		{
			sys_err("_add_biologist_global fourth argument (biologistPCTAdderValue) is invalid (not a number)");
			return 0;			
		}
		biologistPCTAdderValue = static_cast<uint8_t>(lua_tonumber(L, 5));

		if(!lua_isnumber(L, 6))
		{
			sys_err("_add_biologist_global fourth argument (biologistPCTAdderPlusValue) is invalid (not a number)");
			return 0;			
		}
		biologistPCTAdderPlusValue = static_cast<uint8_t>(lua_tonumber(L, 6));

		CBiologistManager::instance().SetBiologistPCTAdderVnum(biologistPCTAdderVnum);
		CBiologistManager::instance().SetBiologistPCTAdderPlusVnum(biologistPCTAdderPlusVnum);
		CBiologistManager::instance().SetBiologistPCTTimeDeleterVnum(biologistPCTTimeDeleterVnum);
		CBiologistManager::instance().SetBiologistQuestItemMaxNum(biologistQuestItemMaxNum);
		CBiologistManager::instance().SetBiologistPCTAdderValue(biologistPCTAdderValue);
		CBiologistManager::instance().SetBiologistPCTAdderPlusValue(biologistPCTAdderPlusValue);
		return 1;
	}

	//add above
	//{	NULL,	NULL	}
			{	"add_biologist_info",			_add_biologist_info	   		},
			{	"add_biologist_globals",		_add_biologist_globals	   	},