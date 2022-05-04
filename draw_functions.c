/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:30 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/04 14:10:56 by gmillon          ###   ########.fr       */
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
	while (y_counter < size && y < data->winheight)
	{
		x_cop = x;
		x_counter = 0;
		while (x_counter < size && y < data->winheight && x_cop < data->winwidth)
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

void	draw_vertical_line(t_data *data, float *a, float *b, int color)
{
	float	ax = a[0] + ORIGIN_X;
	float	ay = a[1] + ORIGIN_Y;
	float	bx = b[0] + ORIGIN_X;
	float	by = b[1] + ORIGIN_Y;
	int	slope;
	slope = -1;
	if	(ay < by)
		slope = 1;
	// printf("vertical: ax: %f, ay: %f, bx: %f, by: %f, \n", ax, ay, bx, by);
	while (((int)ay != (int)by) && (ax < data->winwidth && ax > 0 && ay < data->winheight && ay > 1))
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

void	draw_straight_line(t_data *data, float *a, float *b, int color)
{
	float	ax = a[0] + ORIGIN_X;
	float	ay = a[1] + ORIGIN_Y;
	float	bx = b[0] + ORIGIN_X;
	float	by = b[1] + ORIGIN_Y;
	float	slope;
	
	if (bx == ax)
		draw_vertical_line(data, a, b, color);
	else
	{
		slope = (by - ay) / (bx - ax);
		while ((int)ax != (int)bx && (int)ay != (int)by)
		{
			if (ax < data->winwidth && ax > 0 && ay < data->winheight && ay > 0)
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

float	abs_slope(float *a, float *b)
{
	float	slope;
	
	slope = 1000;
	if (b[0] - a[0] != 0)
		slope = fabs((b[1] - a[1]) / (b[0] - a[0]));
	return (floor(slope * 100) / 100);
}

void draw_rows(float ***tab, t_data *img, float color)
{
	int		i;
	int		j;
	float	slope;
	float	*linestart;
	
	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		slope = abs_slope(tab[i][j], tab[i][j + 1]);
		linestart = tab[i][j];
		while (tab[i][j + 1])
		{
			if (slope != abs_slope(tab[i][j], tab[i][j + 1]))
			{
				// printf("drawing: slope = %f, calcul : %f coordinates (%d, %d) \n ", slope, abs_slope(tab[i][j], tab[i][j + 1]), i, j);
				draw_straight_line(img, linestart, tab[i][j], color);
				draw_straight_line(img, tab[i][j], linestart, color);
				linestart = tab[i][j];
				slope = abs_slope(tab[i][j], tab[i][j + 1]);
			}
			// draw_straight_line(img, tab[i][j + 1], tab[i][j], color);
			j++;
		}
		draw_straight_line(img, linestart, tab[i][j], color);
		draw_straight_line(img, tab[i][j], linestart, color);
		i++;
	}
}

void draw_cols(float ***tab, t_data *img, float color)
{
	int		i;
	int		j;
	float	slope;
	float	oldslope;
	float	*linestart;

	i = 0;
	j = 0;
	
	while (tab[i][j])
	{
		i = 0;
		slope = abs_slope(tab[i][j], tab[i + 1][j]);
		linestart = tab[i][j];
		while (tab[i + 1] && tab[i][j] && tab[i + 1][j])
		{
			if (slope != abs_slope(tab[i][j], tab[i + 1][j]))
			{
				// printf("drawing: slope = %f, calcul : %f coordinates (%d, %d) \n ", slope, abs_slope(tab[i][j], tab[i + 1][j]), i, j);
				draw_straight_line(img, linestart, tab[i][j], color);
				draw_straight_line(img, tab[i][j], linestart, color);
				linestart = tab[i][j];
				slope = abs_slope(tab[i][j], tab[i + 1][j]);
			}
			i++;
		}
		if (slope == abs_slope(linestart, tab[i][j]))
		{
			draw_straight_line(img, linestart, tab[i][j], color);
			draw_straight_line(img, tab[i][j], linestart, color);
		}
		j++;
	}
}

void draw_wireframe(float ***tab, float ***xyztab, t_data *data)
{
	float *result;
	t_data	img;
	t_vars	vars;
	t_frame frame;
	const int x_middle = xyztab[tab_height(xyztab) / 2][tab_width(xyztab) / 2][0];
	const int y_middle = xyztab[tab_height(xyztab) / 2][tab_width(xyztab) / 2][1];
	const int x = 1000;
	const int y = 600;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, x, y, "Le Fdf le plus style au monde");
	img.img = mlx_new_image(vars.mlx, x, y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.winwidth = x;
	img.winheight = y;
	// translate(xyztab, 500 - x_middle, 200 - y_middle);
	tab = flatten_arr(tab);
	draw_rows(tab, &img, 0x000000FF);
	draw_cols(tab, &img, 0x000000FF);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	vars.img = &img;
	vars.flattab = tab;
	vars.xyztab = xyztab;
	vars.color = 0x0000FF00;
	vars.disco = 0;
	vars.framenum = 0;
	vars.winwidth = x;
	vars.winheight = y;
	mlx_hook(vars.win, 17, 0, cross_exit, &vars);
	mlx_mouse_hook(vars.win, zoom_mouse_hook, &vars);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);

}