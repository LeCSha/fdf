/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:55:08 by abaille           #+#    #+#             */
/*   Updated: 2018/07/01 17:55:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	count_points(t_fdf *fdf, char *line)
{
	fdf->xinc = 0;
	fdf->nbpoints = 0;
	while (line[fdf->xinc] != '\0')
	{
		if ((line[fdf->xinc] >= '0' && line[fdf->xinc] <= '9')
		&& (line[fdf->xinc + 1] == ' ' || line[fdf->xinc + 1] == '\0'))
			fdf->nbpoints++;
		fdf->xinc++;
	}
}

int		count_fdf(int fd, t_fdf *fdf)
{
	char	*line;
	int		tmp;

	tmp = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (check_char(line) == -1)
			print_error(2, fdf, 0);
		count_points(fdf, line);
		if (tmp == 0)
			tmp = fdf->nbpoints;
		else if (tmp != fdf->nbpoints || fdf->nbpoints < 2)
			print_error(4, fdf, 0);
		fdf->nblines++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	if (fdf->nblines < 2)
		print_error(4, fdf, 0);
	return (0);
}

int		fill_map(t_fdf *fdf, char *line, char *tmp, int iter)
{
	while (line[fdf->xinc] != '\0')
	{
		if ((line[fdf->xinc] >= '0' && line[fdf->xinc] <= '9') ||
		line[fdf->xinc] == '-')
		{
			if (line[fdf->xinc + 1] >= '0' && line[fdf->xinc + 1] <= '9')
			{
				fdf->startx = fdf->xinc;
				while ((line[fdf->xinc] >= '0' && line[fdf->xinc] <= '9') ||
				line[fdf->xinc] == '-')
					fdf->xinc++;
				if (!(tmp = ft_strsub(line, fdf->startx, fdf->xinc)))
					return (-1);
				fdf->map[fdf->yinc].pt[iter].z = ft_atoi(tmp);
				free(tmp);
				tmp = NULL;
			}
			else
				fdf->map[fdf->yinc].pt[iter].z = ft_atoi(&line[fdf->xinc]);
			iter++;
		}
		if (line[fdf->xinc] != '\0')
			fdf->xinc++;
	}
	return (0);
}

t_map	*read_map(int fd, t_fdf *fdf)
{
	char	*line;
	char	*tmp;
	int		iter;

	tmp = NULL;
	iter = 0;
	if (!(fdf->map = (t_map*)malloc(sizeof(t_map) * fdf->nblines)))
		return (NULL);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(fdf->map[fdf->yinc].pt = (t_point*)malloc(sizeof(t_point) *
		fdf->nbpoints)))
			return (NULL);
		fdf->xinc = 0;
		fill_map(fdf, line, tmp, iter);
		fdf->yinc++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	return (fdf->map);
}

int		ft_open(char *av, t_fdf *fdf)
{
	int fd;

	if ((fd = open(av, O_RDONLY)) == -1)
		print_error(1, fdf, 1);
	else
		count_fdf(fd, fdf);
	if (close(fd) == -1 || (fd = open(av, O_RDONLY)) == -1)
		print_error(1, fdf, 0);
	else if (!(fdf->map = read_map(fd, fdf)))
		print_error(3, fdf, 0);
	if (close(fd) == -1)
		print_error(1, fdf, 0);
	return (0);
}
