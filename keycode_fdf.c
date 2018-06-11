#include "fdf.h"

int hex_to_dec(long long color, t_fdf *fdf)
{
  int r_max;
  int b_max;
  int g_max;

  r_max = 255 >> 16;
  g_max = 255 >> 8;
  b_max = 255;
  fdf->color[0] = (color & r_max) >> 16;
  fdf->color[1] = (color & g_max) >> 8;
  fdf->color[2] = color & b_max;
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

void    exit_fdf(t_fdf *fdf)
{
    mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
    mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
    exit(0);
}

void    zoom_fdf(int key, t_fdf *fdf)
{
    if (key == 69)
    {
        fdf->scalx += 0.5;
        fdf->scaly += 0.5;
        mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
        calc_horizontal_x(&(*fdf));
        calc_vertical_y(&(*fdf));
    }
    else
    {
        fdf->scalx -= 0.5;
        fdf->scaly -= 0.5;
        mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
        calc_horizontal_x(&(*fdf));
        calc_vertical_y(&(*fdf));
    }
}

int   key_fdf(int key, t_fdf *fdf)
{
    if (key == 53)
        exit_fdf(fdf);
    if (key == 78 || key == 69)
        zoom_fdf(key, &(*fdf));
    if (key == 76)
        fdf_random();
    return (0);
}
