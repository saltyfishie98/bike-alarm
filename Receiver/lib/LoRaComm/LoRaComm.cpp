#include "LoRaComm.h"

void LoRaComm::begin(Mode selection,
					 bool overidePin,
					 uint8_t overideNSS,
					 uint8_t overideRST,
					 uint8_t overideDIO0) {

	if (overidePin) { LoRaObj->setPins(overideNSS, overideRST, overideDIO0); }
	if (!LoRaObj->begin(433E6)) {
		Serial.println("Failed");
		delay(500);
		abort();
	}
	LoRaObj->setSpreadingFactor(12);

	switch (selection) {
		case LORA_TX:
			LoRaObj->setTxPower(10);
			break;

		case LORA_RX:
			break;
	}
}

void LoRaComm::transmitChar(const char& message) {
	LoRaObj->beginPacket();
	LoRaObj->print(message);
	LoRaObj->endPacket();
}

void LoRaComm::passCharRespondTo(char& respond) {
	LoRaObj->parsePacket();
	while (LoRaObj->available()) {
		respond = (char)LoRaObj->read();
	}
}