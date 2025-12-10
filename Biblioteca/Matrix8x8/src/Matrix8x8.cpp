#include "Matrix8x8.h"

Matrix8x8::Matrix8x8(int dataPin, int clockPin, int latchPin) {
  this->dataPin = dataPin;
  this->clockPin = clockPin;
  this->latchPin = latchPin;
}

void Matrix8x8::begin() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void Matrix8x8::enviar(byte colunas, byte linhas) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, linhas);
  shiftOut(dataPin, clockPin, MSBFIRST, colunas);
  digitalWrite(latchPin, HIGH);
}

void Matrix8x8::draw(const byte desenho[8], int tempoMs) {
  unsigned long t0 = millis();

  while (millis() - t0 < (unsigned long)tempoMs) {
    for (int linha = 0; linha < 8; linha++) {

      byte linhas = (1 << linha);
      byte colunas = 0xFF;

      for (int c = 0; c < 8; c++) {
        if (desenho[c] & (1 << linha)) {
          colunas &= ~(1 << c);
        }
      }

      enviar(colunas, linhas);
      delayMicroseconds(1);
    }
  }
}