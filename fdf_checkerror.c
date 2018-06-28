#include "fdf.h"

void free_fdf(t_fdf *fdf)
{
	int i;

	i = 0;
  if (fdf->map)
  {
    while (i < fdf->nblines)
    {
      if (fdf->map[i].point)
      {
        free(fdf->map[i].point);
        fdf->map[i].point = NULL;
      }
      i++;
    }
    free(fdf->map);
    fdf->map = NULL;
  }
  if (fdf->img)
  {
    free(fdf->img);
    fdf->img = NULL;
  }
  free(fdf);
  fdf = NULL;
}

int   check_file(char *file)
{
  int len;
  int res;

  res = 0;
  len = ft_strlen(file);
  res = ft_strncmp(&file[len - 4], ".fdf", 4);
  if (res != 0)
    return (print_error(5, NULL));
  return (1);
}

void fdf_usage()
{
  ft_putstr("--- Usage ---\n");
  ft_putstr("./fdf yourfile.fdf\n");
  ft_putstr("--- Keycode ---\n");
  ft_putstr("'+' zoom + \n");
  ft_putstr("'-' zoom -\n");
  ft_putstr("'Entr' change color\n");
  ft_putstr("'w' to run epileptic color\n");
  ft_putstr("'a' to run multicolor\n");
  ft_putstr("'ESC' to exit\n");
}

int check_char(char c)
{
  if ((c <= '0' && c >= '9') && c != ' ' && c != '-')
    return (-1);
  return (0);
}

int   print_error(int nb, t_fdf *fdf)
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
  if (fdf)
    free_fdf(fdf);
  return (-1);
}
