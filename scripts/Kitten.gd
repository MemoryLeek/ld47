extends KinematicBody2D

var RAND = RandomNumberGenerator.new()
var FACING = "Left"
var ACTION = "Idle"
var player
var charging = false
var velocity = Vector2(0, 0)
export var highlight = 0.0 setget set_highlight
export var health = 25

# Called when the node enters the scene tree for the first time.
func _ready():
	RAND.seed = self.get_index()
	player = get_tree().current_scene.find_node("Player")
	$AnimatedSprite.material = $AnimatedSprite.material.duplicate(true)

func mix(a, b, w):
	return a * w + b * (1 - w)

func calcSpeed():
	if charging:
		return 200
	else:
		return 30

func damage(value : float):
	self.health -= value
	$AnimationPlayer.play("OnHit")
	
	if health < 0:
		queue_free()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta : float):
	if charging:
		var dist = (position - player.position).length()
		if dist < 35:
			charging = false
			player.damage(1)
			match FACING:
				"Left": 
					player.velocity.x -= 500
					velocity.x += 1500
				"Right": 
					player.velocity.x += 500
					velocity.x -= 1500
				"Up": 
					player.velocity.y -= 500
					velocity.y += 1500
				"Down": 
					player.velocity.y += 500
					velocity.x -= 1500
	else:
		var xDist = abs(position.x - player.position.x)
		var yDist = abs(position.y - player.position.y)
		
		if FACING == "Right" and player.position.x > position.x and yDist < 20:
			charging = true
			ACTION = "Walk"
			$ChargingTimer.start(0.5)
		elif FACING == "Left" and player.position.x < position.x and yDist < 20:
			charging = true
			ACTION = "Walk"
			$ChargingTimer.start(0.5)
		elif FACING == "Up" and player.position.y < position.y and xDist < 20:
			charging = true
			ACTION = "Walk"
			$ChargingTimer.start(0.5)
		elif FACING == "Down" and player.position.y > position.y and xDist < 20:
			charging = true
			ACTION = "Walk"
			$ChargingTimer.start(0.5)
	
	var desiredVelocity = Vector2(0, 0)
	
	if ACTION == "Walk":
		var speed = calcSpeed()
		match FACING:
			"Left": desiredVelocity.x -= speed
			"Right": desiredVelocity.x += speed
			"Up": desiredVelocity.y -= speed
			"Down": desiredVelocity.y += speed
	
	velocity = mix(desiredVelocity, velocity, delta * 15)
	move_and_slide(velocity)
	$AnimatedSprite.play(ACTION + "_" + FACING)

func set_highlight(value : float):
	if $AnimatedSprite != null:
		$AnimatedSprite.material.set_shader_param("highlight", value)

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
