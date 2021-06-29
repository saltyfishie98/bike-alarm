#ifndef LORA_COMM
#define LORA_COMM

#include <Arduino.h>
#include <LoRa.h>

enum class LORACOMM { TX, RX };

class LoRaComm {
  public:
	LoRaComm(LoRaClass* ObjAddr) : LoRaObj(ObjAddr) {}
	void begin(LORACOMM selection,
			   bool overidePin = false,
			   uint8_t overideNSS = 2,
			   uint8_t overideRST = 1,
			   uint8_t overideDIO0 = 0);

	void transmitChar(const char& message);
	void passCharRespondTo(char* respond);

  private:
	LoRaClass* LoRaObj;
};

#endif