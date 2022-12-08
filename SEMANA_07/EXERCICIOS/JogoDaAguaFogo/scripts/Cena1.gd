extends Node2D

#função própria do godot que roda a todo o momento para verificar se o fogo está
#na porta vermelha e a agua está na porta azul, caso os 2 sejam verdadeiros troca
#pra cena de vitoria
func _process(delta):
	if ScriptGlobal.aguaPassou == true and ScriptGlobal.fogoPassou == true:
		get_tree().change_scene("res://cenas/vitoria.tscn")

#chama a requisição http em uma certa quantidade de tempo
func _on_Timer_timeout():
	var request = $HTTPRequest.request("http://10.128.65.111:3000/leitura_direcao")
	
#chama o endpoint de GET da requisição http e atribui os valores da posição 0
#da array para o fogo e da posição 1 da array para a agua
func _on_HTTPRequest_request_completed(result, response_code, headers, body):
	var json = JSON.parse(body.get_string_from_utf8())
	ScriptGlobal.direcaoFogo = int((json.result[0]))
	ScriptGlobal.direcaoAgua = int((json.result[1]))
