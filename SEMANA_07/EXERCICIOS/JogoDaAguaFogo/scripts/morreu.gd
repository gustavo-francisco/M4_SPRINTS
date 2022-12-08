extends Control

#Quando o botão "reiniciar" é apertado, a cena reseta
func _on_Button_pressed():
	get_tree().change_scene("res://cenas/Cena1.tscn")
