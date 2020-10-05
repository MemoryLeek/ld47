extends KinematicBody2D

onready var _ui : UserInterface = get_node("/root/UI")
var _has_interacted = false

var _boss_scene = preload("res://scenes/Boy_Evil.tscn")

func interact():
	if not _has_interacted:
		if _ui.has_item("Teddy"):
			_play_has_teddy_interaction()
		else:
			_play_no_teddy_interaction()
		_has_interacted = true

func _play_no_teddy_interaction():
	var s = _ui.connect("interaction_ended", self, "_enable_portal")
	assert(s == OK)
	_ui._text_engine.buff_text("BOY: ")
	_ui._text_engine.buff_text("Hi there miss.\n", 0.1)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("Why am I crying, you ask?\n", 0.05)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("Well, you see, I have lost my most precious keepsake, my teddy bear.\n", 0.03)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("I lost it while playing around that glowing altar over there.\n", 0.03)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("What, it's not glowing? I could swear it was...", 0.05)
	_ui._text_engine.set_state(_ui._text_engine.STATE_OUTPUT)
	
func _play_has_teddy_interaction():
	var s = _ui.connect("interaction_ended", self, "_enrage")
	assert(s == OK)
	_ui._text_engine.buff_text("BOY: ")
	_ui._text_engine.buff_text("Hi there miss.\n", 0.1)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("...\n", 0.4)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("Wait. That is... ", 0.1)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("My teddy bear?\n", 0.1)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("You... ", 0.4)
	_ui._text_engine.buff_text("You stole it from me! ", 0.05)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("My most precious keepsake ever.\n", 0.05)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("You are going to ", 0.05)
	_ui._text_engine.buff_text("pay ", 0.3)
	_ui._text_engine.buff_silence(0.2)
	_ui._text_engine.buff_text("for this!!", 0.05)
	_ui._text_engine.set_state(_ui._text_engine.STATE_OUTPUT)

func _enable_portal():
	get_tree().current_scene.find_node("Portal").set_enabled(true)

func _enrage():
	var evil = _boss_scene.instance()
	get_parent().call_deferred("add_child", evil)
	evil.position = position
	queue_free()

