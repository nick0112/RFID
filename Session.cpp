/*----------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Session.cpp -		This is the session layer of the dumb emulator. In this layer,
--										user can connect, initialize or terminate the session.
--
--
--	Program:		Dumb Terminal
--
--
--
-- Functions:		BOOL changeCommParams();
--					void connect();
--					
--
-- Date:			9/30/2017
--
--
-- Programmer:		Nicholas Chow
--
-- Notes:			In this layer, the user is able to change the port paramaters as they want. 
--					A connect function is avaliable for the user to enter connect mode which sets the 
--					state of the program to connect mode.
--			
*/
#define STRICT

#include "Common.h"
#include <stdio.h>
#include "Session.h"
#include <stdlib.h>
#include "Physical.h"


COMMCONFIG cc;
COMMPROP commprop;
DCB dcb;
HANDLE rThread;
DWORD threadId;


/*----------------------------------------------------------------------------------------------------
--	Function		void changeCommParams()
--
--
--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			This function gets the comm config dialog. Then it reads the current configs, and
--					sets the new configs if the user enters new value for each parameter.
--
*/

BOOL changeCommParams()
{
	cc.dwSize = sizeof(COMMCONFIG);
	cc.wVersion = 0x100;
	GetCommConfig(hComm, &cc, &cc.dwSize);
	if (CommConfigDialog(lpszCommName, hwnd, &cc))
	{
		// Read the current configurations
		if (!GetCommState(hComm, &dcb))
		{
			MessageBox(hwnd, "Initialization Failed", NULL, MB_OK);
			return FALSE;
		}
		else
		{
			if (SetCommState(hComm, &cc.dcb))
			{
				MessageBox(hwnd, "Settings Applied", "New Settings", MB_OK);
				return TRUE;
			}
			else
			{
				MessageBox(hwnd, "Settings Failed", NULL, MB_OK);
				return FALSE;
			}
		}
	}
}

/*----------------------------------------------------------------------------------------------------
--	Function		void connect()
--
--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			This function first checks if the commname has been set yet. Then it proceeds 
--					to open the port and set the state to connect mode. It also creates a new thread
--					for reading.
--
*/
void connect()
{
	if (lpszCommName == NULL)
	{
		MessageBox(hwnd, "Please select COM1 or COM2", NULL, MB_OK);
	}
	else
	{
		openPort();
		isConnected = TRUE;
		rThread = 0;
		// Create the reading thread
		rThread = CreateThread(NULL, 0, ReadFromPort, (LPVOID)hwnd, 0, &threadId);
		if (rThread)
		{
			MessageBox(hwnd, "Thread Launched for Reading", "Thread", MB_OK);
			CloseHandle(rThread);
		}
	}
	
}
