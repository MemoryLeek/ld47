extends KinematicBody2D

var rand = RandomNumberGenerator.new()
var player
var active = false

func _ready():
	rand.seed = self.get_index()
	player = get_tree().current_scene.find_node("Player")

func _process(delta):
	if active == false:
		return
	
	var normal = (player.position - position).normalized()
	move_and_slide(normal * 15)

func damage(value):
	$AnimationPlayer.play("Death")

func _on_Timer_timeout():
	if active == false:
		return
	
	$AnimationPlayer.play("Teleport")

func teleport():
	var normal = Vector2(rand.randf() - 0.5, rand.randf() - 0.5).normalized()
	var distance = rand.randf_range(32, 64)
	
	position = player.position + normal * distance

func _on_AggroArea_body_entered(body):
	if body.name == "Player":
		active = true
		$AnimatedSprite.play()


func _on_AggroArea_body_exited(body):
	if body.name == "Player":
		active = false
		$AnimatedSprite.stop()
