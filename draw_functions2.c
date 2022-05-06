/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:24:31 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/06 22:35:57 by gmillon          ###   ########.fr       */
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
			ax += -copysign(1, (ax - bx));
			ay += -copysign((fabs(slope)), (ay - by));
		}
	}
}
