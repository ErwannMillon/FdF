/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:56 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/04 13:06:08 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
int cross_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (1);
}

int close_win(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		ft_printf("escape interrupt, exiting with code : %d", keycode);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (1);
}
