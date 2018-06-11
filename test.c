#include <stdio.h>
#include <time.h>
#include <limits.h>
int hex_to_dec(int color)
{
  int r_max;
  int b_max;
  int g_max;
	int colort[3];

  r_max = 255 << 16;
  g_max = 255 << 8;
  b_max = 255;
  colort[0] = (color & r_max) >> 16;
  colort[1] = (color & g_max) >> 8;
  colort[2] = color & b_max;
	printf("%d\n", colort[0]);
	printf("%d\n", colort[1]);
	printf("%d\n", colort[2]);
  return (0);
}
void	extract_rgb(long long testi, char rslt[3][3])
{
	int			i;
	int			j;

	i = 5;
	j = 1;
	rslt[0][2] = '\0';
	rslt[1][2] = '\0';
	rslt[2][2] = '\0';
	while (i >= 0)
	{
		if (i >= 4)
			rslt[2][j] = "0123456789ABCDEF"[testi % 16];
		else if (i >= 2)
			rslt[1][j] = "0123456789ABCDEF"[testi % 16];
		else if (i >= 0)
			rslt[0][j] = "0123456789ABCDEF"[testi % 16];
		testi /= 16;
		j--;
		if (j == -1)
			j = 1;
		i--;
	}
}
int fdf_random()
{
  time_t seed;
  int multi;
  int addi;
  int i;

  i = 0;
  multi = 46340;
  addi = 19435;
  seed = time(NULL);
	seed = (multi * seed + addi) % INT_MAX;
	if (seed < 0)
		return (-(int)seed);
  //hex_to_dec()
  return ((int)seed);
}
int		main(void)
{
	char	rslt[3][3];
	int a;
	int b;
	int c;
	a = fdf_random();
	printf("%d\n", a);
	hex_to_dec(a);
	extract_rgb(0x7d01c8, rslt);
	printf("%s%s%s\n", rslt[0], rslt[1], rslt[2]);
	fdf_random();
	return (0);
}
