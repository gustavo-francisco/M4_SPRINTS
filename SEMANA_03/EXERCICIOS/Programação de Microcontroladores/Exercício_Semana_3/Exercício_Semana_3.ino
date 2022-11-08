
//Definição de variáveis:
const int Buzzer = 5;
const int ldr = 14;
int frequencias[16] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600 }; //Array com todas as frequências sonoras do botão;
const int tamanhoArray = 360;
int valores[tamanhoArray]; //Array com os valores que ficarão salvos e tocaram quando o botão de tocar for pressionado.
int ultimaPosicao = -1;
int faixa;

void setup() {
  Serial.begin(115200);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(38, INPUT);
}

int estadoSalvar = LOW;
int estadoTocar = LOW;

void loop() {
  int leitura_ldr;
  leitura_ldr = analogRead(ldr);
  //Condição do botão que lê e salva os valores.
  if (digitalRead(38) == HIGH && estadoSalvar == LOW) {
    acendeLuz(encontraFaixa(leitura_ldr));
    salvaValores(encontraFaixa(leitura_ldr));
    estadoSalvar = HIGH;
  } else if (digitalRead(38) == LOW && estadoSalvar == HIGH) {
    estadoSalvar = LOW;
  }
  //Condição do botão que toca os valores salvos.
  if (digitalRead(37) == HIGH && estadoTocar == LOW) {
    tocaRaul();
    estadoTocar = HIGH;
  } else if (digitalRead(37) == LOW && estadoSalvar == HIGH) {
    estadoTocar = LOW;
  }
}
//Função que padroniza o valor lido pelo sensor de luz colocando-o numa escala de 0 a 15:
int encontraFaixa(int leitura_ldr) {
  faixa = (leitura_ldr / 4095.0) * 15;
  return faixa;
}
//Função que transforma o valor padronizado em número binário através da regra dos restos:
int transformaBinario(int faixa) {
  int binario = 0;
  int produto = 1;
  int resto;
  while (faixa > 0) {
    resto = faixa % 2;
    binario = binario + (resto * produto);
    faixa = faixa / 2;
    produto *= 10;
  }
  return binario;
}
//Função que isola cada dígito do número binário, do menos significativo para o mais significativo, para que posteriormente possamos escrever 
//o estado dos leds e assim, conseguir uma série de combinações a depender do valor lido pelo sensor de luz
void acendeLuz(int faixa) {
  int binario = transformaBinario(faixa);
  bool branco = binario % 10;
  binario /= 10;
  bool azul = binario % 10;
  binario /= 10;
  bool amarelo = binario % 10;
  binario /= 10;
  bool vermelho = binario % 10;

  digitalWrite(1, vermelho);
  digitalWrite(2, amarelo);
  digitalWrite(3, azul);
  digitalWrite(4, branco);

  tone(Buzzer, frequencias[faixa]);
  delay(1000);
  noTone(Buzzer);
}
//Função que salva os valores que foram lidos pelo botão e coloca todos em uma array, para podermos repetir a ordem em um outro botão.
void salvaValores(int valor) {
  if (ultimaPosicao + 1 >= tamanhoArray) {
    Serial.println("Não é possível salvar esse valor");
  } else {
    valores[ultimaPosicao + 1] = valor;
    ultimaPosicao++;
  }
}
//Função que passa por todos os valores que foram salvos no array, fazendo com que o led brilhe e o buzzer toque de acordo com o índice atual.
void tocaRaul() {
  for (int i = 0; i < ultimaPosicao + 1; i++) {
    acendeLuz(valores[i]);
    delay(500);
  }
  ultimaPosicao = -1;
}