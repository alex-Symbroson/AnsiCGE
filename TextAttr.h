/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextAttr.h
 * Author: symbroson
 *
 * Created on 24 November 2019, 22:15
 */

#ifndef TEXTATTR_H
#define TEXTATTR_H

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
    FG_PINK, FG_TURKIS, FG_WHITE, FG_COLOR, FG_DEFAULT,
    BG_BLACK = 40, BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE,
    BG_PINK, BG_TURKIS, BG_WHITE, BG_COLOR, BG_DEFAULT,
    FRAMED = 51, ENCIRCLED, OVERLINED, FRM_CIR_OFF, OVRLN_OFF,
    FGB_BLACK = 90, FGB_RED, FGB_GREEN, FGB_YELLOW, FGB_BLUE,
    FGB_PINK, FGB_TURKIS, FGB_WHITE, FGB_HUE_RGB, FGB_DEFAULT,
    BGB_BLACK = 100, BGB_RED, BGB_GREEN, BGB_YELLOW, BGB_BLUE,
    BGB_PINK, BGB_TURKIS, BGB_WHITE, BGB_HUE_RGB, BGB_DEFAULT
};

#endif /* TEXTATTR_H */

