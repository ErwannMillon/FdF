/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:30 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/06 13:23:04 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	call_twice(t_data *img, float *linestart, int *c, float color)
{
	draw_straight_line(img, linestart, img->tab[c[0]][c[1]], color);
	draw_straight_line(img, img->tab[c[0]][c[1]], linestart, color);
}

void	draw_rows(float ***tab, t_data *img, float color)
{
	int		c[2];
	float	slope;
	float	*linestart;

	c[0] = 0;
	img->tab = tab;
	while (tab[c[0]])
	{
		c[1] = 0;
		slope = abs_slope(tab[c[0]][c[1]], tab[c[0]][c[1] + 1]);
		linestart = tab[c[0]][c[1]];
		while (tab[c[0]][c[1] + 1])
		{
			if (slope != abs_slope(tab[c[0]][c[1]], tab[c[0]][c[1] + 1]))
			{
				call_twice(img, linestart, c, color);
				linestart = tab[c[0]][c[1]];
				slope = abs_slope(tab[c[0]][c[1]], tab[c[0]][c[1] + 1]);
			}
			c[1]++;
		}
		draw_straight_line(img, linestart, tab[c[0]][c[1]], color);
		draw_straight_line(img, tab[c[0]][c[1]], linestart, color);
		c[0]++;
	}
}

void	draw_cols(float ***tab, t_data *img, float color)
{
	float	slope;
	float	*linestart;
	int		c[2];

	c[0] = 0;
	c[1] = 0;
	img->tab = tab;
	while (tab[c[0]][c[1]])
	{
		c[0] = 0;
		slope = abs_slope(tab[c[0]][c[1]], tab[c[0] + 1][c[1]]);
		linestart = tab[c[0]][c[1]];
		while (tab[c[0] + 1] && tab[c[0]][c[1]] && tab[c[0] + 1][c[1]])
		{
			if (slope != abs_slope(tab[c[0]][c[1]], tab[c[0] + 1][c[1]]))
			{
				call_twice(img, linestart, c, color);
				linestart = tab[c[0]][c[1]];
				slope = abs_slope(tab[c[0]][c[1]], tab[c[0] + 1][c[1]]);
			}
			c[0]++;
		}
		call_twice(img, linestart, c, color);
		c[1]++;
	}
}

void	draw_wireframe(float ***tab, float ***xyztab)
{
	t_data		img;
	t_vars		vars;

	tab = flatten_arr(tab);
	init_vars(tab, xyztab, &vars, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, cross_exit, &vars);
	mlx_mouse_hook(vars.win, zoom_mouse_hook, &vars);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}
