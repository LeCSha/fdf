#include "fdf.h"

char *hex_to_dec(int color)
{
		char *hex;

		hex = malloc(sizeof(*hex) * 3);
		hex[0] = "0123456789ABCDEF"[color / 16];
		hex[1] = "0123456789ABCDEF"[color % 16];
		hex[2] = '\0';
		return (hex);
}

int int_to_color(unsigned int color)
{
  //int r_max;
  //int b_max;
  //int g_max;
	int r;
	int g;
	int b;
	int res;

  //r_max = 255 << 16;
  //g_max = 255 << 8;
  //b_max = 255;
	//r = (color & r_max) >> 16;
	//g = (color & g_max) >> 8;
	//b = color & b_max;
r = (color & 0xFF0000);
g = (color & 0xFF00);
b = color & 0xFF;
	/*res = r * g * b / 42;
	r = (res & r_max) >> 16;
	g = (res & g_max) >> 8;
	b = res & b_max;*/
	res = r + g + b;
	printf("RGB %i\n", res);
	return (res);
}

unsigned int fdf_random()
{
  time_t seed;
  int multi;
  int addi;

  multi = 65536;
  addi = 7483;
  seed = time(NULL);
	seed = (multi * seed + addi) % UINT_MAX;
	if (seed < 0)
		return (-(unsigned int)seed);
  return ((unsigned int)seed);
}
