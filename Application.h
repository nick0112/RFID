/*-----------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Application.h -		Application Header file contains variables and functions 
--										used for application layer
--
--	Program:		RFID Reader
--
-- Functions:		LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>
#include <stdio.h>


extern HDC hdc;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


#endif