extends KinematicBody2D

export(Vector2) var velocity = Vector2(0, 0)
export(float) var lifetime = 5.0

onready var _tail = find_node("Tail")
onready var _sprite2 = find_node("Sprite2")
onready var _sprite3 = find_node("Sprite3")

func _ready():
	$ExpiryTimer.start(lifetime)

func _process(delta):
	var collision = move_and_collide(velocity)
	if collision != null:
		if collision.collider.name == "Player":
			collision.collider.damage(1)
		queue_free()

	_tail.rotation = velocity.angle()
	_sprite2.rotation = -_tail.rotation
	_sprite3.rotation = -_tail.rotation
