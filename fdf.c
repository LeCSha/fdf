#include "fdf.h"

t_fdf *init_fdf()
{
    t_fdf *new;

    if (!(new = (t_fdf *)malloc(sizeof(t_fdf))))
      return (NULL);
    new->map = NULL;
    new->img_wth = 1000;
    new->scal = 12;
    new->dx = 0;
    new->dy = 0;
    new->startx = 0;
    new->starty = 0;
    new->endx = 0;
    new->endy = 0;
    new->xinc = 0;
    new->yinc = 0;
    new->ptXdepart = 0;
    new->ptYdepart = 0;
    new->nblines = 0;
    new->seed = 0;
    new->rel_z = 2;
    new->moveX = 0;
    new->moveY = 0;
    return (new);
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
      fdf->map[i].point[j].x = coord_x(fdf, j, i);
      fdf->map[i].point[j].y = coord_y(fdf, j, i, fdf->map[i].point[j].z);
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

void res_z(t_fdf *fdf)
{
  int i;
  int j;

  i = 0;
  while (i < fdf->nblines)
  {
    j = 0;
    while (j < fdf->nbpoints)
    {
      fdf->map[i].point[j].z = fdf->map[i].point[j].z / 5;
      j++;
    }
    i++;
  }
}

void check_win_scale(t_fdf *fdf)
{
    coord_x_y(fdf);
    coord_max(fdf);
    coord_min(fdf);
    if (abs(fdf->z_min) > abs(fdf->z_max))
      fdf->z_max = fdf->z_min;
    while (abs(fdf->z_max) > 100)
    {
      res_z(fdf);
      coord_x_y(fdf);
      coord_max(fdf);
      coord_min(fdf);
    }
    while ((fdf->x_max > fdf->img_wth ||
    fdf->y_max - fdf->y_min > HEIGHT) && fdf->scal >= 0)
    {
      fdf->scal -= 1;
      coord_x_y(fdf);
      coord_max(fdf);
      coord_min(fdf);
    }
    fdf->ptXdepart = fdf->img_wth / 2 - fdf->x_max / 2;
    fdf->ptYdepart = HEIGHT / 2 - (fdf->y_max - fdf->y_min) / 2;
    if ((fdf->ptYdepart + fdf->y_min) < 0)
      fdf->ptYdepart += abs(fdf->y_min);
}

void put_string(t_fdf *fdf)
{
  void *win;

  win = mlx_new_window(fdf->mlx_ptr, 230, 800, "Keycode fdf");
  mlx_string_put(fdf->mlx_ptr, win, 40, 40, 0x2EDD17, "-- Keycode --");
  mlx_string_put(fdf->mlx_ptr, win, 20, 130, 0x2EDD17, "'+' : zoom +");
  mlx_string_put(fdf->mlx_ptr, win, 20, 170, 0x2EDD17, "'-' : zoom -");
  mlx_string_put(fdf->mlx_ptr, win, 20, 210, 0x2EDD17, "'up' : move up -");
  mlx_string_put(fdf->mlx_ptr, win, 20, 250, 0x2EDD17, "'down' : move down");
  mlx_string_put(fdf->mlx_ptr, win, 20, 290, 0x2EDD17, "'left' : move left");
  mlx_string_put(fdf->mlx_ptr, win, 20, 330, 0x2EDD17, "'right' : move right");
  mlx_string_put(fdf->mlx_ptr, win, 20, 370, 0x2EDD17, "'t' : increase top");
  mlx_string_put(fdf->mlx_ptr, win, 20, 410, 0x2EDD17, "'e' : decrease top");
  mlx_string_put(fdf->mlx_ptr, win, 20, 450, 0x2EDD17, "'w' : random colors");
  mlx_string_put(fdf->mlx_ptr, win, 20, 490, 0x2EDD17, "'r' : reset");
  mlx_string_put(fdf->mlx_ptr, win, 20, 530, 0x2EDD17, "'ESC' : exit");
  fdf->win_str = win;
}

void launch_fdf(char *av)
{
  t_fdf *fdf;

  if (!(fdf = init_fdf()))
    print_error(6, fdf);
  check_file(av);
  ft_open(av, fdf);
  fdf->mlx_ptr = mlx_init();
  fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "fdf 42");
  check_win_scale(fdf);
  if (!(fdf->img = (t_mlx_img *)malloc(sizeof(t_mlx_img))))
    print_error(6, fdf);
  fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->img_wth, HEIGHT);
  fdf->img->data = (int *)mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_l, &fdf->img->endian);
  fdf->color = 0x84742d;
  calc_horizontal_x(fdf, fdf->color);
  calc_vertical_y(fdf, fdf->color);
  put_string(fdf);
  mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
  mlx_key_hook(fdf->win_ptr, key_fdf, fdf);
  mlx_key_hook(fdf->win_str, key_fdf, fdf);
  mlx_loop(fdf->mlx_ptr);
}
int main(int ac, char **argv)
{
    if (ac != 2)
      print_error(5, NULL);
    launch_fdf(argv[1]);
    return (0);
}
