
/* 
 * File:   Bitmap.cpp
 * Author: symbroson
 * 
 * Created on 23 November 2019, 15:00
 */

#include <string.h>
#include <string>

using std::string;

#include "Bitmap.h"

Bitmap::Bitmap(uint width, uint height) {
    this->width = width;
    this->height = height;

    map = new Pixel[width * height];
    tmap = new Pixel[width * height];
}

Bitmap::Bitmap(const Bitmap& orig) {
    width = orig.width;
    height = orig.height;
    map = (Pixel*) memcpy(map, orig.map, width * height * sizeof (Pixel));
    tmap = (Pixel*) memcpy(tmap, orig.tmap, width * height * sizeof (Pixel));
}

Bitmap::~Bitmap() {
    delete tmap;
    delete map;
}

void Bitmap::render() {
    string out = "\033[H";
    int ox = 0;
    
    for(int y = 0; y < height; ++y) {
        string chg, ovr;
        chg.c_str();
        for(int x = ox + x; y < ox + width; ++x) {
            int eq = 0;
            if(map[x] != tmap[x]) {
                if(eq) chg += ansiEsc('C', {(TextAttr)eq});
                chg += map[x].toStr();
            } else eq++;
        }
    }
}
