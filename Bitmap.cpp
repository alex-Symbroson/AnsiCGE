
/* 
 * File:   Bitmap.cpp
 * Author: symbroson
 * 
 * Created on 23 November 2019, 15:00
 */

#include "Bitmap.h"

#include <string.h>
#include <string>
#include <cmath>

using std::string;
using std::min;
using std::max;

Bitmap::Bitmap(uint width, uint height)
{
    this->width = width;
    this->height = height;
    map = new Pixel[width * height];
    tmap = new Pixel[width * height];
}

Bitmap::Bitmap(const Bitmap& orig)
{
    width = orig.width;
    height = orig.height;
    map = (Pixel*) memcpy(map, orig.map, width * height * sizeof(Pixel));
    tmap = (Pixel*) memcpy(tmap, orig.tmap, width * height * sizeof(Pixel));
}

Bitmap::~Bitmap()
{
    delete[] tmap;
    delete[] map;
}

void Bitmap::render()
{
    string out = "\033[H";
    int ox = 0;

    for (int y = 0; y < height; ++y, ox += width) {
        //string chg, ovr;
        for (int x = ox; x < ox + width; ++x) {
            out += map[x].toStr();
            /*int eq = 0;
            if (map[x] != tmap[x]) {
                if (eq) chg += ansiEsc('C',{(TextAttr) eq});
                chg += map[x].toStr();
            } else eq++;*/
        }
        out += '\n';
    }
    printf("%s", out.c_str());
}

void Bitmap::_drawPixel(int x, int y, Color color)
{
    if (x >= 0 && y >= 0 && x < width && y < height)
        map[y * width + x] = Pixel(' ', color);
}

void Bitmap::drawPixel(int x, int y, Color color)
{
    if (x >= 0 && y >= 0 && x < width && y < height)
        _drawPixel(x, y, color);
}

#define CPSGN(dst, src) std::copysign<uint,int>(dst, src)
#define SGN32(X) ((X >> 31 << 1) + 1)

void Bitmap::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color)
{
    int dx = abs(x2 - x1), sx = SGN32(x1 - x2);
    int dy = -abs(y2 - y1), sy = SGN32(y1 - y2);
    int err = dx + dy, e2;
    do {
        drawPixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 > dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    } while (1);
}

static inline bool isStroke(int diff, uint width, int tol)
{
    // prevented through rect constraints specification in 
    //if (!(width % 2) && 2 * abs(diff + tol) < width) return true;
    return 2 * abs(diff) < width;
}

void Bitmap::drawRectangle(
        int x, int y, uint w, uint h,
        Color fill,
        Color stroke,
        uint strokeWidth, uint radius)
{
    // wtf -1 / 2 = 2147483647
    const int strokeW = strokeWidth ? (strokeWidth - 1) / 2 : 0;
    uint x1 = max(0, x - strokeW),
            y1 = max(0, y - strokeW);
    const uint x2 = min(x + w + strokeW, width),
            y2 = min(y + h + strokeW, height);

    while (x1 < x2) {
        while (y1 < y2) {
            if (radius) {
                // TODO draw quarter circles
                if (x1 < radius && y < radius) break;
                if (x1 > width - radius && y < radius) break;
                if (x1 < radius && y > height - radius) break;
                if (x1 > width - radius && y > height - radius) break;
            }

            _drawPixel(x1, y1, (strokeWidth && (
                    isStroke(x1 - x, strokeWidth, 1) ||
                    isStroke(y1 - y, strokeWidth, 1) ||
                    isStroke(x1 - x - w + 1, strokeWidth, -1) ||
                    isStroke(y1 - y - h + 1, strokeWidth, -1)
                    )) ? stroke : fill);
            ++y1;
        }
        y1 = max(0, y - strokeW);
        ++x1;
    }
}
