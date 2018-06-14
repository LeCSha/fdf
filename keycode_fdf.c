#include "fdf.h"

void    exit_fdf(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	exit(0);
}

void    move_map(int key, t_fdf *fdf)
{
	if (key == 123)
		fdf->ptXdepart += 10;
	if (key == 124)
		fdf->ptXdepart -= 10;
	if (key == 125)
		fdf->ptYdepart -= 10;
	if (key == 126)
		fdf->ptYdepart += 10;
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	calc_horizontal_x(fdf, fdf->color);
	calc_vertical_y(fdf, fdf->color); 
}

void    zoom_fdf(int key, t_fdf *fdf)
{
	if (key == 69)
	{
		fdf->scalx += 0.5;
		fdf->scaly += 0.5;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		calc_horizontal_x(fdf, fdf->color);
		calc_vertical_y(fdf, fdf->color);
	}
	else
	{
		fdf->scalx -= 0.5;
		fdf->scaly -= 0.5;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		calc_horizontal_x(fdf, fdf->color);
		calc_vertical_y(fdf, fdf->color);
 
	}
}

void    random_color(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->seed = fdf_random(fdf->color);
	fdf->color = int_to_color(fdf->seed);
	calc_horizontal_x(fdf, fdf->color);
	calc_vertical_y(fdf, fdf->color);
}

void    ft_sleep()
{
	int i;

	i = 0;
	while (i < 100000000)
		i++;
}

void    epileptic_color(t_fdf *fdf)
{
	int i;
	
	i = 0;
	while (i < 70)
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->seed = fdf_random(fdf->color);
		int color = fdf_random(fdf->seed);
		fdf->color = int_to_color(fdf->seed);
		calc_horizontal_x(fdf, color);
		calc_vertical_y(fdf, color);
		mlx_do_sync(fdf->mlx_ptr);
		ft_sleep();
		i++;
	}
}


int   key_fdf(int key, t_fdf *fdf)
{
	int i;

	i = 0;
	if (key == 53)
		exit_fdf(fdf);
	if (key == 123 || key == 124 || key == 125 || key == 126)
		move_map(key, fdf);
	if (key == 78 || key == 69)
		zoom_fdf(key, fdf);
	if (key == 76)
		random_color(fdf);
	if (key == 13)
		epileptic_color(fdf);
	return (0);
}
