/*-----------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Application.h -		Application Header file contains variables and functions 
--										used for application layer
--
--	Program:		Dumb Terminal
--
--
--
-- Functions:		LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
--
--
-- Date:			9/30/2017
--
--
-- Programmer:		Nicholas Chow
--
*/
#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>
#include <stdio.h>

extern BOOL paramChanged;
extern HDC hdc;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


#endif