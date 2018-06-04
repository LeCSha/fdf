#include "fdf.h"

void    exit_fdf(t_fdf *fdf)
{
    mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
    mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
    exit(0);
}

void    zoom_fdf(int key, t_fdf *fdf)
{
    if (key == 69)
    {
        fdf->scalx += 1;
        fdf->scaly += 1;
        mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
        calc_horizontal_x(&fdf, &(*map));
        calc_vertical_y(&fdf, &(*map));
    }
    else
    {
        fdf->scalx -= 1;
        fdf->scaly -= 1;
        mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
        calc_horizontal_x(&fdf, &(*map));
        calc_vertical_y(&fdf, &(*map));
    }
}

int   key_fdf(int key, t_fdf *fdf)
{
    if (key == 53)
        exit_fdf(fdf);
    if (key == 78 || key == 69)
        zoom_fdf(key, &(*fdf));

    return (0);
}