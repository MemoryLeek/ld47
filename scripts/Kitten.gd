extends Node2D

var RAND = RandomNumberGenerator.new()
const SPEED = 30
var FACING = "Left"
var ACTION = "Idle"

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if ACTION == "Walk":
		match FACING:
			"Left": position.x -= SPEED * delta
			"Right": position.x += SPEED * delta
			"Up": position.y -= SPEED * delta
			"Down": position.y += SPEED * delta
	
	$AnimatedSprite.play(ACTION + "_" + FACING)


func _on_Timer_timeout():
	var i = RAND.randi_range(1, 6)
	
	match i:
		1: ACTION = "Walk"
		2: ACTION = "Idle"
		3: FACING = "Left"
		4: FACING = "Right"
		5: FACING = "Up"
		6: FACING = "Down"
