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

# define WIDTH 1000
# define HEIGHT 800

typedef struct point
{
	float z;
	float x;
	float y;
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
	void *win_str;
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
	int ptXdepart;
	int ptYdepart;
	int seed;
	int img_wth;
	int color;
	int x_max;
	int y_max;
	int z_max;
	int x_min;
	int y_min;
	int z_min;
	int moveX;
	int moveY;
	int deg;
	t_map *map;
	t_mlx_img *img;
}              t_fdf;


void 		check_win_scale(t_fdf *fdf);
int			count_fdf(int fd, t_fdf *fdf);
t_map   *read_map(int fd, t_fdf *fdf);
int			ft_open(char *av, t_fdf *fdf);
int     key_fdf(int key, t_fdf *fdf);
void    calc_horizontal_x(t_fdf *fdf, int color);
void    calc_vertical_y(t_fdf *fdf, int color);
void 		coord_x_y(t_fdf *fdf);
void 		coord_max(t_fdf *fdf);
void 		coord_min(t_fdf *fdf);
int     coord_x(t_fdf *fdf, int x, int y);
int     coord_y(t_fdf *fdf, int x, int y, int z);
void    go_trace_it(t_fdf *fdf, int color);
void    draw_base_line(t_fdf *fdf, int color);
unsigned int			fdf_random(int seed);
int			int_to_color(unsigned int color);
void		free_fdf(t_fdf *fdf);
int			check_file(char *file);
int			check_char(char *line);
void		print_error(int nb, t_fdf *fdf);
// void 		put_string(t_fdf *fdf);

#endif
