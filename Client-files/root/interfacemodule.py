#add the import of your file name for the interface
import uiResearch
#after
		self.equipmentDialogDict = {}
#add
		self.wndBiologistManager = None
#before:
		self.__InitWhisper()
#add:
		self.wndBiologistManager.SetItemToolTip(self.tooltipItem)
#after:
		if self.wndTaskBar:
			self.wndTaskBar.Destroy()
#add:
		if self.wndBiologistManager:
			self.wndBiologistManager.Destroy()
#after
		del self.wndMall
#add
		del self.wndBiologistManager

#after
		if self.wndMiniMap:
			self.wndMiniMap.Hide()
#add
		if self.wndBiologistManager:
			self.wndBiologistManager.Hide()	
#in the	def __HideWindows(self): function
#add:

		if self.wndBiologistManager and self.wndBiologistManager.IsShow():
			hideWindows.append(self.wndBiologistManager)
#this could be different in your client, just follow the behavior used
	
#at the bottom add:
	def ToggleBiologistManager(self):
		if player.IsObserverMode():
			return
		if False == self.wndBiologistManager.IsOpened():
			net.SendBiologistManagerOpenCommand()
		else:
			if False == self.wndBiologistManager.IsShow():
				self.wndBiologistManager.Show()
			else:
				self.wndBiologistManager.Hide()

	def OpenBiologistManager(self, questID, remainTime, deliveredItems):
		if player.IsObserverMode():
			return

		if False == self.wndBiologistManager.IsShow():
			self.wndBiologistManager.Open(questID, remainTime, deliveredItems)
		else:
			self.wndBiologistManager.Close()

	def UpdateBiologistManager(self, deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses, remainingTime):
		self.wndBiologistManager.ResearchRequestInfo(deliversCounter, successDeliveries, failedDeliveries, timeDeleterUses, elixirUses, elixirPlusUses, remainingTime)

	def CloseBiologistManager(self):
		self.wndBiologistManager.Close(False)
