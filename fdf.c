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
    fdf->ptXdepart = 300;
    fdf->ptYdepart = 300;
    fdf->nblines = 0;
    fdf->seed = 0;
}

int main(int ac, char **av)
{
    t_fdf fdf;

    fdf.map = NULL;
    if (ac != 2)
        return (0);
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1500, 2000, "fdf 42");
    init_fdf(&fdf);
    fdf.color = 0xE628AB;
    fdf.map = ft_open(av[1], &fdf);
    calc_horizontal_x(&fdf, fdf.color);
    calc_vertical_y(&fdf, fdf.color);
    mlx_key_hook(fdf.win_ptr, key_fdf, &fdf);
    mlx_loop(fdf.mlx_ptr);
    return (0);
}
