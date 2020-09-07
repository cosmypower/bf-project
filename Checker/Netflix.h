#pragma once

class Netflix
{
public:
	static void Initialise(int threads);
	static Json::Value CheckAccount(const char* email, const char* password, string csrf);

	static string GetCSRF();
};

