import uiScriptLocale
import colorInfo

TASKBAR = "d:/ymir work/ui/taskbar/"

window = {
	"name" : "ResearchWindow",

	"x" : 100,
	"y" : 20,

	"style" : ("movable", "float","limit",),

	"width" : 330,
	"height" : 330,

	"children" :
	(
		{
			"name" : "board",
			"type" : "board_with_titlebar",

			"x" : 0,
			"y" : 0,

			"width" : 330,
			"height" : 330,

			"title": uiScriptLocale.RESEARCH_TITLE,

			"children" :
			(
				{
					"name" : "thinboardAllContainer",
					"type" : "thinboard",

					"x" : 7,
					"y" : 27,
					
					"width" : 316,
					"height" : 296,
				
					
					"style" : ["not_pick"],
					
					"children" :
					(
						{
							"name" : "thinboardDeliverContainer",
							"type" : "thinboard",

							"x" : 5,
							"y" : 5,
							
							"width" : 306,
							"height" : 116,
						
							
							"style" : ["not_pick"],
							"children" :
							(
								{
									"name" : "current_item",
									"type" : "grid_table",

									"x" : 31,
									"y" : 34,

									"start_index" : 0,
									"x_count" : 1,
									"y_count" : 1,
									"x_step" : 32,
									"y_step" : 32,

									"image" : "d:/ymir work/ui/public/Slot_Base.sub",
								},
								{
									"name" : "UpButton0",
									"type" : "button",
									"tooltip_text" : uiScriptLocale.RESEARCH_UP,
									"x" : 31-4,
									"y" : 34+32+2,
									"default_image" : TASKBAR + "pageup.sub",
									"over_image" : TASKBAR + "pageup_over.sub",
									"down_image" : TASKBAR + "pageup_click.sub",
								},
								{
									"name" : "DownButton0",
									"type" : "button",
									"tooltip_text" : uiScriptLocale.RESEARCH_DOWN,

									"x" : 31-4,
									"y" : 34+32+12,

									"default_image" : TASKBAR + "pagedown.sub",
									"over_image" : TASKBAR + "pagedown_over.sub",
									"down_image" : TASKBAR + "pagedown_click.sub",
								},
								{ 
									"name":"ItemSlotbar0", 
									"type":"slotbar", 
									"x":40, 
									"y":34+36, 
									"preset":"parameter_slot_09", 
									"children" :
									(
										{ "name":"ItemSlotbar0Text", "type":"text", "x":1, "y":2, "text":"1", "r":1.0, "g":1.0, "b":1.0, "a":1.0, "text_horizontal_align":"center", "horizontal_align":"center"},
									),
								},
								{
									"name" : "textItemName",
									"type" : "text",

									"x" : 111 - 27,
									"y" : 18,
									
									
									"color" : colorInfo.FONT_COLOR, 
									"fontsize":"middle",
									
									"text" : uiScriptLocale.RESEARCH_OBJECT,
									
									"style" : ["not_pick"],
								},
								{
									"name" : "ItemNametext",
									"type" : "text",

									"x" : 111 - 27 + 84,
									"y" : 18,
									
									
									"color" : colorInfo.GOLD_COLOR, 
									"fontsize":"middle",
									
									"text" : uiScriptLocale.RESEARCH_OBJECT,
									
									"style" : ["not_pick"],
								},
								{
									"name" : "textItemDeliverd",
									"type" : "text",

									"x" : 111 - 27,
									"y" : 18 + 16,
									
									
									"color" : colorInfo.FONT_COLOR, 
									"fontsize":"middle",
									
									"text" : uiScriptLocale.RESEARCH_DELIVERED,
									
									"style" : ["not_pick"],
								},
								{
									"name" : "textItemDeliverdQty",
									"type" : "text",

									"x" : 111 - 27 + 55,
									"y" : 18 + 16,
									
									
									"color" : colorInfo.GOLD_COLOR, 
									"fontsize":"middle",
									
									"text" : "0/0",
									
									"style" : ["not_pick"],
								},								
								{
									"name" : "textItemPct",
									"type" : "text",

									"x" : 111 - 27,
									"y" : 18 + 16 * 2,
									
									
									"color" : colorInfo.FONT_COLOR, 
									"fontsize":"middle",
									
									"text" : uiScriptLocale.RESEARCH_PCT,
									
									"style" : ["not_pick"],
								},
								{
									"name" : "ItemPctText",
									"type" : "text",

									"x" : 111 - 27 + 104,
									"y" : 18 + 16 * 2,
									
									
									"color" : colorInfo.GOLD_COLOR, 
									"fontsize":"middle",
									
									"text" : "",
									
									"style" : ["not_pick"],
								},								
								{
									"name" : "textItemCD",
									"type" : "text",

									"x" : 111 - 27,
									"y" : 18 + 16 * 3,
									
									
									"color" : colorInfo.FONT_COLOR, 
									"fontsize":"middle",
									
									"text" : uiScriptLocale.RESEARCH_TIMER,
									
									"style" : ["not_pick"],
								},
								{
									"name" : "ItemCDText",
									"type" : "text",

									"x" : 111 - 27 + 77,
									"y" : 18 + 16 * 3,
									
									
									"color" : colorInfo.RED, 
									"fontsize":"middle",
									
									"text" : "",
									
									"style" : ["not_pick"],
								},								
								{
									"name" : "exam_button",
									"type" : "dynamic_button",

									"x" : 0,
									"y" : 86,

									"text" : uiScriptLocale.RESEARCH_BUTTON,
									"horizontal_align" : "center",

									"preset" : "not_so_largerer_button",
								},
								{
									"name" : "CD_Image",
									"type" : "image",

									"x" : 246,
									"y" : 46+13,

									"image" : "d:/ymir work/ui/game/mailbox/mailbox_icon_cd.sub",
								},
								{
									"name" : "CD_checkbox",
									"type" : "checkbox_new",


									"x" : 272,
									"y" : 51+14,
								},
							),
						},
						{
							"name" : "thinboardIconContainer",
							"type" : "thinboard",

							"x" : 51-15,
							"y" : 136,
							
							"width" : 214+30,
							"height" : 40,
						
							
							"style" : ["not_pick"],
							
							"children" :
							(
								{
									"name" : "time_deleter_slot",
									"type" : "grid_table",

									"x" : 46,
									"y" : 3,

									"start_index" : 0,
									"x_count" : 1,
									"y_count" : 1,
									"x_step" : 32,
									"y_step" : 32,

									#"image" : "d:/ymir work/ui/public/Slot_Base.sub",
								},
								#{
								#	"name" : "cd_reset_icon",
								#	"type" : "image",
								#	
								#	"x" : 46,
								#	"y" : 3,
								#
								#	"image" : "d:/icon/item/102517.tga",
								#},
								{
									"name" : "UpButton1",
									"type" : "button",
									"tooltip_text" : uiScriptLocale.RESEARCH_UP,
									"x" : 9,
									"y" : 9,
									"default_image" : TASKBAR + "pageup.sub",
									"over_image" : TASKBAR + "pageup_over.sub",
									"down_image" : TASKBAR + "pageup_click.sub",
								},
								{
									"name" : "DownButton1",
									"type" : "button",
									"tooltip_text" : uiScriptLocale.RESEARCH_DOWN,

									"x" : 9,
									"y" : 19,

									"default_image" : TASKBAR + "pagedown.sub",
									"over_image" : TASKBAR + "pagedown_over.sub",
									"down_image" : TASKBAR + "pagedown_click.sub",
								},
								{ 
									"name":"ItemSlotbar1", 
									"type":"slotbar", 
									"x":22, 
									"y":11, 
									"preset":"parameter_slot_09", 
									"children" :
									(
										{ "name":"ItemSlotbar1Text", "type":"text", "x":1, "y":2, "text":"0", "r":1.0, "g":1.0, "b":1.0, "a":1.0, "text_horizontal_align":"center", "horizontal_align":"center"},
									),
								},
								{
									"name" : "elisir_10_slot",
									"type" : "grid_table",

									"x" : 126,
									"y" : 3,

									"start_index" : 0,
									"x_count" : 1,
									"y_count" : 1,
									"x_step" : 32,
									"y_step" : 32,

									#"image" : "d:/ymir work/ui/public/Slot_Base.sub",
								},
								#{
								#	"name" : "elisir_10_icon",
								#	"type" : "image",
									
								#	"x" : 126,
								#	"y" : 3,

								#	"image" : "d:/icon/item/102529.tga",
								#},
								{
									"name" : "UpButton2",
									"type" : "button",
									"tooltip_text" : uiScriptLocale.RESEARCH_UP,
									"x" : 92,
									"y" : 9,
									"default_image" : TASKBAR + "pageup.sub",
									"over_image" : TASKBAR + "pageup_over.sub",
									"down_image" : TASKBAR + "pageup_click.sub",
								},
								{
									"name" : "DownButton2",
									"type" : "button",
									"tooltip_text" : uiScriptLocale.RESEARCH_DOWN,

									"x" : 92,
									"y" : 19,

									"default_image" : TASKBAR + "pagedown.sub",
									"over_image" : TASKBAR + "pagedown_over.sub",
									"down_image" : TASKBAR + "pagedown_click.sub",
								},
								{ 
									"name":"ItemSlotbar2", 
									"type":"slotbar", 
									"x":104, 
									"y":11, 
									"preset":"parameter_slot_09", 
									"children" :
									(
										{ "name":"ItemSlotbar2Text", "type":"text", "x":1, "y":2, "text":"0", "r":1.0, "g":1.0, "b":1.0, "a":1.0, "text_horizontal_align":"center", "horizontal_align":"center"},
									),
								},
								{
									"name" : "elisir_30_slot",
									"type" : "grid_table",

									"x" : 206,
									"y" : 3,

									"start_index" : 0,
									"x_count" : 1,
									"y_count" : 1,
									"x_step" : 32,
									"y_step" : 32,

									#"image" : "d:/ymir work/ui/public/Slot_Base.sub",
								},								
								#{
								#	"name" : "elisir_30_icon",
								#	"type" : "image",
								#	
								#	"x" : 206,
								#	"y" : 3,

								#	"image" : "d:/icon/item/102616.tga",
								#},
								{
									"name" : "UpButton3",
									"type" : "button",
									"tooltip_text" : uiScriptLocale.RESEARCH_UP,
									"x" : 172,
									"y" : 9,
									"default_image" : TASKBAR + "pageup.sub",
									"over_image" : TASKBAR + "pageup_over.sub",
									"down_image" : TASKBAR + "pageup_click.sub",
								},
								{
									"name" : "DownButton3",
									"type" : "button",
									"tooltip_text" : uiScriptLocale.RESEARCH_DOWN,

									"x" : 172,
									"y" : 19,

									"default_image" : TASKBAR + "pagedown.sub",
									"over_image" : TASKBAR + "pagedown_over.sub",
									"down_image" : TASKBAR + "pagedown_click.sub",
								},
								{ 
									"name":"ItemSlotbar3", 
									"type":"slotbar", 
									"x":184, 
									"y":11, 
									"preset":"parameter_slot_09", 
									"children" :
									(
										{ "name":"ItemSlotbar3Text", "type":"text", "x":1, "y":2, "text":"0", "r":1.0, "g":1.0, "b":1.0, "a":1.0, "text_horizontal_align":"center", "horizontal_align":"center"},
									),
								},
							),
						},
						{
							"name" : "MessagesName",
							"type" : "text",
							"x" : 115,
							"y" : 169+16,
							"text" : uiScriptLocale.SYSTEM_MESSAGES,
							"color" : colorInfo.GOLD, 
							"fontsize":"middle",
							"children" : 
							(

								{
									"name" : "NotifySlot", "type" : "slotbar", "x" : -110, "y" : 18 * 1, "width" : 305, "height" : 16*5,
									"children" :
									(
										{ "name" : "NotifyValue1", "type" : "text", "x" : 0, "y" : 0, "text" : " ", "horizontal_align" : "center", "text_horizontal_align" : "center", },
									),
								},
							),
						},
					),
				},
			),
		},
	),
}
