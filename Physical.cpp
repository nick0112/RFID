/*---------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Physical.cpp -	  The phsyical layer of the dumb emulator. This layer provides
--									  access to the physical communication link, these functions 
--									  include opening, reading and writing to port.
--
--
--	Program:		Dumb Terminal
--
--
--
-- Functions:		void openPort();
--					BOOL writeABuffer(char* str, DWORD dwToWrite);
--					DWORD WINAPI ReadFromPort(LPVOID lpvoid)
--
--
-- Date:			9/30/2017
--
--
-- Programmer:		Nicholas Chow
--
-- Notes:			In this layer, the port is opened for reading and writing. WriteABuffer  
--					contains a BOOL value to track if the write operation is overlapped.
--					ReadFromThread behaves similiarly to WriteABuffer, when reading is done,
--					printChar is called to output the character to the screen.
--					
*/

#define STRICT
#define READ_TIMEOUT 500
#include "Common.h"
#include <stdio.h>
#include "Application.h"

/*----------------------------------------------------------------------------------------------------
--	Function		void openPort()

--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			This function simply opens the port, if it fails a message box is displayed.
--
*/

void openPort()
{
	if ((hComm = CreateFile(lpszCommName, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "Error opening COM port:", "", MB_OK);
	}
}

/*----------------------------------------------------------------------------------------------------
--	Function		BOOL writeABuffer(char* str, DWORD dwToWrite)
--
--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			This function first creates the wirte operation's overlapped structure. Next,
--					it calls the WriteFile function to send data to port. Then it calls 
--					GetOverLappedResult to fetch the results of the overlapped operation, it it returns
--					true, then the writing operation has completed.
--
*/


BOOL writeABuffer(char* str, DWORD dwToWrite)
{
	OVERLAPPED osWrite = { 0 };
	DWORD dwWritten;
	DWORD dwRes;
	BOOL writing;


	osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (osWrite.hEvent == NULL)
	{
		return FALSE;
	}

	if (!WriteFile(hComm, str, dwToWrite, &dwWritten, &osWrite))
	{
		if (GetLastError() != ERROR_IO_PENDING) {
			writing = FALSE;
		}
		else
		{
			dwRes = WaitForSingleObject(osWrite.hEvent, INFINITE);
		}
			switch (dwRes)
			{
			case WAIT_OBJECT_0:
				if (!GetOverlappedResult(hComm, &osWrite, &dwWritten, FALSE))
					writing = FALSE;
				else
					writing = TRUE;
				break;
			
			default:
				writing = FALSE;
				break;
			}
	}
	else
	{
		writing = TRUE;
	}

	CloseHandle(osWrite.hEvent);
	return writing;
		
}

/*----------------------------------------------------------------------------------------------------
--	Function		DWORD WINAPI ReadFromPort(LPVOID lpvoid)
--
--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			This function contains a loop to check the state of the program, and only
--					runs when it is connected. When reading is complete, printChar is called
--					to display the character.
--
*/
DWORD WINAPI ReadFromPort(LPVOID lpvoid)
{
	DWORD dwRead;
	DWORD dwRes;
	BOOL fWaitingOnRead = FALSE;
	OVERLAPPED osReader = { 0 };
	char str[80] = "";

	osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (osReader.hEvent == NULL)
	{
		return 0;
	}

	while (isConnected)
	{
		if (!fWaitingOnRead)
		{
			if (!ReadFile(hComm, str, 1, &dwRead, &osReader))
			{
				if (GetLastError() != ERROR_IO_PENDING)
				{
					return 0;
				}
				else
				{
					fWaitingOnRead = TRUE;
				}
			}
			else
			{
				printCharacter(str);
			}
		}
		else
		{
			dwRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);

			switch (dwRes)
			{
			case WAIT_OBJECT_0:
				if (!GetOverlappedResult(hComm, &osReader, &dwRead, FALSE))
				{
					MessageBox(NULL, "Error in Comm", NULL, MB_OK);
				}
				else
				{
					printCharacter(str);
				}
				fWaitingOnRead = FALSE;
				break;
			case WAIT_TIMEOUT:
				break;
			default:
				break;
			}
		}	
	}
}