#add to def __BuildKeyDict(self):
#the following:
		self.onPressKeyDict[app.DIK_P]			= lambda : self.__PressPKey()
       
#or choose your desired button to open the interface

#after:
	def __PressNumKey(self,num):
		if app.IsPressed(app.DIK_LCONTROL) or app.IsPressed(app.DIK_RCONTROL):
			
			if num >= 1 and num <= 9:
				if(chrmgr.IsPossibleEmoticon(-1)):				
					chrmgr.SetEmoticon(-1,int(num)-1)
					net.SendEmoticon(int(num)-1)
		else:
			if num >= 1 and num <= 4:
				self.pressNumber(num-1)
				
			elif num >= 5 and num <= 8:
				self.pressNumber(num-1)
#add:
	def __PressPKey(self):
		self.interface.ToggleBiologistManager()

#at the bottom add:
	def BINARY_BiologistManagerOpen(self, questID, remainTime, deliveredItems):
		self.interface.OpenBiologistManager(questID, remainTime, deliveredItems)

	def BINARY_BiologistManagerResearch(self, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses, remainingTime):
		self.interface.UpdateBiologistManager(deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses, remainingTime)

	def BINARY_BiologistManagerResearchComplete(self):
		self.interface.CloseBiologistManager()
		popup = uiCommon.PopupDialog()
		popup.SetText("Research completed! Go back to the Biologist!") #change the string (localeInfo.CHOOSEANAMEFORTHESTRING) and add it to your locale_game file
		popup.SetAcceptEvent(self.__OnClosePopupDialog)
		popup.Open()
		self.popup = popup