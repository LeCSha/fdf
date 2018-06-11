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
}              t_point;

typedef struct map
{
	t_point *point;
}              t_map;

typedef struct fdf
{
	void *mlx_ptr;
	void *win_ptr;
	int nbpoints;
	int nblines;
	int dx;
	int dy;
	double scalx;
	double scaly;
	int startx;
	int starty;
	int endx;
	int endy;
	int xinc;
	int yinc;
	char *line;
	int ptdepart;
	int seed;
	unsigned int color;
	t_map *map;
}              t_fdf;


void    fdf(char *av, t_fdf *fdf);
void    count_fdf(int fd, t_fdf *fdf);
t_map   *read_map(int fd, t_fdf *fdf);
t_map   *ft_open(char *av, t_fdf *fdf);
int     key_fdf(int key, t_fdf *fdf);
void    calc_horizontal_x(t_fdf *fdf);
void    calc_vertical_y(t_fdf *fdf);
int     coord_x(t_fdf *fdf, int x, int y);
int     coord_y(t_fdf *fdf, int x, int y, int z);
void    go_trace_it(t_fdf *fdf);
void    draw_base_line(t_fdf *fdf);
unsigned int			fdf_random();
int			int_to_color(unsigned int color);
//int convert_nb(char c);
//int power(int nb, int tpower);
//int *char_to_int(char *rgb);

#endif
