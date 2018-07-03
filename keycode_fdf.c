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
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->img_wth = 1000;
	fdf->ptXdepart = 0;
	fdf->ptYdepart = 0;
	fdf->scal = 12;
	fdf->rel_z = 2;
  check_win_scale(fdf);
  fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
  fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
  fdf->color = 0xE628AB;
  calc_horizontal_x(fdf, fdf->color);
  calc_vertical_y(fdf, fdf->color);
  mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 50, 0xFFD700, "ZOOM : ");
  mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
}

void    move_map(int key, t_fdf *fdf)
{
 	if (key == 123)
		fdf->moveX += fdf->scal;
	if (key == 124)
		fdf->moveX -= fdf->scal;
	if (key == 125)
		fdf->ptYdepart -= fdf->scal;
	if (key == 126)
		fdf->ptYdepart += fdf->scal;
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
	fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
	calc_horizontal_x(fdf, fdf->color);
	calc_vertical_y(fdf, fdf->color);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, fdf->moveX, fdf->moveY);
}

void relief_fdf(int key, t_fdf *fdf)
{
    if (key == 14)
      fdf->rel_z -= 1;
    else
      fdf->rel_z += 1;
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		coord_x_y(fdf);
    coord_max(fdf);
    coord_min(fdf);
		fdf->ptXdepart = fdf->img_wth / 2 - fdf->x_max / 2;
		fdf->ptYdepart = HEIGHT / 2 - (fdf->y_max - fdf->y_min) / 2;
		if ((fdf->ptYdepart + fdf->y_min) < 0)
			fdf->ptYdepart += abs(fdf->y_min);
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
		calc_horizontal_x(fdf, fdf->color);
		calc_vertical_y(fdf, fdf->color);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, fdf->moveX, fdf->moveY);
}

void    zoom_fdf(int key, t_fdf *fdf)
{
    if (key == 69)
        fdf->scal += 0.5;
    else
        fdf->scal -= 0.5;
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
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, fdf->moveX, fdf->moveY);
}

void    random_color(int key, t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	if (key == 76)
	{
		fdf->seed = fdf_random(fdf->color * key);
		fdf->color = int_to_color(fdf->seed + fdf->seed);
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
		calc_horizontal_x(fdf, fdf->color);
		calc_vertical_y(fdf, fdf->color);
	}
	else
	{
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
		calc_horizontal_x(fdf, 0);
		calc_vertical_y(fdf, 0);
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, fdf->moveX, fdf->moveY);
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
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
		fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
		calc_horizontal_x(fdf, 0);
		calc_vertical_y(fdf, 0);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, fdf->moveX, fdf->moveY);
		mlx_do_sync(fdf->mlx_ptr);
		ft_sleep();
		i++;
	}
}

// void	rotation(t_fdf *fdf, int xory)
// {
// 	// float	pt;
// 	float	radian;
// 	int i;
//
// 	radian = fdf->deg * 3.141 * 180;
// 	// pt = 0;
// 	if (xory == 1)
// 		pt = (x - fdf->nbpoints / 2) * cos(radian) -
// 			(y - e->len_y / 2) * sin(radian);
// 	else if (xory == 0)
// 		pt = (y - e->len_y / 2) * cos(radian) +
// 			(x - e->len_x / 2) * sin(radian);
// 	// return (pt);
// }

int   key_fdf(int key, t_fdf *fdf)
{
	if (key == 53)
		exit_fdf(fdf);
	if (key == 15)
		reinit_fdf(fdf);
	if (key == 123 || key == 124 || key == 125 || key == 126)
		move_map(key, fdf);
	if (key == 78 || key == 69)
		zoom_fdf(key, fdf);
	if (key == 76 || key == 0)
		random_color(key, fdf);
	if (key == 13)
		epileptic_color(fdf);
	if (key == 14 || key == 17)
		relief_fdf(key, fdf);
	return (0);
}
