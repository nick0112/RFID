/*---------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Physical.cpp -	  The phsyical layer of the RFID Reader. This layer provides
--									  access to the physical communication link, these functions 
--									  read the tag of the reader.
--
--	Program:		RFID Reader
--
--  Functions:		unsigned char ReadTag(LPSKYETEK_TAG lpTag, void *user);
--
--  Date:			10/15/2017
--
--  Revisions:		N/A
--
--	Designer:		Calvin Lai
--
--  Programmer:		Calvin Lai
--
--	Notes:			In this layer, ReadTag Function keeps getting input from the tag that
--					is being scanned from the reader. Once the tag is read, it is being
--					printed by the print function in the application layer.
--					
*/

#define STRICT
#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"
#include <stdio.h>
#include "Application.h"


/*----------------------------------------------------------------------------------------------------
--	Function		ReadTag
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
--  Return:			Returns 0 when user changes state to stop
--
--	Interface		unsigned char ReadTag(LPSKYETEK_TAG lpTag, void *user)
--
--	Notes:			This function checks if start has been set to true. IF it continues, then
--					it checks the tag to ensure it is not null. If it passes, then it prints out
--					the tag.
----------------------------------------------------------------------------------------------------*/

unsigned char ReadTag(LPSKYETEK_TAG lpTag, void *user)
{
	size_t length = sizeof(lpTag->friendly);
	TCHAR* tag = new TCHAR[length];
	memcpy(tag, lpTag, length);
	if (start)
	{
		if (lpTag != NULL) 
		{
			print("Tag: ");
			for (int i = 0; i < length; i++)
			{
				strcat(tag, lpTag->friendly + i);
			}
			print(tag);
			SkyeTek_FreeTag(lpTag);
		}
	}
	
	return (!start);
}


