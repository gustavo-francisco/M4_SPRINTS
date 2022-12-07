// Inclusão das bibliotecas necessárias para a execução do código.
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Inteli-COLLEGE"; // ID da rede Wi-Fi.
const char* password = "QazWsx@123"; // Senha da rede Wi-Fi.

const char* serverName = "http://10.128.65.111:3000/insere_direcao_gt"; // Servidor. Endpoint que recebe o JSON (arquivo que contém um texto) que ditará a direção que o boneco andará e enviará para a engine.

const int botaoDireita = 42; // Definição do pino do botão que comandará o personagem para a direita.
const int botaoEsquerda = 1;// Definição do pino do botão que comandará o personagem para a esquerda.
const int botaoPula = 41; // Definição do pino do botão que comandará o personagem para pular.

void setup() {
  pinMode(botaoDireita, INPUT);// Configuração do comportamento do pino do botão que comandará o personagem para a direita.
  pinMode(botaoEsquerda, INPUT);// Configuração do comportamento do pino do botão que comandará o personagem para a esquerda.
  pinMode(botaoPula, INPUT);// Configuração do comportamento do pino do botão que comandará o personagem para pular.
  pinMode(3, OUTPUT); // Configuração do comportamento do led que acenderá quando qualquer botão for pressionado. Esse led foi adicionado apenas com o intuito de partilhar o feedback do funcionamento dos botões.
  Serial.begin(115200);// Inícia a transmissão de dados seriais.
  WiFi.begin(ssid, password);// Inícia a função WiFi e recebe como parâmetro o ID e senha definidos no início do código.
}

// Função que enviará a requisição HTTP para o servidor. Ela recebe como parâmetro a direção, que será transformada para o formato de string para ser enviada como JSON para o servidor e posteriormente essa informação será processada na Engine.
void sendRequest(int direcao){
  // Condição que configura o cliente no Wi-Fi e HTTP caso a conexão exista
  if (WiFi.status() == WL_CONNECTED) {
  WiFiClient client;
  HTTPClient http;

  String json = "{\"direcao\": \"" + String(direcao) + "\"}";// Transforma o parâmetro recebido em string e o comporta dentro de um arquivo JSON

  // Caminho da requisição HTTP.
  http.begin(client, serverName);


  // Realização da requisição HTTP com conteúdo JSON.
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.sendRequest("POST", json);
  // Printa no monitor serial o status de resposta de acordo com o código HTTP
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  http.end();
  }
}

void loop() {
  // As condições abaixo se referem a locomoção do personagem.
    if (digitalRead(botaoDireita) == HIGH) { // Caso o botão esteja pressionado, ele enviará a requisição com a string "1", que na Engine utilizada significa que o personagem andará para a direita.
      sendRequest(1); 
    } 
    else if (digitalRead(botaoEsquerda) == HIGH){ // Caso o botão esteja pressionado, ele enviará a requisição com a string "2", que na Engine utilizada significa que o personagem andará para a esquerda.
      sendRequest(2);
    }
    if (digitalRead(botaoPula) == HIGH){ // Caso o botão esteja pressionado, ele enviará a requisição com a string "3", que na Engine utilizada significa que o personagem pulará.
      sendRequest(3);
    }
    if (digitalRead(botaoPula) == LOW && digitalRead(botaoDireita) == LOW && digitalRead(botaoEsquerda) == LOW){ // Caso os botões não esteja pressionado, ele enviará a requisição com a string "0", que na Engine utilizada significa que o personagem ficará parado.
      sendRequest(0);
    }
  // As condições abaixo se referem ao led de feedback do botão.
  if(digitalRead(1) == HIGH) { // Caso o botão do pino 1 esteja pressionado, o led acenderá.
    digitalWrite(3, HIGH);
  } else { // Caso o botão do pino 1 não esteja pressionado, o led permanecerá apagado.
    digitalWrite(3, LOW);
  }
  if (digitalRead(42) == HIGH){ // Caso o botão do pino 42 esteja pressionado, o led acenderá.
    digitalWrite(3, HIGH);
  } else { // Caso o botão do pino 42 não esteja pressionado, o led permanecerá apagado.
    digitalWrite(3, LOW);
  }
  if (digitalRead(41) == HIGH){ // Caso o botão do pino 42 esteja pressionado, o led acenderá.
    digitalWrite(3, HIGH);
  } else { // Caso o botão do pino 42 não esteja pressionado, o led permanecerá apagado.
    digitalWrite(3, LOW);
  }
}