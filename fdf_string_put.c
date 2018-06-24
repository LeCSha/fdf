#include "fdf.h"

void put_string(t_fdf *fdf)
{

  mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 50, 50, fdf.color, "ZOOM : ");
  mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 50, 50, fdf.color, );
  mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 50, 50, fdf.color, "Resolution : ");
  mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 50, 50, fdf.color, );
}
