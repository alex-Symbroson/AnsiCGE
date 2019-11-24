
#include "Color.h"

string ansiEsc(char cmd, std::initializer_list<TextAttr> attrs) {
    string res = "\033[";
    for(TextAttr a : attrs)
        res += std::to_string((uint8_t)a) + ";";
    if(attrs.size()) res.back() = cmd;
    else res += cmd;
    return res;
}

string ansiEsc(char cmd, TextAttr* attrs) {
    string res = "\033[";
    while (*attrs != TextAttr::OFF)
        res += std::to_string((uint8_t)*attrs++) + ";";
    char& back = res.back();
    if(back == ';') back = cmd;
    else res += cmd;
    return res;
}