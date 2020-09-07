#include "main.h"

size_t GetOutputAsString(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

size_t GetOutputAsJSON(const char* in, size_t size, size_t num, char* out)
{
	std::string data(in, (std::size_t) size * num);
	*((std::stringstream*) out) << data;
	return size * num;
}

void Postman::SetOptions(CURL* curl) {
	
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.83 Safari/537.36 Edg/85.0.564.44");
}

bool Postman::Send(CURL* curl) {
	CURLcode res = curl_easy_perform(curl);

	if (res != CURLE_OK) return false;

	int httpCode;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

	if (httpCode == 404) return false;

	curl_easy_cleanup(curl);

	return true;
}

/* Post methods */
Json::Value Postman::post(const char* url, const char* postfields)
{
	CURL* curl = curl_easy_init();
	string readBuffer;

	std::stringstream httpData;
	Json::Value jsonData;
	Json::CharReaderBuilder jsonReader;

	curl_easy_setopt(curl, CURLOPT_URL, url);

	this->SetOptions(curl);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetOutputAsJSON);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);

	if (!this->Send(curl)) return jsonData;

	if (!Json::parseFromStream(jsonReader, httpData, &jsonData, NULL)) return jsonData;

	return jsonData;
}

Json::Value Postman::postJson(const char* url, Json::Value json)
{
	CURL* curl = curl_easy_init();
	string readBuffer;

	std::stringstream httpData;
	Json::Value jsonData;
	
	Json::CharReaderBuilder jsonReader;
	Json::StreamWriterBuilder builder;

	curl_easy_setopt(curl, CURLOPT_URL, url);

	this->SetOptions(curl);

	struct curl_slist* hs = NULL;
	hs = curl_slist_append(hs, "Content-Type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetOutputAsJSON);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

	builder["indentation"] = "";
	string output = Json::writeString(builder, json);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, output.c_str());

	if (!this->Send(curl)) return jsonData;
	if (!httpData) return jsonData;

	string errs;
	if (!Json::parseFromStream(jsonReader, httpData, &jsonData, &errs)) return jsonData;

	return jsonData;
}

string Postman::postString(const char* url, const char* postfields)
{
	CURL* curl = curl_easy_init();
	string readBuffer;

	curl_easy_setopt(curl, CURLOPT_URL, url);

	this->SetOptions(curl);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetOutputAsString);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);

	if (!this->Send(curl)) return "";

	return readBuffer;
}

/* Get methods */
string Postman::get(const char* url)
{
	CURL* curl = curl_easy_init();
	string readBuffer;

	curl_easy_setopt(curl, CURLOPT_URL, url);

	this->SetOptions(curl);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetOutputAsString);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	if (!this->Send(curl)) return "";

	return readBuffer;
}

Json::Value Postman::getJSON(const char* url)
{
	CURL* curl = curl_easy_init();
	
	std::stringstream httpData;
	Json::Value jsonData;

	Json::CharReaderBuilder jsonReader;
	Json::StreamWriterBuilder builder;

	curl_easy_setopt(curl, CURLOPT_URL, url);

	this->SetOptions(curl);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetOutputAsJSON);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

	if (!this->Send(curl)) return jsonData;

	if (!Json::parseFromStream(jsonReader, httpData, &jsonData, NULL)) return jsonData;

	return jsonData;
}

