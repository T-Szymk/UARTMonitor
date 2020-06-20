// CppSerial.h

#ifndef __CPPSERIAL_H__
#define __CPPSERIAL_H__

#include <Windows.h>
#include <cstdint>
#include <memory>

constexpr uint16_t FC_DTRDSR	= 0x01;
constexpr uint16_t FC_RTSCTS	= 0x02;
constexpr uint16_t FC_XONXOFF = 0x04;
constexpr uint16_t ASCII_BEL  = 0x07;
constexpr uint16_t ASCII_BS   = 0x08;
constexpr uint16_t ASCII_LF   = 0x0A;
constexpr uint16_t ASCII_CR   = 0x0D;
constexpr uint16_t ASCII_XON  = 0x11;
constexpr uint16_t ASCII_XOFF = 0x13;

class CppSerial
{

public:
	CppSerial();
	~CppSerial();

	BOOL Open( int nPort = 1, int nBaud = 9600 );
	BOOL Close( void );

	int ReadData( void *, int );
	int SendData( const char *, int );
	int ReadDataWaiting( void );

	BOOL IsOpened( void ){ return( port_open ); }

protected:
	BOOL WriteCommByte( unsigned char );

	HANDLE port_handle;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
	BOOL port_open;

};

#endif
