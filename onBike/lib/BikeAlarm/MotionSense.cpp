#include "MotionSense.h"

void MotionSense::begin_MPU6050() {
	// ==== From MPU6050.h =========================
	while (!objPtr->begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G)) {
		Serial.println("aaa");
	}
}

void MotionSense::begin_MPU6050MotionSensor() {
	// ==== From MPU6050.h =========================
	objPtr->setAccelPowerOnDelay(MPU6050_DELAY_3MS);

	objPtr->setIntFreeFallEnabled(false);
	objPtr->setIntMotionEnabled(false);
	objPtr->setIntZeroMotionEnabled(false);

	objPtr->setDHPFMode(MPU6050_DHPF_5HZ);

	objPtr->setMotionDetectionThreshold(2);
	objPtr->setMotionDetectionDuration(2);

	objPtr->setZeroMotionDetectionThreshold(10);
	objPtr->setZeroMotionDetectionDuration(2);
	//============================================
}

void MotionSense::runOnMotion(void (*onMotion)(void), void (*onStationary)(void)) {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(MPU6050_REG_MOT_DETECT_STATUS);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU_ADDR, 1);
	while (!Wire.available()) {}

#ifdef test
	data = ~Wire.read() & 1;
	if (data == 1)
		onMotion();
	else
		onStationary();
#else
	data += ~Wire.read() & 1;
	confirmation++;

	if (confirmation == regularCheck) {
		if (data == confirmation)
			onMotion();
		else
			onStationary();

		data = 0;
		confirmation = 0;
	}

#endif
}