/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:40 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/17 01:31:18 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void zoom_mouse_hook(int button, int x, int y, t_vars *frame)
{
	if (button == 4 || button == 5)
		zoom(button, x, y, frame);
}


void translate_hook(int keycode, t_vars *frame)
{
	const int move = 10;
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
	frame->flattab = flatten_arr(frame->xyztab);
}

void key_rotate(int keycode, t_vars *frame)
{
	int	i;
	const double flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	double angle;
	const int x_scale = frame->xyztab[tab_height(frame->xyztab) / 2][tab_width(frame->xyztab) / 2][0];
	const int y_scale = frame->xyztab[tab_height(frame->xyztab) / 2][tab_width(frame->xyztab) / 2][1];
	angle = -0.0574533;
	i = 0;
	translate(frame->xyztab, -x_scale, -y_scale);
	if (keycode == S || keycode == A)
		angle *= -1;
	double rotate_y_matrix[3][3] =  {{cos(angle),	0, 	sin(angle)},
									{0.0, 			1, 	0}, 
									{-sin(angle),	0, 	cos(angle)}};
	double rotate_x_matrix[3][3] = {{1,				0, 			0},
									{0,				cos(angle), -sin(angle)},
									{0,				sin(angle), cos(angle)}};
	// double rotate_matrix[3][3] =  {{cos(angle), (-1 * sin(angle)), 0.0}, {sin(angle), cos(angle), 0.0}, {0.0, 0.0, 1.0}};
	if (keycode == A || keycode == D)
		frame->xyztab = multiply_arr_by_matrix(frame->xyztab, rotate_y_matrix);
	if (keycode == W || keycode == S)
		frame->xyztab = multiply_arr_by_matrix(frame->xyztab, rotate_x_matrix);
	translate(frame->xyztab, x_scale, y_scale);
	free_triple_arr(frame->flattab);
	frame->flattab = flatten_arr(frame->xyztab);
}

int	key_hook(int keycode, t_vars *frame)
{
	int	i;
	ft_printf("%d keyy\n", keycode);
	i = 0;
	close_win(keycode, frame);
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		translate_hook(keycode, frame);
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		key_rotate(keycode, frame);
	if (keycode == 78)
	{
		scale_z(frame->xyztab, 0.6);
		free_triple_arr(frame->flattab);
		frame->flattab = flatten_arr(frame->xyztab);
	}
	if (keycode == 69)
	{
		scale_z(frame->xyztab, 1.2);
		free_triple_arr(frame->flattab);
		frame->flattab = flatten_arr(frame->xyztab);
	}
}

int	render_next_frame(t_vars *frame)
{
	t_data	newimg;
	// printf("franem");
	draw_square(frame->img, 1920, 0x0000000);
	draw_rows(frame->flattab, frame->img);
	draw_cols(frame->flattab, frame->img);
	mlx_put_image_to_window(frame->mlx, frame->win, frame->img->img, 0, 0);
	return (1);
}
