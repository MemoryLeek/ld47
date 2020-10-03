extends KinematicBody2D

var velocity = Vector2(0, 0)

func _process(delta):
	var collision = move_and_collide(velocity)
	if collision != null:
		queue_free()
