// Rotary Encoder Volume project
// (c) 2019 Stephane Koeberle
// Licensed under MIT
// See LICENSE in the repository

// You need to install the
// * Encoder
// * Debouncer
// * Keyboard

//#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
#include <Debouncer.h>
#include <Keyboard.h>
//#include "HID-Project.h"

#define ENC_PIN1 12
#define ENC_PIN2 13
#define SW_PIN 4
#define LED 2
#define DEBOUNCE_MS 22

char returnKey = KEY_RETURN;

Debouncer debouncer(SW_PIN, DEBOUNCE_MS);

Encoder myEnc(ENC_PIN1, ENC_PIN2);
boolean sw_state;

void setup() {
    Serial.begin(115200);
    Keyboard.begin();
    pinMode(SW_PIN, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
}

long position  = 0;

void loop() {
    debouncer.update();
    long newPos = myEnc.read() / 2;
    if (newPos != position) {
        String output = "left";
        String key = "-";
        if (newPos > position) {
            output = "right";
            key = "+";
        }
        position = newPos;
        //Serial.println(output);
        Keyboard.print(key);
        delay(50);
        Keyboard.releaseAll();
        ledBlink();
    }
    if (debouncer.edge()) {
        if (debouncer.falling()) {
            //Serial.println("click");
            Keyboard.press(returnKey);
            delay(50);
            Keyboard.releaseAll();
            ledBlink();
        }
    }
    Serial.flush();
}

void ledBlink() {
    digitalWrite(LED, LOW);
    delay(150);
    digitalWrite(LED, HIGH);
}