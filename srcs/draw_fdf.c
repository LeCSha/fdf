/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:55:08 by abaille           #+#    #+#             */
/*   Updated: 2018/07/18 14:49:47 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	trace_x(t_fdf *fdf, int ratio, int updown, int rigthleft)
{
	int i;

	i = 0;
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
		if (fdf->starty >= 0 && fdf->startx >= 0 && (fdf->starty
			* fdf->img_wth + fdf->startx) < fdf->img_wth * HEIGHT)
			IMG_DATA[fdf->starty * fdf->img_wth + fdf->startx] = fdf->color;
		i++;
	}
}

void	trace_y(t_fdf *fdf, int ratio, int updown, int rigthleft)
{
	int i;

	i = 0;
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
		if (fdf->starty >= 0 && fdf->startx >= 0 && (fdf->starty
			* fdf->img_wth + fdf->startx) < fdf->img_wth * HEIGHT)
			IMG_DATA[fdf->starty * fdf->img_wth + fdf->startx] = fdf->color;
		i++;
	}
}

void	go_trace_it(t_fdf *fdf)
{
	int	ratio;
	int	rigthleft;
	int	updown;

	ratio = 0;
	rigthleft = 0;
	updown = 0;
	fdf->dx = fdf->endx - fdf->startx;
	fdf->dy = fdf->endy - fdf->starty;
	fdf->xinc = (fdf->dx > 0) ? 1 : -1;
	fdf->yinc = (fdf->dy > 0) ? 1 : -1;
	fdf->dx = abs(fdf->dx);
	fdf->dy = abs(fdf->dy);
	if (fdf->starty >= 0 && fdf->startx >= 0 && (fdf->starty
		* fdf->img_wth + fdf->startx) < fdf->img_wth * HEIGHT)
		IMG_DATA[fdf->starty * fdf->img_wth + fdf->startx] = fdf->color;
	if (fdf->dx > fdf->dy)
		trace_x(fdf, ratio, updown, rigthleft);
	else
		trace_y(fdf, ratio, updown, rigthleft);
}

void	calc_horizontal_x(t_fdf *fdf)
{
	int		i;
	int		j;
	float	ang_x;
	float	ang_y;

	i = -1;
	while (++i < fdf->nblines)
	{
		j = -1;
		while (++j < fdf->nbpoints - 1)
		{
			ang_x = rotate(fdf, j, i, 1);
			ang_y = rotate(fdf, j, i, 0);
			fdf->startx = iso_x(fdf, ang_x, ang_y) + fdf->depx;
			fdf->starty = iso_y(fdf, ang_x, ang_y, fdf->map[i].pt[j].z)
			+ fdf->depy;
			ang_x = rotate(fdf, j + 1, i, 1);
			ang_y = rotate(fdf, j + 1, i, 0);
			fdf->endx = iso_x(fdf, ang_x, ang_y) + fdf->depx;
			fdf->endy = iso_y(fdf, ang_x, ang_y, fdf->map[i].pt[j + 1].z)
			+ fdf->depy;
			multicolor(fdf, j, i);
			go_trace_it(fdf);
		}
	}
}

void	calc_vertical_y(t_fdf *fdf)
{
	int		i;
	int		j;
	float	ang_x;
	float	ang_y;

	i = -1;
	while (++i < fdf->nblines - 1)
	{
		j = -1;
		while (++j < fdf->nbpoints)
		{
			ang_x = rotate(fdf, j, i, 1);
			ang_y = rotate(fdf, j, i, 0);
			fdf->startx = iso_x(fdf, ang_x, ang_y) + fdf->depx;
			fdf->starty = iso_y(fdf, ang_x, ang_y, fdf->map[i].pt[j].z)
			+ fdf->depy;
			ang_x = rotate(fdf, j, i + 1, 1);
			ang_y = rotate(fdf, j, i + 1, 0);
			fdf->endx = iso_x(fdf, ang_x, ang_y) + fdf->depx;
			fdf->endy = iso_y(fdf, ang_x, ang_y, fdf->map[i + 1].pt[j].z)
			+ fdf->depy;
			multicolor(fdf, j, i);
			go_trace_it(fdf);
		}
	}
}
