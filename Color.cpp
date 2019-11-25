
#include "Color.h"

#include <stdexcept>
#include <string.h>
#include <cmath>
#include <cstdarg>

Color::Color() : attrs{TextAttr::OFF, TextAttr::BG_BLACK, TextAttr::FG_WHITE}
{
}

Color::Color(std::initializer_list<TextAttr> attrs) :
    attrs(attrs)
{
    this->attrs.push_front(TextAttr::OFF);
}

Color::~Color()
{
}

Color Color::fromRGB(TextAttr ground, uint8_t r, uint8_t g, uint8_t b)
{
    if (ground != TextAttr::BG_COLOR && ground != TextAttr::FG_COLOR)
        throw std::invalid_argument("ground must be FG_COLOR or BG_COLOR");
    return Color({ground, (TextAttr) 2, (TextAttr) r, (TextAttr) g, (TextAttr) b});
}

Color Color::from8BIT(TextAttr ground, uint8_t hue)
{
    if (ground != TextAttr::BG_COLOR && ground != TextAttr::FG_COLOR)
        throw std::invalid_argument("ground must be FG_COLOR or BG_COLOR");
    return Color({ground, (TextAttr) 5, (TextAttr) hue});
}

string ansiEsc(char cmd, std::initializer_list<TextAttr> attrs)
{
    string res = "\033[";
    for (TextAttr a : attrs)
        res += std::to_string((uint8_t) a) + ';';
    if (res.back() == ';') res.back() = cmd;
    else res += cmd;
    return res;
}

string ansiEsc(char cmd, TextAttr* attrs)
{
    string res = "\033[";
    while (*attrs != TextAttr::OFF)
        res += std::to_string((uint8_t) * attrs++) + ';';
    char& back = res.back();
    if (back == ';') back = cmd;
    else res += cmd;
    return res;
}

string ansiEsc(char cmd, const forward_list<TextAttr>& attrs)
{
    string res = "\033[";
    for (TextAttr a : attrs)
        res += std::to_string((uint8_t) a) + ';';
    if (res.back() == ';') res.back() = cmd;
    else res += cmd;
    return res;
}