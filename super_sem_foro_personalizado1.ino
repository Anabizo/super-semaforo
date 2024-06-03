#include <Wire.h>
#include <EEPROM.h>

#define led_Vermelho 10
#define led_Amarelo 9
#define led_Verde 8
#define sensorLuz A0
#define led_Vermelho2 13
#define led_Amarelo2 12
#define led_Verde2 11
#define led_Vermelho_Pedestre1 6
#define led_Vermelho_Pedestre2 7
#define buzzer 3
#define buzzer2 A4
#define botao_Sinal1 5
#define botao_Sinal2 4
#define MAX_STRING_LENGTH 8
#define EEPROM_START_ADDRESS 0

int trigger1 = 2;
int echo1 = A1;
int trigger2 = A2;
int echo2 = A3;
int multou = 0;
int distancia = 0;
int tempo = 0;
int k = 0;
int limiarEscuro = 140;

int multa(int trigger, int echo){

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(trigger,LOW); 
  delayMicroseconds(2);
  
  digitalWrite(trigger, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigger,LOW);
  
  tempo = pulseIn(echo, HIGH); 
  distancia = tempo/58.2;
  
  if(distancia<30){
    return 1;  
  } else {
    return 0;
  }
}

String hora_multa(int luminosidade){
  
  int hora = random(0,12);
  int minuto = random (0, 60);  
  String relogio = "";
  
  if(hora > 9){
  	relogio += String(hora);
  }else{
    relogio += String(0);
    relogio += String(hora);
  }
  
  relogio += ":";
  
  if(minuto > 9){
  	relogio += String(minuto);
  }else{
    relogio += String(0);
    relogio += String(minuto);
  }

  if(luminosidade < limiarEscuro){
    relogio += " AM";
  } else {
    relogio += " PM";
  }
  return relogio;
}

void ligarLed(int led1, int led2) {
  // Desliga todos os LEDs
  digitalWrite(led_Vermelho, LOW);
  digitalWrite(led_Amarelo, LOW);
  digitalWrite(led_Verde, LOW);
  digitalWrite(led_Vermelho2, LOW);
  digitalWrite(led_Amarelo2, LOW);
  digitalWrite(led_Verde2, LOW);

  // Liga os LEDs especificados
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}

// Função para ler a luminosidade do ambiente
int lerLuminosidade() {
  return analogRead(sensorLuz);
}

void escreverString(int endereco, String dados) {
  // Grava a string na EEPROM
  for (unsigned int i = 0; i < dados.length(); i++) {
    EEPROM.write(endereco + i, dados[i]);   
  }
  EEPROM.write(endereco + dados.length(), '\0'); // Terminador nulo
}

String lerString(int endereco) {
  
  String dados = "";
  char caractere;
  int posicao = endereco;
  
  while ((caractere = EEPROM.read(posicao)) != '\0') {
    dados += caractere;
    posicao++;
  }
  return dados;
}

void botao_1(){
    if(digitalRead(led_Vermelho) == LOW){ // Enquanto o semáforo dos carros não estiver vermelho
      Serial.println("Botao1 Apertado");
      tone(buzzer, 1000, 200);
    }else{ // Verifica se o semáforo dos carros ficou vermelho
      tone(buzzer, 1000);
      return;
    }
}

void botao_2(){
    if(digitalRead(led_Vermelho2) == LOW){ // Enquanto o semáforo dos carros não estiver vermelho
        Serial.println("Botao2 Apertado");
        tone(buzzer2, 200,200); // Emite um bip curto
    }else{ // Verifica se o semáforo dos carros ficou vermelho
       	tone(buzzer2, 200);
        return;
    }
}


void setup() {
  Serial.begin(9600);
  pinMode(led_Vermelho, OUTPUT);
  pinMode(led_Amarelo, OUTPUT);
  pinMode(led_Verde, OUTPUT);
  pinMode(led_Vermelho2, OUTPUT);
  pinMode(led_Amarelo2, OUTPUT);
  pinMode(led_Verde2, OUTPUT);
  pinMode(led_Vermelho_Pedestre1, OUTPUT);
  pinMode(led_Vermelho_Pedestre2, OUTPUT);
  pinMode(sensorLuz, INPUT); 
  randomSeed(analogRead(0));
  pinMode(buzzer, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(botao_Sinal1, INPUT);
  pinMode(botao_Sinal2, INPUT);
}


void loop() {
  
  String relogio = "";
  int luminosidade = lerLuminosidade();
  
  // Se estiver mais escuro, aumenta o tempo do sinal vermelho do primeiro semáforo
  if (luminosidade > limiarEscuro) {
    Serial.print("Luminosidade: Escuro\n\n");

    ligarLed(led_Vermelho, led_Verde2);
    digitalWrite(led_Vermelho_Pedestre2, HIGH);
    
    for(int i=1; i<=16; i++){
      
      //Funcionamento do Buzzer
        if (digitalRead(botao_Sinal1)==HIGH){
          botao_1();
        }  

        if (digitalRead(botao_Sinal2)==HIGH){
          botao_2();
        }
      
      
      if(multa(trigger1, echo1) && multou == 0){
    	Serial.print("Veiculo Multado pelo Radar 1\n");
        Serial.print("Hora da multa: ");
        relogio = hora_multa(luminosidade);
        Serial.println(relogio);
        Serial.print("Valor da Multa: R$ 237,98\n\n");
        multou = 1;
        escreverString(EEPROM_START_ADDRESS + k * (MAX_STRING_LENGTH + 1), relogio);
        k++;
        relogio = "";
  	  }
      delay(500);
    }
    
    noTone(buzzer);
    noTone(buzzer2);
    multou = 0;
 
  } else { // Se não, ambos permanecem com o mesmo tempo
    Serial.print("Luminosidade: Claro\n\n");

    ligarLed(led_Vermelho, led_Verde2);
    digitalWrite(led_Vermelho_Pedestre2, HIGH);
    
    for(int i=1; i<=10; i++){
      
      //Funcionamento do Buzzer
      if (digitalRead(botao_Sinal1)==HIGH){
        botao_1();
      }

      if (digitalRead(botao_Sinal2)==HIGH){
        botao_2();
      }
      
      if(multa(trigger1, echo1) && multou == 0){
    	Serial.print("Veículo Multado pelo Radar 1\n");
        Serial.print("Hora da multa:");
        relogio = hora_multa(luminosidade);
        Serial.println(relogio);
        Serial.print("\nValor da Multa: R$ 237,98\n\n");
        multou = 1;
        escreverString(EEPROM_START_ADDRESS + k * (MAX_STRING_LENGTH + 1), relogio);
        k++;
        relogio = "";
  	  }      
      delay(500);      
    }
    
    noTone(buzzer);
    noTone(buzzer2);
    multou = 0;
    
  }
  
  ligarLed(led_Vermelho, led_Amarelo2);
  
  for(int i=1; i<=4; i++){
    
    //Funcionamento do Buzzer
    if (digitalRead(botao_Sinal1)==HIGH){
      botao_1();
    }

    if (digitalRead(botao_Sinal2)==HIGH){
      botao_2();
    }
    
    if(multa(trigger1, echo1) && multou == 0){      
      Serial.print("Veiculo Multado pelo Radar 1\n");
      Serial.print("Hora da multa: ");
      relogio = hora_multa(luminosidade);
      Serial.println(relogio);
      Serial.print("Valor da Multa: R$ 237,98\n\n");
      multou = 1;
      escreverString(EEPROM_START_ADDRESS + k * (MAX_STRING_LENGTH + 1), relogio);
      k++;
      relogio = "";      
    }    
    delay(500);    
  }
  
  noTone(buzzer);
  noTone(buzzer2);
  multou = 0;
  
  ligarLed(led_Vermelho2, led_Verde);
  digitalWrite(led_Vermelho_Pedestre2, LOW);
  digitalWrite(led_Vermelho_Pedestre1, HIGH);
  
  for(int i=1; i<=10; i++){
    
    //Funcionamento do Buzzer
    if (digitalRead(botao_Sinal1)==HIGH){
      botao_1();
    }

    if (digitalRead(botao_Sinal2)==HIGH){
      botao_2();
    }
    
    if(multa(trigger2, echo2) && multou == 0){      
      Serial.print("Veiculo Multado pelo Radar 2\n");
      Serial.print("Hora da multa: ");
      relogio = hora_multa(luminosidade);
      Serial.println(relogio);
      Serial.print("Valor da Multa: R$ 237,98\n\n");
      multou = 1;
      escreverString(EEPROM_START_ADDRESS + k * (MAX_STRING_LENGTH + 1), relogio);
      k++;
      relogio = "";      
    }    
    delay(500);    
  }
  
  noTone(buzzer);
  noTone(buzzer2);
  multou = 0;

  ligarLed(led_Vermelho2, led_Amarelo);
  
  for(int i=1; i<=4; i++){
    
    //Funcionamento do Buzzer
    if (digitalRead(botao_Sinal1)==HIGH){
      botao_1();
    }

    if (digitalRead(botao_Sinal2)==HIGH){
      botao_2();
    }
    
    if(multa(trigger2, echo2) && multou == 0){      
      Serial.print("Veiculo Multado pelo Radar 2\n");
      Serial.print("Hora da multa: ");
      relogio = hora_multa(luminosidade);
      Serial.println(relogio);
      Serial.print("Valor da Multa: R$ 237,98\n\n");
      multou = 1;
      escreverString(EEPROM_START_ADDRESS + k * (MAX_STRING_LENGTH + 1), relogio);
      k++;
      relogio = "";      
    }    
    delay(500);    
  }
  
  noTone(buzzer);
  noTone(buzzer2);
  multou = 0;
  
  digitalWrite(led_Vermelho_Pedestre1, LOW);
  
  int address = 0; // Endereço inicial da EEPROM
  char data[MAX_STRING_LENGTH + 1];
  
  Serial.print("Horarios de multa:\n\n");
  
  while (address < EEPROM.length()) {
    
    // Verifica se o comando 'q' foi recebido para interromper a leitura da EEPROM
    if (Serial.available() > 0) {
      char comando = Serial.read();
      if (comando == 'q'){
      	break;
      }
    }
    
    // Limpa o buffer de dados antes de ler uma nova string
    memset(data, 0, sizeof(data));

    // Lê uma string da EEPROM
    for (int i = 0; i < MAX_STRING_LENGTH; i++) {
      
      char character = EEPROM.read(address++);
      
      // Verifica se encontrou o terminador nulo indicando o final da string
      if (character == '\0') {
        break;
      }      
      data[i] = character;      
    }

    // Adiciona manualmente o terminador nulo ao final da string
    data[MAX_STRING_LENGTH] = '\0';

    // Imprime a string lida, se não estiver vazia
    if (strlen(data) > 0) {
      Serial.println(data);
    }   
  }  
  Serial.print("\n");  
}