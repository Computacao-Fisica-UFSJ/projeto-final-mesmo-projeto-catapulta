#include <Matrix8x8.h>

// Pinos do registrador (ajuste conforme seu hardware)
#define DATA_PIN 12
#define CLOCK_PIN 13
#define LATCH_PIN 11

Matrix8x8 matriz(DATA_PIN, CLOCK_PIN, LATCH_PIN);

byte smile[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

void setup() {
  matriz.begin();
}

void loop() {
  matriz.draw(smile, 1000);
}