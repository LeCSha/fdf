/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_checkerror.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:00:02 by abaille           #+#    #+#             */
/*   Updated: 2018/07/18 15:00:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_file(char *file)
{
	int len;
	int res;

	res = 0;
	len = ft_strlen(file);
	res = ft_strncmp(&file[len - 4], ".fdf", 4);
	if (res != 0)
		print_error(5, NULL, 1);
}

void	fdf_usage(void)
{
	ft_putstr("--- Usage ---\n");
	ft_putstr(" \n");
	ft_putstr("./fdf yourfile.fdf\n");
	ft_putstr(" \n");
}

int		check_char(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] >= '0' && line[i] <= '9')
		&& line[i] != ' ' && line[i] != '-')
			return (-1);
		i++;
	}
	return (0);
}

void	print_error(int nb, t_fdf *fdf, int ref)
{
	if (nb == 1)
		ft_putstr("Problem opening/closing file - file missing/not valid\n");
	else if (nb == 2)
		ft_putstr("Map not valid\n");
	else if (nb == 3)
		ft_putstr("Problem reading file/allocation failed\n");
	else if (nb == 4)
		ft_putstr("Map size not valid/no value\n");
	else if (nb == 5)
		fdf_usage();
	else if (nb == 6)
		ft_putstr("Allocation failed\n");
	if (ref == 0)
		free_fdf(fdf);
	else
		free(fdf);
	exit(0);
}
