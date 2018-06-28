#include "fdf.h"

int   check_file(char *file)
{
  int len;
  int res;

  res = 0;
  len = ft_strlen(file);
  res = ft_strncmp(&file[len - 4], ".fdf", 4);
  if (res != 0)
    return (print_error(5));
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
}

int check_char(char c)
{
  if ((c <= '0' && c >= '9') && c != ' ' && c != '-')
    return (-1);
  return (0);
}

int   print_error(int nb)
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
  return (-1);
}
