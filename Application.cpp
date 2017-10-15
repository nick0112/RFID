/*---------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Application.cpp - The application layer of the dumb emulator. High level GUI 
--									  provided for users to access the communication parameters, and
--									  displays characters when input is read from the serial port.
-- 
--
--	Program:		Dumb Terminal 
--
--
--
-- Functions:		LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
--					int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance,
-- 										LPSTR lspszCmdParam, int nCmdShow);
--					void printToScreen(char buffer[]);
--
--
-- Date:			9/30/2017
--
--
-- Programmer:		Nicholas Chow
--
-- Notes:			The winMain function creates, registers the window. It also contains a loop to
--					receive messages. WndProc function handles all the events such as key presses, 
--					clicking on menu items. It also contains a print character function to output
--					the character to the screen.
*/
#define STRICT

#include "Common.h"
#include "Application.h"
#include "menu.h"
#include <stdlib.h>
#include <windows.h>
#include "Session.h"

char Name[] = "Dumb Terminal";
char str[80] = "";
HWND hwnd;
HDC hdc;
HANDLE hComm;
LPCSTR	lpszCommName;
BOOL paramChanged;
BOOL isConnected;

#pragma warning (disable: 4096)


/*----------------------------------------------------------------------------------------------------
--	Function		int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance,
 						  LPSTR lspszCmdParam, int nCmdShow);

--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			This function creates, register the window. It also contains a loop
--					to handle messages.
--
*/
int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance,
 						  LPSTR lspszCmdParam, int nCmdShow)
{
	MSG Msg;
	WNDCLASSEX Wcl;

	Wcl.cbSize = sizeof (WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style
	
	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = Name;
	
	Wcl.lpszMenuName = "MYMENU"; // The menu Class
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0; 
	
	if (!RegisterClassEx (&Wcl))
		return 0;

	hwnd = CreateWindow (Name, Name, WS_OVERLAPPEDWINDOW, 10, 10,
   							600, 400, NULL, NULL, hInst, NULL);
	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);


	while (GetMessage (&Msg, NULL, 0, 0))
	{
   		TranslateMessage (&Msg);
		DispatchMessage (&Msg);
	}

	return Msg.wParam;
}


/*----------------------------------------------------------------------------------------------------
--	Function:		LRESULT CALLBACK WndProc (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)		
--              
--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			This function contains a switch statement to handle the messages such as
--					pressing a key, clicking on menu items.
--
*/
LRESULT CALLBACK WndProc (HWND hwnd, UINT Message,
                          WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintstruct;
	DWORD numBytes;

	switch (Message)
	{
		case WM_COMMAND:
			switch (LOWORD (wParam))
			{
				case IDM_Start:
					connect();
				break;
				case IDM_Stop:
					disconnect();
				case IDM_HELP:
					MessageBox(NULL, "Dumb Terminal", "Assignment 1", MB_OK);
				break;
				case IDM_Exit:
					ExitProcess(5);
			}
		break;
		
		case WM_PAINT:		// Process a repaint message
			hdc = BeginPaint (hwnd, &paintstruct); // Acquire DC
			EndPaint (hwnd, &paintstruct); // Release DC
		break;


		case WM_DESTROY:	// Terminate program
      		PostQuitMessage (0);
		break;
		default:
			return DefWindowProc (hwnd, Message, wParam, lParam);
	}
	return 0;
}


/*----------------------------------------------------------------------------------------------------
--	Function:		void printCharacter(char* string)
--
--	Program:		Dumb Terminal
--
--
--	Date:			9/30/2017
--
--
--	Programmer:		Nicholas Chow
--
--	Notes:			Simple function for output.
--
*/
void print(TCHAR* string)
{
	HDC hdc;
	RECT r;
	TEXTMETRIC tm;
	SIZE size;

	static int X = 0;
	static int Y = 0;

	hdc = GetDC((HWND)hwnd);
	GetClientRect(hwnd, &r);
	GetTextMetrics(hdc, &tm);
	int width = r.left - r.right;
	int height = r.top - r.bottom;
	
	GetTextExtentPoint32(hdc, str, strlen(str), &size);


	TextOut(hdc, X, Y, string, strlen(string));
	Y = Y + tm.tmHeight + tm.tmExternalLeading;
	
	ReleaseDC((HWND)hwnd, hdc);
}