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
# include "minilibx/mlx.h"
# include "libft/libft.h"

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
}              t_fdf;

typedef struct point
{
    int x;
    int y;
    int z;
}              t_point;

typedef struct map
{
    t_point *point;
}              t_map;

void    fdf(char *av, t_fdf *fdf);
void    count_fdf(int fd, t_fdf *fdf);
t_map   *read_map(int fd, t_fdf *fdf);
t_map   *ft_open(char *av, t_fdf *fdf);
int     key_fdf(int key, t_fdf *fdf);

#endif
