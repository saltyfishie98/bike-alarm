#ifndef BIKEALARM
#define BIKEALARM

#include <Arduino.h>
#include <Wire.h>

#define MPU_ADDR				  (0x68)
#define MPU6050_REG_MOT_THRESHOLD (0x1F)
#define MPU6050_REG_MOT_DETECT	  (0x61)

class BikeAlarm {
  public:
	BikeAlarm() {}
	inline void begin() { Wire.begin(); }
	void run(void (*onMotion)(void), void (*onStationary)(void));

  private:
	const uint8_t trigger = 10;
	const uint8_t secondTrigger = 28;
	uint16_t count = 0;
	uint16_t secondCount = 0;
	uint16_t data = 0;
};

#endif