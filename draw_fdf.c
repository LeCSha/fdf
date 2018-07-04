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
	if (fdf->starty >= 0 && fdf->startx >= 0 && (fdf->starty * fdf->img_wth + fdf->startx) < fdf->img_wth * HEIGHT)
		fdf->img->data[fdf->starty * fdf->img_wth + fdf->startx] = color;
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
			if (fdf->starty >= 0 && fdf->startx >= 0 && (fdf->starty * fdf->img_wth + fdf->startx) < fdf->img_wth * HEIGHT)
				fdf->img->data[fdf->starty * fdf->img_wth + fdf->startx] = color;
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
			if (fdf->starty >= 0 && fdf->startx >= 0 && (fdf->starty * fdf->img_wth + fdf->startx) < fdf->img_wth * HEIGHT)
				fdf->img->data[fdf->starty * fdf->img_wth + fdf->startx] = color;
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

float		coord_x(t_fdf *fdf, float x, float y)
{
	return ((x + y) * fdf->scal);
}

float		coord_y(t_fdf *fdf, float x, float y, float z)
{
	return (fdf->scal * y - (fdf->scal * x) / fdf->incli - z * fdf->rel_z * 0.82);
}

void	calc_horizontal_x(t_fdf *fdf, int color)
{
	int i;
	int j;
	float ang_x;
	float ang_y;

	i = -1;
	ang_x = 0;
	ang_y = 0;
	while (++i < fdf->nblines)
	{
		j = -1;
		while (++j < fdf->nbpoints - 1)
		{
			ang_x = rotate(fdf, j, i, 1);
			ang_y = rotate(fdf, j, i, 0);
			fdf->startx = coord_x(fdf, ang_x, ang_y) + fdf->ptXdepart;
			fdf->starty = coord_y(fdf, ang_x, ang_y, fdf->map[i].point[j].z) + fdf->ptYdepart;
			ang_x = rotate(fdf, j + 1, i, 1);
			ang_y = rotate(fdf, j + 1, i, 0);
			fdf->endx = coord_x(fdf, ang_x, ang_y) + fdf->ptXdepart;
			fdf->endy = coord_y(fdf, ang_x, ang_y, fdf->map[i].point[j + 1].z) + fdf->ptYdepart;
			pogressiv_color(fdf, fdf->map[i].point[j].z);
			multicolor(fdf, j, i);
			// if (color == 0)
			// {
			// 	fdf->seed = fdf_random(fdf->color);
			// 	fdf->color = int_to_color(fdf->seed * (i + j + fdf->color));
			// 	draw_base_line(fdf, fdf->color);
			// }
			// else
			color = fdf->color;
			draw_base_line(fdf, color);
		}
	}
}

void	calc_vertical_y(t_fdf *fdf, int color)
{
	int i;
	int j;
	float ang_x;
	float ang_y;
	int nbp;
	int nbl;

	i = -1;
	ang_x = 0;
	ang_y = 0;
	nbp = 0;
	nbl = 0;
	while (++i < fdf->nblines - 1)
	{
		j = -1;
		while (++j < fdf->nbpoints)
		{
			ang_x = rotate(fdf, j, i, 1);
			ang_y = rotate(fdf, j, i, 0);
			fdf->startx = coord_x(fdf, ang_x, ang_y) + fdf->ptXdepart;
			fdf->starty = coord_y(fdf, ang_x, ang_y, fdf->map[i].point[j].z) + fdf->ptYdepart;
			ang_x = rotate(fdf, j, i + 1, 1);
			ang_y = rotate(fdf, j, i + 1, 0);
			fdf->endx = coord_x(fdf, ang_x, ang_y) + fdf->ptXdepart;
			fdf->endy = coord_y(fdf, ang_x, ang_y, fdf->map[i + 1].point[j].z) + fdf->ptYdepart;
			pogressiv_color(fdf, fdf->map[i + 1].point[j].z);
			multicolor(fdf, j, i);
			color = fdf->color;
			draw_base_line(fdf, color);
			// if (color == 0)
			// {
			// 	fdf->seed = fdf_random(fdf->color);
			// 	fdf->color = int_to_color(fdf->seed * (i + j + fdf->color));
			// 	draw_base_line(fdf, fdf->color);
			// }
			// else
			// 	draw_base_line(fdf, color);
		}
	}
}
