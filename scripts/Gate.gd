extends StaticBody2D

func interact():
	$AnimationPlayer.play("Open")

func _on_AnimationPlayer_animation_finished(anim_name):
	$CollisionShape2D.queue_free()
