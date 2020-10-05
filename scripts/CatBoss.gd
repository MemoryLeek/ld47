extends StaticBody2D

export var highlight = 0.0 setget set_highlight

var _health = 3 * 15
var _kitten_scene = preload("res://scenes/Kitten.tscn")
var _kitten_positions = []

onready var _ui : UserInterface = get_node("/root/UI")

func damage(value : float):
	if get_tree().get_nodes_in_group("kittens").size() > 0:
		return # No damage while kittens are alive
	
	self._health -= value
	$AnimationPlayer.play("OnHit")
	$BulletSpawner/AnimationPlayer.seek(0, true)
	if _health <= 0:
		get_parent().find_node("Chest").visible = true
		queue_free()
	else:
		_respawn_kittens()

func set_highlight(value : float):
	if $Sprite != null:
		$Sprite.material.set_shader_param("highlight", value)

func _ready():
	add_to_group("enemies")
	# This is needed for the spawner nowadays for it to work for some reason
	$BulletSpawner.active = false
	$BulletSpawner.interval = max(0.2, 0.8 / (_ui.iteration + 1));
	$BulletSpawner/AnimationPlayer.play("Init")
	
	$Sprite.material = $Sprite.material.duplicate(true)

	for kitten in get_tree().get_nodes_in_group("kittens"):
		_kitten_positions.append(kitten.position)

func _respawn_kittens():
	for p in _kitten_positions:
		var kitten = _kitten_scene.instance()
		get_parent().call_deferred("add_child", kitten)
		kitten.position = p
