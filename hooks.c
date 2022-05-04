/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:40 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/04 13:55:04 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void zoom_mouse_hook(int button, int x, int y, t_vars *frame)
{
	if (button == 4 || button == 5)
	{
		zoom(button, x, y, frame);
		frame->framenum += 1;
	}
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
	frame->framenum += 1;
	frame->flattab = flatten_arr(frame->xyztab);
}

// void extrude(t_vars *frame, float scale)
// {
// 	const float ext[3][3] = {{cos(BETA), sin(ALPHA) * sin(BETA), -(cos(ALPHA) * sin(BETA))}, {0, cos(ALPHA), sin(ALPHA)}, {2 * sin(BETA), -2 * cos(BETA) * sin(ALPHA), 2 * cos(ALPHA)* cos(BETA)}};
// 	frame->xyztab = multiply_arr_by_matrix(frame->xyztab, ext);
// 	frame->framenum += 1;
// 	frame->flattab = flatten_arr(frame->xyztab);
// }

void	change_color(t_vars *frame)
{
	static int index = 0;
	const int colors[4] = {0x42e3f5, 0x0000FF00, 0xcc239c, 0xb8ffc8};
	if (index == 4)
		index = 0;
	frame->framenum += 1;
	frame->color = colors[index];
	index++;
}

void key_rotate(int keycode, t_vars *frame)
{
	int			i;
	float		angle;
	const int	x_scale = frame->xyztab[tab_height(frame->xyztab) / 2][tab_width(frame->xyztab) / 2][0];
	const int	y_scale = frame->xyztab[tab_height(frame->xyztab) / 2][tab_width(frame->xyztab) / 2][1];
	
	angle = -0.0574533;
	i = 0;
	translate(frame->xyztab, -x_scale, -y_scale);
	if (keycode == S || keycode == A)
		angle *= -1;
	float rotate_y_matrix[3][3] =  {{cos(angle),	0, 	sin(angle)},
									{0.0, 			1, 	0}, 
									{-sin(angle),	0, 	cos(angle)}};
	float rotate_x_matrix[3][3] = {{1,				0, 			0},
									{0,				cos(angle), -sin(angle)},
									{0,				sin(angle), cos(angle)}};
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
	return(1);
}

int	render_next_frame(t_vars *frame)
{
	static int oldframe = -1;
	t_data	newimg;
	// printf("franem");

	if (frame->framenum != oldframe)
	{
		if (frame->disco)
			change_color(frame);
		printf("rerendering\n");
		draw_square(frame->img, 1920, 0x0000000);
		draw_rows(frame->flattab, frame->img, frame->color);
		draw_cols(frame->flattab, frame->img, frame->color);
		mlx_put_image_to_window(frame->mlx, frame->win, frame->img->img, 0, 0);
		oldframe = frame->framenum;	
	}
	
	return (1);
}
