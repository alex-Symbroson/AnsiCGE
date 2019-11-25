
/* 
 * File:   Pixel.h
 * Author: symbroson
 *
 * Created on 24 November 2019, 22:14
 */

#ifndef PIXEL_H
#define PIXEL_H

#include "Color.h"

struct Pixel {
    char symbol;
    Color color;

    Pixel();
    Pixel(char symbol);
    Pixel(char symbol, Color color);
    ~Pixel();

    string toStr() const {
        return color.toStr() + symbol + symbol;
    }

    static string toStr(char mod, Color color = {}, char symbol = -1) {
        if (symbol == -1) return color.toStr();
        return color.toStr() + symbol;
    }

    bool operator!=(const Pixel& p) const {
        return !(*this == p);
    }

    bool operator==(const Pixel& p) const {
        return symbol == p.symbol && color == p.color;
    }
};

#endif /* PIXEL_H */

