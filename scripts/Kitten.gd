extends Node2D

var RAND = RandomNumberGenerator.new()
var FACING = "Left"
var ACTION = "Idle"
var player
var charging = false

# Called when the node enters the scene tree for the first time.
func _ready():
	player = get_tree().current_scene.find_node("Player")
	pass # Replace with function body.

func calcSpeed():
	if charging:
		return 200
	else:
		return 30

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	#if ACTION == "Idle":
	var xDist = abs(position.x - player.position.x)
	var yDist = abs(position.y - player.position.y)
	
	if FACING == "Right" and player.position.x > position.x and yDist < 30:
		charging = true
		ACTION = "Walk"
		$ChargingTimer.start(0.5)
	elif FACING == "Left" and player.position.x < position.x and yDist < 30:
		charging = true
		ACTION = "Walk"
		$ChargingTimer.start(0.5)
	
	if ACTION == "Walk":
		var speed = calcSpeed()
		match FACING:
			"Left": position.x -= speed * delta
			"Right": position.x += speed * delta
			"Up": position.y -= speed * delta
			"Down": position.y += speed * delta
	
	$AnimatedSprite.play(ACTION + "_" + FACING)


func _on_Timer_timeout():
	if charging:
		pass
	
	var i = RAND.randi_range(1, 6)

	match i:
		1: ACTION = "Walk"
		2: ACTION = "Idle"
		3: FACING = "Left"
		4: FACING = "Right"
		5: FACING = "Up"
		6: FACING = "Down"


func _on_ChargingTimer_timeout():
	charging = false
