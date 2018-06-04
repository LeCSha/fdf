#include "fdf.h"

void  count_fdf(int fd, t_fdf *fdf)
{
    char *line;
    int tmp;

    tmp = 0;
    line = NULL;
    while (get_next_line(fd, &line) != 0)
    {
        fdf->xinc = 0;
        fdf->nbpoints = 0;
        while (line[fdf->xinc] != '\0')
        {
            if ((line[fdf->xinc] >= '0' && line[fdf->xinc] <= '9') && (line[fdf->xinc+1] == ' ' || line[fdf->xinc+1] == '\0'))
                fdf->nbpoints++;
            fdf->xinc++;
        }
        if (tmp == 0)
            tmp = fdf->nbpoints;
        else
            if (tmp != fdf->nbpoints)
               ;
        fdf->nblines++;
        free(line);
        line = NULL;
    }
    if (line)
        free(line);
}

t_map    *read_map(int fd, t_fdf *fdf)
{
    char *line;
    int iter;

    if (!(fdf->map = (t_map*)malloc(sizeof(t_map) * fdf->nblines)))
        return (NULL);
    line = NULL;
    while (get_next_line(fd, &line) > 0)
    {
        if (!(fdf->map[fdf->yinc].point = (t_point*)malloc(sizeof(t_point) * fdf->nbpoints)))
            return (NULL);
        fdf->xinc = 0;
        iter = 0;
        while (line[fdf->xinc] != '\0')
        {
            if ((line[fdf->xinc] >= '0' && line[fdf->xinc] <= '9') || line[fdf->xinc] == '-')
            {
                if (line[fdf->xinc+1] >= '0' && line[fdf->xinc+1] <= '9')
                {
                    fdf->startx = fdf->xinc;
                    while ((line[fdf->xinc] >= '0' && line[fdf->xinc] <= '9' )|| line[fdf->xinc] == '-')
                        fdf->xinc++;
                    fdf->map[fdf->yinc].point[iter].z = ft_atoi(ft_strsub(line, fdf->startx, fdf->xinc));
                }
                else{
                    fdf->map[fdf->yinc].point[iter].z = ft_atoi(&line[fdf->xinc]);
                    }
                iter++;
            }
            fdf->xinc++;
        }
        fdf->yinc++;
        free(line);
        line = NULL;
    }
    if (line)
        free(line);
    return (fdf->map);
}

t_map  *ft_open(char *av, t_fdf *fdf)
{
    int fd;
    t_map *map;

    fd = open(av, O_RDONLY);
    count_fdf(fd, &(*fdf));
    close(fd);
    fd = open(av, O_RDONLY);
    map = read_map(fd, &(*fdf));
    close(fd);
    return (fdf->map);
}