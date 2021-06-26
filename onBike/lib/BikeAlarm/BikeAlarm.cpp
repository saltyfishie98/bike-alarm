#include "BikeAlarm.h"

void BikeAlarm::run(void (*onMotion)(void), void (*onStationary)(void)) {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(MPU6050_REG_MOT_DETECT);
	Wire.endTransmission();

	Wire.beginTransmission(MPU_ADDR);
	Wire.requestFrom(MPU_ADDR, 1);
	while (!Wire.available()) {
	};

	data += Wire.read();
	Serial.println(data);
	count++;
	Wire.endTransmission();

	if (count == trigger) {
		if (data == count) {
			secondCount++;
			// Serial.println(secondCount);
			if (secondCount >= secondTrigger) {
				//Serial.println("triger");
				digitalWrite(4, HIGH);
				secondCount = 0;
			}
		} else {
			//Serial.println("not triger");
			digitalWrite(4, LOW);
			secondCount = 0;
		}
		data = 0;
		count = 0;
	}
}