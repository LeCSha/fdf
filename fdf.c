#include "fdf.h"

// #define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

// int couleur(double t)
// {
// return (RGB(127.5 * (cos(t) + 1),127.5 * (sin(t) + 1),127.5 * (1 - cos(t))));
// }



void init_fdf(t_fdf *fdf)
{
    fdf->scalx = 20;
    fdf->scaly = 20;
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
}

void  count_fdf(int fd, t_fdf *fdf)
{
    char *line;
    int tmp;

    tmp = 0;
    line = NULL;
    printf("fd : %d\n", fd);
    while (get_next_line(fd, &line) != 0)
    {
      //printf("line en rentrant ds gnl de count : %s\n", line);
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
               ;// printf("NO WAYYY\n");
        fdf->nblines++;
        printf("nblines : %d\n", fdf->nblines);
        free(line);
        line = NULL;
    }
    printf("nb lines %d\n", fdf->nblines);
    if (line)
        free(line);
}

t_map    *read_map(int fd, t_fdf *fdf)
{
    char *line;
    int iter;
    t_map *map;

    if (!(map = (t_map*)malloc(sizeof(t_map) * fdf->nblines)))
        return (NULL);
    line = NULL;
    while (get_next_line(fd, &line) > 0)
    {
        if (!(map[fdf->yinc].point = (t_point*)malloc(sizeof(t_point) * fdf->nbpoints)))
            return (NULL);
        fdf->xinc = 0;
        iter = 0;
        printf("LINE DS READ %s\n", line);
        while (line[fdf->xinc] != '\0')
        {
            if ((line[fdf->xinc] >= '0' && line[fdf->xinc] <= '9') || line[fdf->xinc] == '-')
            {
                if (line[fdf->xinc+1] >= '0' && line[fdf->xinc+1] <= '9')
                {
                    fdf->startx = fdf->xinc;
                    while ((line[fdf->xinc] >= '0' && line[fdf->xinc] <= '9' )|| line[fdf->xinc] == '-')
                        fdf->xinc++;
                    map[fdf->yinc].point[iter].z = ft_atoi(ft_strsub(line, fdf->startx, fdf->xinc));
                    // printf("%d\n", map[fdf->yinc].point[iter].z);
                }
                else{
                    map[fdf->yinc].point[iter].z = ft_atoi(&line[fdf->xinc]);
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
    return (map);
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
    return (map);
}

void    go_trace_it(t_fdf *fdf)
{
    int ratio;
    int rigthleft;
    int updown;
    int i;

    i = 0;
    mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xc71515);
    if (fdf->dx > fdf->dy)
    {
        ratio = (2 * fdf->dy) - fdf->dx;
        updown = 2 * (fdf->dy - fdf->dx);
        rigthleft = 2 * fdf->dy;
        while(i < fdf->dx)
        {
            if (ratio >= 0)
            {
                ratio = ratio + updown;
                fdf->starty = fdf->starty + fdf->yinc;
            }
            else
                ratio = ratio + rigthleft;
            fdf->startx = fdf->startx + fdf->xinc;
            mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xc71515);
            i++;
        }
    }
    else
    {
        ratio = (2 * fdf->dx) - fdf->dy;
        rigthleft = 2 * (fdf->dx - fdf->dy);
        updown = 2 * fdf->dx;
        while(i < fdf->dy)
        {
            if (ratio >= 0)
            {
                ratio = ratio + rigthleft;
                fdf->startx = fdf->startx + fdf->xinc;
            }
            else
                ratio = ratio + updown;
            fdf->starty = fdf->starty + fdf->yinc;
            mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, fdf->startx, fdf->starty, 0xc71515);
            i++;
        }
    }
}

void    draw_base_line(t_fdf *fdf)
{
    fdf->dx = fdf->endx - fdf->startx;
    fdf->dy = fdf->endy - fdf->starty;
    fdf->xinc = (fdf->dx > 0) ? 1 : -1;
    fdf->yinc = (fdf->dy > 0) ? 1 : -1;
    fdf->dx = abs(fdf->dx);
    fdf->dy = abs(fdf->dy);
    go_trace_it(&(*fdf));
}

int coord_x(t_fdf *fdf, int x, int y)
{
    return (fdf->ptdepart + (fdf->scalx * x) - (fdf->scalx * y));
}
int coord_y(t_fdf *fdf, int x, int y, int z)
{
	return (fdf->ptdepart + (((fdf->scaly) * x) + ((fdf->scaly) * y) / 2) - (z * 2));
}

void    calc_horizontal_x(t_fdf *fdf, t_map *map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < fdf->nblines)
    {
        j = 0;
        while (j < fdf->nbpoints - 1)
        {
            fdf->startx = coord_x(fdf, j, i);
            fdf->starty = coord_y(fdf, j, i, map[i].point[j].z);
            fdf->endx = coord_x(fdf, j + 1, i);
            fdf->endy = coord_y(fdf, j + 1, i, map[i].point[j + 1].z);
            draw_base_line(&(*fdf));
            j++;
        }
        i++;
    }
}

void    calc_vertical_y(t_fdf *fdf, t_map *map)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < fdf->nblines - 1)
    {
        j = 0;
        while (j < fdf->nbpoints)
        {
            printf("z ds verrt y %d\n", map[i].point[j].z);
            fdf->startx = coord_x(fdf, j, i);
            fdf->starty = coord_y(fdf, j, i, map[i].point[j].z);
            fdf->endx = coord_x(fdf, j, i + 1);
            fdf->endy = coord_y(fdf, j, i + 1, map[i + 1].point[j].z);
            draw_base_line(fdf);
            j++;
        }
        i++;
    }
}

int main(int ac, char **av)
{
    t_fdf fdf;
    t_map *map;
    
    map = NULL;
    if (ac != 2)
    return (0);
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1500, 2000, "fdf 42");
    init_fdf(&fdf);
    map = ft_open(av[1], &fdf);
    printf("coucou\n");
    printf("z ds horizon x %d\n", map[5].point[5].z);
    printf("coucou\n");
    
    calc_horizontal_x(&fdf, &(*map));
    calc_vertical_y(&fdf, &(*map));
    mlx_loop(fdf.mlx_ptr);
    return (0);
}
