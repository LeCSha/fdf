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

void fdf(t_mlx mlx, t_map *map)
{
    
    int dx;
    int dy;
    // int cumul;
    unsigned int i;
    unsigned int j;

    i = 0;
    while (i != map[0].nblignes)
    {
        j = 0;
        dx = map[i].point[map[0].nblignes - 1].x - map[i].point[j].x;
        if (dx != 0)
            if (dx > 0)
            {
                dy = map[i].point[map[0].nblignes - 1].y - map[i].point[j].y;
                if (dy != 0)
                    if (dy > 0)
                    {
                        
                    }
            }
        printf("%d\n", dx);
        // while (j != map[0].nbpoints)
        // {

        //     j++;
        // }
        mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, 100, 100, 0xc71515);
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