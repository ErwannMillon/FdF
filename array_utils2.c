/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:24:21 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/06 22:24:24 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	split_len(char *s)
{
	int		i;
	char	**arr;

	arr = ft_split(s, ' ');
	i = 0;
	while (arr[i])
		i++;
	free_split(arr);
	return ((float)i);
}

void	scale_twod(float ***arr, int *c, float scale)
{
	arr[c[0]][c[1]] = malloc(4 * sizeof(float));
	arr[c[0]][c[1]][0] = (c[1] * scale);
	arr[c[0]][c[1]][1] = (c[0] * scale);
}

void	end_loop(float ***arr, int *c, char *line, char **results)
{
	arr[c[0]][c[1]] = NULL;
	c[0] = c[0] + 1;
	free_split(results);
	free(line);
}
