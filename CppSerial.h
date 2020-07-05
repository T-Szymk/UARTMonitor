// CppSerial.h

#ifndef __CPPSERIAL_H__
#define __CPPSERIAL_H__

#include <Windows.h>
#include <cstdint>
#include <memory>
#include <string>
#include <array>
#include <cstring>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

class CppSerial {

	public:
		
		CppSerial();
		~CppSerial();

		BOOL Open(int nPort = 1, int nBaud = 9600);
		BOOL Close();

		int ReadData(void*, const int);
		int ReadDataWaiting();
		
		BOOL getPortOpen() noexcept;

	protected:

		HANDLE port_handle;
		OVERLAPPED m_OverlappedRead;
		BOOL port_open;

	private:
		// disable copy/move construction/assignment
		CppSerial(const CppSerial&) = delete;
		CppSerial(CppSerial&&) = delete;
		CppSerial& operator=(const CppSerial&) = delete;
		CppSerial& operator=(CppSerial&&) = delete;

		const std::array<std::string, 22> com_ports{ "\\\\.\\COM1", "\\\\.\\COM1",
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
