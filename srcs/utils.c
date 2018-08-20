/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 16:38:40 by abaille           #+#    #+#             */
/*   Updated: 2018/07/18 16:38:42 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_draw(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
	IMG_DATA = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp,
	&fdf->img->size_l, &fdf->img->endian);
	calc_horizontal_x(fdf);
	calc_vertical_y(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
	fdf->img->img_ptr, 0, 0);
}

void	free_fdf(t_fdf *fdf)
{
	int i;

	i = 0;
	if (fdf->map)
	{
		while (i < fdf->nblines)
		{
			if (fdf->map[i].pt)
			{
				free(fdf->map[i].pt);
				fdf->map[i].pt = NULL;
			}
			i++;
		}
		free(fdf->map);
		fdf->map = NULL;
	}
	if (fdf->img)
	{
		free(fdf->img);
		fdf->img = NULL;
	}
	free(fdf);
	fdf = NULL;
}

void	exit_fdf(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_str);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	free_fdf(fdf);
	exit(0);
}

void	reinit_fdf(t_fdf *fdf)
{
	fdf->key = 0;
	fdf->img_wth = 1000;
	fdf->depx = 0;
	fdf->depy = 0;
	fdf->scal = 50;
	fdf->rel_z = 4;
	fdf->deg = 0;
	fdf->incli = 2;
	fdf->color = 0x6501de;
	check_win_scale(fdf);
	key_draw(fdf);
}
