// CppSerial.h

#ifndef __CPPSERIAL_H__
#define __CPPSERIAL_H__

#include <Windows.h>
#include <cstdint>
#include <memory>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

constexpr u16 FC_DTRDSR = 0x01;
constexpr u16 FC_RTSCTS = 0x02;
constexpr u16 FC_XONXOFF = 0x04;
constexpr u16 ASCII_BEL = 0x07;
constexpr u16 ASCII_BS = 0x08;
constexpr u16 ASCII_LF = 0x0A;
constexpr u16 ASCII_CR = 0x0D;
constexpr u16 ASCII_XON = 0x11;
constexpr u16 ASCII_XOFF = 0x13;

class CppSerial {

	public:
		
		CppSerial();
		~CppSerial();

		BOOL Open(int nPort = 1, int nBaud = 9600);
		BOOL Close(void);

		int ReadData(void*, int);
		int SendData(const char*, int);
		int ReadDataWaiting(void);

		BOOL IsOpened(void) { return(port_open); }

	protected:
		
		BOOL WriteCommByte(unsigned char);

		HANDLE port_handle;
		OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
		BOOL port_open;

	private:
		// disable copy/move construction/assignment
		CppSerial(const CppSerial&) = delete;
		CppSerial(CppSerial&&) = delete;
		CppSerial& operator=(const CppSerial&) = delete;
		CppSerial& operator=(CppSerial&&) = delete;
};

#endif
