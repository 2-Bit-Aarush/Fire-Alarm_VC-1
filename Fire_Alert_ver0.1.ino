#include <Arduino.h>
#include "PCM.h"                  
#include "sounddata.h"

#define FIRE_PIN A3             // pin number change karliyo if you wangt 
#define FIRE_THRESHOLD 410      // 1.07 v hai atleast 
#define STOP_DELAY 3000         // 3 sec - agar change karna ho to yahan time change kardiyo in milliseconds 

unsigned long fireGoneTime = 0;
bool fireActive = false;

void setup() {
}

void loop() {

  int adcValue = analogRead(FIRE_PIN);

  // fire detected wala case
  if (adcValue > FIRE_THRESHOLD) {

    fireActive = true;
    fireGoneTime = 0;   // ye new line add kari hai i think yahan problem thi
    if (!isPCMPlaying()) {
      startPlayback(sounddata_data, sounddata_length);
    }
  }

  // volatge normal hone ke baad wala case (fire not detected)
  else {

    if (fireActive) {
      fireActive = false;
      fireGoneTime = millis();   // yahan timer start ho raha hai
    }

    if (isPCMPlaying() && fireGoneTime != 0) {
      if (millis() - fireGoneTime >= STOP_DELAY) {
        stopPlayback();
        fireGoneTime = 0;
      }
    }
  }
}
