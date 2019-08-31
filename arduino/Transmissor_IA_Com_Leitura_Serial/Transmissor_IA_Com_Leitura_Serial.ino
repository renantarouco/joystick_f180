#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define CE 7 //define o pino 7 como CE
#define CSN 8 //define o pino 8 como CS

RF24 radio(CE, CSN); // Define quais serão os pinos do arduino usados para conectar o CE e o CS no rádio

uint8_t dados[9];
int tx_dados[9];
//dado = {id, vx, vy, v0, dx, dy, d0, kick, dribbler}

const uint64_t pipe[6] = {0xF1F1F1F1E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4LL, 0xF0F0F0F0E5LL, 0xF0F0F0F0E6LL};  // Endereços do radio

uint8_t c;
int cont;
int i;

void setup()
{
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(48);
  radio.openWritingPipe(pipe[1]); // Começa a enviar msg para os robos

}

void loop() {
  if(Serial.available()) {
    c = Serial.read();
    
    if (c >= 128) {
      cont = 1;
      dados[0] = c - 128;
    } else if (cont > 0) {
      dados[cont] = c;
      cont++;
    }
    
    if (cont >= sizeof(dados)) {
      cont = 0;

      Serial.print("ID do Robo: ");
      Serial.println(dados[0]);
      Serial.print("Velocidade em X: ");
      Serial.println(dados[1]);
      Serial.print("Velociade em Y: ");
      Serial.println(dados[2]);
      Serial.print("Velocidade em 0: ");
      Serial.println(dados[3]);
      Serial.print("Direcao em X: ");
      Serial.println(dados[4]);
      Serial.print("Direcao em Y: ");
      Serial.println(dados[5]);
      Serial.print("Direcao em 0: ");
      Serial.println(dados[6]);
      Serial.print("Dribbler: ");
      Serial.println(dados[7]);
      Serial.print("Kick: ");
      Serial.println(dados[8]);

      for (i = 0; i < 9; i++) tx_dados[i] = (int)dados[i];

      radio.write(&dados, sizeof(dados));
    }
  }
}
