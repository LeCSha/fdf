#include "fdf.h"

void init_fdf(t_fdf *fdf)
{
    fdf->win_width = 1000;
    fdf->win_height = 800;
    fdf->scal = 0;
    fdf->dx = 0;
    fdf->dy = 0;
    fdf->startx = 0;
    fdf->starty = 0;
    fdf->endx = 0;
    fdf->endy = 0;
    fdf->xinc = 0;
    fdf->yinc = 0;
    fdf->ptXdepart = 100;
    fdf->ptYdepart = 100;
    fdf->nblines = 0;
    fdf->seed = 0;
    fdf->rel_z = 2;
}

void coord_x_y(t_fdf *fdf)
{
  int i;
  int j;

  i = 0;
  while (i < fdf->nblines)
  {
    j = 0;
    while (j < fdf->nbpoints)
    {
      fdf->map[i].point[j].x = coord_x(fdf, j, i, 0);
      fdf->map[i].point[j].y = coord_y(fdf, j, i, fdf->map[i].point[j].z, 0);
      // printf("%i\n", fdf->map[i].point[j].y);
      j++;
    }
    i++;
  }
}

void coord_max(t_fdf *fdf)
{
  int i;
  int j;

  i = 0;
  fdf->x_max = fdf->map[0].point[0].x;
  fdf->y_max = fdf->map[0].point[0].y;
  fdf->z_max = fdf->map[0].point[0].z;
  while (i < fdf->nblines)
  {
    j = 0;
    while (j < fdf->nbpoints)
    {
      if (fdf->x_max < fdf->map[i].point[j].x)
        fdf->x_max = fdf->map[i].point[j].x;
      if (fdf->z_max < fdf->map[i].point[j].z)
        fdf->z_max = fdf->map[i].point[j].z;
      if (fdf->y_max < fdf->map[i].point[j].y)
        fdf->y_max = fdf->map[i].point[j].y;
      j++;
    }

    i++;
  }
}

void coord_min(t_fdf *fdf)
{
  int i;
  int j;

  i = 0;
  fdf->x_min = fdf->map[0].point[0].x;
  fdf->y_min = fdf->map[0].point[0].y;
  fdf->z_min = fdf->map[0].point[0].z;
  while (i < fdf->nblines)
  {
    j = 0;
    while (j < fdf->nbpoints)
    {
      if (fdf->x_min > fdf->map[i].point[j].x)
        fdf->x_min = fdf->map[i].point[j].x;
      if (fdf->z_min > fdf->map[i].point[j].z)
        fdf->z_min = fdf->map[i].point[j].z;
      if (fdf->y_min > fdf->map[i].point[j].y)
        fdf->y_min = fdf->map[i].point[j].y;
      j++;
    }

    i++;
  }
}

void check_win_scale(t_fdf *fdf)
{
    if (fdf->nbpoints < 200)
      fdf->scal = 7;
    else
      fdf->scal = 2;
    coord_x_y(fdf);
    coord_max(fdf);
    coord_min(fdf);
    fdf->ptXdepart = (fdf->win_width / 2) - ((fdf->x_max - fdf->x_min) / 2);
    fdf->ptYdepart = (fdf->win_height / 2) - ((fdf->y_max - fdf->y_min) / 2);
    if ((fdf->ptXdepart + fdf->x_min) < 0)
      fdf->ptXdepart += abs(fdf->ptXdepart + fdf->x_min);
    if ((fdf->ptYdepart + fdf->y_min) < 0)
      fdf->ptYdepart += abs(fdf->ptYdepart + fdf->y_min);
    // printf("%f\n", fdf->scal);
    // printf("%i\n", fdf->ptXdepart);
    // printf("%i\n", fdf->ptYdepart);
    // printf("%i\n", fdf->x_max);
    // printf("%i\n", fdf->x_min);
    // printf("%i\n", fdf->y_max);
    // printf("%i\n", fdf->y_min);
    // printf("%i\n", fdf->win_width);
    // printf("%i\n", fdf->win_height);
}

int main(int ac, char **av)
{
    t_fdf fdf;

    fdf.map = NULL;
    if (ac != 2)
        return (0);
    init_fdf(&fdf);
    fdf.map = ft_open(av[1], &fdf);
    fdf.mlx_ptr = mlx_init();
    check_win_scale(&fdf);
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.win_width, fdf.win_height, "fdf 42");
    if (!(fdf.img = malloc(sizeof(t_mlx_img*))))
      return (0);
    fdf.img->img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.win_width, fdf.win_height);
    fdf.img->data = (int *)mlx_get_data_addr(fdf.img->img_ptr, &fdf.img->bpp, &fdf.img->size_l, &fdf.img->endian);
    fdf.color = 0xE628AB;
    calc_horizontal_x(&fdf, fdf.color);
    calc_vertical_y(&fdf, fdf.color);
    // mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 50, 50, fdf.color, "ZOOM : ");
    mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img->img_ptr, 0, 0);
    mlx_key_hook(fdf.win_ptr, key_fdf, &fdf);
    mlx_loop(fdf.mlx_ptr);
    return (0);
}
