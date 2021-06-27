#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

int rssi;
int pin = 4;
char incoming;

void setup() {
	pinMode(pin, OUTPUT);
	Serial.begin(9600);

	if (!LoRa.begin(433E6)) {
		Serial.println("Failed");
		delay(500);
		abort();
	}
	LoRa.setSpreadingFactor(12);
}

void loop() {
	LoRa.parsePacket();
	while (LoRa.available()) {
		incoming = (char)LoRa.read();
	}

	Serial.print("Received packet: ");
	Serial.print(incoming);

	if (incoming == '1') {
		digitalWrite(pin, HIGH);
		Serial.println(" Turn On");
	} else {
		digitalWrite(pin, LOW);
		Serial.println();
	}
}