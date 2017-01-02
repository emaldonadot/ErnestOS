#ifndef SCREEN_H
#define SCREEN_H

#include "system.h"
#include "string.h"

int cursorX, cursorY;
const uint8 sw, sh, sd;

void clearLine (uint8 from, uint8 to);

void updateCursor();

void clearScreen();

void scrollUp(uint8 lineNumber);

void newLineCheck();

void c_printch(char c, char color);

void printch(char c);

void c_print(string ch, char color);

void print(string ch);

#endif
