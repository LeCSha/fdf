/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:01:59 by abaille           #+#    #+#             */
/*   Updated: 2018/07/21 18:53:38 by abaille          ###   ########.fr       */
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
# include "mlx.h"
# include "libft.h"

# define WIDTH 1000
# define HEIGHT 800
# define IMG_DATA fdf->img->data

typedef	struct	s_point
{
	float		z;
	float		x;
	float		y;
}				t_point;

typedef struct	s_map
{
	t_point		*pt;
}				t_map;

typedef struct	s_mlx_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_mlx_img;

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*win_str;
	int			nbpoints;
	int			nblines;
	int			dx;
	int			dy;
	float		scal;
	int			startx;
	int			starty;
	int			endx;
	int			endy;
	int			xinc;
	int			yinc;
	float		rel_z;
	char		*line;
	int			depx;
	int			depy;
	int			seed;
	int			img_wth;
	int			color;
	int			x_max;
	int			y_max;
	int			z_max;
	int			x_min;
	int			y_min;
	int			z_min;
	float		deg;
	float		incli;
	int			key;
	t_map		*map;
	t_mlx_img	*img;
}				t_fdf;

void			check_win_scale(t_fdf *fdf);
int				count_fdf(int fd, t_fdf *fdf);
t_map			*read_map(int fd, t_fdf *fdf);
int				ft_open(char *av, t_fdf *fdf);

void			coord_x_y(t_fdf *fdf);
void			coord_max(t_fdf *fdf);
void			coord_min(t_fdf *fdf);
void			res_z(t_fdf *fdf);
void			calcul_coord(t_fdf *fdf);

float			rotate(t_fdf *fdf, float x, float y, int xoy);
void			inclinate(int key, t_fdf *fdf);
unsigned int	fdf_random(int seed);
float			iso_x(t_fdf *fdf, float x, float y);
float			iso_y(t_fdf *fdf, float x, float y, float z);

void			calc_horizontal_x(t_fdf *fdf);
void			calc_vertical_y(t_fdf *fdf);
void			go_trace_it(t_fdf *fdf);

void			check_file(char *file);
int				check_char(char *line);
void			print_error(int nb, t_fdf *fdf, int ref);

void			move_map(int key, t_fdf *fdf);
void			relief_fdf(int key, t_fdf *fdf);
void			zoom_fdf(int key, t_fdf *fdf);
void			rotation(int key, t_fdf *fdf);
int				key_fdf(int key, t_fdf *fdf);

int				int_to_color(unsigned int color);
void			random_color(int key, t_fdf *fdf);
void			multicolor(t_fdf *fdf, int x, int y);
void			epileptic_color(t_fdf *fdf);

void			key_draw(t_fdf *fdf);
void			free_fdf(t_fdf *fdf);
void			exit_fdf(t_fdf *fdf);
void			reinit_fdf(t_fdf *fdf);
#endif
