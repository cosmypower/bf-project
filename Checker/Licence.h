#pragma once

class Licence
{
public:
	static Licence* getInstance() { static Licence* inst = new Licence(); return inst; };
	
	bool CheckLicence(const char* hwid);
	void GetSettings();

	Json::Value GetUserInfo();
private:
	Json::Value user;
};

