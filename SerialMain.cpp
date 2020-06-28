
#include "CppSerial.h"

int main() {
	CppSerial cppserial;
	unsigned char buff[4096]{};
	cppserial.Open(1,9600);

	for(auto iter = 0; iter < 10; ++iter) {
		cppserial.ReadData(buff, 4095);
		Sleep(500);
	}
	
	cppserial.Close();

	return 0;
}