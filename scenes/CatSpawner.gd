extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
onready var kittenScene = preload("res://scenes/Kitten.tscn")


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Timer_timeout():
	var kitten = kittenScene.instance()
	kitten.position = position
	get_tree().current_scene.add_child(kitten)
