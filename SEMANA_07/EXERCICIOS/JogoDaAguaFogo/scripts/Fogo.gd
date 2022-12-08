extends KinematicBody2D

#variaveis
var velocidade = Vector2.ZERO
var vetor_normal = Vector2(0,  -1)
var contagem_pulo = 0

#função que coordena a movimentação do personagem 
#baseados no valor indicado pelo JSON recebido pela comunicação http
func _andar():
	if ScriptGlobal.direcaoFogo == 1:
		velocidade.x = 200
	
	elif ScriptGlobal.direcaoFogo == 2:
		velocidade.x = -200
	
	else:
		velocidade.x = 0

#função que coordena o pulo do personagem 
#baseados no valor indicado pelo JSON recebido pela comunicação http
#a função também limita o personagem fazer apenas 2 pulos, pois caso
#nao tivesse isso o personagem pularia infinitas vezes
func _pular():
	if ScriptGlobal.direcaoFogo == 3 and contagem_pulo < 2:
		velocidade.y = -400
		contagem_pulo += 1

#função própria do godot que interpreta física
func _physics_process(_delta):
	
	velocidade.y += 12 #gravidade
	
	_andar()
	_pular()
	
	#função própria do godot que valida o movimento das funções _andar() e _pula() 
	move_and_slide(velocidade, vetor_normal) 
	
	#caso esteja no chão, a velocidade no y e a contagem de pulos são zerados 
	if is_on_floor():
		contagem_pulo = 0
		velocidade.y = 0
	
	#caso o personagem bata no teto ele bate a cabeça
	if is_on_ceiling():
		velocidade.y += 10

#funções das linhas 50, 54, 58 dizem sobre o personagem pegar as gemas
func _on_gemaVermelha_body_entered(body):
	if body == self:
		ScriptGlobal.gemaVermelha1 = true
		
func _on_gemaVermelha2_body_entered(body):
	if body == self:
		ScriptGlobal.gemaVermelha2 = true

func _on_gemaVermelha3_body_entered(body):
	if body == self:
		ScriptGlobal.gemaVermelha3 = true

#caso o personagem entre no lago verde ele muda a cena para a cena de "morreu"
func _on_Laguinho_verde_body_entered(body):
	if body == self:
		get_tree().change_scene("res://cenas/morreu.tscn")
		
		ScriptGlobal.gemaAzul1 = false
		ScriptGlobal.gemaAzul2 = false
		ScriptGlobal.gemaAzul3 = false
		ScriptGlobal.gemaVermelha1 = false
		ScriptGlobal.gemaVermelha2 = false
		ScriptGlobal.gemaVermelha3 = false

#caso o personagem entre no lago azul ele muda a cena para a cena de "morreu"
#e todas as variaveis de gema se resetam
func _on_Laguinho_azul_body_entered(body):
	if body == self:
		get_tree().change_scene("res://cenas/morreu.tscn")
		
		ScriptGlobal.gemaAzul1 = false
		ScriptGlobal.gemaAzul2 = false
		ScriptGlobal.gemaAzul3 = false
		ScriptGlobal.gemaVermelha1 = false
		ScriptGlobal.gemaVermelha2 = false
		ScriptGlobal.gemaVermelha3 = false

#caso o personagem entre na porta vermelha ele passa
func _on_portaVermelha_body_entered(body):
	if body == self:
		ScriptGlobal.fogoPassou = true
	else:
		ScriptGlobal.fogoPassou = false
