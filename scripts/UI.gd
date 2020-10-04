extends CanvasLayer
class_name UserInterface

export(int, 3) var hearts = 3 setget set_hearts

onready var _heart1 : TextureButton = find_node("Heart1")
onready var _heart2 : TextureButton = find_node("Heart2")
onready var _heart3 : TextureButton = find_node("Heart3")

onready var _text_engine = find_node("TextInterfaceEngine")

func give_item(name : String):
	find_node(name).visible = true

func set_hearts(h : int):
	hearts = h
	if _heart3 != null:
		_heart3.disabled = h < 3
	if _heart2 != null:
		_heart2.disabled = h < 2
	if _heart1 != null:
		_heart1.disabled = h < 1

func get_text_engine() -> Node:
	return _text_engine
	
func is_interacting() -> bool:
	return $TextBackground.visible
	
func try_mark_read():
	if $TextBackground.visible and _text_engine._state == _text_engine.STATE_WAITING:
		$TextBackground.visible = false
		_text_engine.reset()

func _ready():
	set_hearts(hearts)

func _on_TextInterfaceEngine_state_change(state : int):
	if state == _text_engine.STATE_OUTPUT:
		$TextBackground.visible = true


func _on_TextInterfaceEngine_buff_cleared():
	$TextBackground.visible = false
