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

void	draw_straight_line(t_data *data, int *a, int *b, int color)
{
	int	ax = a[0];
	int	ay = a[1];
	int	bx = b[0];
	int	by = b[1];
	float	slope;


	slope = (by - ay) / (bx - ax);
	while (ax != bx && ax < 1900)
	{
		// ft_printf("ax: %d, ay: %d, bx: %d, by: %d", ax, ay, bx, by);
		my_mlx_pixel_put(data, ax, ay, color);
		ax++;
		ay += slope;
	}

}

int renderer(void)
{
	t_data	img;
	t_data	img2;
	int red = 0x00FF0000;
	int a[2] = {900, 500};
	int b[2] = {800, 500};
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");

	mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);

	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img2.img = mlx_new_image(vars.mlx, 1920, 1080);
	img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
	
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// draw_square(&img, a, 200, 0x0000FF00);
	// draw_rotated_square(&img, a, 200, red);
	// draw_straight_line(&img, a, b, 0x00FF0000);
	// draw_square(&img, a, 200, 0x00FF0000);
	draw_rotated_square(&img, a, 40, red);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
}

int	main(int argc, char **argv)
{
	// if (argc != 2)
	// {
	// 	ft_printf("Invalid number of args");
	// 	exit(0)
	// }
	int	file;

	// file = open("./test_maps/42.fdf", O_RDONLY);
	char *filepath = "./test_maps/42.fdf";
	// file = open(filepath, O_RDONLY);
	// char *line  = get_next_line(file);

	// while (line)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(file);
	// }
	double ***tab = str_arr_atoi(filepath);
	
	// renderer();
}