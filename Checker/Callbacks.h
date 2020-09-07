#pragma once

constexpr auto CHECKER_MINECRAFT = "Minecraft";
constexpr auto CHECKER_NETFLIX = "Netflix";

class Callbacks
{
public:
	static void OnAccountFound(const char* type, const char* username, const char* password, Json::Value data);
};

