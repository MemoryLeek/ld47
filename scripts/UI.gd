extends CanvasLayer
class_name UserInterface

export(int, 3) var hearts = 3 setget set_hearts
var iteration = 0
var deaths = 0

onready var _heart1 : TextureButton = find_node("Heart1")
onready var _heart2 : TextureButton = find_node("Heart2")
onready var _heart3 : TextureButton = find_node("Heart3")

onready var _text_engine = find_node("TextInterfaceEngine")

signal interaction_ended

func give_item(name : String):
	$OnPickupSound.play()
	find_node(name).visible = true

func take_item(name : String):
	find_node(name).visible = false

func has_item(name : String) -> bool:
	return find_node(name).visible

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
		emit_signal("interaction_ended")

func show_stats():
	var t = $StatsBackground/CenterContainer/Stats.text
	t = t.replace("{x}", str(deaths))
	t = t.replace("{y}", str(iteration))
	$StatsBackground/CenterContainer/Stats.text = t
	$AnimationPlayer.play("FadeInStats")

func _ready():
	set_hearts(hearts)
	_text_engine.set_break_key_by_scancode(KEY_SPACE)

func _on_TextInterfaceEngine_state_change(state : int):
	if state == _text_engine.STATE_OUTPUT:
		$TextBackground.visible = true

func _on_TextInterfaceEngine_buff_cleared():
	$TextBackground.visible = false
