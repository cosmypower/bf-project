#pragma once

class Postman
{
public:
	static Postman* getInstance() { static Postman* inst = new Postman(); return inst; };

	Json::Value post(const char* url, const char* postfields);
	Json::Value postJson(const char* url, Json::Value json);
	string postString(const char* url, const char* postfields);

	Json::Value getJSON(const char* url);
	string get(const char* url);
private:
	void SetOptions(CURL* curl);
	bool Send(CURL* curl);
};

