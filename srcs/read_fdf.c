/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 17:55:08 by abaille           #+#    #+#             */
/*   Updated: 2019/05/27 21:35:21 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	count_points(t_env *fdf, char *line)
{
	fdf->inc.x = 0;
	fdf->nbpoints = 0;
	while (line[fdf->inc.x] != '\0')
	{
		if ((line[fdf->inc.x] >= '0' && line[fdf->inc.x] <= '9')
		&& (line[fdf->inc.x + 1] == ' ' || line[fdf->inc.x + 1] == '\0'))
			fdf->nbpoints++;
		fdf->inc.x++;
	}
}

int		count_fdf(int fd, t_env *fdf)
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
		fdf->nblines++;
		if (!(fdf->nbpt = realloc(fdf->nbpt, fdf->nblines * sizeof(*fdf->nbpt))))
			print_error(1, fdf, 0);
		fdf->nbpt[fdf->nblines - 1] = fdf->nbpoints;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	return (0);
}

int		fill_map(t_env *fdf, char *line, char *tmp, int *iter)
{
	while (line[fdf->inc.x] != '\0')
	{
		if ((line[fdf->inc.x] >= '0' && line[fdf->inc.x] <= '9') ||
		line[fdf->inc.x] == '-')
		{
			if (line[fdf->inc.x + 1] >= '0' && line[fdf->inc.x + 1] <= '9')
			{
				fdf->start.x = fdf->inc.x;
				while ((line[fdf->inc.x] >= '0' && line[fdf->inc.x] <= '9') ||
				line[fdf->inc.x] == '-')
					fdf->inc.x++;
				if (!(tmp = ft_strsub(line, fdf->start.x, fdf->inc.x)))
					return (-1);
				fdf->map[fdf->inc.y].pt[*iter].z = ft_atoi(tmp);
				free(tmp);
				tmp = NULL;
			}
			else
				fdf->map[fdf->inc.y].pt[*iter].z = ft_atoi(&line[fdf->inc.x]);
			(*iter)++;
		}
		if (line[fdf->inc.x] != '\0')
			fdf->inc.x++;
	}
	return (0);
}

t_map	*read_map(int fd, t_env *fdf)
{
	char	*line;
	char	*tmp;
	int		iter;

	tmp = NULL;
	if (!(fdf->map = (t_map*)malloc(sizeof(t_map) * fdf->nblines)))
		return (NULL);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		iter = 0;
		if (!(fdf->map[fdf->inc.y].pt = (t_point*)malloc(sizeof(t_point) *
		fdf->nbpt[fdf->inc.y])))
			return (NULL);
		fdf->inc.x = 0;
		fill_map(fdf, line, tmp, &iter);
		fdf->inc.y++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	return (fdf->map);
}

int		ft_open(char *av, t_env *fdf)
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
