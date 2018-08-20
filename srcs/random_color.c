/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 17:03:08 by abaille           #+#    #+#             */
/*   Updated: 2018/07/18 17:03:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		int_to_color(unsigned int color)
{
	int	r;
	int g;
	int b;
	int res;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0x00FF00) >> 8;
	b = color & 0x0000FF;
	res = (r << 16) + (g << 8) + b;
	return (res);
}

void	multicolor(t_fdf *fdf, int x, int y)
{
	if (fdf->key == 38)
	{
		fdf->seed = fdf_random(fdf->color);
		fdf->color = int_to_color(fdf->seed * (x + y + fdf->color));
	}
}

void	random_color(int key, t_fdf *fdf)
{
	fdf->seed = fdf_random(fdf->color * key);
	fdf->color = int_to_color(fdf->seed + fdf->seed);
	key_draw(fdf);
}

void	ft_sleep(void)
{
	int i;

	i = 0;
	while (i < 100000000)
		i++;
}

void	epileptic_color(t_fdf *fdf)
{
	int i;

	i = 0;
	fdf->key = 38;
	while (i < 50)
	{
		key_draw(fdf);
		mlx_do_sync(fdf->mlx_ptr);
		ft_sleep();
		i++;
	}
}
