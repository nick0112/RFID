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

// Global Variables
extern BOOL isConnected;
extern HWND hwnd;
extern HANDLE hComm;
extern LPCSTR	lpszCommName;
extern BOOL paramChanged;
extern COMMCONFIG cc;


// Functions shared by layers
void openPort();
BOOL changeCommParams();
void connect();
void printCharacter(char* str);
BOOL writeABuffer(char* str, DWORD dwToWrite);


#endif