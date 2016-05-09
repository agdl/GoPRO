/*
Copyright (C) 2016 Arturo Guadalupi. All right reserved.

This example is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This example is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

created 09 May 2016
by Arturo Guadalupi
*/

#include <GoPRO.h>

#define CONNECT_PRESSED 1
#define ON_PRESSED  2
#define CAPTURE_PRESSED 3

char ssid[] = "yourNetwork";      //  your network SSID (name)
char pass[] = "yourPassword";     // your network password

const int buttonConnect = A1;
const int buttonOn = A2;
const int buttonCapture = A3;

const int connectLED = 3;
const int onLED = 4;
const int captureLED = 5;

bool onStatus = true;
bool captureStatus = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonConnect, INPUT_PULLUP);
  pinMode(buttonOn, INPUT_PULLUP);
  pinMode(buttonCapture, INPUT_PULLUP);

  pinMode(connectLED, OUTPUT);
  pinMode(onLED, OUTPUT);
  pinMode(captureLED, OUTPUT);

  digitalWrite(connectLED, LOW);
  digitalWrite(onLED, HIGH);
  digitalWrite(captureLED, LOW);
}

void loop() {
  switch (isButtonPressed()) {
    default: break;

    case CONNECT_PRESSED:
      if (!GoPRO.checkConnection()) {
        if (GoPRO.begin(ssid, pass)) {
          digitalWrite(connectLED, HIGH);
        }
        else {
          digitalWrite(connectLED, LOW);
        }
      }
      else {
        digitalWrite(connectLED, HIGH);
      }
      break;

    case ON_PRESSED:
      if (GoPRO.checkConnection()) {
        onStatus = !onStatus;
        if (onStatus) {
          if (GoPRO.turnOn())
            digitalWrite(onLED, HIGH);
        }
        else {
          if (GoPRO.turnOff())
            digitalWrite(onLED, LOW);
        }
      }
      break;

    case CAPTURE_PRESSED:
      if (GoPRO.checkConnection()) {
        captureStatus = !captureStatus;
        if (captureStatus) {
          if (GoPRO.startCapture())
            digitalWrite(captureLED, HIGH);
        }
        else {
          if (GoPRO.stopCapture())
            digitalWrite(captureLED, LOW);
        }
      }
      break;
  }

  delay(100);
}

int isButtonPressed() {
  if (digitalRead(buttonConnect) == LOW) return 1;

  else if (digitalRead(buttonOn) == LOW) return 2;

  else if (digitalRead(buttonCapture) == LOW) return 3;

  else return 0;
}

