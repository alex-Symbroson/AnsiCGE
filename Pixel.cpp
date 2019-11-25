
#include "Pixel.h"

Pixel::Pixel() : Pixel(' ')
{
}

Pixel::Pixel(char symbol) :
    symbol(symbol)
{
    //printf(" new  pxl 1 %p\n", this);
    //printf("*new  pxl 1 %p\n", this);
}

Pixel::Pixel(char symbol, Color color) :
    symbol(symbol),
    color(color)
{
    //printf(" new  pxl 2 %p\n", this);
    //printf("*new  pxl 2 %p\n", this);
}

Pixel::~Pixel()
{
}