/*---------------------------------------------------------------------------------------------------
--	SOURCE FILE:	Application.cpp - The application layer of the dumb emulator. High level GUI 
--									  provided for users to access the communication parameters, and
--									  displays characters when input is read from the serial port.
-- 
--	Program:		RFID Reader
--
--
--  Functions:		LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
--					int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance,
-- 										LPSTR lspszCmdParam, int nCmdShow);
--					void print(TCHAR* string);
--
-- Date:			10/15/2017
--
-- Designer:		Nicholas Chow , Calvin Lai
--
-- Programmer:		Nicholas Chow , Calvin Lai
--
-- Notes:			The winMain function creates, registers the window. It also contains a loop to
--					receive messages. WndProc function handles all the events such as key presses, 
--					clicking on menu items. It also contains a print character function to output
--					the character to the screen.
---------------------------------------------------------------------------------------------------*/
#define STRICT

#include "Common.h"
#include "Application.h"
#include "menu.h"
#include <stdlib.h>
#include <windows.h>
#include "Session.h"

char Name[] = "RFID Reader";
char str[80] = "";
HWND hwnd;
HDC hdc;
LPCSTR	lpszCommName;
BOOL paramChanged;
BOOL isConnected;
void cls(HANDLE hConsole);

#pragma warning (disable: 4096)


/*----------------------------------------------------------------------------------------------------
--	Function		WinMain
--
--	Date:			9/30/2017
--
--	Revisions:		N/A
--
--	Designer:		Nicholas Chow
--
--	Programmer:		Nicholas Chow
--	
--  Interface:		int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance,
--													  LPSTR lspszCmdParam, int nCmdShow);
--	
--	Returns:		returns an int, conveys a status code
--
--	Notes:			This function creates, register the window. It also contains a loop
--					to handle messages.
----------------------------------------------------------------------------------------------------*/
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
--	Function:		WndProc		
--
--	Date:			10/15/2017
--
--	Revisions:		N/A
--
--	Designer:		Nicholas Chow
--
--	Programmer:		Nicholas Chow
--
--	Interface:		LRESULT CALLBACK WndProc (HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
--
--  Returns:		Return value is the result of the message processing and depends on the message sent
--
--	Notes:			This function contains a switch statement to handle the messages such as
--					pressing a key, clicking on menu items.
----------------------------------------------------------------------------------------------------*/

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
					print("Disconnected");
				break;
				case IDM_Clear:
					cls(hdc);
				break;
				case IDM_HELP:
					MessageBox(NULL, "RFID", "Assignment 2", MB_OK);
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
--	Function:		print
--
--	Date:			10/15/2017
--
--  Revisions:		N/A
--
--	Designer:		Nicholas Chow
--
--	Programmer:		Nicholas Chow
--
--  Interface:		void print(TCHAR* string)
--
--	Returns:		void
--
--	Notes:			Simple function for printing characters to the window.
----------------------------------------------------------------------------------------------------*/
void print(TCHAR* string)
{
	HDC hdc;
	RECT r;
	TEXTMETRIC tm;
	SIZE size;
	static int x = 0;
	static int y = 0;
	
	hdc = GetDC((HWND)hwnd);
	GetClientRect(hwnd, &r);
	GetTextMetrics(hdc, &tm);
	int width = r.left - r.right;
	int height = r.top - r.bottom;
	GetTextExtentPoint32(hdc, str, strlen(str), &size);
	TextOut(hdc, x, y, string, strlen(string));
	y = y + tm.tmHeight + tm.tmExternalLeading;
	ReleaseDC((HWND)hwnd, hdc);
}


void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the
									 cursor */
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in
									 the current buffer */

									 /* get the number of character cells in the current buffer */

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */

	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);

	/* get the current text attribute */

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);

	/* now set the buffer's attributes accordingly */

	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);
	

	/* put the cursor at (0, 0) */

	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);

	return;
}