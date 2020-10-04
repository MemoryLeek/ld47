extends StaticBody2D

onready var _ui : UserInterface = get_node("/root/UI")
var _has_interacted = false

func interact():
	if not _has_interacted:
		if _ui.has_item("Hat"):
			_play_move_interaction()
		else:
			_play_block_interaction()
		_has_interacted = true

func _play_block_interaction():
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

func _play_move_interaction():
	var s = _ui.connect("interaction_ended", self, "_move_gandolf")
	assert(s == OK)
	_ui._text_engine.buff_text("GANDOLF: ")
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("Oh, a hat? ", 0.08)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("For me?\n", 0.08)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("I must admit that my hairline has been receding lately...\n", 0.03)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("Fine. I don't know what interest you have in my personal living quarters, but sure...\n", 0.03)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("You. ", 0.1)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("Shall. ", 0.1)
	_ui._text_engine.buff_silence(0.5)
	_ui._text_engine.buff_text("Pass!", 0.1)
	_ui._text_engine.set_state(_ui._text_engine.STATE_OUTPUT)
	pass

func _ready():
	var animation = Animation.new()
	var track_index = animation.add_track(Animation.TYPE_VALUE)
	animation.track_set_path(track_index, ":position")
	animation.track_insert_key(track_index, 0.0, position)
	animation.track_insert_key(track_index, 1.0, position + Vector2(8, 0))
	$AnimationPlayer.add_animation("Move", animation)

func _move_gandolf():
	_ui.take_item("Hat")
	$AnimationPlayer.play("Move")
