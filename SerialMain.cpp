
#include "CppSerial.h"
#include <iostream>

int main() {
	CppSerial cppserial;
	unsigned char buff[4096]{0};
	cppserial.Open(4, 9600);

	for (auto iter = 0; iter < 200; ++iter) {
		if(cppserial.ReadData(buff, 4095)) {
		};
		
		
	}

	cppserial.Close();

	return 0;
}