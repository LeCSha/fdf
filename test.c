#include "fdf.h"

t_map *ft_open(char *av, t_map *map)
{
    int fd;
    char *line;
    int nblignes;
    int i;
    int j;
    // char *tmp;
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
    // map[0].nblignes = nblignes;
    // map[0].nbpoints = nbpoints;
    close(fd);

    fd = open(av, O_RDONLY);
    if (fd == -1)
        return (0);

    while (get_next_line(fd, &line) > 0)
    {
        printf("%d\n", nbpoints);
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
        // free(line);
        i++;
        if (line != NULL)
            free(line);
    }
    close(fd);
    return (map);
}

int main(int ac, char **av)
{
    // t_mlx mlx;
    t_map *map = NULL;
    if (ac != 2)
        return (0);

    ft_open(av[1], map);
    // mlx = init_mlx();
    // fdf(mlx, &tab);
    free(map);
    return (0);
}