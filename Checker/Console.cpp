#include "main.h"

void Console::ShowMainMessage() {
	Json::Value user_info = Licence::getInstance()->GetUserInfo();
	int days_remaining = floor((user_info["expires_at"].asUInt() - time(0)) / 86400);

	printf("\033[1;31m%s - \033[1;32mWelcome back, \033[1;33m%s\033[0m\n", NAME, user_info["name"].asString().c_str());
	printf("\033[1;31m%s - \033[1;32mYour licence expires in \033[1;33m%d \033[1;32mdays.\033[0m\n", NAME, days_remaining);
	printf("\n");
}

void Console::DisplayMenu() {
	printf("\033[1;31m%s - \033[1;32mChoose what you want to do:\033[0m\n", NAME);

	printf("\033[1;31m1. \033[1;36mView info about your licence\n");
	printf("\033[1;31m2. \033[1;36mView all methods\n");
	printf("\033[1;31m3. \033[1;36mView all your hits\n");

	printf("\n");

	printf("\033[1;31mType here the chosen number: \033[1;36m");

	while (scanf_s("%d", &this->current_option) != 1) {
		system("cls");

		this->ShowMainMessage();
		this->DisplayMenu();
	}

	this->HandleMenu();
}

void Console::DisplayLicenceInfo() {
	Json::Value user_info = Licence::getInstance()->GetUserInfo();

	int days_remaining = floor((user_info["expires_at"].asUInt() - time(0)) / 86400);

	printf("\033[1;31mI N F O - \033[1;32mLicence name: \033[1;33m%s\n", user_info["name"].asString().c_str());
	printf("\033[1;31mI N F O - \033[1;32mLicence type: \033[1;33m%d\n", days_remaining);
	printf("\033[1;31mI N F O - \033[1;32mLicence expire date: \033[1;33m%d \033[1;32mdays.\033[0m\n", days_remaining);

	printf("\n");

	printf("\033[1;31m%s - \033[1;32mIf you want to go back, press \033[1;33many letter\033[0m\n", NAME);

	_getch();
}

void Console::DisplayMethods() {
	printf("\033[1;31m1. \033[1;36mSteam\n");
	printf("\033[1;31m2. \033[1;36mMinecraft\n");
	printf("\033[1;31m3. \033[1;36mRoblox\n");

	printf("\033[1;31m4. \033[1;36mNetflix\n");
	printf("\033[1;31m5. \033[1;36mSpotify\n");

	printf("\033[1;31m6. \033[1;36mNordVPN\n");
	printf("\033[1;31m7. \033[1;36mWindscribe\n");

	printf("\033[1;31m8. \033[1;36mWeb.de\n");

	printf("\n");

	printf("\033[1;31mType here the chosen number: \033[1;36m");

	scanf_s("%d", &this->selected_checker);

	switch (this->selected_checker)
	{
		case 2:
			Minecraft::Initialise(6);
			break;
		case 4:
			Netflix::Initialise(6);
			break;
	}
}

void Console::HandleMenu() {
	if (this->current_option < 0 || this->current_option > 3) {
		system("cls");

		this->ShowMainMessage();
		this->DisplayMenu();

		return;
	}

	switch (this->current_option)
	{
		case 1:
			this->DisplayLicenceInfo();
			break;
		case 2:
			this->DisplayMethods();
			break;
	}
}