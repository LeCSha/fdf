/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 16:38:40 by abaille           #+#    #+#             */
/*   Updated: 2018/07/18 16:38:42 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_map(int key, t_fdf *fdf)
{
	if (key == 123)
		fdf->depx += fdf->scal;
	if (key == 124)
		fdf->depx -= fdf->scal;
	if (key == 125)
		fdf->depy -= fdf->scal;
	if (key == 126)
		fdf->depy += fdf->scal;
	if (fdf->depx + fdf->x_max > fdf->img_wth)
		fdf->img_wth += fdf->depx + fdf->x_max - fdf->img_wth;
	key_draw(fdf);
}

void	relief_fdf(int key, t_fdf *fdf)
{
	if (key == 32)
		fdf->rel_z -= 1;
	else
		fdf->rel_z += 1;
	key_draw(fdf);
}

void	zoom_fdf(int key, t_fdf *fdf)
{
	if (key == 69)
		fdf->scal += 1;
	else
	{
		if (fdf->scal >= 1)
			fdf->scal -= 1;
	}
	coord_x_y(fdf);
	coord_max(fdf);
	coord_min(fdf);
	if (fdf->depx + fdf->x_max > fdf->img_wth)
		fdf->img_wth += fdf->depx + fdf->x_max - fdf->img_wth;
	key_draw(fdf);
}

void	rotation(int key, t_fdf *fdf)
{
	if (key == 35)
		fdf->deg += 0.1;
	else
		fdf->deg -= 0.1;
	coord_x_y(fdf);
	coord_max(fdf);
	coord_min(fdf);
	if (fdf->depx + fdf->x_max > fdf->img_wth)
		fdf->img_wth += fdf->depx + fdf->x_max - fdf->img_wth;
	key_draw(fdf);
}

int		key_fdf(int key, t_fdf *fdf)
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
	return (0);
}
