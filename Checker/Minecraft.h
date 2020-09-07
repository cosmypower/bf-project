#pragma once
#include <wincrypt.h>

class Minecraft
{
public:
	static void Initialise(int threads);
	static Json::Value CheckAccount(const char* email, const char* password);
	static bool CheckCape(const char* nickname);

	static int GetMonthlyViews(const char* nickname);
	static Json::Value GetHypixelStats();

	static constexpr auto CLIENT_TOKEN = "909772fc24bc4d92bf2dc48bfecb375f";
	static constexpr auto MOJANG_AUTH = "https://authserver.mojang.com/authenticate";

	static constexpr auto NAMEMC_SEARCH = "https://namemc.com/search?q=";
	static constexpr auto OPTIFINE_SEARCH = "http://s.optifine.net/capes/";
};

