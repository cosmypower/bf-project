#include "main.h"
#include "main.h"

void Callbacks::OnAccountFound(const char* type, const char* username, const char* password, Json::Value data)
{
	char str[256];

	if (!strcmp(type, CHECKER_MINECRAFT)) {
		sprintf_s(str, " \033[1;32m%s\033[1;33m, with \033[1;32m%d \033[1;33mmonthly views%s", data["nickname"].asString().c_str(), Minecraft::GetMonthlyViews(data["nickname"].asString().c_str()), data["cape"].asBool() == false ? "." : " and has an optifine cape.");
	}

	printf("\033[1;32m[+] \033[1;33mFound \033[1;32m%s\033[1;33m account named%s\n", type, str);
}
