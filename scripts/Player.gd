extends KinematicBody2D

const SPEED = 100
var FACING = "Down"
var ACTION = "Idle"
var attacking = false
var velocity = Vector2(0, 0)

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func mix(a, b, w):
	return a * w + b * (1 - w)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	var desiredVelocity = Vector2(0, 0)
	
	if Input.is_action_pressed("attack"):
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
	
	velocity = mix(desiredVelocity, velocity, delta * 20)
	move_and_slide(velocity)
	
	$AnimatedSprite.play(ACTION + "_" + FACING)


func _on_animation_finished():
	if $AnimatedSprite.animation.begins_with("Attack"):
		attacking = false
