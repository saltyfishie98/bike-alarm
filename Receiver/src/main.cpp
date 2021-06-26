#include <Arduino.h>
#include <LoRa.h>

void setup() {
	Serial.begin(9600);
	LoRa.setPins(1,2,3);

	while (!Serial) {
	};
	Serial.println("LoRa Sender");
	if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
		Serial.println("Starting LoRa failed!");
		while (1) {
		};
	}
	Serial.println("Setup success!!!");
}

void loop() {}