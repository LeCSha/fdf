/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:55:08 by abaille           #+#    #+#             */
/*   Updated: 2018/07/01 17:55:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	go_trace_it(t_fdf *fdf, int color)
{
	int	ratio;
	int	rigthleft;
	int	updown;
	int	i;

	i = 0;
	if (fdf->starty >= 0 && fdf->startx >= 0)
		fdf->img->data[fdf->starty * fdf->win_width + fdf->startx] = color;
	if (fdf->dx > fdf->dy)
	{
		ratio = (2 * fdf->dy) - fdf->dx;
		updown = 2 * (fdf->dy - fdf->dx);
		rigthleft = 2 * fdf->dy;
		while (i < fdf->dx)
		{
			if (ratio >= 0)
			{
				ratio = ratio + updown;
				fdf->starty = fdf->starty + fdf->yinc;
			}
			else
				ratio = ratio + rigthleft;
			fdf->startx = fdf->startx + fdf->xinc;
			if (fdf->starty >= 0 && fdf->startx >= 0)
				fdf->img->data[fdf->starty * fdf->win_width + fdf->startx] = color;
			i++;
		}
	}
	else
	{
		ratio = (2 * fdf->dx) - fdf->dy;
		rigthleft = 2 * (fdf->dx - fdf->dy);
		updown = 2 * fdf->dx;
		while (i < fdf->dy)
		{
			if (ratio >= 0)
			{
				ratio = ratio + rigthleft;
				fdf->startx = fdf->startx + fdf->xinc;
			}
			else
				ratio = ratio + updown;
			fdf->starty = fdf->starty + fdf->yinc;
			if (fdf->starty >= 0 && fdf->startx >= 0)
				fdf->img->data[fdf->starty * fdf->win_width + fdf->startx] = color;
			i++;
		}
	}
}

void	draw_base_line(t_fdf *fdf, int color)
{
	fdf->dx = fdf->endx - fdf->startx;
	fdf->dy = fdf->endy - fdf->starty;
	fdf->xinc = (fdf->dx > 0) ? 1 : -1;
	fdf->yinc = (fdf->dy > 0) ? 1 : -1;
	fdf->dx = abs(fdf->dx);
	fdf->dy = abs(fdf->dy);
	go_trace_it(fdf, color);
}

int		coord_x(t_fdf *fdf, int x, int y)
{
	return ((x + y) * fdf->scal);
}

int		coord_y(t_fdf *fdf, int x, int y, int z)
{
	return (fdf->scal * y - (fdf->scal * x) / 2 - z * fdf->rel_z);
}

void	calc_horizontal_x(t_fdf *fdf, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < fdf->nblines)
	{
		j = -1;
		while (++j < fdf->nbpoints - 1)
		{
			fdf->startx = coord_x(fdf, j, i) + fdf->ptXdepart;
			fdf->starty = coord_y(fdf, j, i, fdf->map[i].point[j].z) + fdf->ptYdepart;
			fdf->endx = coord_x(fdf, j + 1, i) + fdf->ptXdepart;
			fdf->endy = coord_y(fdf, j + 1, i, fdf->map[i].point[j + 1].z) + fdf->ptYdepart;
			if (color == 0)
			{
				fdf->seed = fdf_random(fdf->color);
				fdf->color = int_to_color(fdf->seed * (i + j));
				draw_base_line(fdf, fdf->color);
			}
			else
				draw_base_line(fdf, color);
		}
		i++;
	}
}

void	calc_vertical_y(t_fdf *fdf, int color)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->nblines - 1)
	{
		j = -1;
		while (++j < fdf->nbpoints)
		{
			fdf->startx = coord_x(fdf, j, i) + fdf->ptXdepart;
			fdf->starty = coord_y(fdf, j, i, fdf->map[i].point[j].z) + fdf->ptYdepart;
			fdf->endx = coord_x(fdf, j, i + 1) + fdf->ptXdepart;
			fdf->endy = coord_y(fdf, j, i + 1, fdf->map[i + 1].point[j].z) + fdf->ptYdepart;
			if (color == 0)
			{
				fdf->seed = fdf_random(fdf->color);
				fdf->color = int_to_color(fdf->seed * (i + j));
				draw_base_line(fdf, fdf->color);
			}
			else
				draw_base_line(fdf, color);
		}
		i++;
	}
}
