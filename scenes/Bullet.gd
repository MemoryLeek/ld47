extends KinematicBody2D

var velocity = Vector2(0, 0)

func _process(delta):
	move_and_slide(velocity)
