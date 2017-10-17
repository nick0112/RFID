/*----------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Session.cpp -		This is the session layer of the RFID. In this layer,
--										user connects to the reader through SKYETECH API.
--
--	Program:		RFID Reader
--
--  Functions:		DWORD WINAPI ConnectReader(LPVOID lpParameter)
--					void connect();
--					void disconnect();
--
--  Date:			10/15/2017
--
--	Revisions:		N/A
--
--	Designer:		Calvin Lai, Nicholas Chow
--
--  Programmer:		Calvin Lai, Nicholas Chow
--
--  Notes:			In this layer, a thread is created to monitor the SkyeTech Reader.
--					Connect() function connects the device and reader.  
---------------------------------------------------------------------------------------------------*/
#define STRICT

#include "Common.h"
#include <stdio.h>
#include "Session.h"
#include <stdlib.h>
#include "Physical.h"


HANDLE h;
DWORD id;
unsigned int numDevices;
unsigned int numReaders;
BOOL start;

/*----------------------------------------------------------------------------------------------------
--	Function		ConnectReader
--
--	Program:		RFID
--
--	Date:			10/15/2017
--
--	Revisions:		N/A
--
--	Designer:		Nicholas Chow,	Calvin Lai
--
--	Programmer:		Nicholas Chow , Calvin Lai
--
--  Return:			Returns DWORD, 1 indicating the user has quitted scanning
--
--	Interface		DWORD WINAPI ConnectReader(LPVOID lpParameter)
--
--	Notes:			This function is the main thread function. It finds the reader then it calls
--					selectTags. Loop breaks when SelectLoopCallBack returns 0
----------------------------------------------------------------------------------------------------*/

DWORD WINAPI ConnectReader(LPVOID lpParameter)
{
	LPSKYETEK_DEVICE *devices = NULL;
	LPSKYETEK_READER *readers = NULL;
	unsigned int numDevices;
	unsigned int numReaders;

	print("Discovering Reader...");
	start = TRUE;
	// Infinite Loop to look for reader
	while (start)
	{
		numDevices = SkyeTek_DiscoverDevices(&devices);
		if (numDevices == 0)
		{
			print("No Device Found...Please Connect");
			continue;
		}
		numReaders = SkyeTek_DiscoverReaders(devices, numDevices, &readers);

		if (numReaders == 0)
		{
			print("No Reader Found...Please Connect");
			continue;
		}
		
		print("Start Reading...");
		break;
	}
	
	SkyeTek_SelectTags(readers[0], AUTO_DETECT, ReadTag, 0, 1, NULL);
	SkyeTek_FreeReaders(readers, numReaders);
	SkyeTek_FreeDevices(devices, numDevices);

	return 1;
}



/*----------------------------------------------------------------------------------------------------
--	Function		connect
--
--	Program:		RFID
--
--	Date:			10/15/2017
--
--	Revisions:		N/A
--
--	Designer:		Nicholas Chow,	Calvin Lai
--
--	Programmer:		Nicholas Chow , Calvin Lai
--
--	Interface:		void connect()
--
--  Return:			void
--
--	Notes:			This function creates the thread, if thread creation failed, display messaage box.
----------------------------------------------------------------------------------------------------*/
void connect()
{
	h = CreateThread(NULL, 0, ConnectReader, NULL, 0, &id);
	if (h == NULL)
	{
		MessageBox(NULL, "Thread Creation Failed", "", MB_OK);
	}
}


/*----------------------------------------------------------------------------------------------------
--	Function		disconnect
--
--	Program:		RFID
--
--	Date:			10/15/2017
--
--	Revisions:		N/A
--
--	Designer:		Nicholas Chow,	Calvin Lai
--
--	Programmer:		Nicholas Chow , Calvin Lai
--
--	Interface:		void disconnect()
--
--  Return:			void
--
--	Notes:			This function terminates the thread and sets the state to stop.
----------------------------------------------------------------------------------------------------*/
void disconnect()
{
	start = false;
	CloseHandle(h);
	h = NULL;
}