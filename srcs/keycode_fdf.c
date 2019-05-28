/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 16:38:40 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 10:17:54 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_map(int key, t_env *fdf)
{
	if (key == 123)
		fdf->dep.x += fdf->scal;
	if (key == 124)
		fdf->dep.x -= fdf->scal;
	if (key == 125)
		fdf->dep.y -= fdf->scal;
	if (key == 126)
		fdf->dep.y += fdf->scal;
	if (fdf->dep.x + fdf->max.x > fdf->mlx.img_wth)
		fdf->mlx.img_wth += fdf->dep.x + fdf->max.x - fdf->mlx.img_wth;
	key_draw(fdf);
}

void	relief_fdf(int key, t_env *fdf)
{
	if (key == 32)
		fdf->rel_z -= 0.1;
	else
		fdf->rel_z += 0.1;
	key_draw(fdf);
}

void	zoom_fdf(int key, t_env *fdf)
{
	if (key == 46)
		fdf->scal += 0.1;
	else
	{
		if (fdf->scal >= 0.1)
			fdf->scal -= 0.1;
	}
	calcul_coord(fdf);
	if (fdf->dep.x + fdf->max.x > fdf->mlx.img_wth)
		fdf->mlx.img_wth += fdf->dep.x + fdf->max.x - fdf->mlx.img_wth;
	key_draw(fdf);
}

void	rotation(int key, t_env *fdf)
{
	if (key == 35)
		fdf->deg += 0.1;
	else
		fdf->deg -= 0.1;
	calcul_coord(fdf);
	if (fdf->dep.x + fdf->max.x > fdf->mlx.img_wth)
		fdf->mlx.img_wth += fdf->dep.x + fdf->max.x - fdf->mlx.img_wth;
	key_draw(fdf);
}

int		key_fdf(int key, t_env *fdf)
{
	if (key == 53)
		exit_fdf(fdf);
	if (key == 76)
		reinit_fdf(fdf);
	if (key == 123 || key == 124 || key == 125 || key == 126)
		move_map(key, fdf);
	if (key == 45 || key == 46)
		zoom_fdf(key, fdf);
	if (key == 4)
	{
		fdf->icolor > 3 ? fdf->icolor = 0 : fdf->icolor++;
		fdf->pal_ptr = &(fdf->pal)[fdf->icolor];
		key_draw(fdf);
	}
	if (key == 32 || key == 34)
		relief_fdf(key, fdf);
	if (key == 31 || key == 35)
		rotation(key, fdf);
	if (key == 40 || key == 37)
		inclinate(key, fdf);
	return (0);
}
