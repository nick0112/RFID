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

BOOL start = false;

/*----------------------------------------------------------------------------------------------------
--	Function		unsigned char SelectLoopCallback(LPSKYTEK_TAG, void*)

--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow, Calvin Lai
--
--	Notes:			This function will continuously read the tag when it is detected by the reader.
--					Once the reader is complete, we retrieve the tag, and print out the Tag ID.
--
*/

unsigned char SelectLoopCallback(LPSKYETEK_TAG lpTag, void *user)
{
		/*
		if (lpTag != NULL) {
			LPCSTR msg = "";
			char* msg2 = "";
			for (int i = 0; i < sizeof(lpTag->friendly); i++) {
				msg2 += (lpTag->friendly + i);
			}
			MessageBox(NULL, lpTag->friendly+1, "", MB_OK);
			print("Tag: ");
			print(lpTag->friendly);
			print(" Type: ");
			print(SkyeTek_GetTagTypeNameFromType(lpTag->type));
			print("\n");
			SkyeTek_FreeTag(lpTag);
		}
		*/
		char inputBuffer[100] = "";
		DWORD nBytesRead;
		DWORD dwEvent;
		DWORD dwError;
		DWORD dwRes;
		DWORD dwRead;
		COMSTAT cs;
		OVERLAPPED osReader = { 0 };
		BOOL fWaitingOnRead = FALSE;

		osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (osReader.hEvent == NULL) {

		}

		SetCommMask(h, EV_RXCHAR);
		while (start) {
			if (WaitCommEvent(h, &dwEvent, NULL)) {

				ClearCommError(h, &dwError, &cs);
				if ((dwEvent & EV_RXCHAR) && cs.cbInQue) {
					print(lpTag->friendly);
				}
			}
			else {
				locProcessCommError(GetLastError());
			}
			if (fWaitingOnRead) {
				dwRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);
				switch (dwRes) {
				case WAIT_OBJECT_0:
					if (!GetOverlappedResult(h, &osReader, &dwRead, FALSE)) {

					}
					else {
						fWaitingOnRead = FALSE;
					}
					break;
				case WAIT_TIMEOUT:
					break;
				default:
					break;
				}
			}
		}
		PurgeComm(h, PURGE_RXCLEAR);
		return start;
}


void locProcessCommError(DWORD dwError) {
	LPDWORD lrc = 0;
	COMSTAT cs;
	ClearCommError(h, lrc, &cs);
}

