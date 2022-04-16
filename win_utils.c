/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:56 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/17 00:14:23 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
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
