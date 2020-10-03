extends KinematicBody2D

const SPEED = 100
var FACING = "Down"
var ACTION = "Idle"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	var velocity = Vector2(0, 0)
	ACTION = "Idle"
	
	if Input.is_action_pressed("ui_left"):
		velocity.x -= SPEED
		FACING = "Left"
		ACTION = "Walk"
	if Input.is_action_pressed("ui_right"):
		velocity.x += SPEED
		FACING = "Right"
		ACTION = "Walk"
	if Input.is_action_pressed("ui_up"):
		velocity.y -= SPEED
		FACING = "Up"
		ACTION = "Walk"
	if Input.is_action_pressed("ui_down"):
		velocity.y += SPEED
		FACING = "Down"
		ACTION = "Walk"
	
	move_and_slide(velocity)
	
	$AnimatedSprite.play(ACTION + "_" + FACING)
