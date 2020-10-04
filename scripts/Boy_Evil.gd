extends KinematicBody2D

onready var _ui : UserInterface = get_node("/root/UI")
var rand = RandomNumberGenerator.new()
var player
var aggro = false

var originalPos

func _ready():
	originalPos = position
	rand.seed = self.get_index()
	player = get_tree().current_scene.find_node("Player")
	$BulletSpawner.active = false
	$BulletSpawner2.active = false
	
func _process(delta):
	if not aggro:
		return
	
	position = originalPos + Vector2(rand.randf_range(-3, 3), rand.randf_range(-3, 3))
#	$BulletSpawner.active = true
#	$BulletSpawner.pattern = 2
#	$BulletSpawner.set_interval(0.1)


func _on_AggroArea_body_entered(body):
	if body.name == "Player" and not aggro:
		aggro = true
		$AnimationPlayer.play("Battle")
		
