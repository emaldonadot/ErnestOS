#include "../include/types.h"
#include "../include/string.h"

int strlen(string s) {
	int i = 1;
	while (s[i++]);
	return --i;
}

