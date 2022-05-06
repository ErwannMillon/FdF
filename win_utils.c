/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:56 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/06 12:55:09 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_tab(float ***tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i] && i == 0)
	{
		j = 0;
		while (tab[i][j])
		{
			ft_printf("i: %d index: %d, arr[%d, %d, %d]\n", i, j,
				(int)tab[i][j][0], (int)tab[i][j][1], (int)tab[i][j][2]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("=======================================================");
}

int	cross_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (1);
}

int	close_win(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (1);
}

int	render_next_frame(t_vars *frame)
{
	static int	oldframe = -1;

	if (frame->framenum != oldframe)
	{
		if (frame->disco)
			change_color(frame);
		draw_square(frame->img, 1920, 0x0000000);
		draw_rows(frame->flattab, frame->img, frame->color);
		draw_cols(frame->flattab, frame->img, frame->color);
		mlx_put_image_to_window(frame->mlx, frame->win, frame->img->img, 0, 0);
		oldframe = frame->framenum;
	}
	return (1);
}
