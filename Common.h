/*---------------------------------------------------------------------------------------------------
-- SOURCE FILE:		Common.h -		Header file contains global variables and functions shared by
--									all 3 layers.
--
-- Program:			RFID Reader
--
-- Functions:		void connect();
--					void disconnect();
--					void print(TCHAR* str);
--					DWORD WINAPI ConnectReader(LPVOID lpParameter);
--					unsigned char ReadTag(LPSKYETEK_TAG lpTag, void *user);
--
-- Date:			10/15/2017
--
-- Revisions:		N/A
--
-- Designer:		Nicholas Chow
--
-- Programmer:		Nicholas Chow
--
*/

#pragma once

#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <stdio.h>
#include "SkyeTekAPI.h"
#include "SkyeTekProtocol.h"

// Global Variables
extern BOOL start;
extern HWND hwnd;
extern HANDLE h;
extern DWORD id;
extern BOOL printing;


// Functions shared by layers
void connect();
void disconnect();
void print(TCHAR* str);
DWORD WINAPI ConnectReader(LPVOID lpParameter);
unsigned char ReadTag(LPSKYETEK_TAG lpTag, void *user);


#endif