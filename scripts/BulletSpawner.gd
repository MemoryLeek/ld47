extends Node2D

export var active = false setget set_active
export var interval = 0.2 setget set_interval
export(PackedScene) var bullet_type

func _ready():
	assert(bullet_type != null, "BulletSpawner with no bullet type assigned")
	if active:
		$Timer.start()

func _on_Timer_timeout():
	var bullet = bullet_type.instance()
	bullet.velocity = Vector2(0, 100)
	add_child(bullet)

func set_active(active: bool):
	if active:
		$Timer.start()
	else:
		$Timer.stop()

func set_interval(interval: float):
	$Timer.wait_time = interval
