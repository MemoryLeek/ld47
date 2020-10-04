extends KinematicBody2D

onready var _ui : UserInterface = get_node("/root/UI")
var _has_interacted = false

func interact():
	if not _has_interacted:
		var s = _ui.connect("interaction_ended", self, "_enable_portal")
		assert(s == OK)
		
		_ui._text_engine.buff_text("BOY: ")
		_ui._text_engine.buff_text("Hello there!\n", 0.1)
		_ui._text_engine.buff_silence(0.5)
		_ui._text_engine.buff_text("I seem to have lost my teddy bear.", 0.05)
		_ui._text_engine.set_state(_ui._text_engine.STATE_OUTPUT)
		_has_interacted = true

func _enable_portal():
	get_tree().current_scene.find_node("Portal").set_enabled(true)
