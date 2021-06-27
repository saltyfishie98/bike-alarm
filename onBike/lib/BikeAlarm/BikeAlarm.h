#ifndef BIKEALARM
#define BIKEALARM

#define test

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

#define MPU_ADDR (0x68)

class BikeAlarm {
  public:
	BikeAlarm(MPU6050* objectPtr) : objPtr(objectPtr) {}
	void begin_MPU6050();
	void begin_MPU6050MotionSensor();
	void run(void (*onMotion)(void), void (*onStationary)(void));

  private:
	const uint8_t regularCheck = 10;
	uint16_t data = 0;
	uint8_t confirmation = 0;

	MPU6050* objPtr;
};

#endif