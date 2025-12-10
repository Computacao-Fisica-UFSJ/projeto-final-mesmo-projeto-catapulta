#include <Matrix8x8.h>

// Pinos do registrador (ajuste conforme seu hardware)
#define DATA_PIN 12
#define CLOCK_PIN 13
#define LATCH_PIN 11

Matrix8x8 matriz(DATA_PIN, CLOCK_PIN, LATCH_PIN);

byte smile[8] = {
  B00000001,
  B00000010,
  B00000111,
  B00000101,
  B10001001,
  B11110010,
  B01000100,
  B00111000
};

void setup() {
  matriz.begin();
}

void loop() {
  matriz.draw(smile, 1000);
}