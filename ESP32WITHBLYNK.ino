#include <Wire.h>
#include "MAX30102_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected() {
    Serial.println("Beat!");
}

void setup() {
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter...");

    if (!pox.begin()) {
        Serial.println("FAILED");
        for (;;);
    } else {
        Serial.println("SUCCESS");
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
    pox.update();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate: ");
        Serial.print(pox.getHeartRate());
        Serial.print(" bpm / SpO₂: ");
        Serial.print(pox.getSpO2());
        Serial.println(" %");
        tsLastReport = millis();
    }
}
