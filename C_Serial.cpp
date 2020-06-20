
#include "Serial.h"

int main() {
	CSerial cserial;
	unsigned char buff[4096]{};
	cserial.Open(1,9600);

	for(auto iter = 0; iter < 10; ++iter) {
		cserial.ReadData(buff, 4095);
		Sleep(500);
	}


	cserial.Close();

	return 0;
}