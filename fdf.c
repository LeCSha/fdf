#include "fdf.h"

// #define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

// int couleur(double t)
// {
// return (RGB(127.5 * (cos(t) + 1),127.5 * (sin(t) + 1),127.5 * (1 - cos(t))));
// }

t_mlx init_mlx(void)
{
    t_mlx mlx;

    mlx.mlx_ptr = mlx_init();
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 800, 800, "fdf 42");
    return (mlx);
}
t_map *ft_open(char *av, t_map *map)
{
    int fd;
    char *line;
    int nblignes;
    int i;
    int j;
    int tmp;
    // char *tmp;
    int begin;
    int iter;
    int nbpoints;

    i = 0;
    nbpoints = 0;
    iter = 0;
    nblignes = 0;
    tmp = 0;
    fd = open(av, O_RDONLY);
    if (fd == -1)
        return (0);
    while (get_next_line(fd, &line) != 0)
    {
        j = 0;
        nbpoints = 0;
        while (line[j] != '\0')
        {
            if ((line[j] >= '0' && line[j] <= '9') && (line[j+1] == ' ' || line[j+1] == '\0'))
                nbpoints++;
            j++;
        }
        if (tmp == 0)
            tmp = nbpoints;
        else
            if (tmp != nbpoints)
                return (0);

        nblignes++;
    }
    if (!(map = (t_map*)malloc(sizeof(t_map) * nblignes)))
        return (NULL);
    map[0].nblignes = nblignes;
    map[0].nbpoints = nbpoints;
    close(fd);

    fd = open(av, O_RDONLY);
    if (fd == -1)
        return (0);

    while (get_next_line(fd, &line) > 0)
    {
        // printf("%d\n", nbpoints);
        if (!(map[i].point = (t_point*)malloc(sizeof(t_point) * nbpoints)))
            return (NULL);
        j = 0;
        begin = 0;
        iter = 0;
        while (line[j] != '\0')
        {
            if ((line[j] >= '0' && line[j] <= '9') || line[j] == '-')
            {
                if (line[j+1] >= '0' && line[j+1] <= '9')
                {
                    begin = j;

                    while ((line[j] >= '0' && line[j] <= '9' )|| line[j] == '-')
                        j++;
                    // tmp = ft_strsub(line, begin, j);
                    // printf("%d\n", iter);
                    map[i].point[iter].z = ft_atoi(ft_strsub(line, begin, j));
                    map[i].point[iter].x = iter;
                    map[i].point[iter].y = i;
                    // free(tmp);
                    // printf("nb valeur du point n'%d de la ligne n'%i : %i\n", iter, i, map[i].point[iter].z);
                }
                else{
                    map[i].point[iter].z = ft_atoi(&line[j]);
                    map[i].point[iter].x = iter;
                    map[i].point[iter].y = i;
                    // printf("chiffre valeur du point n'%d de la ligne n'%i : %i\n", iter, i, map[i].point[iter].z);
                }
                iter++;
            }
            j++;
        }
        // free(line);
        i++;
        if (line != NULL)
            free(line);
    }
    close(fd);
    return (map);
}

  void line_rightup(t_mlx mlx, int x1, int y1, int x2, int y2)
  {
      printf("je rentre ds rightUP \n");
    int x;
    int y;
    int dx;
    int dy;
    int xinc;
    int yinc;
    int cumul;
printf("x1 %d et x2 %d\n", x1, x2);
printf("y1 %d et y2 %d\n", y1, y2);
    x = x1;
    y = y1;
    dx = x2 - x;
    dy = y2 - y;
    xinc = (dx > 0) ? 1 : -1;
    yinc = (dy > 0) ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);
    mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y + 200, 0xc71515);
    if (dx > dy)
    {
      printf("dx > dy \n");
      printf("dx %d et dy %d\n", dx, dy);
        cumul = dx / 2;
        while (x != x2)
        {
            x += xinc;
            cumul += dy;
            printf("cumul + dy %d\n", cumul);
            if (cumul >= dx)
            {
                cumul -= dx;
                y += yinc;
                printf("cumul > dx %d\n", cumul);
            }
          printf("x ds while %d\n", x);
          printf("y ds while %d\n", y);
          mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y + 200, 0xc71515);
        }
    }
    else
    {
      printf("dx < dy \n");
      printf("y%d \n", y);
      printf("y1 %d \n", y2);
        cumul = dy / 2;
        while (y > y2)
        {
            y += yinc;
            printf("y + yinc %d \n", y);
            cumul += dx;
            printf("cumul + dx %d \n", cumul);
            if (cumul >= dy)
            {
                cumul -= dy;
                x += xinc;
            }
            mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y + 200, 0xc71515);
        }
      }
  }

// void line_rightdown(t_mlx mlx, int x, int y, int x1, int y1)
// {
//       printf("je rentre ds rightDOWN \n");

//   int dx;
//   int dy;
//   int dp;
//   int deltae;
//   int deltane;

//   dx = abs(x1 - x);
//   dy = abs(y1 - y);
//   if (dx >= dy)
//   {
//       printf("dx >= dy \n");

//       dp = (2 * dy) - dx;
//       deltae = 2 * dy;
//       deltane = 2 * (dy - dx);
//       while (x < x1)
//       {
//         if (dp <= 0)
//         {
//             dp += deltae;
//             x++;
//         }
//         else
//         {
//             dp += deltane;
//             x++;
//             y++;
//         }
//       }
//       mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y + 200, 0xc71515);
//   }
//   else
//   {
//       printf("dx < dy \n");

//       dp = (2 * dx) - dy;
//       deltae = 2 * dx;
//       deltane = 2 * (dx - dy);
//       while(y < y1)
//       {
//         if (dp <= 0)
//         {
//             dp += deltae;
//             y++;
//         }
//         else
//         {
//             dp += deltane;
//             x++;
//             y++;
//         }
//       }
//       mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y + 200, 0xc71515);
//   }

// }

void fdf(t_mlx mlx, t_map *map)
{
    unsigned int i;
    unsigned int j;

    i = 0;
    while (i < map[0].nblignes)
    {
        j = 0;
        while (j < map[0].nbpoints - 1)
        {
            // if (map[i].point[j+1].x * 20 > map[i].point[j].x * 20)
              line_rightup(mlx, map[i].point[j].x * 20 * 0.8 + (i * 20),
              (map[i].point[j].y * 20 * 0.8) - (j * 20), (map[i].point[j + 1].x * 20 * 0.8) + (i * 20), (map[i].point[j + 1].y * 20 * 0.8) - ((j + 1) * 20));
            // else
            //   line_rightdown(mlx, (map[i].point[j].x * 20 * 0.8) - (i * 20), map[i].point[j].y * 20 * 0.8 + (j * 20),
            //   (map[i].point[j + 1].x * 20 * 0.8) - (i * 20), (map[i].point[j + 1].y * 20 * 0.8) + (j * 20));
            // seg = 0;
            // while (seg < 19)
            // {
            //   if (map->point[map[0].nbpoints - 1].x > map->point[j].x)
            //     line_rightup(mlx, map[i].point[j].x * 20, map[i].point[j].y * 20, map[i].point[map[0].nbpoints - 1].x * 20, map[i].point[map[0].nbpoints - 1].y * 20, i, j);
            //   else
            //     line_rightdown(mlx, map[i].point[j].x * 20, map[i].point[j].y * 20, map[i].point[map[0].nbpoints - 1].x * 20, map[i].point[map[0].nbpoints - 1].y * 20, i, j);
            //   seg++;
            // }
            //mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, (map[i].point[j].x * 0.8 * 20) + i * 20, (map[i].point[j].y * 20 * 0.8 + 200) - j * 20, 0xc71515);
            // if (j != map[0].nbpoints - 1)
            //     for (int v = 0; v < 20; v++)
            //         mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, ((map[i].point[j].x * 0.8) * 20 + v + 200) + i * 20, (map[i].point[j].y * 0.8 * 20 + v + 200) - j * 20, 0xc71515);
            // if (i != map[0].nblignes - 1)
            //     for (unsigned int z = 0; z < 20; z++)
            //         mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, ((map[i].point[j].x * 0.8) * 20 + 200) + (i * 20), (map[i].point[j].y * 0.8 * 20 + z + 200) - (j * 20), 0xc71515);
            j++;
        }
        i++;
    }

    mlx_loop(mlx.mlx_ptr);

}
int main(int ac, char **av)
{
    t_mlx mlx;
    t_map *map;
    // int *tab;
    if (ac != 2)
        return (0);
    map = NULL;
    map = ft_open(av[1], map);
    mlx = init_mlx();
    fdf(mlx, map);
    return (0);
}
