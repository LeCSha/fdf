#include "fdf.h"

int int_to_color(unsigned int color)
{
	int r;
	int g;
	int b;
	int res;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = color & 0xFF;
	res = (r << 16) + (g << 8) + b;
	return (res);
}

unsigned int fdf_random(int seed)
{
	time_t tmp;

  int multi;
  int addi;

	if (seed == 0)
	{
		tmp = time(NULL);
		seed = tmp;
	}
	else
		tmp = seed;
  multi = 45878;
  addi = 7483;
	seed = (multi * tmp + addi) % INT_MAX;
  return ((unsigned int)seed);
}
