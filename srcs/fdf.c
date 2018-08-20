/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:08:51 by abaille           #+#    #+#             */
/*   Updated: 2018/07/18 15:08:53 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*init_fdf(void)
{
	t_fdf *new;

	if (!(new = (t_fdf *)malloc(sizeof(t_fdf))))
		return (NULL);
	new->map = NULL;
	new->img_wth = 1000;
	new->scal = 50;
	new->dx = 0;
	new->dy = 0;
	new->startx = 0;
	new->starty = 0;
	new->endx = 0;
	new->endy = 0;
	new->xinc = 0;
	new->yinc = 0;
	new->depx = 0;
	new->depy = 0;
	new->nblines = 0;
	new->seed = 0;
	new->rel_z = 4;
	new->deg = 0;
	new->incli = 2;
	return (new);
}

void	check_win_scale(t_fdf *fdf)
{
	int z_max;

	z_max = 0;
	calcul_coord(fdf);
	z_max = abs(fdf->z_min) > abs(fdf->z_max)
	? abs(fdf->z_min) : abs(fdf->z_max);
	while (z_max > 100)
	{
		res_z(fdf);
		calcul_coord(fdf);
	}
	while ((fdf->x_max + abs(fdf->x_min) >= fdf->img_wth ||
				fdf->y_max - fdf->y_min > HEIGHT) && fdf->scal >= 0)
	{
		fdf->scal -= 2;
		calcul_coord(fdf);
	}
	fdf->depx = (fdf->img_wth / 2 - fdf->x_max / 2)
	+ fdf->nbpoints * fdf->scal / 2;
	if (fdf->depx + fdf->x_max > WIDTH)
		fdf->depx -= fdf->depx + fdf->x_max - WIDTH;
	fdf->depy = HEIGHT / 2 - (fdf->y_max - fdf->y_min) / 2;
	if ((fdf->depy + fdf->y_min) < 0)
		fdf->depy += abs(fdf->y_min);
}

void	put_string(t_fdf *fdf)
{
	void *win;

	win = mlx_new_window(fdf->mlx_ptr, 330, 355, "Keycode");
	mlx_string_put(fdf->mlx_ptr, win, 20, 40, 0x2EDD17, "Author: abaille");
	mlx_string_put(fdf->mlx_ptr, win, 20, 65, 0x2EDD17, "Zoom: [+][-]");
	mlx_string_put(fdf->mlx_ptr, win,
		20, 90, 0x2EDD17, "Move: [UP][DOWN][LEFT][RIGHT]");
	mlx_string_put(fdf->mlx_ptr, win,
		20, 115, 0x2EDD17, "Increase top: [U][I]");
	mlx_string_put(fdf->mlx_ptr, win, 20, 140, 0x2EDD17, "Rotate: [O][P]");
	mlx_string_put(fdf->mlx_ptr, win, 20, 165, 0x2EDD17, "Inclinate: [K][L]");
	mlx_string_put(fdf->mlx_ptr, win, 20, 215, 0x2EDD17, "Random colors: [J]");
	mlx_string_put(fdf->mlx_ptr, win, 20, 240, 0x2EDD17, "Change color: [H]");
	mlx_string_put(fdf->mlx_ptr, win, 20, 290, 0x2EDD17, "Reset: [Entr]");
	mlx_string_put(fdf->mlx_ptr, win, 20, 315, 0x2EDD17, "Exit: [ESC]");
	fdf->win_str = win;
}

void	launch_fdf(char *av)
{
	t_fdf *fdf;

	fdf = NULL;
	check_file(av);
	if (!(fdf = init_fdf()))
		print_error(6, fdf, 1);
	ft_open(av, fdf);
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "fdf 42");
	check_win_scale(fdf);
	if (!(fdf->img = (t_mlx_img *)malloc(sizeof(t_mlx_img))))
		print_error(6, fdf, 0);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
	IMG_DATA = (int *)mlx_get_data_addr(fdf->img->img_ptr,
		&fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
	fdf->color = 0x6501de;
	calc_horizontal_x(fdf);
	calc_vertical_y(fdf);
	put_string(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr,
		fdf->win_ptr, fdf->img->img_ptr, 0, 0);
	mlx_key_hook(fdf->win_ptr, key_fdf, fdf);
	mlx_key_hook(fdf->win_str, key_fdf, fdf);
	mlx_loop(fdf->mlx_ptr);
}

int		main(int ac, char **argv)
{
	if (ac != 2)
		print_error(5, NULL, 1);
	launch_fdf(argv[1]);
	return (0);
}
