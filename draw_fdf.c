#include "fdf.h"

void    go_trace_it(t_fdf *fdf)
{
    int ratio;
    int rigthleft;
    int updown;
    int i;

    i = 0;
    mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xCC0066);
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
            mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xCC0066);
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
            mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xCC0066);
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

void    calc_horizontal_x(t_fdf *fdf)
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
            fdf->starty = coord_y(fdf, j, i, fdf->map[i].point[j].z);
            fdf->endx = coord_x(fdf, j + 1, i);
            fdf->endy = coord_y(fdf, j + 1, i, fdf->map[i].point[j + 1].z);
            draw_base_line(&(*fdf));
            j++;
        }
        i++;
    }
}

void    calc_vertical_y(t_fdf *fdf)
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
            fdf->starty = coord_y(fdf, j, i, fdf->map[i].point[j].z);
            fdf->endx = coord_x(fdf, j, i + 1);
            fdf->endy = coord_y(fdf, j, i + 1, fdf->map[i + 1].point[j].z);
            draw_base_line(fdf);
            j++;
        }
        i++;
    }
}