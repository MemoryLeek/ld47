extends StaticBody2D

export(bool) var locked = false
export(String, "Key", "Hat", "Teddy") var content = "Hat"
var _has_content = true
onready var _ui : UserInterface = get_node("/root/UI")

func interact():
	if _has_content and not locked:
		$Sprite_Closed.visible = false
		$Sprite_Open.visible = true
		_ui.give_item(content)
		_has_content = false
