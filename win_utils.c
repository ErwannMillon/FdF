#include "fdf.h"

int close_win(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		ft_printf("escape interrupt, exiting with code : %d", keycode);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (1);
}
