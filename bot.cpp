#include <iostream>
#include <windows.h>
#define write std::cout << 
#define scan std::cin >> 



void MouseCoordinates()
{
	POINT save;
	GetCursorPos(&save);
	write save.x;
	write '\n';
	write save.y;
}

void KeyboardSetup(INPUT* buffer)
{
	buffer->type = INPUT_KEYBOARD;
	buffer->ki.wScan = 0;
	buffer->ki.time = 0;
	buffer->ki.dwExtraInfo = 0;
}

void KeyDown(INPUT * buffer, int selection)
{
	buffer->ki.wVk = (char)selection;
	buffer->ki.dwFlags = 0;
	SendInput(1, buffer, sizeof(INPUT));
}

void KeyUp(INPUT* buffer, int selection)
{
	buffer->ki.wVk = (char)selection;
	buffer->ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, buffer, sizeof(INPUT));
}

void SimulateKeyDown(int selection)
{
	INPUT buffer;
	KeyboardSetup(&buffer);
	KeyDown(&buffer, (char)selection);
}
void SimulateKeyUp(int selection)
{
	INPUT buffer;
	KeyboardSetup(&buffer);
	KeyUp(&buffer, (char)selection);
}

void SimulateKeyPress(int selection)
{
	INPUT buffer;
	KeyboardSetup(&buffer);
	KeyDown(&buffer, selection);
	KeyUp(&buffer, selection);
}

void MouseSetup(INPUT* buffer)
{
	buffer->type = INPUT_MOUSE;
	buffer->mi.dx = (0 * (0xFFFF / GetSystemMetrics(SM_CXSCREEN)));
	buffer->mi.dy = (0 * (0xFFFF / GetSystemMetrics(SM_CYSCREEN)));
	buffer->mi.mouseData = 0;
	buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	buffer->mi.time = 0;
	buffer->mi.dwExtraInfo = 0;
}

void MouseMoveAbsolute(INPUT* buffer, int x, int y)
{
	buffer->mi.dx = (x * (0xFFFF / GetSystemMetrics(SM_CXSCREEN)));
	buffer->mi.dy = (y * (0xFFFF / GetSystemMetrics(SM_CYSCREEN)));
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

	SendInput(1, buffer, sizeof(INPUT));
}

void MouseClick(INPUT* buffer)
{
	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, buffer, sizeof(INPUT));

	Sleep(10);

	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, buffer, sizeof(INPUT));
}

void SimulateMove(int x, int y)
{
	INPUT buffer;
	MouseSetup(&buffer);
	MouseMoveAbsolute(&buffer, x, y);
}
void SimulateClick()
{
	INPUT buffer;
	MouseSetup(&buffer);
	MouseClick(&buffer);
}



int main(int argc, char* argv[])
{
	//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	/*
	SimulateMove(1746,127);
	for (size_t i = 0; i < 12; i++)
	{
		SimulateClick();
		Sleep(5);
		SimulateClick();
		Sleep(575);
	}
	
	MouseCoordinates();
	*/
	Sleep(5000);
	SimulateKeyDown(0x39);
	SimulateKeyUp(0x39);
	SimulateKeyPress(0x2C);
	

	return 0;
}
