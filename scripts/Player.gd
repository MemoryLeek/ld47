extends Node2D

const SPEED = 100
var FACING = "Down"
var ACTION = "Idle"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	ACTION = "Idle"
	
	if Input.is_action_pressed("ui_left"):
		position.x -= SPEED * delta
		FACING = "Left"
		ACTION = "Walk"
	if Input.is_action_pressed("ui_right"):
		position.x += SPEED * delta
		FACING = "Right"
		ACTION = "Walk"
	if Input.is_action_pressed("ui_up"):
		position.y -= SPEED * delta
		FACING = "Up"
		ACTION = "Walk"
	if Input.is_action_pressed("ui_down"):
		position.y += SPEED * delta
		FACING = "Down"
		ACTION = "Walk"
	
	$AnimatedSprite.play(ACTION + "_" + FACING)
