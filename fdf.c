#include "fdf.h"

// #define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

// int couleur(double t)
// {
// return (RGB(127.5 * (cos(t) + 1),127.5 * (sin(t) + 1),127.5 * (1 - cos(t))));
// }

int fdf_random()
{
  int *seed;
  int modulo;
  int res;
  int multi;
  int addi;
  int i;

  i = 0;
  multi = 16;
  addi = 7;
  seed = &modulo;
  res = 0;
  modulo = 256;
  res = (multi * *seed + addi) % modulo;
  printf("coucou");
  printf("%d", res);

  //hex_to_dec()
  return (res);
}

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
    printf("coucou");
}

int main(int ac, char **av)
{
  printf("coucou");
    t_fdf fdf;
    // t_map *map;

    fdf.map = NULL;
    if (ac != 2)
    return (0);
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1500, 2000, "fdf 42");
    init_fdf(&fdf);
    fdf.map = ft_open(av[1], &fdf);
        fdf_random();
    calc_horizontal_x(&fdf);
    calc_vertical_y(&fdf);

    mlx_key_hook(fdf.win_ptr, key_fdf, &fdf);
    mlx_loop(fdf.mlx_ptr);
    return (0);
}
