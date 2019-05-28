/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 17:03:08 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 17:52:18 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			iso(t_env *f, t_point *p)
{
	float	oldx;
	float	oldy;
	(void)f;
	oldx = p->x;
	oldy = p->y;
	p->x = (oldx - oldy) * cos(0.523599);
	p->y = -p->z + (oldx + oldy) * sin(0.523599);

}

float			iso_x(t_env *fdf, float x, float y)
{
	return ((x - y) * fdf->scal * cos(0.523599));
}

float			iso_y(t_env *fdf, float x, float y, float z)
{
	return (-z * fdf->rel_z + (fdf->scal * y + (fdf->scal * x) / fdf->incli) * sin(0.523599));
}

void			rotate(t_env *fdf, float *x, float *y)
{
	float	radian;
	float	oldx;
	float	oldy;

	radian = fdf->deg * 3.141 * 180;
	oldx = *x;
	oldy = *y;
	*x = (oldx - fdf->nbpoints / 2) * cos(radian) - (oldy - fdf->nblines / 2) * sin(radian);
	*y = (oldx - fdf->nbpoints / 2) * sin(radian) + (oldy - fdf->nblines / 2) * cos(radian);
}

void			inclinate(int key, t_env *fdf)
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
