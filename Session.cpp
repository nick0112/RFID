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


HANDLE h;
DWORD id;

/*----------------------------------------------------------------------------------------------------
--	Function		DWORD WINAPI ConnectReader(LPVOID lpParameter)
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
--	Notes:			This function is the main thread function. It finds the reader then it calls
--					selectTags. Loop breaks when SelectLoopCallBack returns 0
--
*/

DWORD WINAPI ConnectReader(LPVOID lpParameter)
{
	return 0;
}



/*----------------------------------------------------------------------------------------------------
--	Function		void connect()
--
--	Program:		RFID
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			This function creates a thread that communicates with the SkyeModule
--					reader.
--
*/
void connect()
{
	h = CreateThread(NULL, 0, ConnectReader, NULL, 0, &id);
	if (h == NULL)
	{
		MessageBox(NULL, "Thread Creation Failed", "", MB_OK);
	}
}
