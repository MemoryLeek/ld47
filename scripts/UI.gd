extends CanvasLayer

export(int, 3) var hearts = 3 setget set_hearts

onready var _heart1 : TextureButton = find_node("Heart1")
onready var _heart2 : TextureButton = find_node("Heart2")
onready var _heart3 : TextureButton = find_node("Heart3")

func set_hearts(h : int):
	hearts = h
	if _heart3 != null:
		_heart3.disabled = h < 3
	if _heart2 != null:
		_heart2.disabled = h < 2
	if _heart1 != null:
		_heart1.disabled = h < 1

func _ready():
	set_hearts(hearts)
