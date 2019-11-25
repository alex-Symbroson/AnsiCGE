/* 
 * File:   Color.h
 * Author: symbroson
 *
 * Created on 23 November 2019, 20:00
 */

#ifndef COLOR_H
#define COLOR_H

#include "TextAttr.h"

#include <string>
#include <forward_list>

#define LOG2(X) log2<X>
#define BITS(X) __builtin_popcount(X)

#define t_log2(X) std::__log2p1(X)
#define i_log2(X) std::__lg(X)

#define COLORS(...) {__VA_ARGS__}

using std::string;
using std::forward_list;

template <uint x>
constexpr std::enable_if_t<x != 0U, int> _log2 = 1 + _log2< x / 2 >;
template<>
constexpr uint _log2<1U> = 0;

template<typename T>
inline T dflt(T value, T none, T dflt) {
    return value == none ? dflt : value;
}

string ansiEsc(char cmd, std::initializer_list<TextAttr> attrs);
string ansiEsc(char cmd, const forward_list<TextAttr>& attrs);
string ansiEsc(char cmd, TextAttr* attrs);

struct Color {
public:
    static Color fromRGB(TextAttr mode, uint8_t r, uint8_t g, uint8_t b);

    /**
     * 8bit colors:\
     * 0x00-0x07:  standard colors (same as the 4-bit colours) \
     * 0x08-0x0F:  high intensity colors \
     * 0x10-0xE7:  6 × 6 × 6 cube (216 colors): 16 + 36 × r + 6 × g + b (0 ≤ r, g, b ≤ 5)\
     * 0xE8-0xFF:  grayscale from black to white in 24 steps
     */
    static Color from8BIT(TextAttr mode, uint8_t hue);

    forward_list<TextAttr> attrs;

    Color();
    Color(std::initializer_list<TextAttr> attrs);

    ~Color();

    Color(const Color& other) : attrs(other.attrs) {
    }

    string toStr() const {
        return ansiEsc('m', attrs);
    }

    bool operator!=(const Color& c) const {
        return !(*this == c);
    }

    bool operator==(const Color& c) const {
        auto a = attrs.begin(), b = c.attrs.begin();
        while (a != attrs.end() && b != attrs.end())
            if (*a != *b) return false;
        return true;
    }
};


#endif /* COLOR_H */

