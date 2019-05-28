/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_coord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:08:51 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 13:52:57 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	coord_x_y(t_env *fdf)
{
	int		i;
	int		j;
	float	ang_x;
	float	ang_y;

	i = 0;
	ang_x = 0;
	ang_y = 0;
	while (i < fdf->nblines)
	{
		j = 0;
		while (j < fdf->nbpt[i])
		{
			ang_x = j;
			ang_y = i;
			rotate(fdf, &ang_x, &ang_y);
			fdf->map[i].pt[j].x = iso_x(fdf, ang_x, ang_y);
			fdf->map[i].pt[j].y = iso_y(fdf, ang_x,
				ang_y, fdf->map[i].pt[j].z);
			j++;
		}
		i++;
	}
}

static void	coord_max(t_env *fdf)
{
	int i;
	int j;

	i = -1;
	fdf->max.x = fdf->map[0].pt[0].x;
	fdf->max.y = fdf->map[0].pt[0].y;
	fdf->max.z = fdf->map[0].pt[0].z;
	while (++i < fdf->nblines)
	{
		j = -1;
		while (++j < fdf->nbpt[i])
		{
			fdf->max.x < fdf->map[i].pt[j].x ? fdf->max.x = fdf->map[i].pt[j].x : 0;
			fdf->max.z < fdf->map[i].pt[j].z ? fdf->max.z = fdf->map[i].pt[j].z : 0;
			fdf->max.y < fdf->map[i].pt[j].y ? fdf->max.y = fdf->map[i].pt[j].y : 0;
		}
	}
}

static void	coord_min(t_env *fdf)
{
	int i;
	int j;

	i = -1;
	fdf->min.x = fdf->map[0].pt[0].x;
	fdf->min.y = fdf->map[0].pt[0].y;
	fdf->min.z = fdf->map[0].pt[0].z;
	while (++i < fdf->nblines)
	{
		j = -1;
		while (++j < fdf->nbpt[i])
		{
			fdf->min.x > fdf->map[i].pt[j].x ? fdf->min.x = fdf->map[i].pt[j].x : 0;
			fdf->min.z > fdf->map[i].pt[j].z ? fdf->min.z = fdf->map[i].pt[j].z : 0;
			fdf->min.y > fdf->map[i].pt[j].y ? fdf->min.y = fdf->map[i].pt[j].y : 0;
		}
	}
}

void	calcul_coord(t_env *fdf)
{
	coord_x_y(fdf);
	coord_max(fdf);
	coord_min(fdf);
}
