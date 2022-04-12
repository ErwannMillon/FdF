#include "fdf.h"
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square(t_data *data, int *a, int size, int color)
{
	int x = a[0];
	int y = a[1];
	
	int y_counter = 0;
	int x_counter = 0;

	int x_cop;
	while (y_counter < size)
	{
		x_cop = x;
		x_counter = 0;
		while (x_counter < size)
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


void draw_rotated_square(t_data *data, int *a, int size, int color)
{
	double x = a[0];
	double y = a[1];
	double angle = PI / 4;
	int x_counter = 0;
	int y_counter = 0;

	double x_cop = x;
	double x_rot = 0;
	double y_rot = 0;

	printf("rotx: %lf, roty: %lf\n", x_rot, y_rot);

	while (y_counter < size)
	{
		x = x_cop;
		x_counter = 0;
		while (x_counter < size)
		{
			x_rot = (cos(angle) * x) - (sin(angle) * y);
			y_rot = (sin(angle) * x) + (cos(angle) * y);
			printf("ax: %lf, ay: %lf\n", x_rot, y_rot);
			my_mlx_pixel_put(data, (int)x_rot - ORIGIN_X, (int)y_rot - ORIGIN_Y, color);
			x++;
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
	printf("vertical: ax: %f, ay: %f, bx: %f, by: %f, \n", ax, ay, bx, by);
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
	float	slope;
	if (bx == ax)
		draw_vertical_line(data, a, b, color);
	else
	{
		slope = (by - ay) / (bx - ax);
		printf("ax: %f, ay: %f, bx: %f, by: %f, slope: %f\n", ax, ay, bx, by, slope );
		while (((int)ax != (int)bx) && ((int)ay != (int)by) && (ax < 1900 && ax > 100 && ay < 1000 && ay > 100))
		{
			// printf("ax: %f, ay: %f, bx: %f, by: %f, slope: %f\n", ax, ay, bx, by, slope);
			my_mlx_pixel_put(data, (int)(ax), (int)(ay), color);
			if (ax < bx)
				ax++;
			else
				ax--;
			
			ay += fabs(slope);
		}
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

void draw_wireframe(double ***tab, t_vars *varss, t_data *data)
{
	int	i;
	int	j;
	int	k;
	double *result;
	double a[2] = {0, 100};
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
 	i = 0;
	j = 0;
	mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);
	draw_rows(tab, &img);
	// while (tab[i])
	// {
	// 	j = 0;
	// 	while (tab[i][j + 1])
	// 	{
	// 		draw_straight_line(&img, tab[i][j], tab[i][j + 1], 0x0000FF00);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// i = 0;

	while (tab[i + 1])
	{
		j = 0;
		while (tab[i][j])
		{
			draw_straight_line(&img, tab[i][j], tab[i + 1][j], 0x0000FF00);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);

}