
#include "CppSerial.h"
#include <iostream>

constexpr int BLUE = 1;
constexpr int GREEN = 2;
constexpr int RED = 4;
constexpr int WHITE = 15;

void change_colour(int colour) {
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}

u32 find_time_pos(std::string str, const int msg_size) {
	
	int nmea_addr_pos{0};
	/* check if NMEA message address is contained within string
	 and check whether the corresponding time value is also within the string
	 if so, return starting position of time value
	 else return 0 */
	nmea_addr_pos = str.find("$GPGGA");
	if((nmea_addr_pos >= 0) && ((msg_size - nmea_addr_pos) >= 13 ) ) {
		return (nmea_addr_pos + 7);
	}
	return 0;
}

int main() {
	
	char buff[4096]{0};
	u32 bytes_to_read, time_code_pos;
	std::string buff_str, time_code_val;
	
	CppSerial cppserial;
	cppserial.Open(4, 9600);
	change_colour(GREEN);

	while(true) {
		
		bytes_to_read = cppserial.ReadDataWaiting();
		
		if(bytes_to_read >= 100) {
			// update bytes to read in case buffer has received additional data since initial check
			bytes_to_read = cppserial.ReadData(buff, 4095);
			buff_str.assign(buff, bytes_to_read);
			time_code_pos = find_time_pos(buff_str, bytes_to_read);
			
			if (time_code_pos) {
			  time_code_val = buff_str.substr(time_code_pos, 6);
				std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
				std::cout << time_code_val[0] << time_code_val[1] << ":" <<
					           time_code_val[2] << time_code_val[3] << ":" <<
										 time_code_val[4] << time_code_val[5] << " UTC+00";
			}
		}
	}
	change_colour(WHITE);
	cppserial.Close();

	return 0;
}