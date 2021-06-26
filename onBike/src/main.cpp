#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <BikeAlarm.h>

#define MPU_ADDR (0x68)

MPU6050 onBikeMPU;
BikeAlarm onBike(&onBikeMPU);

void onMotion() { digitalWrite(4, HIGH); }

void onStationary() { digitalWrite(4, LOW); }

void setup() {
	onBike.begin_MPU6050();
	onBike.begin_MPU6050MotionSensor();

	pinMode(4, OUTPUT);
	digitalWrite(4, LOW);
	delay(300);
}

void loop() { onBike.run(onMotion, onStationary); }
