#include "fdf.h"

void    exit_fdf(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_str);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	free_fdf(fdf);
	exit(0);
}

void reinit_fdf(t_fdf *fdf)
{
	fdf->key = 0;
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->img_wth = 1000;
	fdf->ptXdepart = 0;
	fdf->ptYdepart = 0;
	fdf->scal = 12;
	fdf->rel_z = 2;
	fdf->deg = 0;
	fdf->incli = 2;
  check_win_scale(fdf);
  fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
  fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
  fdf->color = 0xE628AB;
  calc_horizontal_x(fdf, fdf->color);
  calc_vertical_y(fdf, fdf->color);
  mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
}

void    move_map(int key, t_fdf *fdf)
{
 	if (key == 123)
		fdf->ptXdepart += fdf->scal;
	if (key == 124)
		fdf->ptXdepart -= fdf->scal;
	if (key == 125)
		fdf->ptYdepart -= fdf->scal;
	if (key == 126)
		fdf->ptYdepart += fdf->scal;
	if (fdf->ptXdepart + fdf->x_max > fdf->img_wth)
		fdf->img_wth += fdf->ptXdepart + fdf->x_max - fdf->img_wth;
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
	fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
	calc_horizontal_x(fdf, fdf->color);
	calc_vertical_y(fdf, fdf->color);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
}

void relief_fdf(int key, t_fdf *fdf)
{
    if (key == 32)
      fdf->rel_z -= 1;
    else
      fdf->rel_z += 1;
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
		calc_horizontal_x(fdf, fdf->color);
		calc_vertical_y(fdf, fdf->color);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
}

void    zoom_fdf(int key, t_fdf *fdf)
{
		fdf->key = 0;
		if (key == 69)
			fdf->scal += 1;
    else
			if (fdf->scal >= 1)
				fdf->scal -= 1;
    mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		coord_x_y(fdf);
		coord_max(fdf);
		coord_min(fdf);
		if (fdf->ptXdepart + fdf->x_max > fdf->img_wth)
			fdf->img_wth += fdf->ptXdepart + fdf->x_max - fdf->img_wth;
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
		calc_horizontal_x(fdf, fdf->color);
		calc_vertical_y(fdf, fdf->color);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
}

void    random_color(int key, t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->seed = fdf_random(fdf->color * key);
	fdf->color = int_to_color(fdf->seed + fdf->seed);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
	fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
	calc_horizontal_x(fdf, fdf->color);
	calc_vertical_y(fdf, fdf->color);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
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
	fdf->key = 38;
	while (i < 50)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
		calc_horizontal_x(fdf, fdf->color);
		calc_vertical_y(fdf, fdf->color);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
		mlx_do_sync(fdf->mlx_ptr);
		ft_sleep();
		i++;
	}
}
void rotation(int key, t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	if (key == 35)
		fdf->deg += 0.1;
	else
		fdf->deg -= 0.1;
	coord_x_y(fdf);
	coord_max(fdf);
	coord_min(fdf);
	if (fdf->ptXdepart + fdf->x_max > fdf->img_wth)
		fdf->img_wth += fdf->ptXdepart + fdf->x_max - fdf->img_wth;
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
	fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
	calc_horizontal_x(fdf, fdf->color);
	calc_vertical_y(fdf, fdf->color);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
}
float	rotate(t_fdf *fdf, float x, float y, int xoy)
{
	float	point;
	float	radian;

	radian = fdf->deg * 3.141 * 180;
	point = 0;
	if (xoy == 1)
		point = (x - fdf->nbpoints / 2) * cos(radian) -
			(y - fdf->nblines / 2) * sin(radian);
	else if (xoy == 0)
		point = (y - fdf->nblines / 2) * cos(radian) +
			(x - fdf->nbpoints / 2) * sin(radian);
	return (point);
}

void inclinate(int key, t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	if (key == 40)
	{
		if (fdf->incli < 8)
			fdf->incli += 0.1;
	}
	else
	{
		if (fdf->incli > 1)
			fdf->incli -= 0.1;
	}
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
	fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
	calc_horizontal_x(fdf, fdf->color);
	calc_vertical_y(fdf, fdf->color);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
}

void pogressiv_color(t_fdf *fdf, int z)
{
	int res;
	int color;
	int r;
	int g;
	int b;

	res = 0;
	color = 0;
	r = 0;
	g = 204;
	b = 0;
	if (fdf->key == 48)
	{
		res = z * 5;
		if (res > 0)
		{
			r = res - 204;
			if (r < 0)
				r = 0;
			if (r > 204)
				r = 204;
			g -= res/3;
			if (g < 0)
				g = 0;
		}
		else
		{
			res = -z * 3;
			b = 100 + res;
			if (res > 210)
				b = 210;
			g = 0;
		}
		fdf->color = (r << 16) + (g << 8) + b;
	}

}

int   key_fdf(int key, t_fdf *fdf)
{
	if (key == 53)
		exit_fdf(fdf);
	if (key == 76)
		reinit_fdf(fdf);
	if (key == 123 || key == 124 || key == 125 || key == 126)
		move_map(key, fdf);
	if (key == 78 || key == 69)
		zoom_fdf(key, fdf);
	if (key == 4)
		random_color(key, fdf);
	if (key == 38)
		epileptic_color(fdf);
	if (key == 32 || key == 34)
		relief_fdf(key, fdf);
	if (key == 31 || key == 35)
		rotation(key, fdf);
	if (key == 40 || key == 37)
		inclinate(key, fdf);
	if (key == 48)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->key = 48;
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
		calc_horizontal_x(fdf, fdf->color);
		calc_vertical_y(fdf, fdf->color);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
	}

	return (0);
}
