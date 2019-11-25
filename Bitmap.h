
/* 
 * File:   Bitmap.h
 * Author: symbroson
 *
 * Created on 23 November 2019, 15:00
 */

#ifndef BITMAP_H
#define BITMAP_H

#include "Pixel.h"

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

    void drawPixel(int x, int y, Color color = COLORS(TextAttr::BGB_WHITE));

    void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color);

    void drawRectangle(
            int x, int y, uint w, uint h,
            Color fill = Color(),
            Color stroke = COLORS(TextAttr::BGB_WHITE),
            uint strokeWidth = 0,
            uint radius = 0);

private:
    uint width, height;
    Pixel* tmap;
    Pixel* map;

    void _drawPixel(int x, int y, Color color);
};

#endif /* BITMAP_H */

