/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:08:51 by abaille           #+#    #+#             */
/*   Updated: 2019/05/28 18:56:16 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_palete(t_env *fdf)
{
	fdf->pal[0] = (t_pal){{0xE84C9A, 0x09BC8A, 0x32FFFF}, 5};
	fdf->pal[1] = (t_pal){{0x4A051C, 0x52FFB8, 0xD0FEF5}, 5};
	fdf->pal[2] = (t_pal){{0x90BEDE, 0x68EDC6, 0x90F3FF}, 5};
	fdf->pal[3] = (t_pal){{0x2D3047, 0xF29D00, 0xF7B538}, 5};
	fdf->pal[4] = (t_pal){{0x693668, 0xA74482, 0xF84AA7}, 5};

}

void	init_fdf(t_env *new)
{
	ft_bzero(new, sizeof(t_env));
	new->map = NULL;
	new->mlx.img_wth = 1000;
	new->scal = 50;
	new->rel_z = 4;
	new->incli = 2;
}

void	check_win_scale(t_env *fdf)
{
	int z_max;

	z_max = 0;
	calcul_coord(fdf);

	z_max = fabs(fdf->min.z) > fabs(fdf->max.z)
	? fabs(fdf->min.z) : fabs(fdf->max.z);
	while ((fdf->max.x + fabs(fdf->min.x) >= fdf->mlx.img_wth ||
				fdf->max.y - fdf->min.y > HEIGHT) && fdf->scal >= 0)
	{
		fdf->scal -= 2;
		calcul_coord(fdf);
	}
	fdf->dep.x = (fdf->mlx.img_wth / 2 - fdf->max.x / 2) + fdf->nbpoints * fdf->scal / 2;
	if (fdf->dep.x + fdf->max.x > WIDTH)
		fdf->dep.x -= fdf->dep.x + fdf->max.x - WIDTH;
	fdf->dep.y = HEIGHT / 2 - (fdf->max.y - fdf->min.y) / 2;
	if ((fdf->dep.y + fdf->min.y) < 0)
		fdf->dep.y += fabs(fdf->min.y);
}

void	put_string(t_env *fdf)
{
	void *win;

	win = mlx_new_window(fdf->mlx.mlx_ptr, 330, 355, "Keycode");
	mlx_string_put(fdf->mlx.mlx_ptr, win, 20, 40, 0x2EDD17, "Author: abaille");
	mlx_string_put(fdf->mlx.mlx_ptr, win, 20, 65, 0x2EDD17, "Zoom: [+][-]");
	mlx_string_put(fdf->mlx.mlx_ptr, win,
		20, 90, 0x2EDD17, "Move: [UP][DOWN][LEFT][RIGHT]");
	mlx_string_put(fdf->mlx.mlx_ptr, win,
		20, 115, 0x2EDD17, "Increase top: [U][I]");
	mlx_string_put(fdf->mlx.mlx_ptr, win, 20, 140, 0x2EDD17, "Rotate: [O][P]");
	mlx_string_put(fdf->mlx.mlx_ptr, win, 20, 165, 0x2EDD17, "Inclinate: [K][L]");
	mlx_string_put(fdf->mlx.mlx_ptr, win, 20, 215, 0x2EDD17, "Change color: [H]");
	mlx_string_put(fdf->mlx.mlx_ptr, win, 20, 265, 0x2EDD17, "Reset: [Entr]");
	mlx_string_put(fdf->mlx.mlx_ptr, win, 20, 295, 0x2EDD17, "Exit: [ESC]");
	fdf->mlx.win_str = win;
}

void	launch_fdf(char *av)
{
	t_env fdf;

	check_file(av);
	init_fdf(&fdf);
	init_palete(&fdf);
	ft_open(av, &fdf);
	fdf.mlx.mlx_ptr = mlx_init();
	fdf.mlx.win_ptr = mlx_new_window(fdf.mlx.mlx_ptr, WIDTH, HEIGHT, "fdf 42");
	check_win_scale(&fdf);
	if (!(fdf.mlx.img = (t_mlx_img *)malloc(sizeof(t_mlx_img))))
		print_error(6, &fdf, 0);
	fdf.mlx.img->img_ptr = mlx_new_image(fdf.mlx.mlx_ptr, fdf.mlx.img_wth, HEIGHT);
	fdf.mlx.img->data = (int *)mlx_get_data_addr(fdf.mlx.img->img_ptr,
		&fdf.mlx.img->bpp, &fdf.mlx.img->size_l, &fdf.mlx.img->endian);
	fdf.icolor = 0;
	fdf.pal_ptr = &(fdf.pal)[0];
	calc_horizontal_x(&fdf);
	calc_vertical_y(&fdf);
	put_string(&fdf);
	mlx_put_image_to_window(fdf.mlx.mlx_ptr,
		fdf.mlx.win_ptr, fdf.mlx.img->img_ptr, 0, 0);
	mlx_hook(fdf.mlx.win_ptr, 2, (1L << 0), key_fdf, &fdf);
	mlx_hook(fdf.mlx.win_str, 2, (1L << 0), key_fdf, &fdf);
	mlx_loop(fdf.mlx.mlx_ptr);
}

int		main(int ac, char **argv)
{
	if (ac != 2)
		print_error(5, NULL, 1);
	launch_fdf(argv[1]);
	return (0);
}
