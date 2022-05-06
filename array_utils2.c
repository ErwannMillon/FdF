/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:24:21 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/06 13:24:22 by gmillon          ###   ########.fr       */
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

void	scale_twod(float ***arr, char *line, int *i, int *j)
{
	float	scale;

	scale = 7037.684 * ((split_len(line) - 1) / 1920);
	arr[*i][*j] = malloc(4 * sizeof(float));
	arr[*i][*j][0] = (*j * scale);
	arr[*i][*j][1] = (*i * scale);
}

void	end_loop(float ***arr, int *i, int *j, char **results)
{
	arr[*i][*j] = NULL;
	*i = *i + 1;
	free_split(results);
}
