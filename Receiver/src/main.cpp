#include <LoRa.h>
#include "LoRaComm.h"

void blinkCheck();
void postProcess(char toProcess);

// == Main loop ========================================
// =====================================================
LoRaComm receiver(&LoRa);

#define PIN 4
int rssi;
char respond = '0';

void setup() {
	Serial.begin(9600);

	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);

	receiver.begin(LORA_RX);

	blinkCheck();
}

void loop() {
	receiver.passCharRespondTo(respond);
	postProcess(respond);
}

// == Functions ========================================
// =====================================================
void blinkCheck() {
	digitalWrite(PIN, HIGH);
	delay(500);
	digitalWrite(PIN, LOW);
	delay(500);
	digitalWrite(PIN, HIGH);
	delay(500);
	digitalWrite(PIN, LOW);
	delay(500);
	digitalWrite(PIN, HIGH);
	delay(500);
	digitalWrite(PIN, LOW);
	delay(500);
}

void postProcess(char toProcess) {
	Serial.print("Received packet: ");
	Serial.print(toProcess);

	if (toProcess == '1') {
		digitalWrite(PIN, HIGH);
		Serial.println(" Turn On");
	} else {
		digitalWrite(PIN, LOW);
		Serial.println();
		toProcess = '0';
	}
}