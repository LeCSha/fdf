/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 16:38:40 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 17:44:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_draw(t_env *fdf)
{
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img->img_ptr);
	mlx_clear_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
	fdf->mlx.img->img_ptr = mlx_new_image(fdf->mlx.mlx_ptr, fdf->mlx.img_wth, HEIGHT);
	IMG_DATA = (int *)mlx_get_data_addr(fdf->mlx.img->img_ptr, &fdf->mlx.img->bpp,
	&fdf->mlx.img->size_l, &fdf->mlx.img->endian);
	calc_horizontal_x(fdf);
	calc_vertical_y(fdf);
	// draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr,
	fdf->mlx.img->img_ptr, 0, 0);
}

void	free_fdf(t_env *fdf)
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
	if (fdf->mlx.img)
	{
		free(fdf->mlx.img);
		fdf->mlx.img = NULL;
	}
}

void	exit_fdf(t_env *fdf)
{
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->mlx.img->img_ptr);
	mlx_clear_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
	mlx_clear_window(fdf->mlx.mlx_ptr, fdf->mlx.win_str);
	mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
	free_fdf(fdf);
	exit(0);
}

void	reinit_fdf(t_env *fdf)
{
	fdf->key = 0;
	fdf->mlx.img_wth = 1000;
	fdf->dep.x = 0;
	fdf->dep.y = 0;
	fdf->scal = 50;
	fdf->rel_z = 4;
	fdf->deg = 0;
	fdf->incli = 2;
	fdf->pal_ptr = &(fdf->pal)[0];
	check_win_scale(fdf);
	key_draw(fdf);
}
