#include "../include/screen.h"

int cursorX = 0, cursorY = 0;
const uint8 sw = 80,sh = 25,sd = 2; 
int color = 0x0F;

void clearLine (uint8 from, uint8 to) {
	int  i = sw * from * sd;
	string vidmem =(string)0xb8000;
	for (i; i< (sw*(to+1)*sd); i++)
		vidmem[i] = 0x0;
}

void updateCursor() {
	unsigned temp  = cursorY * sw + cursorX;
	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}

void clearScreen() {
	clearLine(0, sh-1);
	cursorX = 0;
	cursorY = 0;
	updateCursor();
}

void scrollUp(uint8 lineNumber) {
	string vidmem = (string)0xb8000;
	uint16 i =0;
	for(i;i<sw*(sh-1)*sd;i++){
		vidmem[i]=vidmem[i+sw*2*lineNumber];
	}
	clearLine(sh-1-lineNumber,sh-1);
	if((cursorY-lineNumber)<0)
		cursorY=cursorX=0;
	else
		cursorY-=lineNumber;

	updateCursor();
}

void newLineCheck(){
	if(cursorY>=sh-1)
		scrollUp(1);
}

void c_printch(char c, char color) {
	string vidmem= (string) 0xb8000;
	switch(c)
	{
	case (0x08):
		if(cursorX>0)
		{cursorX--; vidmem[(cursorY*sw+cursorX)*sd]=0x00;}
		break;
	case (0x09):
		cursorX=cursorX+8 &-(8-1);
		break;
	case ('\r'):
		cursorX=0;
		break;
	case ('\n'):
		cursorX=0;
		cursorY++;
	default:
		vidmem[((cursorY*sw+cursorX))*sd] = c;
		vidmem[((cursorY*sw+cursorX))*sd+1]= color;
		cursorX++;
		break;
	}
	if(cursorX>=sw)
	{
		cursorX=0;
		cursorY++;
	}
	newLineCheck();
	updateCursor();

}

void printch(char c) {
	c_printch(c, 0x0F);
}

void c_print(string ch, char color) {
	uint16 i = 0;
	for (i;i<strlen(ch);i++)
		c_printch(ch[i],color);
}

void print(string ch) {
	uint16 i =0;
	for (i;i<strlen(ch);i++)
		printch(ch[i]);
}

