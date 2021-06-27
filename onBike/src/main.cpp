#include <Arduino.h>
#include <MPU6050.h>
#include <LoRa.h>

#include "BikeAlarm.h"

MPU6050 onBikeMPU;
BikeAlarm onBike(&onBikeMPU);

#define nss	  2
#define RESET 1
#define dio0  0
#define pin	  6

int val = 1010;

void onMotion() {
	Serial.println("On");
	digitalWrite(pin, HIGH);
	LoRa.beginPacket();
	LoRa.print('1');
	LoRa.endPacket();
	LoRa.beginPacket();
	LoRa.print('0');
	LoRa.endPacket();
}

void onStationary() {
	Serial.println("Off");
	digitalWrite(pin, LOW);
}

void setup() {
	Serial.begin(9600);
	LoRa.setPins(nss, RESET, dio0);

	if (!LoRa.begin(433E6)) {
		Serial.println("Failed");
		delay(500);
		abort();
	}
	LoRa.setSpreadingFactor(12);

	LoRa.setTxPower(10);

	onBike.begin_MPU6050();
	onBike.begin_MPU6050MotionSensor();

	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	Serial.println("Success");

	for (int i = 0; i < 5; i++) {
		LoRa.beginPacket();
		LoRa.print("0");
		LoRa.endPacket();
	}
}

void loop() { onBike.run(onMotion, onStationary); }
