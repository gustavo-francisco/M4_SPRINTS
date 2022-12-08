extends Node

#variaveis que veem se o fogo ta na porta vermelha e a agua na porta azul
var fogoPassou = false
var aguaPassou = false

#caso algum personagem seja morto em algum lago a variavel vira verdadeira e troca pra cena de "morreu"
var morreu = false

#variaveis que contam as gemas pegas pelos personagens

#a agua pega apenas as azuis
var gemaAzul1 = false
var gemaAzul2 = false
var gemaAzul3 = false

#o fogo pega apenas as vermelhas
var gemaVermelha1 = false
var gemaVermelha2 = false
var gemaVermelha3 = false

#variaveis que consideram os valores das direções
#caso seja 1, o personagem anda pra direita
#caso seja 2, o personagem anda pra esquerda
#caso seja 3, o personagem pula
var direcaoFogo = 0
var direcaoAgua = 0
