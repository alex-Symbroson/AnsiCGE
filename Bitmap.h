
/* 
 * File:   Bitmap.h
 * Author: symbroson
 *
 * Created on 23 November 2019, 15:00
 */

#ifndef BITMAP_H
#define BITMAP_H

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <type_traits>

#include "Color.h"

struct Pixel {
    char symbol = ' ';
    Color color = {.attrs = new TextAttr[2]
        {TextAttr::BGB_WHITE, TextAttr::FGB_BLACK}};

    ~Pixel() {
        delete color.attrs;
    }\
    

    string toStr() {
        return color.toStr() + symbol;
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

class Bitmap {
public:
    Bitmap(uint width, uint height);
    Bitmap(const Bitmap& orig);
    ~Bitmap();

    uint GetWidth() const {
        return width;
    }

    uint GetHeight() const {
        return height;
    }

    Pixel* GetMap() const {
                return map;
    }

    void render();

private:
    uint width, height;
    Pixel* tmap;
    Pixel* map;

};

#endif /* BITMAP_H */

