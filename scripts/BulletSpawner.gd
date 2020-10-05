extends Node2D

enum SpawnPattern { CIRCULAR_45, CIRCULAR_20, WALL_1, WALL_SLOW }

export var active = false setget set_active, get_active
export var interval = 0.2 setget set_interval
export(SpawnPattern) var pattern = SpawnPattern.CIRCULAR_45
export(PackedScene) var bullet_type

var _direction = Vector2(0, 1)
var _offset = Vector2(20, 0)

func _ready():
	assert(bullet_type != null, "BulletSpawner with no bullet type assigned")
	$Timer.paused = false
	set_interval(interval)
	set_active(active)

func _on_Timer_timeout():
	var bullet = bullet_type.instance()
	_initialize_bullet(bullet)
	add_child(bullet)

func _initialize_bullet(bullet):
	match pattern:
		SpawnPattern.CIRCULAR_45:
			bullet.velocity = _direction * 1.5
			_direction = _direction.rotated(deg2rad(45)).normalized()
		SpawnPattern.CIRCULAR_20:
			bullet.velocity = _direction * 1.5
			_direction = _direction.rotated(deg2rad(20)).normalized()
		SpawnPattern.WALL_1:
			bullet.velocity = Vector2(0, 10)
			bullet.position += _offset
			_offset *= 1.1
			_offset.x = -fmod(_offset.x, 100)
		SpawnPattern.WALL_SLOW:
			bullet.velocity = Vector2(0, 3)
			bullet.position += _offset
			_offset *= 1.1
			_offset.x = -fmod(_offset.x, 100)

func set_active(a: bool):
	if active == a:
		return

	active = a
	if active:
		$Timer.start(interval)
	else:
		$Timer.stop()
		
func get_active() -> bool:
	return active

func set_interval(i: float):
	if interval == i:
		return
	
	interval = i
	$Timer.wait_time = interval
