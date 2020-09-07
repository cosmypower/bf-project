#include "main.h"

DWORD WINAPI netflixThread(LPVOID lpThreadParameter) {

    Json::Value data = Netflix::CheckAccount("", "", "");

    if (!data || data["error"]) return 1;

    return 1;
}

void Netflix::Initialise(int threads)
{
    string csrf = Netflix::GetCSRF();

    Netflix::CheckAccount("a", "a", csrf);
}

Json::Value Netflix::CheckAccount(const char* email, const char* password, string csrf)
{
    string received = Postman::getInstance()->postString("https://www.netflix.com:443/Login", "");

    cout << received << endl;

	return Json::Value();
}

string Netflix::GetCSRF() {
    string received = Postman::getInstance()->get("https://www.netflix.com/nl-en/Login");

    //(<input type="hidden" name="authURL" value=")[0-9a-zA-Z.\/+=]*
    
    regex re("<input type=\"hidden\" name=\"authURL\" value=\"([0-9a-zA-Z.\\/+=]*)");
    cmatch searches_string;

    regex_search(received.c_str(), searches_string, re);

    if (searches_string.size() <= 0) return 0;

    return searches_string[1].str();
}