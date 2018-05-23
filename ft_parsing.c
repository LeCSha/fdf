/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 15:34:39 by abaille           #+#    #+#             */
/*   Updated: 2018/05/01 15:34:41 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// t_point ft_new_point(int j, int i, char line)
// {
//      t_point new_point;
//      new_point = 
// }
int **ft_open(char *av)
{
    int fd;
    char *line;
    int taby;
    int **tab;
    int tabx;
    int i;
    int j;

    i = 0;
    j = 0;
    taby = 0;
    tabx = 0;
    fd = open(av, O_RDONLY);
    if (fd == -1)
        return (0);
    while (get_next_line(fd, &line) != 0)
    {
        printf("%s", line);
        taby++;
    }
    tab = (int**)malloc(sizeof(int) * taby + 1);
    close(fd);

    fd = open(av, O_RDONLY);
    if (fd == -1)
        return (0);
    while (get_next_line(fd, &line) != 0)
    {
        tabx = ft_strlen(line);
        tab[i] = (int*)malloc(sizeof(int) * tabx + 1);
        while (line[j] != '\0')
        {
            // point = ft_new_point(j, i, line[j]);
            tab[i][j] = line[j];
            j++;
        }
        tab[i][j] = '\0';
        j = 0;
        i++;
    }
    close(fd);
    return (tab);
}

// void trace_segment(t_mlx mlx, int **tab)
// {
//     int i;
//     int xinc; 
//     int yinc;
//     int cumul;
//     int dx;
//     int dy;

//     i = 0;
//     dx = ;
//     dy = yf - yi;
//     xinc = (dx > 0) ? 1: -1;
//     yinc = (dy > 0) ? 1: -1;
//     dx = abs(dx);
//     dy = abs(dy);
//     mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, xi, yi, 0xc71515);
//     while (*tab)
//     if (dx > dy)
//     {
//         cumul = dx/2;
//         while (i++ <= dx)
//         {
//             xi += xinc;
//             cumul += dy;
//             if (cumul >= dx)
//             {
//                 cumul -= dx;
//                 yi += yinc;
//             }
//             mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, xi, yi, 0xc71515);
//         }
//     }
//     else{
//         cumul = dy/2;
//         while (i++ <= dy)
//         {
//             yi += yinc;
//             cumul += dx;
//             if (cumul >= dy){
//                 cumul -= dy;
//                 xi += xinc;
//             }
//             mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, xi, yi, 0xc71515);
//         }
//     }
//     mlx_loop(mlx.mlx_ptr);
// }