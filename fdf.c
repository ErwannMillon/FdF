/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:34 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/04 14:13:59 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int	file;
	if (argc != 2)
	{
		ft_printf("Invalid number of args");
		exit(0);
	}

	char *filepath = argv[1];
	float ***tab = str_arr_atoi(filepath);
	float ***xyztab = copy_int_arr(tab);
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	float flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	// float ***isotab = isometric_projection(tab);
	// float ***flat_tab = multiply_arr_by_matrix(isotab, flatten);
	// float ***flat_tab = tab;
	draw_wireframe(tab, xyztab, &img);
}