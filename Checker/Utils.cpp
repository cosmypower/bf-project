#include "main.h"

vector<string> Utils::string_split(char* phrase, string delimiter) {
    vector<string> list;
    string s = string(phrase);
    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}