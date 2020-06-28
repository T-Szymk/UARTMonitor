#include "CppSerial.h"

CppSerial::CppSerial() {

	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
	port_handle = NULL;
	port_open = FALSE;
}

CppSerial::~CppSerial() {

	Close();

}

BOOL CppSerial::Open(int nPort, int nBaud) {

	if (port_open) {
		return(TRUE);
	}

	// conver com_port from std::string to cstring
	const char* szPort = const_cast<char*>(com_ports[nPort].c_str());
	LPWSTR szComParams{};
	DCB dcb;

	port_handle = CreateFileA(szPort,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED, // asynchronous operation
		NULL);

	if (port_handle == NULL) {
		return(FALSE);
	}

	memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));

	// CreateEvent(securityAttribs, manual_reset, initial_state, ptr_to_event_obj_name)
	m_OverlappedRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(port_handle, &CommTimeOuts);

	dcb.DCBlength = sizeof(DCB);
	GetCommState(port_handle, &dcb);
	dcb.BaudRate = nBaud;
	dcb.ByteSize = 8;

	// note that SetupComm() is used to set the size of input/output buffer in bytes
	if (!SetCommState(port_handle, &dcb) ||	!SetupComm(port_handle, 10000, 10000) ||
		   m_OverlappedRead.hEvent == NULL) {
		DWORD dwError = GetLastError();
		if (m_OverlappedRead.hEvent != NULL) {
			CloseHandle(m_OverlappedRead.hEvent);
		}
		CloseHandle(port_handle);
		return(FALSE);
	}

	port_open = TRUE;

	return(port_open);

}

BOOL CppSerial::Close(void) {

	if (!port_open || port_handle == NULL) { 
		return(TRUE);
	}
	if (m_OverlappedRead.hEvent != NULL) {
		CloseHandle(m_OverlappedRead.hEvent);
	}
	CloseHandle(port_handle);
	port_open = FALSE;
	port_handle = NULL;

	return(TRUE);
}

int CppSerial::ReadDataWaiting(void) {

	if (!port_open || port_handle == NULL) {
		return(0);
	}

	DWORD dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(port_handle, &dwErrorFlags, &ComStat);

	return((int)ComStat.cbInQue);
}

int CppSerial::ReadData(void* buffer, const int bytes_to_read) {

	if (!port_open || port_handle == NULL) {
		return(0);
	}

	BOOL bReadStatus;
	DWORD dwBytesRead, dwErrorFlags;
	COMSTAT ComStat;

	ClearCommError(port_handle, &dwErrorFlags, &ComStat);
	
	// if input buffer is empty
	if (!ComStat.cbInQue) {
		return(0);
	}

	dwBytesRead = (DWORD)ComStat.cbInQue;
	// read all data in buffer or specified number of bytes to read, whichever is smallest
	if (bytes_to_read < (int)dwBytesRead) {
		dwBytesRead = (DWORD)bytes_to_read;
	}

	bReadStatus = ReadFile(port_handle, buffer, dwBytesRead, &dwBytesRead, &m_OverlappedRead);
	
	if (!bReadStatus) {
		if (GetLastError() == ERROR_IO_PENDING) {
			// if readline operation has not completed yet, delay 2s to wait for function to return
			WaitForSingleObject(m_OverlappedRead.hEvent, 2000);
			return((int)dwBytesRead);
		}
		// return 0 if readline fails
		return(0);
	}

	return((int)dwBytesRead);

}

BOOL CppSerial::getPortOpen() noexcept {
	return(port_open);
}

