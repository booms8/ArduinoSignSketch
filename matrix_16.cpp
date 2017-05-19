#include "message_16.c"
#include "Arduino.h"

void setup();
void loop();
void loopQuads(byte pattern[4][8]);
void showQuad(byte charPattern[]);
void plexUp();
void doReset();
void doClock();

//clock pin
int clock = 8;
//resent pin
int reset = 9;

int plex0 = 10;
int plex1 = 11;

int countPins = 10;
int charDelay = 100;
int pulse = 5;

int cycle = 100;

void setup() {
  DDRD = B11111111;
  pinMode(clock, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(plex0, OUTPUT);
  pinMode(plex1, OUTPUT);
  doReset();
}

void loop() {
  for (int k = 0; k < sizeof(pattern) / 32; k++) {
    loopQuads(pattern[k]);
  }
}

void loopQuads(byte pattern[4][8]) {
  for (int m = 0; m < charDelay; m++) {
    for (int n = 0; n < 4; n++) {
      showQuad(pattern[n]);
      plexUp();
    }
    doReset();
  }
}

void showQuad(byte charPattern[]) {
  for (int i = 0; i < countPins; i++) {
    if (i >= 8) {
      doClock();
    }
    else {
      PORTD = charPattern[i];
      delayMicroseconds(cycle);
      PORTD = B00000000;
      doClock();
    }
  }
}

void plexUp() {
  if (digitalRead(plex1) == LOW && digitalRead(plex0) == LOW) {
    digitalWrite(plex0, HIGH);
  }
  else if (digitalRead(plex1) == LOW && digitalRead(plex0) == HIGH) {
    digitalWrite(plex0, LOW);
    digitalWrite(plex1, HIGH);
  }
  else if (digitalRead(plex1) == HIGH && digitalRead(plex0) == LOW) {
    digitalWrite(plex0, HIGH);
  }
  else {
    digitalWrite(plex0, LOW);
    digitalWrite(plex1, LOW);
  }
}

void doReset() {
  digitalWrite(reset, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(reset, LOW);
}

void doClock() {
  digitalWrite(clock, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(clock, LOW);
}
