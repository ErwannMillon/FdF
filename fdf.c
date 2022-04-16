/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:34 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/17 00:06:25 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	int	file;
	if (argc != 2)
	{
		ft_printf("Invalid number of args");
		exit(0);
	}

	// file = open("./test_maps/42.fdf", O_RDONLY);
	char *filepath = argv[1];
	double ***tab = str_arr_atoi(filepath);
	double ***xyztab = str_arr_atoi(filepath);
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	double flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	// multiply_coordinates_by_matrix(coordinates, matrix);
	double ***isotab = isometric_projection(tab);
	double ***flat_tab = multiply_arr_by_matrix(tab, flatten);
	// print_tab(flat_tab);
	
	// translate(xyztab, xyz -900);
	draw_wireframe(flat_tab, xyztab, &img);
	// renderer();
}