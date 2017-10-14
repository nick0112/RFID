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
	if (start) {
		if (lpTag != NULL) {
			printCharacter("Tag: ");
			printCharacter(lpTag->friendly);
			printCharacter(" Type: ");
			printCharacter(SkyeTek_GetTagTypeNameFromType(lpTag->type));
			printCharacter("\n");
			SkyeTek_FreeTag(lpTag);
		}
	}
	return start;
}



