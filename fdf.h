/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:01:59 by abaille           #+#    #+#             */
/*   Updated: 2018/04/11 11:02:07 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

typedef struct point
{
	int z;
	int x;
	int y;
}              t_point;

typedef struct map
{
	t_point *point;
}              t_map;

typedef struct mlx_img
{
	void *img_ptr;
	int *data;
	int size_l;
	int bpp;
	int endian;
}							t_mlx_img;

typedef struct fdf
{
	void *mlx_ptr;
	void *win_ptr;
	int nbpoints;
	int nblines;
	int dx;
	int dy;
	double scal;
	int startx;
	int starty;
	int endx;
	int endy;
	int xinc;
	int yinc;
	int rel_z;
	char *line;
	int ptdepart;
	int ptXdepart;
	int ptYdepart;
	int xwin;
	int ywin;
	int seed;
	int win_height;
	int win_width;
	int color;
	int x_max;
	int y_max;
	int z_max;
	int x_min;
	int y_min;
	int z_min;
	int moveX;
	int moveY;
	t_map *map;
	t_mlx_img *img;
}              t_fdf;

typedef


void    fdf(char *av, t_fdf *fdf);
void    count_fdf(int fd, t_fdf *fdf);
t_map   *read_map(int fd, t_fdf *fdf);
t_map   *ft_open(char *av, t_fdf *fdf);
int     key_fdf(int key, t_fdf *fdf);
void    calc_horizontal_x(t_fdf *fdf, int color);
void    calc_vertical_y(t_fdf *fdf, int color);
int     coord_x(t_fdf *fdf, int x, int y, int ptX);
int     coord_y(t_fdf *fdf, int x, int y, int z, int ptY);
void    go_trace_it(t_fdf *fdf, int color);
void    draw_base_line(t_fdf *fdf, int color);
unsigned int			fdf_random(int seed);
int			int_to_color(unsigned int color);

#endif
