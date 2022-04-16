/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:30 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/17 01:18:09 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (((int)ay != (int)by) && (ax < 1919 && ax > 1 && ay < 1079 && ay > 1))
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
		// printf("ax: %f, ay: %f, bx: %f, by: %f, slope: %f\n", floor(10*ax)/10, floor(10*ay)/10, bx, by, slope );
		while ((int)ax != (int)bx && (int)ay != (int)by && (ax < 1919 && ax > 1 && ay < 1079 && ay > 1))
		{
			// printf("ax: %f, ay: %f, bx: %f, by: %f, slope: %f\n", floor(10*ax)/10, floor(10*ay)/10, floor(10*bx)/10, floor(10*by)/10, slope );
			my_mlx_pixel_put(data, (int)(ax), (int)(ay), color);
			if (ax < bx)
				ax += 0.25;
			else
				ax -= 0.25;
			if (ay < by)
				ay += fabs(slope) / 4;
			else
				ay -= fabs(slope) / 4;
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
			draw_straight_line(img, tab[i][j + 1], tab[i][j], 0x0000FF00);
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
	while (tab[i] && tab[i + 1])
	{
		j = 0;
		while (tab[i][j])
		{
			draw_straight_line(img, tab[i][j], tab[i + 1][j], 0x0000FF00);
			draw_straight_line(img, tab[i + 1][j], tab[i][j], 0x0000FF00);
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
	const int x_middle = xyztab[tab_height(xyztab) / 2][tab_width(xyztab) / 2][0];
	const int y_middle = xyztab[tab_height(xyztab) / 2][tab_width(xyztab) / 2][1];

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Le Fdf le plus style au monde le couz");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	translate(xyztab, 960 - x_middle, 540 - y_middle);
	tab = flatten_arr(xyztab);
	draw_rows(tab, &img);
	draw_cols(tab, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	vars.img = &img;
	vars.flattab = tab;
	vars.xyztab = xyztab;
	mlx_mouse_hook(vars.win, zoom_mouse_hook, &vars);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);

}