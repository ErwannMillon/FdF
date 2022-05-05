#include "fdf.h"

int	get_x_scale(t_vars *frame)
{
	const int	height = tab_height(frame->flattab) / 2;
	const int	width = tab_width(frame->flattab) / 2;

	return (frame->xyztab[height][width][0]);
}

int	get_y_scale(t_vars *frame)
{
	const int	height = tab_height(frame->flattab) / 2;
	const int	width = tab_width(frame->flattab) / 2;

	return (frame->xyztab[height][width][1]);
}

float	abs_slope(float *a, float *b)
{
	float	slope;

	slope = 1000;
	if (b[0] - a[0] != 0)
		slope = fabs((b[1] - a[1]) / (b[0] - a[0]));
	return (floor(slope * 100) / 100);
}

void	init_vars(float ***tab, float ***xyztab, t_vars *vars, t_data *img)
{
	const int	x = 1000;
	const int	y = 600;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, x, y, "un fdf tarpin cool");
	img->img = mlx_new_image(vars->mlx, x, y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->winwidth = x;
	img->winheight = y;
	vars->img = img;
	vars->flattab = tab;
	vars->xyztab = xyztab;
	vars->color = 0x0000FF00;
	vars->disco = 0;
	vars->framenum = 0;
	vars->winwidth = x;
	vars->winheight = y;
}
