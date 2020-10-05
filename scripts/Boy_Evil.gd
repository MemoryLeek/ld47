extends KinematicBody2D

onready var _ui : UserInterface = get_node("/root/UI")
var rand = RandomNumberGenerator.new()
var player
var aggro = false
var _health = 3 * 15

var originalPos

var _normal_scene = load("res://scenes/Boy.tscn")

func damage(amount : int):
	$OnTakeDamage.play()
	$DamageAnimation.play("OnHit")
	_health -= amount
	print(_health)
	if _health <= 0:
		_go_nice()

func _ready():
	add_to_group("enemies")
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


func _go_nice():
	var nice = _normal_scene.instance()
	get_parent().call_deferred("add_child", nice)
	nice.exhausted = true
	nice.position = position
	queue_free()
