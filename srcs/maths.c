/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 17:03:08 by abaille           #+#    #+#             */
/*   Updated: 2018/07/18 17:03:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float			iso_x(t_fdf *fdf, float x, float y)
{
	return ((x + y) * fdf->scal);
}

float			iso_y(t_fdf *fdf, float x, float y, float z)
{
	return (fdf->scal * y - (fdf->scal * x) / fdf->incli - z
	* fdf->rel_z * 0.82);
}

float			rotate(t_fdf *fdf, float x, float y, int xoy)
{
	float	point;
	float	radian;

	radian = fdf->deg * 3.141 * 180;
	point = 0;
	if (xoy == 1)
		point = (x - fdf->nbpoints / 2) * cos(radian) -
			(y - fdf->nblines / 2) * sin(radian);
	else if (xoy == 0)
		point = (y - fdf->nblines / 2) * cos(radian) +
			(x - fdf->nbpoints / 2) * sin(radian);
	return (point);
}

void			inclinate(int key, t_fdf *fdf)
{
	if (key == 40)
	{
		if (fdf->incli < 8)
			fdf->incli += 0.1;
	}
	else
	{
		if (fdf->incli > 1)
			fdf->incli -= 0.1;
	}
	key_draw(fdf);
}

unsigned int	fdf_random(int seed)
{
	time_t	tmp;
	int		multi;
	int		addi;

	if (seed == 0)
	{
		tmp = time(NULL);
		seed = tmp;
	}
	else
		tmp = seed;
	multi = 45878;
	addi = 7483;
	seed = (multi * tmp + addi) % INT_MAX;
	return ((unsigned int)seed);
}
