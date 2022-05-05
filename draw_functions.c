/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:30 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/05 19:50:40 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *data, int size, int color)
{
	const int	x = 0;
	int			y;
	int			y_counter;
	int			x_counter;
	int			x_cop;

	y = 0;
	y_counter = 0;
	x_counter = 0;
	while (y_counter < size && y < data->winheight)
	{
		x_cop = x;
		x_counter = 0;
		while (x_counter < size && y < data->winheight
			&& x_cop < data->winwidth)
		{
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
	float		ax;
	float		ay;
	const float	bx = b[0] + ORIGIN_X;
	const float	by = b[1] + ORIGIN_Y;
	int			slope;

	ax = a[0] + ORIGIN_X;
	ay = a[1] + ORIGIN_Y;
	slope = -1;
	if (ay < by)
		slope = 1;
	while (((int)ay != (int)by) && (ax < data->winwidth && ax > 0
			&& ay < data->winheight && ay > 1))
	{
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
	float		ax;
	float		ay;
	const float	bx = b[0] + ORIGIN_X;
	const float	by = b[1] + ORIGIN_Y;
	float		slope;

	ax = a[0] + ORIGIN_X;
	ay = a[1] + ORIGIN_Y;
	if (bx == ax)
		draw_vertical_line(data, a, b, color);
	else
	{
		slope = (by - ay) / (bx - ax);
		while ((int)ax != (int)bx && (int)ay != (int)by)
		{
			if (ax < data->winwidth && ax > 0 && ay < data->winheight && ay > 0)
				my_mlx_pixel_put(data, (int)(ax), (int)(ay), color);
			ax += -copysign(0.25, (ax - bx));
			ay += -copysign((fabs(slope) / 4), (ay - by));
		}
	}
}



void	draw_rows(float ***tab, t_data *img, float color)
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
				draw_straight_line(img, linestart, tab[i][j], color);
				draw_straight_line(img, tab[i][j], linestart, color);
				linestart = tab[i][j];
				slope = abs_slope(tab[i][j], tab[i][j + 1]);
			}
			j++;
		}
		draw_straight_line(img, linestart, tab[i][j], color);
		draw_straight_line(img, tab[i][j], linestart, color);
		i++;
	}
}

void	draw_cols(float ***tab, t_data *img, float color)
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

void draw_wireframe(float ***tab, float ***xyztab)
{
	float		*result;
	t_data		img;
	t_vars		vars;
	t_frame		frame;

	tab = flatten_arr(tab);
	init_vars(tab, xyztab, &vars, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, cross_exit, &vars);
	mlx_mouse_hook(vars.win, zoom_mouse_hook, &vars);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
