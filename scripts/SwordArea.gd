extends Area2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

func activate():
	pass

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


func _on_SwordArea_body_entered(body):
	if body.has_method("damage") and body.name != "Player":
		body.damage(15)
	if body.has_method("interact"):
		body.interact()
