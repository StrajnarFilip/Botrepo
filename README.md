# Botrepo

Include inpt header to your cpp project. API functions are in namespace inpt.

Functions you want to use:

1. inpt::SimulateMove(int x,int y);                     //Note: SimulateMove function takes in coordinates of 1920x1080 display, you may want to modify it
2. inpt::SimulateClick();
3. inpt::SimulateKeyDown(int selection);
4. inpt::SimulateKeyUp(int selection);
5. inpt::SimulateKeyPress(int selection);
6. inpt::GameTickWait(int amount of clicks);


- int x and int y represent x and y coordinate on your screen (in pixels)

- int selection expects virtual key code, all of them you can find here: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
