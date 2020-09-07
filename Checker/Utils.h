#pragma once

class Utils
{
public:
	static vector<string> string_split(char* phrase, string delimiter);
};

struct {
	vector<string> proxy_list;
} g_Variables;

constexpr auto NAME = "D E L U X E";