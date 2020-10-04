extends StaticBody2D

onready var _ui : UserInterface = get_node("/root/UI")
var _has_interacted = false

func interact():
	if not _has_interacted:
		var s = _ui.connect("interaction_ended", self, "_enable_portal")
		assert(s == OK)
		
		_ui._text_engine.buff_text("GANDOLF: ")
		_ui._text_engine.buff_silence(0.5)
		_ui._text_engine.buff_text("You. ", 0.1)
		_ui._text_engine.buff_silence(0.5)
		_ui._text_engine.buff_text("Shall. ", 0.1)
		_ui._text_engine.buff_silence(0.5)
		_ui._text_engine.buff_text("Not. ", 0.1)
		_ui._text_engine.buff_silence(0.5)
		_ui._text_engine.buff_text("Pass!", 0.1)
		_ui._text_engine.set_state(_ui._text_engine.STATE_OUTPUT)
		_has_interacted = true
