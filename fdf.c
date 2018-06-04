#include "fdf.h"

// #define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

// int couleur(double t)
// {
// return (RGB(127.5 * (cos(t) + 1),127.5 * (sin(t) + 1),127.5 * (1 - cos(t))));
// }



void init_fdf(t_fdf *fdf)
{
    fdf->scalx = 7;
    fdf->scaly = 7;
    fdf->dx = 0;
    fdf->dy = 0;
    fdf->startx = 0;
    fdf->starty = 0;
    fdf->endx = 0;
    fdf->endy = 0;
    fdf->xinc = 0;
    fdf->yinc = 0;
    fdf->ptdepart = 300;
    fdf->nblines = 0;
}

void    go_trace_it(t_fdf *fdf)
{
    int ratio;
    int rigthleft;
    int updown;
    int i;

    i = 0;
    mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xc71515);
    if (fdf->dx > fdf->dy)
    {
        ratio = (2 * fdf->dy) - fdf->dx;
        updown = 2 * (fdf->dy - fdf->dx);
        rigthleft = 2 * fdf->dy;
        while(i < fdf->dx)
        {
            if (ratio >= 0)
            {
                ratio = ratio + updown;
                fdf->starty = fdf->starty + fdf->yinc;
            }
            else
                ratio = ratio + rigthleft;
            fdf->startx = fdf->startx + fdf->xinc;
            mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xc71515);
            i++;
        }
    }
    else
    {
        ratio = (2 * fdf->dx) - fdf->dy;
        rigthleft = 2 * (fdf->dx - fdf->dy);
        updown = 2 * fdf->dx;
        while(i < fdf->dy)
        {
            if (ratio >= 0)
            {
                ratio = ratio + rigthleft;
                fdf->startx = fdf->startx + fdf->xinc;
            }
            else
                ratio = ratio + updown;
            fdf->starty = fdf->starty + fdf->yinc;
            mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xc71515);
            i++;
        }
    }
}

void    draw_base_line(t_fdf *fdf)
{
    fdf->dx = fdf->endx - fdf->startx;
    fdf->dy = fdf->endy - fdf->starty;
    fdf->xinc = (fdf->dx > 0) ? 1 : -1;
    fdf->yinc = (fdf->dy > 0) ? 1 : -1;
    fdf->dx = abs(fdf->dx);
    fdf->dy = abs(fdf->dy);
    go_trace_it(&(*fdf));
}

int coord_x(t_fdf *fdf, int x, int y)
{
    return (fdf->ptdepart + (fdf->scalx * x) - (fdf->scalx * y));
}
int coord_y(t_fdf *fdf, int x, int y, int z)
{
	return (fdf->ptdepart + (((fdf->scaly) * x) + ((fdf->scaly) * y) / 2) - (z * 2));
}

void    calc_horizontal_x(t_fdf *fdf, t_map *map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < fdf->nblines)
    {
        j = 0;
        while (j < fdf->nbpoints - 1)
        {
            fdf->startx = coord_x(fdf, j, i);
            fdf->starty = coord_y(fdf, j, i, map[i].point[j].z);
            fdf->endx = coord_x(fdf, j + 1, i);
            fdf->endy = coord_y(fdf, j + 1, i, map[i].point[j + 1].z);
            draw_base_line(&(*fdf));
            j++;
        }
        i++;
    }
}

void    calc_vertical_y(t_fdf *fdf, t_map *map)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < fdf->nblines - 1)
    {
        j = 0;
        while (j < fdf->nbpoints)
        {
            fdf->startx = coord_x(fdf, j, i);
            fdf->starty = coord_y(fdf, j, i, map[i].point[j].z);
            fdf->endx = coord_x(fdf, j, i + 1);
            fdf->endy = coord_y(fdf, j, i + 1, map[i + 1].point[j].z);
            draw_base_line(fdf);
            j++;
        }
        i++;
    }
}

int main(int ac, char **av)
{
    t_fdf fdf;
    t_map *map;
    
    map = NULL;
    if (ac != 2)
    return (0);
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1500, 2000, "fdf 42");
    init_fdf(&fdf);
    map = ft_open(av[1], &fdf);
    calc_horizontal_x(&fdf, &(*map));
    calc_vertical_y(&fdf, &(*map));
    mlx_key_hook(fdf.win_ptr, key_fdf, &fdf);
    mlx_loop(fdf.mlx_ptr);
    return (0);
}
