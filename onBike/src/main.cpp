#include <Arduino.h>
#include <MPU6050.h>
#include <LoRa.h>
#include "MotionSense.h"
#include "LoRaComm.h"

void blinkCheck();
void onMotion();
void onStationary();

// == Main loop ========================================
// =====================================================
MPU6050 onBikeMPU;
MotionSense onBike(&onBikeMPU);
LoRaComm transmitter(&LoRa);

#define NSS	  2
#define RESET 1
#define DIO0  0
#define PIN	  6

void setup() {
	Serial.begin(9600);

	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);

	transmitter.begin(LORACOMM::TX, true, NSS, RESET, DIO0);
	onBike.begin_MPU6050();
	onBike.begin_MPU6050MotionSensor();

	blinkCheck();
}

void loop() { onBike.runOnMotion(onMotion, onStationary); }

// == Functions ========================================
// =====================================================
void blinkCheck() {
	for (int i = 0; i < 3; i++) {
		digitalWrite(PIN, HIGH);
		delay(100);
		digitalWrite(PIN, LOW);
		delay(100);
	}
}

void onMotion() {
	Serial.println("On");
	digitalWrite(PIN, HIGH);
	transmitter.transmitChar('1');
	transmitter.transmitChar('0');
}

void onStationary() {
	Serial.println("Off");
	digitalWrite(PIN, LOW);
}