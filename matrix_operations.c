/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:48 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/06 13:22:49 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	*multiply_coord_by_matrix(float coord[3], const float matrix[3][3])
{
	int		i;
	int		j;
	float	sum;
	float	*result;

	result = malloc(3 * sizeof(float));
	if (!result)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		j = 0;
		sum = 0;
		while (j < 3)
		{
			sum += coord[j] * matrix[i][j];
			j++;
		}
		result[i] = sum;
		i++;
	}
	return (result);
}

float	***multiply_arr_by_matrix(float ***tab, const float matrix[3][3])
{
	int		i;
	int		j;
	float	*result;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			result = multiply_coord_by_matrix(tab[i][j], matrix);
			tab[i][j] = result;
			j++;
		}
		i++;
	}
	return (tab);
}

float	***flatten_arr(float ***tab)
{
	float		***copy;
	const float	flatten[3][3] = {{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 0.0}};

	copy = multiply_arr_by_matrix(isometric_projection(
				copy_int_arr(tab, 0)), flatten);
	return (copy);
}

float	***isometric_projection(float ***tab)
{
	const float	firstiso[3][3] = {{cos(BETA), 0.0, (-1 * sin(BETA))},
	{0.0, 1.0, 0.0},
	{sin(BETA), 0.0, cos(BETA)}};
	const float	secondiso[3][3] = {{1.0, 0.0, 0.0},
	{0.0, cos(ALPHA), sin(ALPHA)},
	{0.0, (-1 * sin(ALPHA)), cos(ALPHA)}};

	tab = multiply_arr_by_matrix(
			multiply_arr_by_matrix(tab, firstiso), secondiso);
	return (tab);
}
