/*---------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Session.h -		Session Header file contains global variables and functions 
--									used for session layer.
--
--	Program:		Dumb Terminal
--
--
--
-- Functions:		N/A
--
--
-- Date:			9/30/2017
--
--
-- Programmer:		Nicholas Chow
--
*/
#pragma once

#ifndef SESSION_H
#define SESSIon_H

#include <windows.h>
#include <stdio.h>

extern COMMPROP commprop;
extern DCB dcb;
extern HANDLE rThread;
extern DWORD threadId;


#endif