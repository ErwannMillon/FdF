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

void	draw_straight_line(t_data *data, double *a, double *b, int color)
{
	double	ax = a[0];
	double	ay = a[1];
	double	bx = b[0];
	double	by = b[1];
	float	slope;
	
	slope = (by - ay) / (bx - ax);
	while (ax != bx && ax < 1900 && ay < 1000)
	{
		printf("ax: %f, ay: %f, bx: %f, by: %f, slope: %f\n", ax, ay, bx, by, slope );
		my_mlx_pixel_put(data, (int)(ax + ORIGIN_X), (int)(ay + ORIGIN_Y), color);
		if (ax < bx)
			ax++;
		else
			ax--;
		ay += slope;
	}

}

void draw_wireframe(double ***tab, t_vars *vars, t_data *data)
{
	int	i;
	int	j;
	int	k;
	double *result;

 	i = 0;
	while (tab[i + 9])
	{
		j = 0;
		while (tab[i][j + 1])
		{
			draw_straight_line(data, tab[i][j], tab[i][j+1], 0x0000FF00);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, data->img, 0, 0);
}