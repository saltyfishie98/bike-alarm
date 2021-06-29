#include <LoRa.h>
#include "LoRaComm.h"

void blinkCheck();
void postProcess(char& toProcess);

// == Main loop ========================================
// =====================================================
LoRaComm receiver(&LoRa);

#define NSS	  5
#define RESET 22
#define DIO0  21
#define PIN	  16
int rssi;
char respond = '0';

void setup() {
	Serial.begin(115200);

	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, HIGH);
	delay(500);
	digitalWrite(PIN, LOW);
	delay(500);

	receiver.begin(LORACOMM::TX, true, NSS, RESET, DIO0);

	blinkCheck();
}

void loop() {
	receiver.passCharRespondTo(&respond);
	postProcess(respond);
}

// == Functions ========================================
// =====================================================
void blinkCheck() {
	for (int i = 0; i < 3; i++) {
		digitalWrite(PIN, HIGH);
		delay(100);
		digitalWrite(PIN, LOW);
		delay(100);
	}
}

void postProcess(char& toProcess) {
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