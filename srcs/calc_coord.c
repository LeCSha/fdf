/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_coord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:08:51 by abaille           #+#    #+#             */
/*   Updated: 2018/07/18 15:08:53 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	coord_x_y(t_fdf *fdf)
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
		while (j < fdf->nbpoints)
		{
			ang_x = rotate(fdf, j, i, 1);
			ang_y = rotate(fdf, j, i, 0);
			fdf->map[i].pt[j].x = iso_x(fdf, ang_x, ang_y);
			fdf->map[i].pt[j].y = iso_y(fdf, ang_x,
				ang_y, fdf->map[i].pt[j].z);
			j++;
		}
		i++;
	}
}

void	coord_max(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	fdf->x_max = fdf->map[0].pt[0].x;
	fdf->y_max = fdf->map[0].pt[0].y;
	fdf->z_max = fdf->map[0].pt[0].z;
	while (i < fdf->nblines)
	{
		j = 0;
		while (j < fdf->nbpoints)
		{
			if (fdf->x_max < fdf->map[i].pt[j].x)
				fdf->x_max = fdf->map[i].pt[j].x;
			if (fdf->z_max < fdf->map[i].pt[j].z)
				fdf->z_max = fdf->map[i].pt[j].z;
			if (fdf->y_max < fdf->map[i].pt[j].y)
				fdf->y_max = fdf->map[i].pt[j].y;
			j++;
		}
		i++;
	}
}

void	coord_min(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	fdf->x_min = fdf->map[0].pt[0].x;
	fdf->y_min = fdf->map[0].pt[0].y;
	fdf->z_min = fdf->map[0].pt[0].z;
	while (i < fdf->nblines)
	{
		j = 0;
		while (j < fdf->nbpoints)
		{
			if (fdf->x_min > fdf->map[i].pt[j].x)
				fdf->x_min = fdf->map[i].pt[j].x;
			if (fdf->z_min > fdf->map[i].pt[j].z)
				fdf->z_min = fdf->map[i].pt[j].z;
			if (fdf->y_min > fdf->map[i].pt[j].y)
				fdf->y_min = fdf->map[i].pt[j].y;
			j++;
		}
		i++;
	}
}

void	res_z(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->nblines)
	{
		j = 0;
		while (j < fdf->nbpoints)
		{
			fdf->map[i].pt[j].z = fdf->map[i].pt[j].z / 5;
			j++;
		}
		i++;
	}
}

void	calcul_coord(t_fdf *fdf)
{
	coord_x_y(fdf);
	coord_max(fdf);
	coord_min(fdf);
}
