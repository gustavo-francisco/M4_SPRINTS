extends Control

#caso o botão "jogar de novo" é apertado a cena começa de novo
func _on_Button_pressed():
	get_tree().change_scene("res://cenas/Cena1.tscn")
