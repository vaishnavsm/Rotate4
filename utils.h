#ifndef ROT4_UTILS
#define ROT4_UTILS

#include "string"
#include "windows.h"

void initutils(void);
bool wincheck(int state[8][8]);
void putBlockLine();
void putHalfBlockLine(bool);
void setCursor(const int,const int);
void setColor(WORD);
void addspaces();

#endif
