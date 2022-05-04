/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:48 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/04 13:54:07 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
float *multiply_coordinates_by_matrix(float coordinates[3], float matrix[3][3])
{
	int	i;
	int	j;
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
			sum += coordinates[j] * matrix[i][j];
			j++;
		}
		result[i] = sum;
		// printf("i: %d, val: %f", i, result[i]);
		i++;
	}
	return (result);
}

float ***multiply_arr_by_matrix(float ***tab, float matrix[3][3])
{
	int	i;
	int	j;
	int	k;
	float *result;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			result = multiply_coordinates_by_matrix(tab[i][j], matrix);
			// free(tab[i][j]);
			tab[i][j] = result;
			j++;
		}
		i++;
	}
	return (tab);
}

float ***flatten_arr(float ***tab)
{
	float ***copy;
	float flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	copy = multiply_arr_by_matrix(isometric_projection(copy_int_arr(tab)), flatten);
	return (copy);
}

void print_tab(float ***tab)
{
	int	i;
	int	j;
	i = 0;

	while (tab[i] && i == 0)
	{
		j = 0;
		while (tab[i][j])
		{
			printf("i: %d index: %d, arr[%d, %d, %d]\n", i, j, (int)tab[i][j][0], (int)tab[i][j][1], (int)tab[i][j][2]);
			// printf("(%d, %d)\n", (int)tab[i][j][0], (int)tab[i][j][1]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("=======================================================");
}

float ***isometric_projection(float ***tab)
{
	// print_tab(tab);
	float firstiso[3][3] = {{cos(BETA), 0.0, (-1 * sin(BETA))}, {0.0, 1.0, 0.0},{sin(BETA), 0.0, cos(BETA)}};
	float secondiso[3][3] = {{1.0, 0.0, 0.0}, {0.0, cos(ALPHA), sin(ALPHA)},{0.0, (-1 * sin(ALPHA)), cos(ALPHA)}};
	float flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	tab = multiply_arr_by_matrix(multiply_arr_by_matrix(tab, firstiso), secondiso);
	return (tab);
}