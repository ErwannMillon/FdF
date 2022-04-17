/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:52 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/17 19:36:31 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	tab_height(float ***tab)
{
	int	i;

	i = 0;
	while(tab[i])
		i++;
	return (i);
}


int	tab_width(float ***tab)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while(tab[0][j])
		j++;
	return (j);
}

void zoom(int button, int x,int y, t_vars *frame)
{
	int		i;
	int		j;
	float	***arr;
	float scale = 1;
	static int oldbutton = 0;
	
	// if (button != oldbutton)
	// 	scale = 1;
	if (button == 4)
		scale += 0.1;
	if (button == 5)
		scale -= 0.1;
	arr = frame->xyztab;
	i = 0;
	printf("adfkladsfj\n");
	while (arr[i] && (button == 4 || button == 5))
	{
		j = 0;
		while (arr[i][j] && (button == 4 || button == 5) && scale <= 20 && scale >= 0.05)
		{
			arr[i][j][0] *= scale;
			arr[i][j][1] *= scale;
			arr[i][j][2] *= scale;
			// printf("index: %d, arr[%f, %f, %f]\n", j, arr[i][j][0],arr[i][j][1],arr[i][j][2]);
			j++;
		}
		i++;
	}
	oldbutton = button;
	free_triple_arr(frame->flattab);
	frame->flattab = flatten_arr(frame->xyztab);
}

void	translate(float ***tab, int x, int y)
{


	int	i;
	int	j;
	if (1)
	{
		i = 0;
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				// if (tab[0][0][0] + ORIGIN_X > 1 && tab[0][tab_width(tab) - 1][0] + ORIGIN_X < 1899)
				tab[i][j][0] += x;
				// if (tab[tab_height(tab) -1][0][1] > 1 && tab[tab_height(tab) -1][0][1] < 1079)
				tab[i][j][1] += y;
				j++;
			}
			i++;
		}
	}
}
