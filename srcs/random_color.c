/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 17:03:08 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 19:00:15 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	lightn(int start, int end, double perc)
{
	return ((int)((1 - perc) * start + perc * end));
}

double	get_percentage(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int	get_color(t_ipoint current, t_ipoint start, t_ipoint end, t_ipoint delta)
{
	int		red;
	int		green;
	int		blue;
	double	perc;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		perc = get_percentage(start.x, end.x, current.x);
	else
		perc = get_percentage(start.y, end.y, current.y);
	red = lightn((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, perc);
	green = lightn((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, perc);
	blue = lightn(start.color & 0xFF, end.color & 0xFF, perc);
	return ((red << 16) | (green << 8) | blue);
}

int	default_color(int z, t_env *fdf)
{
	double	perc;

	perc = get_percentage(fdf->min.z, fdf->max.z, z);
	if (perc < 0.3)
		return (fdf->pal_ptr->color[0]);
	else if (perc < 0.7)
		return (fdf->pal_ptr->color[1]);
	else
		return (fdf->pal_ptr->color[2]);
}
