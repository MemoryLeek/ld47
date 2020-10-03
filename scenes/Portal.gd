extends Area2D

export(PackedScene) var target_scene

func _ready():
	connect("body_entered", self, "on_body_entered")

func on_body_entered(body: Node):
	print(body.name + " entered portal")
	get_tree().change_scene_to(target_scene)
