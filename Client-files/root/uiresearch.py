import ui
import app
import localeInfo
import item
import colorInfo
import net
import uiCommon
import player
import chat
class uiResearchWindow(ui.ScriptWindow):

	BIOLOGIST_QUEST_DICT = {
		0 : { 'item_wanted': 30006, 'pct' : 90, 'required': 20 },
		1 : { 'item_wanted': 30055, 'pct' : 90, 'required': 20 },
		2 : { 'item_wanted': 30047, 'pct' : 90, 'required': 20 },
		3 : { 'item_wanted': 30324, 'pct' : 90, 'required': 25 },
		4 : { 'item_wanted': 30015, 'pct' : 90, 'required': 20 },
		5 : { 'item_wanted': 30050, 'pct' : 90, 'required': 25 },
		6 : { 'item_wanted': 30198, 'pct' : 44, 'required': 30 },
		7 : { 'item_wanted': 30166, 'pct' : 42, 'required': 35 },
		8 : { 'item_wanted': 30495, 'pct' : 30, 'required': 15 },
		9 : { 'item_wanted': 100029, 'pct' : 38, 'required': 40 },
		10 : { 'item_wanted': 30329, 'pct' : 36, 'required': 45 },
		11 : { 'item_wanted': 100039, 'pct' : 34, 'required': 50 },
	}

	MAX_ITEM_QUANTITY = 5
	PCT_BONUS = 10
	PCT_BONUS_PLUS = 30

	BIOLOGIST_PCT_ADDER_VNUM = 102529
	BIOLOGIST_PCT_ADDER_PLUS_VNUM = 102616
	BIOLOGIST_TIME_DELETER_VNUM = 102517

	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.remainTime = 0
		self.receivedTime = app.GetTime()
		self.remainTimeText = None
		self.questID = 0
		self.itemRequestedText = None
		self.pctSuccessText = None
		self.lastCountDownRefresh = 0
		self.itemToDeliverCount = 1
		self.itemToDeliverVnum = 0
		self.questionDialog = None
		self.popupDialog = None
		self.deliveredItemsQty = 0
		self.isOpened = False
		self.LoadWindow()

	def __del__(self):
		self.remainTime = 0
		self.questID = 0
		self.itemRequestedText = None
		self.pctSuccessText = None
		self.lastCountDownRefresh = 0
		self.itemToDeliverVnum = 0
		self.questionDialog = None
		self.popupDialog = None
		self.isOpened = False
		self.tooltipItem = 0
		ui.ScriptWindow.__del__(self)

	def LoadWindow(self):
		try:
			PythonScriptLoader = ui.PythonScriptLoader()
			PythonScriptLoader.LoadScriptFile(self, "UIScript/researchwindow.py")

		except:
			import exception
			exception.Abort("ResearchWindow.LoadWindow.LoadUIScriptFiles")

		try:
			self.board = self.GetChild("board")
			self.remainTimeText = self.GetChild("ItemCDText")
			self.itemRequestedText = self.GetChild("ItemNametext")
			self.pctSuccessText = self.GetChild("ItemPctText")
			self.buttonTimeDeleterUP = self.GetChild("UpButton1")
			self.itemTimeDeleterTextqty = self.GetChild("ItemSlotbar1Text")
			self.buttonTimeDeleterDown = self.GetChild("DownButton1")

			self.buttonElixirUP = self.GetChild("UpButton2")
			self.buttonElixirTextQty = self.GetChild("ItemSlotbar2Text")
			self.buttonElixirDown = self.GetChild("DownButton2")

			self.buttonElixirPlusUP = self.GetChild("UpButton3")
			self.buttonElixirPlusTextQty = self.GetChild("ItemSlotbar3Text")
			self.buttonElixirPlusDown = self.GetChild("DownButton3")

			self.itemWanted = self.GetChild("current_item")
			self.itemWantedButtonUP = self.GetChild("UpButton0")
			self.itemWantedButtonText = self.GetChild("ItemSlotbar0Text")
			self.itemWantedButtonDown = self.GetChild("DownButton0")

			self.deliverItemButton = self.GetChild("exam_button")
			self.deliveredItemsText = self.GetChild("textItemDeliverdQty")
			self.notifySlot = self.GetChild("NotifySlot")

			self.elixirSlot = self.GetChild("elisir_10_slot")
			self.elixirPlusSlot = self.GetChild("elisir_30_slot")
			self.timeDeleterSlot = self.GetChild("time_deleter_slot")


		except:
			import exception
			exception.Abort("ResearchWindow.LoadWindow.BindObject")

		self.board.SetCloseEvent(ui.__mem_func__(self.Close))

		self.buttonTimeDeleterUP.SAFE_SetEvent(self.__OnClickButtonTimeDeleterUP)
		self.buttonTimeDeleterDown.SAFE_SetEvent(self.__OnClickButtonTimeDeleterDown)

		self.buttonElixirUP.SAFE_SetEvent(self.__OnClickbuttonElixirUP)
		self.buttonElixirDown.SAFE_SetEvent(self.__OnClickbuttonElixirDown)

		self.buttonElixirPlusUP.SAFE_SetEvent(self.__OnClickbuttonElixirPlusUP)
		self.buttonElixirPlusDown.SAFE_SetEvent(self.__OnClickbuttonElixirPlusDown)

		self.itemWantedButtonUP.SAFE_SetEvent(self.__OnClickButtonItemWantedUP)
		self.itemWantedButtonDown.SAFE_SetEvent(self.__OnClickButtonItemWantedDown)
		self.deliverItemButton.SAFE_SetEvent(self.__OnClickDeliverButton)


		item.SelectItem(self.BIOLOGIST_PCT_ADDER_VNUM)
		itemName = item.GetItemName()				
		self.pctAdderName = itemName
		item.SelectItem(self.BIOLOGIST_PCT_ADDER_PLUS_VNUM)
		itemName = item.GetItemName()		
		self.pctAdderPlusName = itemName
		item.SelectItem(self.BIOLOGIST_TIME_DELETER_VNUM)
		itemName = item.GetItemName()		
		self.timeDeleterName = itemName		

	def SendDeliverPacket(self):
		net.SendBiologistManagerDeliverCommand(self.questID, self.itemToDeliverCount,\
			int(self.buttonElixirTextQty.GetText()), int(self.buttonElixirPlusTextQty.GetText()),\
			int(self.itemTimeDeleterTextqty.GetText()))


	def CanSendRequest(self):
		elixirPlayerCount = player.GetItemCountByVnum(self.BIOLOGIST_PCT_ADDER_VNUM)
		elixirPlusPlayerCount = player.GetItemCountByVnum(self.BIOLOGIST_PCT_ADDER_PLUS_VNUM)
		timeDeleterPlayerCount = player.GetItemCountByVnum(self.BIOLOGIST_TIME_DELETER_VNUM)
		itemToDeliverPlayerCount = player.GetItemCountByVnum(self.itemToDeliverVnum)
		if self.itemToDeliverCount > itemToDeliverPlayerCount or \
		int(self.buttonElixirTextQty.GetText()) > elixirPlayerCount or\
		int(self.buttonElixirPlusTextQty.GetText()) > elixirPlusPlayerCount or\
		int(self.itemTimeDeleterTextqty.GetText()) > timeDeleterPlayerCount:
			self.popupDialog = uiCommon.PopupDialog()
			self.popupDialog.SetText(localeInfo.BIOLOGIST_MANAGER_OVERFLOW_ERROR)
			self.popupDialog.SetAcceptEvent(self.__OnClosePopupDialog)
			self.popupDialog.Open()
			return False
		elif self.GetRemainTime() > 0 and int(self.itemTimeDeleterTextqty.GetText()) <= 0:
			self.popupDialog = uiCommon.PopupDialog()
			self.popupDialog.SetText(localeInfo.BIOLOGIST_MANAGER_TIME_ERROR)
			self.popupDialog.SetAcceptEvent(self.__OnClosePopupDialog)
			self.popupDialog.Open()			
		else:
			return True

	def __OnClickDeliverButton(self):
		if self.pct > 100:
			self.questionDialog = uiCommon.QuestionDialog()
			self.questionDialog.Open()
			self.questionDialog.SetText(localeInfo.BIOLOGIST_MANAGER_CHECK_PCT)
			self.questionDialog.SetAcceptText(localeInfo.UI_ACCEPT)
			self.questionDialog.SetCancelText(localeInfo.UI_DENY)
			self.questionDialog.SetAcceptEvent(lambda arg = True: self.QuestionDialogAnswer(arg))
			self.questionDialog.SetCancelEvent(lambda arg = False: self.QuestionDialogAnswer(arg))
			self.questionDialog.SetTop()
		else:
			if self.CanSendRequest() == True:
				self.SendDeliverPacket()
				

	def __OnClosePopupDialog(self):
		self.popupDialog = None
		
	def QuestionDialogAnswer(self, answer):
		if not self.questionDialog:
			return

		if answer == True:
			if self.CanSendRequest() == True:
				self.SendDeliverPacket()

		self.questionDialog.Close()
		self.questionDialog = None

	def __OnClickButtonItemWantedUP(self):
		if self.itemToDeliverCount >= self.MAX_ITEM_QUANTITY:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.BIOLOGIST_MANAGER_ITEMS_OVERFLOW % (str(self.MAX_ITEM_QUANTITY), self.itemName))
			return
		if self.itemToDeliverCount + 1 > player.GetItemCountByVnum(self.itemToDeliverVnum):
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.BIOLOGIST_manager_NOT_ENOUGH_ITEMS % (str(self.MAX_ITEM_QUANTITY), self.itemName))
			return				
		self.itemToDeliverCount += 1
		self.itemWantedButtonText.SetText(str(self.itemToDeliverCount))

	def __OnClickButtonItemWantedDown(self):
		if self.itemToDeliverCount <= 1:
			return		
		self.itemToDeliverCount -= 1
		self.itemWantedButtonText.SetText(str(self.itemToDeliverCount))

	def __OnClickButtonTimeDeleterUP(self):
		number = int(self.itemTimeDeleterTextqty.GetText())
		if number >= self.MAX_ITEM_QUANTITY: 
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.BIOLOGIST_MANAGER_ITEMS_OVERFLOW % (str(self.MAX_ITEM_QUANTITY), self.timeDeleterName))
			return
		if number + 1 > player.GetItemCountByVnum(self.BIOLOGIST_TIME_DELETER_VNUM):
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.BIOLOGIST_manager_NOT_ENOUGH_ITEMS % (str(self.MAX_ITEM_QUANTITY), self.timeDeleterName))
			return	
		self.itemTimeDeleterTextqty.SetText(str(number+1))
		self.UpdatePct()

	def __OnClickButtonTimeDeleterDown(self):
		number = int(self.itemTimeDeleterTextqty.GetText())
		if number <= 0:
			return
		self.itemTimeDeleterTextqty.SetText(str(number-1))
		self.UpdatePct()

	def __OnClickbuttonElixirUP(self):		
		number = int(self.buttonElixirTextQty.GetText())
		if number >= self.MAX_ITEM_QUANTITY:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.BIOLOGIST_MANAGER_ITEMS_OVERFLOW % (str(self.MAX_ITEM_QUANTITY), self.pctAdderName))
			return
		if number + 1 > player.GetItemCountByVnum(self.BIOLOGIST_PCT_ADDER_VNUM):
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.BIOLOGIST_manager_NOT_ENOUGH_ITEMS % (str(self.MAX_ITEM_QUANTITY), self.pctAdderName))
			return				
		self.buttonElixirTextQty.SetText(str(number+1))
		self.UpdatePct()

	def __OnClickbuttonElixirDown(self):
		number = int(self.buttonElixirTextQty.GetText())
		if number <= 0:
			return
		self.buttonElixirTextQty.SetText(str(number-1))
		self.UpdatePct()

	def __OnClickbuttonElixirPlusUP(self):
		number = int(self.buttonElixirPlusTextQty.GetText())
		if number >= self.MAX_ITEM_QUANTITY:
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.BIOLOGIST_MANAGER_ITEMS_OVERFLOW % (str(self.MAX_ITEM_QUANTITY), self.pctAdderPlusName))
			return
		if number + 1 > player.GetItemCountByVnum(self.BIOLOGIST_PCT_ADDER_PLUS_VNUM):
			chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.BIOLOGIST_manager_NOT_ENOUGH_ITEMS % (str(self.MAX_ITEM_QUANTITY), self.pctAdderPlusName))
			return			
		self.buttonElixirPlusTextQty.SetText(str(number+1))
		self.UpdatePct()

	def __OnClickbuttonElixirPlusDown(self):
		number = int(self.buttonElixirPlusTextQty.GetText())
		if number <= 0:
			return
		self.buttonElixirPlusTextQty.SetText(str(number-1))
		self.UpdatePct()
		
	def GetRemainTime(self):
		return self.remainTime - (app.GetTime() - self.receivedTime)

	def ResearchRequestInfo(self, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses, remainingTime):
		self.remainTime = remainingTime
		self.deliveredItemsQty += successDeliveries
		self.deliveredItemsText.SetText(str(self.deliveredItemsQty) + "/" + str(self.BIOLOGIST_QUEST_DICT[self.questID]['required']))
		self.itemWanted.SetItemSlot(0, self.itemToDeliverVnum, player.GetItemCountByVnum(self.itemToDeliverVnum))
		text = ""
		
		if failedDeliveries == 1:
			text = localeInfo.BIOLOGIST_SYSTEM_MESSAGE_SINGLE_FAIL % (deliversCounter, self.itemName, successDeliveries, failedDeliveries, self.pctAdderName, elixirUses, self.pctAdderPlusName, elixirPlusUses, self.timeDeleterName, timeDeleterUses)
		else:
			text = localeInfo.BIOLOGIST_SYSTEM_MESSAGE_MULTIPLE_FAIL % (deliversCounter, self.itemName, successDeliveries, failedDeliveries, self.pctAdderName, elixirUses, self.pctAdderPlusName, elixirPlusUses, self.timeDeleterName, timeDeleterUses)
		self.multiHolder = ui.GenerateMultiLine(self.notifySlot, text, 300, colorInfo.GOLD)
		for i in self.multiHolder:
			totalH = self.multiHolder[0].GetTextSize()[1] * len(self.multiHolder) + 3 * (len(self.multiHolder) - 1)
			i.SetPosition(3, 80 / 2 - totalH / 2 + 3 * self.multiHolder.index(i) + i.GetTextSize()[1] * self.multiHolder.index(i))
		self.UpdateSlots()	

	def UpdateInfo(self, questID, remain_time, deliveredItems):
		self.remainTime = remain_time
		self.questID = questID
		self.itemToDeliverVnum = self.BIOLOGIST_QUEST_DICT[questID]['item_wanted']
		self.deliveredItemsQty = deliveredItems
		self.deliveredItemsText.SetText(str(self.deliveredItemsQty) + "/" + str(self.BIOLOGIST_QUEST_DICT[self.questID]['required']))
		item.SelectItem(self.itemToDeliverVnum)
		self.itemName = item.GetItemName()
		self.itemRequestedText.SetText(self.itemName)
		self.itemWanted.SetItemSlot(0, self.itemToDeliverVnum, player.GetItemCountByVnum(self.itemToDeliverVnum))
		self.UpdatePct()
		self.UpdateTimer()

	def UpdatePct(self):
		elixir_qty = int(self.buttonElixirTextQty.GetText())
		elixir_plus_qty = int(self.buttonElixirPlusTextQty.GetText())
		if elixir_qty > 0 and elixir_plus_qty > 0:
			self.pct = self.BIOLOGIST_QUEST_DICT[self.questID]['pct'] + self.PCT_BONUS + self.PCT_BONUS_PLUS
		elif elixir_qty > 0:
			self.pct = self.BIOLOGIST_QUEST_DICT[self.questID]['pct'] + self.PCT_BONUS
		elif elixir_plus_qty > 0:
			self.pct = self.BIOLOGIST_QUEST_DICT[self.questID]['pct'] + self.PCT_BONUS_PLUS
		elif elixir_qty <= 0 and elixir_plus_qty <= 0:
			self.pct = self.BIOLOGIST_QUEST_DICT[self.questID]['pct']
		elif elixir_qty <= 0:
			self.pct -= self.PCT_BONUS
		elif elixir_plus_qty <= 0:
			self.pct -= self.PCT_BONUS_PLUS
		self.pctSuccessText.SetText(str(self.pct) + "%")

	def OnUpdate(self):
		if app.GetTime() <= self.lastCountDownRefresh + 1.0:
			return

		self.lastCountDownRefresh = app.GetTime()
		self.UpdateTimer()

	def UpdateTimer(self):
		remain_time = self.GetRemainTime()
		if remain_time <= 0:
			self.remainTimeText.SetPackedFontColor(colorInfo.GREEN)
			self.remainTimeText.SetText(localeInfo.BIOLOGIST_MANAGER_CAN_DELIVER)
		else:
			self.remainTimeText.SetPackedFontColor(colorInfo.RED)
			self.remainTimeText.SetText("%s" % (str(localeInfo.SecondsToClock(remain_time))))

	def SetItemToolTip(self, tooltipItem):
		self.tooltipItem = tooltipItem

	def OverInItem(self, itemVnum):
		if not self.tooltipItem:
			return

		self.tooltipItem.ClearToolTip()
		metinSlot = []
		for i in range(player.METIN_SOCKET_MAX_NUM):
			metinSlot.append(0)
		attrSlot = []
		for i in range(player.ATTRIBUTE_SLOT_MAX_NUM):
			attrSlot.append((0, 0, 0))
		realValue = []
		for i in range(player.REAL_VALUES_MAX_NUM):
			realValue.append(0)
			
		self.tooltipItem.AddItemData(itemVnum, metinSlot, attrSlot, realValue)

	def OverOutItem(self):
		if 0 != self.tooltipItem:
			self.tooltipItem.HideToolTip()

	def UpdateSlots(self):
		self.elixirSlot.SetItemSlot(0, self.BIOLOGIST_PCT_ADDER_VNUM, player.GetItemCountByVnum(self.BIOLOGIST_PCT_ADDER_VNUM))
		self.elixirPlusSlot.SetItemSlot(0, self.BIOLOGIST_PCT_ADDER_PLUS_VNUM, player.GetItemCountByVnum(self.BIOLOGIST_PCT_ADDER_PLUS_VNUM))
		self.timeDeleterSlot.SetItemSlot(0, self.BIOLOGIST_TIME_DELETER_VNUM, player.GetItemCountByVnum(self.BIOLOGIST_TIME_DELETER_VNUM))
		self.itemWanted.SetItemSlot(0, self.itemToDeliverVnum, player.GetItemCountByVnum(self.itemToDeliverVnum))

	def SetSlotsEvents(self):
		self.elixirSlot.SetEvent(ui.SLOT_OVER_IN_ITEM, self.OverInItem, self.BIOLOGIST_PCT_ADDER_VNUM)
		self.elixirPlusSlot.SetEvent(ui.SLOT_OVER_IN_ITEM, self.OverInItem, self.BIOLOGIST_PCT_ADDER_PLUS_VNUM)
		self.timeDeleterSlot.SetEvent(ui.SLOT_OVER_IN_ITEM, self.OverInItem, self.BIOLOGIST_TIME_DELETER_VNUM)

		self.elixirSlot.SetEvent(ui.SLOT_OVER_OUT_ITEM, self.OverOutItem)
		self.elixirPlusSlot.SetEvent(ui.SLOT_OVER_OUT_ITEM, self.OverOutItem)
		self.timeDeleterSlot.SetEvent(ui.SLOT_OVER_OUT_ITEM, self.OverOutItem)

		
		self.itemWanted.SetEvent(ui.SLOT_OVER_IN_ITEM, self.OverInItem, self.itemToDeliverVnum)
		self.itemWanted.SetEvent(ui.SLOT_OVER_OUT_ITEM, self.OverOutItem)

	def Open(self, questID, remainTime, deliveredItems):
		self.UpdateInfo(questID, remainTime, deliveredItems)
		self.UpdateSlots()
		self.SetSlotsEvents()
		self.Show()
		self.isOpened = True

	def IsOpened(self):
		return self.isOpened

	def Close(self, isOpened = True):
		if self.tooltipItem:
			self.tooltipItem.ClearToolTip()
		self.isOpened = isOpened
		self.Hide()
	
	def Destroy(self):
		self.ClearDictionary()
		if self.tooltipItem:
			self.tooltipItem.ClearToolTip()
		self.remainTime = 0
		self.remainTimeText = None
		self.questID = 0
		self.itemRequestedText = None
		self.pctSuccessText = None
		self.lastCountDownRefresh = 0
		self.itemToDeliverVnum = 0
		self.questionDialog = None
		self.tooltipItem = 0
		self.popupDialog = None
		

	def OnPressEscapeKey(self):
		self.Close()
		return True