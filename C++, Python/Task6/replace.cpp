#include"replace.h"
char redund[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ*";
void starReplace(char* src, int& repNum) {
	char* srcptr = src;
	while (*srcptr)
	{
		if (!isalpha(*srcptr) && *srcptr != '*') {
			++repNum;
			*srcptr = '*';
		}
		++srcptr;
	}
}

void starReplace_Two(char* src, int& repNum) {
	char* srcptrOne = src, * srcptrTwo = src;
	while (srcptrOne = strpbrk(srcptrOne, redund)) {
		for (;srcptrOne - srcptrTwo > 0; ++srcptrTwo) {
			++repNum;
			*srcptrTwo = '*';
		}
		++srcptrTwo;
		++srcptrOne;
	}
	while (*srcptrTwo) {
		++repNum;
		*(srcptrTwo++) = '*';
	}
	// use strpbrk to find redundant symbols between them
}