#pragma once

#include "../EterLibrary/FuncObject.h"
#include "../EterLibrary/NetStream.h"
#include "../EterLibrary/NetPacketHeaderMap.h"
#include "InsultChecker.h"
#include "packet.h"
#include "PythonSwitchbot.h"

class CInstanceBase;
class CNetworkActorManager;
struct SNetworkActorData;
struct SNetworkUpdateActorData;

class CPythonNetworkStream : public CNetworkStream, public CSingleton<CPythonNetworkStream>
{
	public:
		enum
		{
			SERVER_COMMAND_LOG_OUT = 0,
			SERVER_COMMAND_RETURN_TO_SELECT_CHARACTER = 1,
			SERVER_COMMAND_QUIT = 2,

			MAX_ACCOUNT_PLAYER
		};
		
		enum
		{
			ERROR_NONE,
			ERROR_UNKNOWN,
			ERROR_CONNECT_MARK_SERVER,			
			ERROR_LOAD_MARK,
			ERROR_MARK_WIDTH,
			ERROR_MARK_HEIGHT,

			// MARK_BUG_FIX
			ERROR_MARK_UPLOAD_NEED_RECONNECT,
			ERROR_MARK_CHECK_NEED_RECONNECT,
			// END_OF_MARK_BUG_FIX
		};

		enum
		{
			ACCOUNT_CHARACTER_SLOT_ID,
			ACCOUNT_CHARACTER_SLOT_NAME,
			ACCOUNT_CHARACTER_SLOT_RACE,
			ACCOUNT_CHARACTER_SLOT_LEVEL,
			ACCOUNT_CHARACTER_SLOT_STR,
			ACCOUNT_CHARACTER_SLOT_DEX,
			ACCOUNT_CHARACTER_SLOT_HTH,
			ACCOUNT_CHARACTER_SLOT_INT,
			ACCOUNT_CHARACTER_SLOT_PLAYTIME,
			ACCOUNT_CHARACTER_SLOT_FORM,
			ACCOUNT_CHARACTER_SLOT_ADDR,
			ACCOUNT_CHARACTER_SLOT_PORT,
			ACCOUNT_CHARACTER_SLOT_GUILD_ID,
			ACCOUNT_CHARACTER_SLOT_GUILD_NAME,
			ACCOUNT_CHARACTER_SLOT_HAIR,
		};

		enum
		{
			PHASE_WINDOW_LOGO,
			PHASE_WINDOW_LOGIN,
			PHASE_WINDOW_SELECT,
			PHASE_WINDOW_CREATE,
			PHASE_WINDOW_LOAD,
			PHASE_WINDOW_GAME,
			PHASE_WINDOW_EMPIRE,
			PHASE_WINDOW_NUM,
		};

	public:
		CPythonNetworkStream();
		virtual ~CPythonNetworkStream();
		
		bool SendSpecial(int nLen, void * pvBuf);

		void StartGame();
		void Warp(LONG lGlobalX, LONG lGlobalY);
		
		void NotifyHack(const char* c_szMsg);		
		void SetWaitFlag();

		void SendEmoticon(UINT eEmoticon);

		void ExitApplication();
		void ExitGame();
		void LogOutGame();
		void AbsoluteExitGame();
		void AbsoluteExitApplication();

		void EnableChatInsultFilter(bool isEnable);		
		bool IsChatInsultIn(const char* c_szMsg);
		bool IsInsultIn(const char* c_szMsg);

		DWORD GetGuildID();

		UINT UploadMark(const char* c_szImageFileName);
		UINT UploadSymbol(const char* c_szImageFileName);

		bool LoadInsultList(const char* c_szInsultListFileName);
		bool LoadConvertTable(DWORD dwEmpireID, const char* c_szFileName);

		UINT		GetAccountCharacterSlotDatau(UINT iSlot, UINT eType);
		const char* GetAccountCharacterSlotDataz(UINT iSlot, UINT eType);

		// SUPPORT_BGM
		const char*		GetFieldMusicFileName();
		float			GetFieldMusicVolume();
		// END_OF_SUPPORT_BGM

		bool IsSelectedEmpire();

		void ToggleGameDebugInfo();

		void SetMarkServer(const char* c_szAddr, UINT uPort);
		void ConnectLoginServer(const char* c_szAddr, UINT uPort);
		void ConnectGameServer(UINT iChrSlot);

		void SetLoginInfo(const char* c_szID, const char* c_szPassword);
		void SetLoginKey(DWORD dwLoginKey);
		void ClearLoginInfo( void );

		void SetHandler(PyObject* poHandler);
		void SetPhaseWindow(UINT ePhaseWnd, PyObject* poPhaseWnd);
		void ClearPhaseWindow(UINT ePhaseWnd, PyObject* poPhaseWnd);
		void SetServerCommandParserWindow(PyObject* poPhaseWnd);

		bool SendAttackPacket(UINT uMotAttack, DWORD dwVIDVictim, BOOL bPacket, BlendingPosition& sBlending);
		bool SendCharacterStatePacket(const TPixelPosition& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg);
		bool SendUseSkillPacket(DWORD dwSkillIndex, DWORD dwTargetVID=0);
		bool SendTargetPacket(DWORD dwVID);

		// OLDCODE:
		bool SendCharacterStartWalkingPacket(float fRotation, long lx, long ly);
		bool SendCharacterEndWalkingPacket(float fRotation, long lx, long ly);
		bool SendCharacterCheckWalkingPacket(float fRotation, long lx, long ly);

		bool SendCharacterPositionPacket(BYTE iPosition);

		bool SortInventory(BYTE invType, BYTE option);

		bool SendPlayerInfo(const char * szPlayerName);
		bool SendAchievementInfo(DWORD dwCategory);
		
		bool SendItemUsePacket(TItemPos pos);
		bool SendItemUseToItemPacket(TItemPos source_pos, TItemPos target_pos);
		bool SendItemUseToItemExPacket(TItemPos source_pos, TItemPos target_pos, int nArgument);
		bool SendItemDropPacket(TItemPos pos, DWORD elk);
		bool SendItemDeletePacket(TItemPos item_pos);
		bool SendItemDropPacketNew(TItemPos pos, DWORD elk, DWORD count);
		bool SendItemMovePacket(TItemPos pos, TItemPos change_pos, WORD num);
		bool SendItemPickUpPacket(DWORD vid);

		bool SendWikiRequestInfo(unsigned long long retID, DWORD vnum, bool isMob);
		void ToggleWikiWindow();

		bool DungeonTeleport(DWORD coordX, DWORD coordY, DWORD dwMinLevel, DWORD dwMaxLevel);;

		bool SendQuickSlotAddPacket(WORD wpos, BYTE type, WORD pos);
		bool SendQuickSlotDelPacket(WORD wpos);
		bool SendQuickSlotMovePacket(WORD wpos, WORD change_pos);

		// PointReset �� �ӽ�
		bool SendPointResetPacket();

		// Shop
		bool SendShopEndPacket();
		bool SendShopBuyPacket(WORD wCount);
		bool SendShopSellPacket(TItemPos ItemPos, WORD wCount);
		bool SendShopSellPacketDirect(TItemPos ItemPos, WORD wCount);
		bool SendShopChanceRefreshPacket();
		bool SendShopUnlockChancePacket(BYTE bSlot);

		// Exchange
		bool SendExchangeStartPacket(DWORD vid);
		bool SendExchangeItemAddPacket(TItemPos ItemPos, BYTE byDisplayPos);
		bool SendExchangeElkAddPacket(DWORD elk);
		bool SendExchangeItemDelPacket(WORD pos);
		bool SendExchangeAcceptPacket();
		bool SendExchangeExitPacket();
		bool SendExchangeElkKKAddPacket(DWORD elkKK);

		// Quest
		bool SendScriptAnswerPacket(int iAnswer);
		bool SendScriptButtonPacket(unsigned int iIndex);
		bool SendAnswerMakeGuildPacket(const char * c_szName);
		bool SendQuestInputStringPacket(const char * c_szString);
		bool SendQuestConfirmPacket(BYTE byAnswer, DWORD dwPID);

		// Event
		bool SendOnClickPacket(DWORD vid);

		// Fly
		bool SendFlyTargetingPacket(DWORD dwTargetVID, const TPixelPosition& kPPosTarget);
		bool SendAddFlyTargetingPacket(DWORD dwTargetVID, const TPixelPosition& kPPosTarget);
		bool SendShootPacket(UINT uSkill);

		// Command
		bool ClientCommand(const char * c_szCommand);
		void ServerCommand(char * c_szCommand);

		// Emoticon
		void RegisterEmoticonString(const char * pcEmoticonString);

		// Party
		bool SendPartyInvitePacket(DWORD dwVID);
		bool SendPartyInviteAnswerPacket(DWORD dwLeaderVID, BYTE byAccept);
		bool SendPartyRemovePacket(DWORD dwPID);
		bool SendPartySetStatePacket(DWORD dwVID, WORD wState, BYTE byFlag);

		// SafeBox
		bool SendSafeBoxMoneyPacket(BYTE byState, DWORD dwMoney);
		bool SendSafeBoxCheckinPacket(TItemPos InventoryPos, BYTE bySafeBoxPos);
		bool SendSafeBoxCheckoutPacket(BYTE bySafeBoxPos, TItemPos InventoryPos);
		bool SendSafeBoxItemMovePacket(BYTE bySourcePos, BYTE byTargetPos, WORD wCount);

		// Mall
		bool SendMallCheckoutPacket(BYTE byMallPos, TItemPos InventoryPos);

		// Guild
		bool SendGuildAddMemberPacket(DWORD dwVID);
		bool SendGuildRemoveMemberPacket(DWORD dwPID);
		bool SendGuildChangeGradeNamePacket(BYTE byGradeNumber, const char * c_szName);
		bool SendGuildChangeGradeAuthorityPacket(BYTE byGradeNumber, BYTE byAuthority);
		bool SendGuildChangeMemberGradePacket(DWORD dwPID, BYTE byGrade);
		bool SendGuildInviteAnswerPacket(DWORD dwGuildID, BYTE byAnswer);
		bool SendGuildWarAgreeChangeStatePacket(bool bFlag);

		bool SendGuildDiplomacyRequest(const char * c_szGuildName, unsigned char ucType);
		bool SendGuildDiplomacyResponse(unsigned int unGuildID, unsigned char ucType, bool bRespopnse);

		// Mall
		bool RecvMallOpenPacket();
		bool RecvMallItemSetPacket();
		bool RecvMallItemDelPacket();

#ifdef __ENABLE_NEW_OFFLINESHOP__
		bool RecvOfflineshopPacket();


		bool RecvOfflineshopShopList();
		bool RecvOfflineshopShopOpen();
		bool RecvOfflineshopShopOpenOwner();
		bool RecvOfflineshopShopOpenOwnerNoShop();
		bool RecvOfflineshopShopClose();
		bool RecvOfflineshopShopFilterResult();
		bool RecvOfflineshopOfferList();
		bool RecvOfflineshopShopSafeboxRefresh();
		bool RecvOfflineshopShopBuyItemFromSearch();

		bool RecvOfflineshopAuctionList();
		bool RecvOfflineshopOpenMyAuction();
		bool RecvOfflineshopOpenMyAuctionNoAuction();
		bool RecvOfflineshopOpenAuction();
#ifdef ENABLE_NEW_SHOP_IN_CITIES
		bool RecvOfflineshopInsertEntity();
		bool RecvOfflineshopRemoveEntity();

		bool SendOfflineshopOnClickShopEntity(DWORD dwPickedShopVID);
#endif


		bool SendOfflineshopShopCreate(const offlineshop::TShopInfo& shopInfo, const std::vector<offlineshop::TShopItemInfo>& items);
		bool SendOfflineshopChangeName(const char* szName);
		bool SendOfflineshopExtendDuration(DWORD dwHours);
		bool SendOfflineshopForceCloseShop();

		bool SendOfflineshopRequestShopList();

		bool SendOfflineshopOpenShop(DWORD dwOwnerID);
		bool SendOfflineshopOpenShopOwner();

		bool SendOfflineshopBuyItem(DWORD dwOwnerID, DWORD dwItemID, bool isSearch);
		
		bool SendOfflineshopAddItem(offlineshop::TShopItemInfo& itemInfo);
		bool SendOfflineshopRemoveItem(DWORD dwItemID);
		bool SendOfflineShopEditItem(DWORD dwItemID, const offlineshop::TPriceInfo& price);

		bool SendOfflineshopFilterRequest(const offlineshop::TFilterInfo& filter);
		
		bool SendOfflineshopOfferCreate(const offlineshop::TOfferInfo& offer);
		bool SendOfflineshopOfferAccept(DWORD dwOfferID);
		bool SendOfflineshopOfferCancel(DWORD dwOfferID, DWORD dwOwnerID);
		bool SendOfflineshopOfferListRequest();

		bool SendOfflineshopSafeboxOpen();
		bool SendOfflineshopSafeboxGetItem(DWORD dwItemID);
		bool SendOfflineshopSafeboxGetValutes(const offlineshop::TValutesInfo& valutes);
		bool SendOfflineshopSafeboxClose();

		//AUCTION
		bool SendOfflineshopAuctionListRequest();
		bool SendOfflineshopAuctionOpen(DWORD dwOwnerID);
		bool SendOfflineshopAuctionAddOffer(DWORD dwOwnerID, const offlineshop::TPriceInfo& price);
		bool SendOfflineshopAuctionExitFrom(DWORD dwOwnerID);
		bool SendOfflineshopAuctionCreate(const TItemPos& pos, const offlineshop::TPriceInfo& price, DWORD dwDuration);
		bool SendOfflineshopAuctionOpenMy();

		bool SendOfflineshopCloseBoard();
#endif
		bool RecvWikiPacket();
		bool RecvEventsPacket();
		bool RecvPlayerAchievementInfo();
		bool RecvBiologistManagerOpen();
		bool RecvBiologistManagerResearch();

		// Lover
		bool RecvLoverInfoPacket();
		bool RecvLovePointUpdatePacket();

		// Dig
		bool RecvDigMotionPacket();

		// Fishing
		bool SendFishingPacket(int iRotation);
		bool SendGiveItemPacket(DWORD dwTargetVID, TItemPos ItemPos, int iItemCount);

		// Private Shop
		bool SendBuildPrivateShopPacket(const char * c_szName, const std::vector<TShopItemTable> & c_rSellingItemStock);

		// Refine
		bool SendSelectItemPacket(TItemPos itemPos);
		bool SendRefinePacket(TItemPos ItemPos, BYTE byType, BYTE bRefineIndex, BYTE * add_item);

		//Land
		bool SendSelectLandPacket(DWORD dwItemPos);
		bool SendGuildAddResourcePacket(int nSlotIndex);

		//Guild
		bool SendGuildAnnouncePacket(char * szAnnounce, BYTE bSubHeader);
		bool SendGuildRefreshReportPacket(unsigned int last);
		bool SendGuildWarDeclarePacket(TGuildWarConfiguration * twg, unsigned int * aunTeam, char * aszName);
		bool SendGuildWarDeclarationResponsePacket(unsigned int unGuildID, bool bAccept, unsigned int * aunTeam = NULL, char * aszName = NULL);

		//Pet item
		bool SendItemPetMovePacket(TItemPos from_pos, TItemPos to_pos, BYTE bHeader);
		bool SendItemPetUsePacket(TItemPos pet_pos);

		//Lobby
		bool SendLobbyCreatePacket(BYTE bType, BYTE bSubType, char * szName, char * szPasswrod);
		bool SendLobbyApplyPacket(DWORD dwLobbyID, char * szPasswrod);
		bool SendLobbyCommandPacket(DWORD dwLobbyID, BYTE bCommand);
		bool SendLobbyRemovePartecipantPacket(DWORD dwLobbyID, DWORD dwPID);
		bool SendCloseLobbyWindowPacket(BYTE bSubType);

		//Raid
		bool SendStartRaidRequestPacket(unsigned int unID, unsigned int unDifficulty, unsigned int unIndex);

		// Client Version
		bool SendClientVersionPacket();

		// CRC Report
		bool __SendCRCReportPacket();

		// Handshake
		bool RecvHandshakePacket();
		bool RecvHandshakeOKPacket();

#ifdef _IMPROVED_PACKET_ENCRYPTION_
		bool RecvKeyAgreementPacket();
		bool RecvKeyAgreementCompletedPacket();

#endif
		// ETC
		DWORD GetMainActorVID();
		WORD GetMainActorRace();
		BYTE GetMainActorEmpire();
		BYTE GetMainActorSkillGroup();
		void SetEmpireID(DWORD dwEmpireID);
		DWORD GetEmpireID();
		void __TEST_SetSkillGroupFake(int iIndex);
		bool CubeRenewalMakeItem(int index_item, int count_item, int index_item_improve);
		bool CubeRenewalClose();
		bool RecvCubeRenewalPacket();
		//NOTIFICATION SYSTEM
		bool RecvNotificationPacket();

		// SkillTree
		bool SendSkillTreeStatusPacket(DWORD dwTreeID, bool bStatus);
		bool SendSkillTreeLevelupPacket(DWORD dwTreeID, DWORD dwTreeNodeID);
		bool SendSkillTreeRechargePacket(DWORD dwTreeID);

		// Biologist Manager
		bool SendBiologistManagerOpenCommand();
		bool BiologistManagerDeliverItems(uint8_t questID, uint8_t itemWantedCount, uint8_t elixirCount, uint8_t elixirPlusCount, uint8_t timeDeleterCount);

	//////////////////////////////////////////////////////////////////////////
	// Phase ����
	//////////////////////////////////////////////////////////////////////////
	public:
		void SetOffLinePhase();
		void SetHandShakePhase();
		void SetLoginPhase();
		void SetSelectPhase();
		void SetLoadingPhase();
		void SetGamePhase();
		void ClosePhase();

		// Login Phase
		bool SendLoginPacket(const char * c_szName, const char * c_szPassword);
		bool SendLoginPacketNew(const char * c_szName, const char * c_szPassword);
		bool SendDirectEnterPacket(const char * c_szName, const char * c_szPassword, UINT uChrSlot);

		bool SendEnterGame();

		// Select Phase
		bool SendSelectEmpirePacket(DWORD dwEmpireID);
		bool SendSelectCharacterPacket(BYTE account_Index);
		bool SendCreateCharacterPacket(BYTE index, const char *name, BYTE job, BYTE shape, BYTE byStat1, BYTE byStat2, BYTE byStat3, BYTE byStat4);
		bool SendDestroyCharacterPacket(BYTE index, const char * szPrivateCode);

		// Main Game Phase
		bool SendChatPacket(const char * c_szChat, BYTE byType = CHAT_TYPE_TALKING);
		bool SendWhisperPacket(const char * name, const char * c_szChat);
		bool SendMessengerAddByVIDPacket(DWORD vid);
		bool SendMessengerAddByNamePacket(const char * c_szName);
		bool SendMessengerRemovePacket(const char * c_szKey, const char * c_szName);

		void TEST_SyncActor(DWORD dwVID, LONG lPosX, LONG lPosY, unsigned int unDuration);

	protected:
		bool OnProcess();	// State���� ������ �����Ѵ�.
		void OffLinePhase();
		void HandShakePhase();
		void LoginPhase();
		void SelectPhase();
		void LoadingPhase();
		void GamePhase();

		bool __IsNotPing();

		void __DownloadMark();
		void __DownloadSymbol(const std::vector<DWORD> & c_rkVec_dwGuildID);

		void __PlayInventoryItemUseSound(TItemPos uSlotPos);
		void __PlayInventoryItemDropSound(TItemPos uSlotPos);
		void __PlaySafeBoxItemDropSound(UINT uSlotPos);
		void __PlayMallItemDropSound(UINT uSlotPos);

		bool __CanActMainInstance();

		enum REFRESH_WINDOW_TYPE
		{
			RefreshStatus = (1 << 0),
			RefreshAlignmentWindow = (1 << 1),
			RefreshCharacterWindow = (1 << 2),
			RefreshEquipmentWindow = (1 << 3), 
			RefreshInventoryWindow = (1 << 4),
			RefreshExchangeWindow = (1 << 5),
			RefreshSkillWindow = (1 << 6),
			RefreshSafeboxWindow  = (1 << 7),
			RefreshMessengerWindow = (1 << 8),
			RefreshGuildWindowInfoPage = (1 << 9),
			RefreshGuildWindowBoardPage = (1 << 10),
			RefreshGuildWindowMemberPage = (1 << 11), 
			RefreshGuildWindowMemberPageGradeComboBox = (1 << 12),
			RefreshGuildWindowSkillPage = (1 << 13),
			RefreshGuildWindowGradePage = (1 << 14),
			RefreshTargetBoard = (1 << 15),
			RefreshMallWindow = (1 << 16),
		};

		void __RefreshStatus();
		void __RefreshAlignmentWindow();
		void __RefreshCharacterWindow();
		void __RefreshEquipmentWindow();
		void __RefreshInventoryWindow();
		void __RefreshExchangeWindow();
		void __RefreshSkillWindow();
		void __RefreshSafeboxWindow();
		void __RefreshMessengerWindow();
		void __RefreshGuildWindowInfoPage();
		void __RefreshGuildWindowMemberPage();
		void __RefreshGuildWindowMemberPageGradeComboBox();
		void __RefreshGuildWindowSkillPage();
		void __RefreshGuildWindowGradePage();
		void __RefreshTargetBoardByVID(DWORD dwVID);
		void __RefreshTargetBoardByName(const char * c_szName);
		void __RefreshTargetBoard();
		void __RefreshMallWindow();
		void __RefreshRage();
		void __RefreshMasterHunt();
		void __RefreshPetStatus();
		void __RefreshPetBonus();
		void __RefreshGuildWindowReportPage();

		bool __SendHack(const char* c_szMsg);

	protected:
		bool RecvObserverAddPacket();
		bool RecvObserverRemovePacket();
		bool RecvObserverMovePacket();

		// Common
		bool RecvErrorPacket(int header);
		bool RecvPingPacket();
		bool RecvDefaultPacket(int header);
		bool RecvPhasePacket();

		// Login Phase
		bool __RecvLoginSuccessPacket3();
		bool __RecvLoginSuccessPacket4();
		bool __RecvLoginFailurePacket();
		bool __RecvEmpirePacket();

		// Select Phase
		bool __RecvPlayerCreateSuccessPacket();
		bool __RecvPlayerCreateFailurePacket();
		bool __RecvPlayerDestroySuccessPacket();
		bool __RecvPlayerDestroyFailurePacket();
		bool __RecvPreserveItemPacket();
		bool __RecvPlayerPoints();

		// Loading Phase
		bool RecvMainCharacter();

		void __SetFieldMusicFileName(const char* musicName);
		void __SetFieldMusicFileInfo(const char* musicName, float vol);
		// END_OF_SUPPORT_BGM

		// Main Game Phase
		bool RecvWarpPacket();
		bool RecvPVPPacket();
		bool RecvDuelStartPacket();
        bool RecvGlobalTimePacket();
		bool RecvCharacterAppendPacket();
		bool RecvCharacterAdditionalInfo();
		bool RecvCharacterAppendPacketNew();
		bool RecvCharacterUpdatePacket();
		bool RecvCharacterDeletePacket();
		bool RecvChatPacket();
		bool RecvSyncPositionPacket();
		bool RecvWhisperPacket();
		bool RecvPointChange();					// Alarm to python
		bool RecvChangeSpeedPacket();

		bool RecvStunPacket();
		bool RecvDeadPacket();
		bool RecvCharacterMovePacket();
		bool RecvCharacterAttackPacket();

		bool RecvItemSetPacket();					// Alarm to python
		bool RecvItemSetPacket2();					// Alarm to python
		bool RecvItemUsePacket();					// Alarm to python
		bool RecvItemUpdatePacket();				// Alarm to python
		bool RecvItemGroundAddPacket();
		bool RecvItemGroundDelPacket();
		bool RecvItemOwnership();

		bool RecvQuickSlotAddPacket();				// Alarm to python
		bool RecvQuickSlotDelPacket();				// Alarm to python
		bool RecvQuickSlotMovePacket();				// Alarm to python

		bool RecvCharacterPositionPacket();
		bool RecvMotionPacket();

		bool RecvShopPacket();
		bool RecvShopSignPacket();
		bool RecvExchangePacket();

		// Quest
		bool RecvScriptPacket();
		bool RecvQuestInfoPacket();
		bool RecvQuestConfirmPacket();
		bool RecvRequestMakeGuild();

		// Skill
		bool RecvSkillLevelNew();

		// Target
		bool RecvTargetPacket();
		bool RecvViewEquipPacket();
		bool RecvDamageInfoPacket();

		//TARGET INFO
		bool RecvTargetInfoPacket();
		bool RecvDungeonsInformation();
		bool RecvFakeCloks();
		bool RecvPlayerInfo();
		
		public:
			bool SendTargetInfoLoadPacket(DWORD dwVID);

		// Mount
		bool RecvMountPacket();

		// Fly
		bool RecvCreateFlyPacket();
		bool RecvFlyTargetingPacket();
		bool RecvAddFlyTargetingPacket();
		bool RecvCreateFlySemiFreePacket();
		bool RecvCreateFlyFreePacket();
		bool RecvCreateFlyFreeEnumPacket();

		// Messenger
		bool RecvMessenger();

		// Guild
		bool RecvGuild();

		// Party
		bool RecvPartyInvite();
		bool RecvPartyAdd();
		bool RecvPartyUpdate();
		bool RecvPartyRemove();
		bool RecvPartyLink();
		bool RecvPartyUnlink();
		bool RecvPartyPositionInfo();
		
		// SafeBox
		bool RecvSafeBoxSetPacket();
		bool RecvSafeBoxDelPacket();
		bool RecvSafeBoxWrongPasswordPacket();
		bool RecvSafeBoxSizePacket();
		bool RecvSafeBoxMoneyChangePacket();

		// Fishing
		bool RecvFishing();

		// Dungeon
		bool RecvDungeon();

		// Time
		bool RecvTimePacket();

		// WalkMode
		bool RecvWalkModePacket();

		// ChangeSkillGroup
		bool RecvChangeSkillGroupPacket();

		// Refine
		bool RecvRefineInformationPacketNew();

		// Use Potion
		bool RecvSpecialEffect();

		// �������� ������ ����Ʈ �ߵ� ��Ŷ.
		bool RecvSpecificEffect();
		bool RecvRemoveSpecificEffect();
		bool RecvAmbienceEffect();
		bool RecvAmbienceEffectDel();

		// MiniMap Info
		bool RecvNPCList();
		bool RecvLandPacket();
		bool RecvTargetCreatePacket();
		bool RecvTargetCreatePacketNew();
		bool RecvTargetUpdatePacket();
		bool RecvTargetDeletePacket();

		// Affect
		bool RecvAffectAddPacket();
		bool RecvAffectRemovePacket();

		// Channel
		bool RecvChannelPacket();

		// misc
		bool RecvSkillCooltime();
		bool RecvScreenWaving();
		bool RecvInventoryLockerData();

		// MSSYS
		bool RecvMssysData();


		bool RecvUnk213();
		
		// star skill
		bool RecvStellarSphereData();
		// pet
		bool RecvPetEstheticData();
		bool RecvPetStateData();
		bool RecvPetUpdateExpData();
		bool RecvPetUpdateBonusData();

		//decorum
		bool RecvDecorumStat();
		bool RecvDecorumBase();
		bool RecvDecorumBattle();
		bool RecvPVPArenaBattle();
		bool RecvDecorumKills();

		//battle pass
		bool RecvBattlePass();
		bool RecvBattlePassQuestUpdate();
		bool RecvBattlePassUpdate();

		// Master Hunt
		bool RecvMasterHuntDataPacket();
		bool RecvMasterHuntBountyDetails();

		// Target Gauge
		bool RecvTargetGauge();
		bool RecvTargetGaugeUpdate();
		bool RecvTargetGaugeClose();

		// Lobby
		bool RecvLobbyInformations();

		//Raid
		bool RecvRaidInformations();
		bool RecvRaidAbortReason();

		bool RecvBotMonitorPacket();

		// SkillTree
		bool RecvSkillTreeStatusPacket();
		bool RecvSkillTreeInfoPacket();

	protected:
		// �̸�Ƽ��
		bool ParseEmoticon(const char * pChatMsg, DWORD * pdwEmoticon);

		// ���̽����� ������ �ݵ�
		void OnConnectFailure();
		void OnScriptEventStart(int iSkin, int iIndex);
		
		void OnRemoteDisconnect();
		void OnDisconnect();

		void SetGameOnline();
		void SetGameOffline();
		BOOL IsGameOnline();
		bool RecvMaintenancePacket();

	protected:
		bool CheckPacket(TPacketHeader * pRetHeader);
		
		void __InitializeGamePhase();
		void __InitializeMarkAuth();
		void __GlobalPositionToLocalPosition(LONG& rGlobalX, LONG& rGlobalY);
		void __LocalPositionToGlobalPosition(LONG& rLocalX, LONG& rLocalY);

		bool __IsPlayerAttacking();
		bool __IsEquipItemInSlot(TItemPos Cell);

		void __ShowMapName(LONG lLocalX, LONG lLocalY);

		void __LeaveOfflinePhase() {}
		void __LeaveHandshakePhase() {}
		void __LeaveLoginPhase() {}
		void __LeaveSelectPhase() {}
		void __LeaveLoadingPhase() {}
		void __LeaveGamePhase();

		void __ClearNetworkActorManager();

		void __ClearSelectCharacterData();

		// DELETEME
		//void __SendWarpPacket();

		void __ConvertEmpireText(DWORD dwEmpireID, char* szText);

		void __RecvCharacterAppendPacket(SNetworkActorData * pkNetActorData);
		void __RecvCharacterUpdatePacket(SNetworkUpdateActorData * pkNetUpdateActorData);

		void __FilterInsult(char* szLine, UINT uLineLen);
		void __FilterIgnored(char* szLine, UINT uLineLen);

		void __SetGuildID(DWORD id);

	protected:
		TPacketGCHandshake m_HandshakeData;
		DWORD m_dwChangingPhaseTime;
		DWORD m_dwBindupRetryCount;
		DWORD m_dwMainActorVID;
		DWORD m_wMainActorRace;
		DWORD m_bMainActorEmpire;
		DWORD m_bMainActorSkillGroup;
		BOOL m_isGameOnline;
		BOOL m_isStartGame;

		DWORD m_dwGuildID;
		DWORD m_dwEmpireID;
		
		struct SServerTimeSync
		{
			DWORD m_dwChangeServerTime;
			DWORD m_dwChangeClientTime;
		} m_kServerTimeSync;

		void __ServerTimeSync_Initialize();
		//DWORD m_dwBaseServerTime;
		//DWORD m_dwBaseClientTime;

		DWORD m_dwLastGamePingTime;

		std::string	m_stID;
		std::string	m_stPassword;
		std::string	m_strLastCommand;
		std::string	m_strPhase;
		DWORD m_dwLoginKey;
		BOOL m_isWaitLoginKey;

		std::string m_stMarkIP;

		CFuncObject<CPythonNetworkStream>	m_phaseProcessFunc;
		CFuncObject<CPythonNetworkStream>	m_phaseLeaveFunc;

		PyObject*							m_poHandler;
		PyObject*							m_apoPhaseWnd[PHASE_WINDOW_NUM];
		PyObject*							m_poSerCommandParserWnd;

		TSimplePlayerInformation			m_akSimplePlayerInfo[PLAYER_PER_ACCOUNT4];
		DWORD								m_adwGuildID[PLAYER_PER_ACCOUNT4];
		std::string							m_astrGuildName[PLAYER_PER_ACCOUNT4];
		bool m_bSimplePlayerInfo;

		CRef<CNetworkActorManager>			m_rokNetActorMgr;

		bool m_isRefreshStatus;
		bool m_isRefreshCharacterWnd;
		bool m_isRefreshEquipmentWnd;
		bool m_isRefreshInventoryWnd;
		bool m_isRefreshExchangeWnd;
		bool m_isRefreshSkillWnd;
		bool m_isRefreshSafeboxWnd;
		bool m_isRefreshMallWnd;
		bool m_isRefreshMessengerWnd;
		bool m_isRefreshGuildWndInfoPage;
		bool m_isRefreshGuildWndMemberPage;
		bool m_isRefreshGuildWndMemberPageGradeComboBox;
		bool m_isRefreshGuildWndSkillPage;
		bool m_isRefreshGuildWndGradePage;
		bool m_isRefreshGuildWndReportPage;
		bool m_isRefreshRage;
		bool m_isRefreshMasterHunt;
		bool m_isRefreshPetStatus;
		bool m_isRefreshPetBonus;

		// Emoticon
		std::vector<std::string> m_EmoticonStringVector;

		struct STextConvertTable 
		{
			char acUpper[26];
			char acLower[26];
			BYTE aacHan[5000][2];
		} m_aTextConvTable[3];



		struct SMarkAuth
		{
			CNetworkAddress m_kNetAddr;
			DWORD m_dwHandle;
			DWORD m_dwRandomKey;
		} m_kMarkAuth;



		DWORD m_dwSelectedCharacterIndex;

		CInsultChecker m_kInsultChecker;

		bool m_isEnableChatInsultFilter;
		bool m_bComboSkillFlag;

		std::deque<std::string> m_kQue_stHack;

	private:
		struct SDirectEnterMode
		{
			bool m_isSet;
			DWORD m_dwChrSlotIndex;
		} m_kDirectEnterMode;

		void __DirectEnterMode_Initialize();
		void __DirectEnterMode_Set(UINT uChrSlotIndex);
		bool __DirectEnterMode_IsSet();

	public:
		DWORD EXPORT_GetBettingGuildWarValue(const char* c_szValueName);

	private:
		struct SBettingGuildWar
		{
			DWORD m_dwBettingMoney;
			DWORD m_dwObserverCount;
		} m_kBettingGuildWar;

		CInstanceBase * m_pInstTarget;

		void __BettingGuildWar_Initialize();
		void __BettingGuildWar_SetObserverCount(UINT uObserverCount);
		void __BettingGuildWar_SetBettingMoney(UINT uBettingMoney);
	public:
		bool RecvSwitchbotPacket();

		bool SendSwitchbotStartPacket(BYTE slot, std::vector<CPythonSwitchbot::TSwitchbotAttributeAlternativeTable> alternatives);
		bool SendSwitchbotStopPacket(BYTE slot);	

		bool SendBotMonitorCaptcha(char* szCode);
};