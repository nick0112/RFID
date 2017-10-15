/*---------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Common.h -		Header file contains global variables and functions shared by
--									all 3 layers.
--
--
--	Program:		Dumb Terminal
--
--
--
-- Functions:		void openPort();
--					BOOL changeCommParams();
--					void connect();
--					void printCharacter(char* str);
--					BOOL writeABuffer(char* str, DWORD dwToWrite);
--
--
-- Date:			9/30/2017
--
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
extern LPSKYETEK_DEVICE *devices;
extern LPSKYETEK_READER *readers;
extern SKYETEK_STATUS status;


// Functions shared by layers
void connect();
void disconnect();
void print(TCHAR* str);
DWORD WINAPI ConnectReader(LPVOID lpParameter);
unsigned char SelectLoopCallback(LPSKYETEK_TAG lpTag, void *user);


#endif