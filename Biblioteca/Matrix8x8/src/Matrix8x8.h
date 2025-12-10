#ifndef MATRIX8X8_H
#define MATRIX8X8_H

#include <Arduino.h>

class Matrix8x8 {
  private:
    int dataPin, clockPin, latchPin;

    void enviar(byte colunas, byte linhas);

  public:
    Matrix8x8(int dataPin, int clockPin, int latchPin);

    void begin();

    void draw(const byte desenho[8], int tempoMs = 1000);
};

#endif