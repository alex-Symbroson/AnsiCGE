/* 
 * File:   Color.h
 * Author: symbroson
 *
 * Created on 23 November 2019, 20:00
 */

#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <string.h>
#include <cmath>
#include <cstdarg>

using std::string;

template <uint x>
constexpr std::enable_if_t<x != 0U, int> _log2 = 1 + _log2< x / 2 >;
template<>
constexpr uint _log2<1U> = 0;

#define LOG2(X) log2<X>
#define _B(n) (1 << n)
#define BITS(X) __builtin_popcount(X)

inline uint log2u(uint x) {
    return x ? 31 - ffs(x) : 0;
}

#define t_log2(X) std::__log2p1(X)
#define i_log2(X) std::__lg(X)

enum class TextAttr : char {
    _NONE = '\255',
    OFF = 0, // All attributes off
    BOLD,
    THIN, // Not widely supported.
    ITALIC, // Not widely supported.
    UNDERLINE, SLOWBLINK, FASTBLINK,
    INVERSE, // swap fg and bg color
    CONCEAL, // Not widely supported.
    CROSSOUT,
    NORMALFONT = 10, FONT1, FONT2, FONT3,
    FONT4, FONT5, FONT6, FONT7, FONT8, FONT9,
    FRAKTUR = 20, // hardly ever supported
    DBL_UNDL, BOLD_THIN_OFF, ITALIC_OFF, UNTERLINE_OFF, BLINK_OFF,
    INVERSE_OFF = 27, COLCEAL_OFF, CROSSOUT_OFF,
    FG_BLACK = 30, FG_RED, FG_GREEN, FG_YELLOW, FG_BLUE,
    FG_PINK, FG_TURKIS, FG_WHITE, FG_HUE_RGB, FG_DEFAULT,
    BG_BLACK = 40, BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE,
    BG_PINK, BG_TURKIS, BG_WHITE, BG_HUE_RGB, BG_DEFAULT,
    FRAMED = 51, ENCIRCLED, OVERLINED, FRM_CIR_OFF, OVRLN_OFF,
    FGB_BLACK = 90, FGB_RED, FGB_GREEN, FGB_YELLOW, FGB_BLUE,
    FGB_PINK, FGB_TURKIS, FGB_WHITE, FGB_HUE_RGB, FGB_DEFAULT,
    BGB_BLACK = 100, BGB_RED, BGB_GREEN, BGB_YELLOW, BGB_BLUE,
    BGB_PINK, BGB_TURKIS, BGB_WHITE, BGB_HUE_RGB, BGB_DEFAULT
};

template<typename T>
inline T dflt(T value, T none, T dflt) {
    return value == none ? dflt : value;
}

string ansiEsc(char cmd, std::initializer_list<TextAttr> attrs);
string ansiEsc(char cmd, TextAttr* attrs);

struct Color {
public:
    TextAttr* attrs = NULL;

    string toStr() const {
        return ansiEsc('m', attrs);
    }

    bool operator!=(const Color& c) const {
        return !(*this == c);
    }

    bool operator==(const Color& c) const {
        TextAttr *a = attrs, *b = c.attrs;
        while (a != NULL && b != NULL) 
            if (a++ != b++) return false;
        return true;
    }

};


#endif /* COLOR_H */

