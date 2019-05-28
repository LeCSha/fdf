/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 11:01:59 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 19:03:41 by abaille          ###   ########.fr       */
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
# define HEIGHT 700
# define IMG_DATA fdf->mlx.img->data

# define TEXT_COLOR			0xEAEAEA
# define BACKGROUND			0x222222
# define MENU_BACKGROUND	0x1E1E1E

# define COLOR_DISCO		0x9A1F6A
# define COLOR_BRICK_RED	0xC2294E
# define COLOR_FLAMINGO		0xEC4B27
# define COLOR_JAFFA		0xEF8633
# define COLOR_SAFFRON		0xF3AF3D

typedef	struct	s_point
{
	float		z;
	float		x;
	float		y;
	int			color;
}				t_point;

typedef	struct	s_ipoint
{
	int			z;
	int			x;
	int			y;
	int			color;
}				t_ipoint;

typedef struct	s_map
{
	t_point		*pt;
}				t_map;

typedef struct 	s_pal
{
	int			color[3];
	int 		size;
}				t_pal;


typedef struct	s_mlx_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_mlx_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*win_str;
	t_mlx_img	*img;
	int			img_wth;
	
}				t_mlx;

typedef struct	s_env
{
	char		*line;
	int			nbpoints;
	int			nblines;
	int			icolor;
	int			key;
	int			*nbpt;
	t_map		*map;
	float		scal;
	float		rel_z;
	float		deg;
	float		incli;
	t_ipoint	d;
	t_ipoint	dep;
	t_point		max;
	t_point		min;
	t_ipoint	start;
	t_ipoint	end;
	t_ipoint	inc;
	t_pal		pal[5];
	t_pal		*pal_ptr;
	t_mlx		mlx;
}				t_env;

void			check_win_scale(t_env *fdf);
int				count_fdf(int fd, t_env *fdf);
t_map			*read_map(int fd, t_env *fdf);
int				ft_open(char *av, t_env *fdf);

void			calcul_coord(t_env *fdf);
void			rotate(t_env *fdf, float *x, float *y);
void			inclinate(int key, t_env *fdf);
unsigned int	fdf_random(int seed);
float			iso_x(t_env *fdf, float x, float y);
float			iso_y(t_env *fdf, float x, float y, float z);

void			iso(t_env *f, t_point *p);

void			calc_horizontal_x(t_env *fdf);
void			calc_vertical_y(t_env *fdf);
void			go_trace_it(t_env *fdf);

void			check_file(char *file);
int				check_char(char *line);
void			print_error(int nb, t_env *fdf, int ref);

void			move_map(int key, t_env *fdf);
void			relief_fdf(int key, t_env *fdf);
void			zoom_fdf(int key, t_env *fdf);
void			rotation(int key, t_env *fdf);
int				key_fdf(int key, t_env *fdf);

int				int_to_color(unsigned int color);
void			random_color(int key, t_env *fdf);
void			multicolor(t_env *fdf, int x, int y);
void			epileptic_color(t_env *fdf);
int				z_color(t_env *fdf, float z);
int				default_color(int z, t_env *fdf);
int				get_color(t_ipoint current, t_ipoint start, t_ipoint end, t_ipoint delta);

void			key_draw(t_env *fdf);
void			free_fdf(t_env *fdf);
void			exit_fdf(t_env *fdf);
void			reinit_fdf(t_env *fdf);
#endif
