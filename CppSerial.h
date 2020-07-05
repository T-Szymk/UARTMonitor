/**************************************************************************************************
* CppSerial.h
* -----------
***************************************************************************************************
* Description
* -----------
* Class to utilise a serial port in Windows. This is based on the implementation that is contained
* using the Win32 API described within the article by Tom Archer:
* https://www.codeguru.com/cpp/i-n/network/serialcommunications/article.php/c2503/CSerial--A-C-Class-for-Serial-Communications.htm
* The implementation has been modified slightly from the articla to try and simplify the class to
* only recieve serial data (and not send any data). Additionally, I will continuously try to 
* update this class to use best practices for modern C++. 
***************************************************************************************************
* History
* -------
* JULY-2020: Created class definition.
***************************************************************************************************/

#ifndef __CPPSERIAL_H__
#define __CPPSERIAL_H__

/**************************************************************************************************
* Includes
**************************************************************************************************/

#include <Windows.h>
#include <cstdint>
#include <memory>
#include <string>
#include <array>
#include <cstring>

/**************************************************************************************************
* Constants aliases
**************************************************************************************************/

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

/**************************************************************************************************
* Class definition
**************************************************************************************************/

class CppSerial {

	public:
		
		CppSerial();
		~CppSerial();

		// funtions to open/close serial port
		BOOL Open(int nPort = 1, int nBaud = 9600);
		BOOL Close();

		int ReadData(void*, const int); // move data from serial buffer to data structure
		int ReadDataWaiting(); // read how much data is currently in serial buffer
		
		BOOL getPortOpen() noexcept; // get open state of port

	protected:

		HANDLE port_handle; // Win32 object used to represent the serial port
		OVERLAPPED m_OverlappedRead; // overlapped object used to monitor events on port
		BOOL port_open; // open state of port updated during port operations

	private:
		// disable copy/move construction/assignment
		CppSerial(const CppSerial&) = delete;
		CppSerial(CppSerial&&) = delete; //TODO create definition of move
		CppSerial& operator=(const CppSerial&) = delete;
		CppSerial& operator=(CppSerial&&) = delete; //TODO create definition of move

		// partial list of serial ports available on a windows platform. Note that this list is not
		// exhaustive, but is sufficient for practical applications.
		const std::array<std::string, 22> com_ports{ "\\\\.\\COM1",
                                                 "\\\\.\\COM2", "\\\\.\\COM3",
                                                 "\\\\.\\COM4", "\\\\.\\COM5",
                                                 "\\\\.\\COM6", "\\\\.\\COM7",
                                                 "\\\\.\\COM8", "\\\\.\\COM9",
                                                 "\\\\.\\COM10", "\\\\.\\COM11",
                                                 "\\\\.\\COM12", "\\\\.\\COM13",
                                                 "\\\\.\\COM14", "\\\\.\\COM15",
                                                 "\\\\.\\COM16", "\\\\.\\COM17",
                                                 "\\\\.\\COM18", "\\\\.\\COM19",
                                                 "\\\\.\\COM20", "\\\\.\\COM21" };
};

#endif
