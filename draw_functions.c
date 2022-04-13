#include "fdf.h"
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_data *data, int size, int color)
{
	int x = 0;
	int y = 0;
	
	int y_counter = 0;
	int x_counter = 0;

	int x_cop;
	while (y_counter < size && y < 1080)
	{
		x_cop = x;
		x_counter = 0;
		while (x_counter < size && y < 1080 && x_cop < 1920)
		{
			// ft_printf("ax: %d, ay: %d", x_cop, y);
			my_mlx_pixel_put(data, x_cop, y, color);
			x_cop++;
			x_counter++;
		}
		y++;
		y_counter++;
	}
}

void	draw_vertical_line(t_data *data, double *a, double *b, int color)
{
	double	ax = a[0] + ORIGIN_X;
	double	ay = a[1] + ORIGIN_Y;
	double	bx = b[0] + ORIGIN_X;
	double	by = b[1] + ORIGIN_Y;
	int	slope;
	slope = -1;
	if	(ay < by)
		slope = 1;
	// printf("vertical: ax: %f, ay: %f, bx: %f, by: %f, \n", ax, ay, bx, by);
	while (((int)ay != (int)by) && (ax < 1900 && ax > 100 && ay < 1000 && ay > 100))
	{
		// printf("vertical: ax: %f, ay: %f, bx: %f, by: %f, \n", ax, ay, bx, by);
		my_mlx_pixel_put(data, (int)(ax), (int)(ay), color);
		if (ax < bx)
			ax++;
		else
			ax--;
		ay += slope;
	}
}

void	draw_straight_line(t_data *data, double *a, double *b, int color)
{
	double	ax = a[0] + ORIGIN_X;
	double	ay = a[1] + ORIGIN_Y;
	double	bx = b[0] + ORIGIN_X;
	double	by = b[1] + ORIGIN_Y;
	// int		test[2];
	float	slope;
	if (bx == ax)
		draw_vertical_line(data, a, b, color);
	else
	{
		slope = (by - ay) / (bx - ax);
		// printf("ax: %f, ay: %f, bx: %f, by: %f, slope: %f\n", ax, ay, bx, by, slope );
		while (((int)ax != (int)bx) && ((int)ay != (int)by) && (ax < 1910 && ax > 2 && ay < 1078 && ay > 2))
		{
			// printf("ax: %f, ay: %f, bx: %f, by: %f, slope: %f\n", ax, ay, bx, by, slope);
			my_mlx_pixel_put(data, (int)(ax), (int)(ay), color);
			if (ax < bx)
				ax++;
			else
				ax--;
			if (ay < by)
				ay += fabs(slope);
			else
				ay += slope;
		}
		// test[0] = ax;
		// test[1] = ay;
		// draw_square(data, test, 10, 0x00FF0000);
	}
}

void draw_rows(double ***tab, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j + 1])
		{
			draw_straight_line(img, tab[i][j], tab[i][j + 1], 0x0000FF00);
			j++;
		}
		i++;
	}
}

void draw_cols(double ***tab, t_data *img)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
	while (tab[i + 1])
	{
		j = 0;
		while (tab[i][j])
		{
			draw_straight_line(img, tab[i][j], tab[i + 1][j], 0x0000FF00);
			j++;
		}
		i++;
	}
}

void draw_wireframe(double ***tab, double ***xyztab, t_data *data)
{
	double *result;
	t_data	img;
	t_vars	vars;
	t_frame frame;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);
	draw_rows(tab, &img);
	draw_cols(tab, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	vars.img = &img;
	vars.flattab = tab;
	vars.xyztab = xyztab;
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_hook(vars.win, ON_DESTROY, 0, close, &vars);
	mlx_hook(vars.win, 4, 1L<<6, &mouse_rotate, &vars);
	mlx_hook(vars.win, 6, 1L<<8, &mouse_hook, &vars);
	mlx_mouse_hook(vars.win, zoom, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);

}