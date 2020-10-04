extends StaticBody2D

export(String, "Key", "Hat", "Teddy") var content = "Hat"
var _has_content = true
onready var _ui : UserInterface = get_node("/root/UI")

func interact():
	if _has_content:
		$Sprite_Closed.visible = false
		$Sprite_Open.visible = true
		_ui.give_item(content)
		_has_content = false
