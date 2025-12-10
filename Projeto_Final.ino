#include "Matrix8x8.h"

// Pinos da matriz
#define DATA_PIN 12
#define CLOCK_PIN 13
#define LATCH_PIN 11

// Botões do Joystick
#define BOT_A 2
#define BOT_B 3
#define BOT_C 4
#define BOT_D 5
#define BOT_E 6
#define BOT_F 7
#define BOT_K 8

struct Debounce {
  int lastState = HIGH;
  int stableState = HIGH;
  unsigned long lastChange = 0;
};

Debounce dbA, dbB, dbC, dbD, dbE, dbF, dbK;

bool debounceRead(int pin, Debounce &db) {
  int reading = digitalRead(pin);

  if(reading != db.lastState){
    db.lastChange = millis();
    db.lastState = reading;
  }

  if((millis() - db.lastChange) > 50){ 
    if(reading != db.stableState){
      db.stableState = reading;
      return true;     // mudança REAL detectada
    }
  }

  return false;
}

// ===== MATRIZ =====
Matrix8x8 matriz(DATA_PIN, CLOCK_PIN, LATCH_PIN);

// LEDs fixos
byte desenho[8];

// Cursor
int x = 0, y = 0;
int modo = 0;

// Cursor piscante
unsigned long ultimoBlink = 0;
bool mostrarCursor = true;

void setup() {
  matriz.begin();

  for (int i = 2; i <= 8; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  // matriz apagada
  for(int i = 0; i < 8; i++){
    desenho[i] = 0x00;
  }
}

void loop() {
  // ===== MOVIMENTO DO CURSOR =====
  if(debounceRead(BOT_A, dbA) && dbA.stableState == LOW){
    x = (x > 0) ? x - 1 : x;   // cima
  }

  if(debounceRead(BOT_B, dbB) && dbB.stableState == LOW){
    y = (y > 0) ? y - 1 : y;   // direita
  }

  if(debounceRead(BOT_C, dbC) && dbC.stableState == LOW){
    x = (x < 7) ? x + 1 : x;   // baixo
  }

  if(debounceRead(BOT_D, dbD) && dbD.stableState == LOW){
    y = (y < 7) ? y + 1 : y;   // esquerda
  }

  // ===== TROCA DE MODO =====
  if(debounceRead(BOT_E, dbE) && dbE.stableState == LOW){
    modo = !modo;  // alterna entre 0 e 1
  }

  // ===== APAGA DESENHO =====
  if(debounceRead(BOT_F, dbF) && dbF.stableState == LOW){
    for (int i = 0; i < 8; i++) {
      desenho[i] = 0x00;  // apaga tudo
    }
  }

  // ===== DESENHAR LED =====
  if(debounceRead(BOT_K, dbK) && dbK.stableState == LOW){
    desenho[x] ^= (1 << y);   // acende LED permanente
  }

  // ===== CURSOR PISCANTE =====
  if(millis() - ultimoBlink > 300){
    ultimoBlink = millis();
    mostrarCursor = !mostrarCursor;
  }

  // Buffer temporário para exibição
  byte buffer[8];
  for(int i = 0; i < 8; i++){
    buffer[i] = desenho[i];
  }

  // Desenhar cursor piscando
  if(mostrarCursor){
    buffer[x] |= (1 << y);
  }

  // Troca de modo
  if(modo == 1){
    for(int i = 0; i < 8; i++){
      buffer[i] = ~buffer[i];
    }
  } 

  matriz.draw(buffer, 20);
}