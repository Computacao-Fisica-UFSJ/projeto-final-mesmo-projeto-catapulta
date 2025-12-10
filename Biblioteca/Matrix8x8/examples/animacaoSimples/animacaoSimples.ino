#include <Matrix8x8.h>

#define DATA_PIN 12
#define CLOCK_PIN 13
#define LATCH_PIN 11

Matrix8x8 matriz(DATA_PIN, CLOCK_PIN, LATCH_PIN);

// Duas imagens para alternar
byte frame1[8] = {
  B00011000,
  B00100100,
  B01000010,
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00000000
};

byte frame2[8] = {
  B00000000,
  B00011000,
  B00100100,
  B01000010,
  B00100100,
  B00011000,
  B00000000,
  B00000000
};

void setup() {
  matriz.begin();
}

void loop() {
  matriz.draw(frame1, 200);
  matriz.draw(frame2, 200);
}