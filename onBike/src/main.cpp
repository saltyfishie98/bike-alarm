/*
	MPU6050 Triple Axis Gyroscope & Accelerometer. Motion detection.
	Read more:
   http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
	GIT: https://github.com/jarzebski/Arduino-MPU6050
	Web: http://www.jarzebski.pl
	(c) 2014 by Korneliusz Jarzebski
*/
#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

#define MPU_ADDR (0x68)

// #define MPU6050_REG_MOT_THRESHOLD (0x1F)
// #define MPU6050_REG_MOT_DETECT	  (0x61)

MPU6050 mpu;

uint8_t data = false;
uint8_t trigger = 15;
uint8_t secondTrigger = 25;
uint8_t count = 0;
uint8_t secondCount = 0;

void setup() {
	Serial.begin(9600);

	while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G)) {
	}

	mpu.setAccelPowerOnDelay(MPU6050_DELAY_3MS);

	mpu.setIntFreeFallEnabled(false);
	mpu.setIntZeroMotionEnabled(false);
	mpu.setIntMotionEnabled(false);

	mpu.setDHPFMode(MPU6050_DHPF_5HZ);

	mpu.setMotionDetectionThreshold(2);
	mpu.setMotionDetectionDuration(5);

	mpu.setZeroMotionDetectionThreshold(4);
	mpu.setZeroMotionDetectionDuration(2);

	pinMode(4, OUTPUT);
	digitalWrite(4, LOW);
}

void loop() {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(MPU6050_REG_MOT_DETECT_STATUS);
	Wire.endTransmission();

	Wire.beginTransmission(MPU_ADDR);
	Wire.requestFrom(MPU_ADDR, 1);
	while (!Wire.available()) {
	}

	data += ~Wire.read() & 1;
	count++;
	if (count == trigger) {
		if (data == count) {
			secondCount++;
			Serial.print(secondCount);
			Serial.print("\t");
			if (secondCount >= secondTrigger) {
				digitalWrite(4, HIGH);
				secondCount = 0;
				Serial.println();
			}
		} else {
			digitalWrite(4, LOW);
			secondCount = 0;
		}

		data = 0;
		count = 0;
	}
}
