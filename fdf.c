#include "fdf.h"

int renderer(void)
{
	t_data	img;
	// t_data	img2;
	// int red = 0x00FF0000;
	double a[2] = {0, 0};
	double b[2] = {200, 100};
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");

	mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);

	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// img2.img = mlx_new_image(vars.mlx, 1920, 1080);
	// img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
	
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// draw_square(&img, a, 200, 0x0000FF00);
	// draw_rotated_square(&img, a, 200, red);
	// draw_straight_line(&img, a, b, 0x00FF0000);
	draw_square(&img, a, 200, 0x00FF0000);
	// draw_rotated_square(&img, a, 40, red);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (1);
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
	double ***tab = str_arr_atoi(filepath);
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	double matrix[3][3] = {{1.0, 2.0 ,3.0},{4.0, 0.0, 3.0},{1.0, 9.0, 11.0}};
	double coordinates[3] = {5.0, 6.0 ,7.0};
	// multiply_coordinates_by_matrix(coordinates, matrix);
	double ***flat_tab = isometric_projection(tab);
	draw_wireframe(flat_tab, NULL, &img);
	// renderer();
}