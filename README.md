# Botrepo

Include inpt header to your cpp project. API functions are in namespace inpt.

Functions you want to use:

1. inpt::SimulateMove(int x,int y);
2. inpt::SimulateClick();
3. inpt::SimulateKeyDown(int selection);
4. inpt::SimulateKeyUp(int selection);
5. inpt::SimulateKeyPress(int selection);
6. inpt::GameTickWait(int amount of clicks);


- int x and int y represent x and y coordinate on your screen (in pixels) NOTE: by default, it takes coordinates for 1920x1080 resolution. Value is then multiplied to give NORMALISED values. Normalized absolute coordinates between 0 and 65,535 for both x and y, is what windows.h INPUT structure expect. Hence 65535 / 1920 (\*‭34,1328125‬) and 65535 / 1080 (\*‭‭60,680555555555555555555555555556‬‬) multipliers respectively. 

- int selection expects virtual key code, all of them you can find here: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
