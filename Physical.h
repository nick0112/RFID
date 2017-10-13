/*-----------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Physical.h -		Phsyical Header file contains functions used for physical layer
--
--	Program:		Dumb Terminal
--
--
--
-- Functions:		DWORD WINAPI ReadFromPort(LPVOID lpvoid);
--
--
-- Date:			9/30/2017
--
--
-- Programmer:		Nicholas Chow
--
*/

#pragma once

#ifndef PHYSICAL_H
#define PHYSICAL_H

#include <windows.h>
#include <stdio.h>


DWORD WINAPI ReadFromPort(LPVOID lpvoid);


#endif