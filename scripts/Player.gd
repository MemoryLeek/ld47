extends KinematicBody2D
class_name Player

const SPEED = 100
var FACING = "Down"
var ACTION = "Idle"
var attacking = false
var velocity = Vector2(0, 0)
var damageVisualOpacity = 0
var vulnerable = true
export(Color) var camera_overlay_color setget set_camera_overlay_color

onready var _ui : UserInterface = get_node("/root/UI")

func swordShapeSetState():
	$SwordArea/SwordShapeDown.disabled = not (attacking and FACING == "Down")
	$SwordArea/SwordShapeUp.disabled = not (attacking and FACING == "Up")
	$SwordArea/SwordShapeLeft.disabled = not (attacking and FACING == "Left")
	$SwordArea/SwordShapeRight.disabled = not (attacking and FACING == "Right")

# Called when the node enters the scene tree for the first time.
func _ready():
	$Camera2D/CanvasLayer/ColorRect.visible = true
	$Camera2D/CanvasLayer/ProperColorRect.visible = true
	$AnimationPlayer.play("Transition")

func mix(a, b, w):
	return a * w + b * (1 - w)

func damage(value):
	$Timer.start()
	if vulnerable:
		vulnerable = false
		_ui.hearts -= value
		damageVisualOpacity = value * 0.4
		$OnHitSound.play()
		if _ui.hearts <= 0:
			_ui.deaths += 1
			$DeathAnimationPlayer.play("Death")
	
func set_camera_overlay_color(color : Color):
	if $Camera2D/CanvasLayer/ColorRect != null:
		$Camera2D/CanvasLayer/ColorRect.color.a = 0
		$Camera2D/CanvasLayer/ProperColorRect.color = color

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	damageVisualOpacity = damageVisualOpacity * (1 - delta) - delta
	$Camera2D/CanvasLayer/ColorRect.color = Color(255, 0, 0, damageVisualOpacity)
	
	var desiredVelocity = Vector2(0, 0)
	
	if _ui.is_interacting():
		ACTION = "Idle"
		attacking = false
		if Input.is_action_just_pressed("attack"):
			_ui.try_mark_read()
	elif Input.is_action_pressed("attack"):
		ACTION = "Attack"
		attacking = true
	elif not attacking:
		ACTION = "Idle"
		if Input.is_action_pressed("ui_left"):
			desiredVelocity.x -= SPEED
			FACING = "Left"
			ACTION = "Walk"
		if Input.is_action_pressed("ui_right"):
			desiredVelocity.x += SPEED
			FACING = "Right"
			ACTION = "Walk"
		if Input.is_action_pressed("ui_up"):
			desiredVelocity.y -= SPEED
			FACING = "Up"
			ACTION = "Walk"
		if Input.is_action_pressed("ui_down"):
			desiredVelocity.y += SPEED
			FACING = "Down"
			ACTION = "Walk"
	
	velocity = mix(desiredVelocity, velocity, delta * 15)
	move_and_slide(velocity)
	
	swordShapeSetState()
	$AnimatedSprite.play(ACTION + "_" + FACING)


func _on_animation_finished():
	if $AnimatedSprite.animation.begins_with("Attack"):
		attacking = false

func _pause_world():
	get_tree().paused = true

func _on_DeathAnimationPlayer_animation_finished(anim_name):
	get_tree().reload_current_scene()
	_ui.set_hearts(3)
	get_tree().paused = false


func _on_Timer_timeout():
	vulnerable = true
