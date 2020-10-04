extends Area2D

enum ActivationMode { MANUAL, ENEMIES_DEAD }

export(String, FILE) var target_scene
export(ActivationMode) var activation_mode = ActivationMode.ENEMIES_DEAD

export(Color) var overlay_color setget set_overlay_color
export(Vector2) var player_offset setget set_player_offset
export(bool) var enabled setget set_enabled

onready var player : Player = get_tree().current_scene.find_node("Player")
var player_start_position = Vector2(0, 0)

func set_overlay_color(color : Color):
	if player != null:
		player.camera_overlay_color = color

func set_player_offset(offset : Vector2):
	if player == null:
		return
	if player_start_position.length() == 0:
		player_start_position = player.position
	player.position = player_start_position + offset

func set_enabled(e : bool):
	enabled = e
	if enabled:
		$AnimatedSprite.play("On")
	else:
		$AnimatedSprite.play("Off")

func _ready():
	assert(player != null, "Portal could not find and store reference to player")
	assert(target_scene != "", "Portal with no target scene")
	pause_mode = Node.PAUSE_MODE_PROCESS

func _physics_process(delta):
	if not enabled and activation_mode == ActivationMode.ENEMIES_DEAD:
		if get_tree().get_nodes_in_group("enemies").size() == 0:
			set_enabled(true)

func _on_body_entered(body : Node):
	if enabled and body.name == "Player":
		body.pause_mode
		get_tree().paused = true
		$AnimationPlayer.play("Transition")

func _on_animation_finished(anim_name : String):
	if anim_name == "Transition":
		get_tree().change_scene(target_scene)
		get_tree().paused = false
