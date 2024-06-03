#Semáforo inteligente
##Projeto de embarcados com simulação presente: https://www.tinkercad.com/things/5pCKpzBtUn9-super-semaforo-personalizado/editel

###O que usamos:
- C++
- IDE Arduino
- Simulador Tinkercad
- Componentes físicos para montagem

###O que consiste o projeto:
O projeto realizado é um conjunto de Semáforos sincronizados, com configurações de funcionamentos personalizados, os quais simulam um cruzamento que possui dois semáforos principais, tendo cada semáforo principal um semáforo de pedestre.
Foram três personalizações realizadas:
- Fotorresistor como sensor de luminosidade
- Botão e Buzzer como sinalização para pessoas com deficiência visual
- Sensor ultrassônico para captação de multas

O fotorresistor é utilizado para analisar a claridade (dia ou noite), mudando o tempo de funcionamento dos semáforos quando anoitece.
Os botões foram colocados um em cada semáforo de pedestre, funcionam como uma sinalização, emitindo sons pelo buzzer, os quais indicam se a pessoa deve esperar ou seguir.
O sensor ultrassônico capta movimentos nos semáforos, e caso haja algum movimento enquanto o sinal vermelho, aplicam uma mensagem de multa, indicando em qual semáforo foi detectado o movimento. Também há um sensor para cada semáforo principal

###imagem dos componentes montados na protoboard pelo simulador tinkercad:
![foto-semaforo-simulador](https://github.com/Anabizo/super-semaforo/assets/107151980/caf0120e-1052-4258-9cdc-045ea9496d46)

###imagem dos componentes montados na protoboard física:
![foto-semaforo-fisico](https://github.com/Anabizo/super-semaforo/assets/107151980/4db2c53e-fe95-42c4-9ae3-f0724ba0de59)



