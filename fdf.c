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
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 500, "fdf 42");
    return (mlx);
}
t_map *ft_open(char *av, t_map *map)
{
    int fd;
    char *line;
    int nblignes;
    int i;
    int j;
    char *tmp;
    int begin;
    int iter;
    int nbpoints;
    
    i = 0;
    j = 0;
    nbpoints = 0;
    iter = 0;
    nblignes = 0;
    fd = open(av, O_RDONLY);
    if (fd == -1)
        return (0);
    while (get_next_line(fd, &line) != 0)
    {
        nbpoints = 0;
        while (line[j] != '\0')
        {
            if ((line[j] >= '0' && line[j] <= '9') && (line[j+1] == ' ' || line[j+1] == '\0'))
                nbpoints++;
            j++;
        }
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
    while (get_next_line(fd, &line))
    {
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
                    tmp = ft_strsub(line, begin, j);
                    printf("%d\n", iter);
                    map[i].point[iter].z = ft_atoi(tmp);
                    map[i].point[iter].x = iter;
                    map[i].point[iter].y = i;
                    printf("nb valeur du point n'%d de la ligne n'%i : %i\n", iter, i, map[i].point[iter].z);
                }
                else{
                    map[i].point[iter].z = ft_atoi(&line[j]);
                    map[i].point[iter].x = iter;
                    map[i].point[iter].y = i;
                    printf("chiffre valeur du point n'%d de la ligne n'%i : %i\n", iter, i, map[i].point[iter].z);                    
                }
                iter++;
            }
            j++;
        }
        i++;
    }
    close(fd);
    return (map);
}

void fdf(t_mlx mlx, t_map *map)
{
    int i;
    int iter;
    int xinc; 
    int yinc;
    int cumul;
    int dx;
    int dy;
    int j;
    int xd;
    int yd;

    i = 0;
    j = 0;
    iter = 0;
    // dx = xf - xi;
    // dy = yf - yi;
    // mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, xd, yd, 0xc71515);
    while (i != map[0].nblignes)
    {
        // printf("passe ds le tab[i]");
        while (j != map[0].nbpoints)
        {
        // printf("passe ds le tab[i][j]");
            
            xd = j;
            dx = xd+1 - xd + 5;
            dy = i;
            yd = i;
            dx = abs(dx);
            dy = abs(dy);
            xinc = (dx > 0) ? 1: -1;
            yinc = (dy > 0) ? 1: -1;
            if (dx > dy)
            {
                cumul = dx/2;
                while (iter++ <= dx)
                {
                    xd += xinc;
                    cumul += dy;
                    if (cumul >= dx)
                    {
                        cumul -= dx;
                        yd += yinc;
                    }
                    mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, xd, yd, 0xc71515);
                    j++;
                }
            }
            else{
                cumul = dy/2;
                while (iter++ <= dy)
                {
                    yd += yinc;
                    cumul += dx;
                    if (cumul >= dy){
                        cumul -= dy;
                        xd += xinc;
                    }
                    mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, xd, yd, 0xc71515);
                    j++;
                }
            }
        }
        j = 0;
        i++;
    }
    mlx_loop(mlx.mlx_ptr);

}
int main(int ac, char **av)
{
    t_mlx mlx;
    t_map map;
    // int *tab;
    if (ac != 2)
        return (0);

    ft_open(av[1], &map);
    mlx = init_mlx();
    // fdf(mlx, &map);
    return (0);
}