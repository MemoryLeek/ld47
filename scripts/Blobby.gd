extends KinematicBody2D

onready var _ray : RayCast2D = $RayCast2D
onready var _player : Player = get_tree().current_scene.find_node("Player")

onready var _ui : UserInterface = get_node("/root/UI")
onready var _health = (_ui.iteration + 2) * 15

func damage(amount : int):
	$OnTakeDamage.play()
	_health -= amount
	if _health <= 0:
		$AnimationPlayer.play("Death")
	else:
		$AnimationPlayer.play("Hit")

func _ready():
	add_to_group("enemies")
	var animation_clone = $AnimationPlayer.get_animation("Attack").duplicate(true)
	$AnimationPlayer.remove_animation("Attack")
	$AnimationPlayer.add_animation("Attack", animation_clone)

func _physics_process(delta):
	var animation = $AnimationPlayer.current_animation
	if animation == "Attack" or animation == "Death" or animation == "Hit":
		return

	_ray.cast_to = to_local(_player.global_position)
	if _ray.get_collider() != null and _ray.get_collider().name == "Player":
		_jump_towards(to_local(_ray.get_collision_point()))

func _jump_towards(target : Vector2):
	var anim : Animation = $AnimationPlayer.get_animation("Attack")
	target = target.clamped(2 * 32)
	print("Jumping from " + str(position) + " to " + str(target))
	anim.track_set_key_value(1, 0, position)
	anim.track_set_key_value(1, 1, position + target)
	$AnimationPlayer.play("Attack")

func _on_DamageArea_body_entered(body):
	if body.name == "Player":
		body.damage(1)
