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
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 1500, 2000, "fdf 42");
    return (mlx);
}

void   init_fdf(t_fdf *fdf, int nbpoint, int nblines)
{
    fdf->nblines = nbpoints;
    fdf->nbpoints = nblines;
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
    fdf->line = NULL;
    fdf->ptdepart = 300;
}

t_fdf count_fdf(int fd)
{
    // char *line;
    int tmp;
    t_fdf fdf;

    init_fdf(&fdf, 0, 0);
    // line = NULL;
    while (get_next_line(fd, &fdf.line) != 0)
    {
        while (fdf.line[fdf.xinc] != '\0')
        {
            if ((fdf.line[fdf.xinc] >= '0' && fdf.line[fdf.xinc] <= '9') && (fdf.line[fdf.xinc+1] == ' ' || fdf.line[fdf.xinc+1] == '\0'))
                fdf.nbpoints++;
            fdf.xinc++;
        }
        if (tmp == 0)
            tmp = fdf.nbpoints;
        else
            if (tmp != fdf.nbpoints)
                return (exit(1));
        fdf.nblines++;
        free(fdf.line);
        fdf.line = NULL;
    }
    if (fdf.line)
        free(fdf.line);
    return (fdf);
}

t_map *read_map(int fd, t_fdf *fdf)
{
    // char *line;
    int iter;

    init_fdf(&fdf, fdf->nbpoints, fdf->nblines);
    while (get_next_line(fd, &fdf->line) > 0)
    {
        if (!(map[fdf->yinc].point = (t_point*)malloc(sizeof(t_point) * nbpoints)))
            return (NULL);
        fdf->xinc = 0;
        iter = 0;
        while (fdf->line[fdf->xinc] != '\0')
        {
            if ((fdf->line[fdf->xinc] >= '0' && fdf->line[fdf->xinc] <= '9') || fdf->line[fdf->xinc] == '-')
            {
                if (fdf->line[fdf->xinc+1] >= '0' && fdf->line[fdf->xinc+1] <= '9')
                {
                    fdf->startx = fdf->xinc;
                    while ((fdf->line[fdf->xinc] >= '0' && fdf->line[fdf->xinc] <= '9' )|| fdf->line[fdf->xinc] == '-')
                        fdf->xinc++;
                    map[fdf->yinc].point[iter].z = ft_atoi(ft_strsub(fdf->line, fdf->startx, fdf->xinc));
                    map[fdf->yinc].point[iter].x = iter;
                    map[fdf->yinc].point[iter].y = fdf->yinc;
                }
                else{
                    map[fdf->yinc].point[iter].z = ft_atoi(&fdf->line[fdf->xinc]);
                    map[fdf->yinc].point[iter].x = iter;
                    map[fdf->yinc].point[iter].y = fdf->yinc;
                    }
                iter++;
            }
            fdf->xinc++;
        }
        fdf->yinc++;
        free(fdf->line);
        fdf->line = NULL;
    }
    if (fdf->line)
        free(fdf->line);
    return (map);
}

t_map *ft_open(char *av, t_map *map, t_fdf *fdf)
{
    int fd;
    t_map *map;

    if (!(fd = open(av, O_RDONLY)))
        exit(1);
    else
        fdf = count_fdf(fd);
    if (!(map = (t_map*)malloc(sizeof(t_map) * fdf.nblines)))
        return (NULL);
    close(fd);
    if (!(fd = open(av, O_RDONLY)))
        exit(1); 
    else
        map = read_fdf(fd);
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
    mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, fdf->startx, fdf->starty, 0xc71515);
    if (fdf->dx > fdf->dy)
    {
        ratio = (2 * fdf->dy) - fdf->dx;
        updown = 2 * (fdf->dy - fdf->dx);
        rigthleft = 2 * fdf->dy;
        while(i < fdf->dx)
        {
            if (ratio >= 0)
            {
                ratio += updown;
                fdf->starty = fdf->starty + fdf->yinc;
            }
            else
                ratio += rigthleft;
            fdf->startx = fdf->startx + fdf->xinc;
            mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, fdf->startx, fdf->starty, 0xc71515);
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
                ratio += rigthleft;
                fdf->startx = fdf->startx + fdf->xinc;
            }
            else
                ratio += updown;
            fdf->starty = fdf->starty + fdf->yinc;
            mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, fdf->startx, fdf->starty, 0xc71515);
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
    go_trace_it(fdf);
}

int coord_x(t_fdf *fdf, int x, int y)
{
    return (fdf->ptdepart + (fdf->scalx * y) + (fdf->scalx * x));
}
int coord_y(t_fdf *fdf, int x, int y, int z)
{
	return (fdf->ptdepart + fdf->starty + ((fdf->scaly) * x) + ((fdf->scaly) * y) - (z * 2));
}

void    calc_horizontal_x(t_fdf *fdf, t_map *map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    init_fdf(&fdf);
    while (i < fdf->nblines)
    {
        j = 0;
        while (j < fdf->nbpoints - 1)
        {
            fdf->startx = coord_x(fdf, j, i);
            fdf->starty = coord_y(fdf, j, i, map[i]->point[j].z);
            fdf->endx = coord_x(fdf, j + 1, i);
            fdf->endy = coord_y(fdf, j + 1, i, map[i]->point[j].z);
            draw_base_line(fdf);
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
    init_fdf(&fdf);
    while (i < fdf->nblines)
    {
        j = 0;
        while (j < fdf->nbpoints - 1)
        {
            fdf->startx = coord_x(fdf, j, i);
            fdf->starty = coord_y(fdf, j, i, map[i]->point[j].z);
            fdf->endx = coord_x(fdf, j, i + 1);
            fdf->endy = coord_y(fdf, j, i + 1, map[i]->point[j].z);
            draw_base_line(fdf);
            j++;
        }
        i++;
    }    
}

void fdf(t_mlx mlx, t_map *map)
{
    calc_horizontal_x(&fdf, map);
    calc_vertical_y(&fdf, map);
    mlx_loop(mlx.mlx_ptr);
}


}
int main(int ac, char **av)
{
    t_mlx mlx;
    t_map *map;
    t_fdf fdf;
    // int *tab;
    if (ac != 2)
        return (0);
    map = NULL;
    map = ft_open(av[1], map, &fdf);
    mlx = init_mlx();
    fdf(mlx, map);
    return (0);
}
