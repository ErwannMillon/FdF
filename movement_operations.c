/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:52 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/06 13:20:34 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	tab_height(float ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	tab_width(float ***tab)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (tab[0][j])
		j++;
	return (j);
}

void	zoom(int button, t_vars *frame)
{
	int			i;
	int			j;
	float		***arr;
	float		scale;

	scale = 0.9;
	if (button == 4)
		scale = 1.1;
	arr = frame->xyztab;
	i = 0;
	while (arr[i] && (button == 4 || button == 5))
	{
		j = 0;
		while (arr[i][j] && scale <= 20 && scale >= 0.05)
		{
			arr[i][j][0] *= scale;
			arr[i][j][1] *= scale;
			arr[i][j][2] *= scale;
			j++;
		}
		i++;
	}
	free_triple_arr(frame->flattab);
	frame->flattab = flatten_arr(frame->xyztab);
}

void	translate(float ***tab, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			tab[i][j][0] += x;
			tab[i][j][1] += y;
			j++;
		}
		i++;
	}
}
