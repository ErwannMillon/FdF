/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:40 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/06 13:22:19 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoom_mouse_hook(int button, int x, int y, t_vars *frame)
{
	(void) x;
	(void) y;
	if (button == 4 || button == 5)
	{
		zoom(button, frame);
		frame->framenum += 1;
	}
	return (0);
}

void	translate_hook(int keycode, t_vars *frame)
{
	const int	move = 10;

	if (keycode == 53)
		close_win(keycode, frame);
	if (keycode == UP)
		translate(frame->xyztab, 0, -move);
	if (keycode == DOWN)
		translate(frame->xyztab, 0, move);
	if (keycode == LEFT)
		translate(frame->xyztab, -move, 0);
	if (keycode == RIGHT)
		translate(frame->xyztab, move, 0);
	free_triple_arr(frame->flattab);
	frame->framenum += 1;
	frame->flattab = flatten_arr(frame->xyztab);
}

void	change_color(t_vars *frame)
{
	static int	index = 0;
	const int	colors[4] = {0x42e3f5, 0x0000FF00, 0xcc239c, 0xb8ffc8};

	if (index == 4)
		index = 0;
	frame->framenum += 1;
	frame->color = colors[index];
	index++;
}

void	key_rotate(int keycode, t_vars *frame, float angle)
{
	const int	x_scale = get_x_scale(frame);
	const int	y_scale = get_y_scale(frame);
	const float	rotate_y_matrix[3][3] = {{cos(angle), 0, sin(angle)},
	{0, 1, 0},
	{-sin(angle), 0, cos(angle)}};
	const float	rotate_x_matrix[3][3] = {{1, 0, 0},
	{0,				cos(angle), -sin(angle)},
	{0,				sin(angle), cos(angle)}};

	translate(frame->xyztab, -x_scale, -y_scale);
	if (keycode == A || keycode == D)
		frame->xyztab = multiply_arr_by_matrix(frame->xyztab, rotate_y_matrix);
	if (keycode == W || keycode == S)
		frame->xyztab = multiply_arr_by_matrix(frame->xyztab, rotate_x_matrix);
	translate(frame->xyztab, x_scale, y_scale);
	free_triple_arr(frame->flattab);
	frame->framenum += 1;
	frame->flattab = flatten_arr(frame->xyztab);
}

int	key_hook(int keycode, t_vars *frame)
{
	close_win(keycode, frame);
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		translate_hook(keycode, frame);
	if (keycode == W || keycode == D)
		key_rotate(keycode, frame, -0.0574533);
	if (keycode == A || keycode == S)
		key_rotate(keycode, frame, 0.0574533);
	if (keycode == 78)
	{
		scale_z(frame->xyztab, 0.6);
		free_triple_arr(frame->flattab);
		frame->framenum += 1;
		frame->flattab = flatten_arr(frame->xyztab);
	}
	if (keycode == 69)
	{
		scale_z(frame->xyztab, 1.2);
		free_triple_arr(frame->flattab);
		frame->framenum += 1;
		frame->flattab = flatten_arr(frame->xyztab);
	}
	if (keycode == 49)
		frame->disco = 1;
	return (1);
}
