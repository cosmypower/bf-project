#include "main.h"

bool Licence::CheckLicence(const char* hwid)
{
	char licence_str[256];

	sprintf_s(licence_str, "type=verify&hwid=%s", hwid);

	this->user = Postman::getInstance()->post("http://localhost", licence_str);

	if (!this->user) return false;

	return true;
}

Json::Value Licence::GetUserInfo() {
	return this->user;
}
