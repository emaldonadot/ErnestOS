#include "../include/kernel.h"

void kmain()
{
	clearScreen();
	scrollUp(25);
	c_print("===============================================================================\n",0x02);
	c_print("Welcome to Ernesto's OS\n",0x03);
	c_print("ErnestOS is an Operating System created for recreational  purpose\n", 0x04);
	c_print("Please enjoy the code to make this possible\n", 0x05);
	c_print("===============================================================================",0x06);

	c_print("\n\nThis is so crazy ;) ",0x07);

}
