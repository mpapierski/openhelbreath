#include "Game.h"

#ifdef DEF_CONSOLE
#include <io.h>
#include <FCNTL.H>
void ActivateConsole()
{
    AllocConsole();

    HANDLE newConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE newConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	int inFd = _open_osfhandle((long) newConsoleInput, _O_TEXT);
	int outFd = _open_osfhandle((long) newConsoleOutput, _O_TEXT);

	FILE* consoleIn = _fdopen(inFd, "r");
	FILE* consoleOut = _fdopen(outFd, "w");

	setvbuf(consoleIn, NULL, _IONBF, 0);
	setvbuf(consoleOut, NULL, _IONBF, 0);

	*stdin = *consoleIn;
	*stdout = *consoleOut;
}
#endif

int main(int argc, char** argv)
{
#ifdef DEF_CONSOLE
	ActivateConsole();
#endif
	return Game::GetInstance().OnExecute();
}
