#include "main.h"

DWORD WINAPI mainThread(LPVOID lpThreadParameter) {
	if (Licence::getInstance()->CheckLicence("1234a")) {
		Console::getInstance()->ShowMainMessage();
		Console::getInstance()->DisplayMenu();
	}
	else {
		exit(0);
	}
}

int main()
{
	CreateThread(NULL, NULL, mainThread, NULL, NULL, NULL);

	while (true);
}