/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:55:08 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 19:01:45 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	trace_x(t_env *fdf, int ratio, int updown, int rigthleft)
{
	int i;
	t_ipoint s;

	i = 0;
	ratio = (2 * fdf->d.y) - fdf->d.x;
	updown = 2 * (fdf->d.y - fdf->d.x);
	rigthleft = 2 * fdf->d.y;
	s = fdf->start;
	while (i < fdf->d.x)
	{
		if (ratio >= 0)
		{
			ratio = ratio + updown;
			fdf->start.y = fdf->start.y + fdf->inc.y;
		}
		else
			ratio = ratio + rigthleft;
		fdf->start.x = fdf->start.x + fdf->inc.x;
		if (fdf->start.y >= 0 && fdf->start.x >= 0 && (fdf->start.y
			* fdf->mlx.img_wth + fdf->start.x) < fdf->mlx.img_wth * HEIGHT)
			IMG_DATA[fdf->start.y * fdf->mlx.img_wth + fdf->start.x] = get_color(fdf->start, s, fdf->end, fdf->d);
		i++;
	}
}

void	trace_y(t_env *fdf, int ratio, int updown, int rigthleft)
{
	int 	i;
	t_ipoint s;

	i = 0;
	ratio = (2 * fdf->d.x) - fdf->d.y;
	rigthleft = 2 * (fdf->d.x - fdf->d.y);
	updown = 2 * fdf->d.x;
	s = fdf->start;
	while (i < fdf->d.y)
	{
		if (ratio >= 0)
		{
			ratio = ratio + rigthleft;
			fdf->start.x = fdf->start.x + fdf->inc.x;
		}
		else
			ratio = ratio + updown;
		fdf->start.y = fdf->start.y + fdf->inc.y;
		if (fdf->start.y >= 0 && fdf->start.x >= 0 && (fdf->start.y
			* fdf->mlx.img_wth + fdf->start.x) < fdf->mlx.img_wth * HEIGHT)
			IMG_DATA[fdf->start.y * fdf->mlx.img_wth + fdf->start.x] = get_color(fdf->start, s, fdf->end, fdf->d);
		i++;
	}
}

void	go_trace_it(t_env *fdf)
{
	int	ratio;
	int	rigthleft;
	int	updown;

	ratio = 0;
	rigthleft = 0;
	updown = 0;
	fdf->d.x = abs(fdf->end.x - fdf->start.x);
	fdf->d.y = abs(fdf->end.y - fdf->start.y);
	fdf->inc.x = (fdf->start.x < fdf->end.x) ? 1 : -1;
	fdf->inc.y = (fdf->start.y < fdf->end.y) ? 1 : -1;
	if (fdf->d.x > fdf->d.y)
		trace_x(fdf, ratio, updown, rigthleft);
	else
		trace_y(fdf, ratio, updown, rigthleft);
}

void	calc_horizontal_x(t_env *fdf)
{
	int		i;
	int		j;
	float	ang_x;
	float	ang_y;

	i = -1;
	while (++i < fdf->nblines)
	{
		j = -1;
		while (++j < fdf->nbpt[i] - 1)
		{
			ang_x = j;
			ang_y = i;
			rotate(fdf, &ang_x, &ang_y);
			fdf->start.x = iso_x(fdf, ang_x, ang_y) + fdf->dep.x;
			fdf->start.y = iso_y(fdf, ang_x, ang_y, fdf->map[i].pt[j].z)
			+ fdf->dep.y;
			ang_x = j + 1;
			ang_y = i;
			rotate(fdf, &ang_x, &ang_y);
			fdf->end.x = iso_x(fdf, ang_x, ang_y) + fdf->dep.x;
			fdf->end.y = iso_y(fdf, ang_x, ang_y, fdf->map[i].pt[j + 1].z)
			+ fdf->dep.y;
			fdf->start.color = default_color(fdf->map[i].pt[j].z, fdf);
			fdf->end.color = default_color(fdf->map[i].pt[j + 1].z, fdf);
			go_trace_it(fdf);
		}
	}
}

void	calc_vertical_y(t_env *fdf)
{
	int		y;
	int		j;
	float	ang_x;
	float	ang_y;

	y = -1;
	while (++y < fdf->nblines - 1)
	{
		j = -1;
		while (++j < fdf->nbpt[y])
		{
			ang_x = j;
			ang_y = y;
			rotate(fdf, &ang_x, &ang_y);
			fdf->start.x = iso_x(fdf, ang_x, ang_y) + fdf->dep.x;
			fdf->start.y = iso_y(fdf, ang_x, ang_y, fdf->map[y].pt[j].z)
			+ fdf->dep.y;
			ang_x = j;
			ang_y = y + 1;
			rotate(fdf, &ang_x, &ang_y);
			fdf->end.x = iso_x(fdf, ang_x, ang_y) + fdf->dep.x;
			fdf->end.y = iso_y(fdf, ang_x, ang_y, fdf->map[y + 1].pt[j].z)
			+ fdf->dep.y;
			fdf->start.color = default_color(fdf->map[y].pt[j].z, fdf);
			fdf->end.color = default_color(fdf->map[y + 1].pt[j].z, fdf);
			go_trace_it(fdf);
		}
	}
}
