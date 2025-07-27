#include <math.h>
#include "r32m.h"

static unsigned long int iu = 0, iuhold = 0, mult = 663608941l;



void rnrest(void)
{
	rninit(iuhold);
}

void rnconst(unsigned long int multnew)
{
	int rest = multnew % 8;
	if ((rest != 5) && (rest != 3))
		mult = multnew - rest + 5;
	else
		mult = multnew;
}

unsigned long int rnlast(void)
{
	return (iu);
}

unsigned long int rnfirst(void)
{
	return (iuhold);
}
