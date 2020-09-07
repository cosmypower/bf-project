#pragma once

class Console
{
public:
	static Console* getInstance() { static Console* inst = new Console(); return inst; };

	void ShowMainMessage();

	void DisplayMenu();

	void DisplayLicenceInfo();

	void DisplayMethods();

	void HandleMenu();

private:
	int current_option = 0;
	int selected_checker = 0;
};

