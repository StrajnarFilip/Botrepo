#include <windows.h>
#include <cmath>
#include <ctime>
#include <thread>
#include <random>
#include <fstream>

namespace inpt {

#define write std::cout <<
#define scan std::cin >>

	int mousecoord_x_normalised = 0;
	int mousecoord_y_normalised = 0;
	int mousecoord_x = 0;
	int mousecoord_y = 0;
	int globaltoggle = 0;



	void FileAppend(int x, int y)
	{
		std::ofstream csvFile;
		csvFile.open("C:\\Users\\Filip\\Desktop\\Coordfile.txt", std::fstream::app);
		csvFile << "SimulateMove(" << x << " , " << y << ");" << std::endl;
		csvFile.close();
	}

	void MouseCoordinatesRead()
	{
		POINT save;
		GetCursorPos(&save);
		write '\n';
		write "Coordinate X: " << save.x;
		mousecoord_x = save.x;
		mousecoord_y = save.y;
		write '\n';
		write "Coordinate Y: " << save.y;
	}
	void MouseCoordinates()
	{
		POINT save;
		GetCursorPos(&save);
		mousecoord_x = save.x;
		mousecoord_y = save.y;
	}

	void MouseCoordinatesNormalised()
	{
		POINT save;
		GetCursorPos(&save);
		/*write '\n';
		write "Coordinate X: "<<save.x;*/
		mousecoord_x_normalised = ceil(save.x * 34.1328125);
		mousecoord_y_normalised = ceil(save.y * 60.680555555555555555555555555556);
		/*write '\n';
		write "Coordinate Y: " << save.y;*/
	}

	void KeyboardSetup(INPUT* buffer)
	{
		buffer->type = INPUT_KEYBOARD;
		buffer->ki.wScan = 0;
		buffer->ki.time = 0;
		buffer->ki.dwExtraInfo = 0;
	}

	void KeyDown(INPUT* buffer, int selection)
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
		MouseCoordinatesNormalised();
		buffer->type = INPUT_MOUSE;
		buffer->mi.dx = (mousecoord_x_normalised);
		buffer->mi.dy = (mousecoord_y_normalised);
		buffer->mi.mouseData = 0;
		buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
		buffer->mi.time = 0;
		buffer->mi.dwExtraInfo = 0;
	}

	void MouseMoveAbsolute(INPUT* buffer, int x, int y)
	{
		buffer->mi.dx = (x);
		buffer->mi.dy = (y);
		buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

		SendInput(1, buffer, sizeof(INPUT));
	}

	void MouseClick(INPUT* buffer)
	{
		buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
		SendInput(1, buffer, sizeof(INPUT));


		buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
		SendInput(1, buffer, sizeof(INPUT));
	}

	void MouseRightClick(INPUT* buffer)
	{
		buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN);
		SendInput(1, buffer, sizeof(INPUT));


		buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP);
		SendInput(1, buffer, sizeof(INPUT));
	}
	void SimulateRightClick()
	{
		INPUT buffer;
		MouseSetup(&buffer);
		MouseRightClick(&buffer);
	}

	void SimulateMove(int x, int y)
	{
		INPUT buffer;
		x = ceil(x * 34.1328125);
		y = ceil(y * 60.680555555555555555555555555556);
		MouseSetup(&buffer);
		MouseMoveAbsolute(&buffer, x, y);
	}
	void SimulateClick()
	{
		INPUT buffer;
		MouseSetup(&buffer);
		MouseClick(&buffer);
	}

	void TestMouseCoordinates() {
		POINT save;
		for (int count = 0; count < 200; count++)
		{
			GetCursorPos(&save);
			write "Coordinate X: " << save.x;
			write '\n';
			write "Coordinate Y: " << save.y;
			SimulateMove(save.x, save.y);
		}
	}



	void GameTickWait(int amount_of_ticks)
	{
		int amnt = amount_of_ticks * 600;
		Sleep(amnt);
	}

	void alchbot() {
		Sleep(1000);
		MouseCoordinatesNormalised();
		int counter_click = 0;

		while (true) {

			int times = rand() % 150 + 50;
			printf("\n\nHow many times: %d\n", times);
			for (int x = 0; x < times; x++)
			{
				SimulateMove(1743, 580);
				SimulateClick();
				counter_click++;
				int chance = rand() % 1000;
				if (chance > 700)
				{
					x--;
					printf("\nLucky proc!");
				}

				int interval = rand() % 40 + 130;


				printf(" Pause duration (ms): %d\n", interval);
				SimulateMove(3, 3);
				int smallpause = rand() % 1000;
				if (smallpause < 150)
				{
					Sleep(100);
					printf("\ntiny pause!\n");
				}
				Sleep(interval);
			}
			printf("\nNumber of clicks: %d\n", counter_click);
			counter_click = 0;

			char yo[80];
		}
	}

	int globalrng = 1;

	void alchhelper()
	{
		//srand(time(NULL));
		MouseCoordinates();
		if (mousecoord_x > 1864 && mousecoord_x < 1872 && mousecoord_y>835 && mousecoord_y < 851)
		{
			write "\nCLICK!\n";
			SimulateClick();
		}

		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<> dist(150, 200);




		int interval = dist(rng) + globalrng;
		if (interval > 195)
		{
			globalrng = 1;
		}
		int smallpauseduration = rand() % 600 + 50;
		int smallpause = rand() % 1000;
		if (smallpause > 250)
		{
			Sleep(smallpauseduration);
			printf("\ntiny pause add: ");
			write  "+ " << smallpauseduration;
		}
		Sleep(interval);
		write "\nRegular pause: " << interval;
	}

	int isKeyPressed(int x)
	{
		int ispressed = GetKeyState(x);
		if (ispressed < -100) {
			return 1;
		}
		else return 0;

	}

	int leftrighttoggle()
	{
		/*
		int on = isKeyPressed(0x25);
		int off = isKeyPressed(0x27);

		if (on==1) {
			return 1;
		}
		if (off == 1) {
			return 0;
		}*/
		if (globaltoggle) {
			//Check if we turn off
			return !isKeyPressed(0x27);
		}
		else {
			//if it's off, check to turn on
			return isKeyPressed(0x25);
		}
	}

	void coordreader()
	{
		while (1)
		{
			int toggle = globaltoggle;
			if (true) {
				system("cls");
				MouseCoordinatesRead();
				if (isKeyPressed(0x01)) {
					FileAppend(mousecoord_x, mousecoord_y);
					write "  CLICK!";
					Sleep(100);
				}
			}
			Sleep(16);
		}
	}

	void improvedalchhelp()
	{
		while (1)
		{
			if (globaltoggle)
			{
				alchhelper();
			}
		}
	}




	int main_t_one() {
		while (1)
		{
			globaltoggle = leftrighttoggle();
		}
		return  0;
	}

	void asynctimer()
	{
		while (1) {
			globalrng++;
			globalrng = globalrng + (rand() % 15);
			if (globalrng > 60) {
				globalrng = 0;
			}
		}
	}




#undef write
#undef scan

}
