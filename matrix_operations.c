/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:48 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/17 01:04:28 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
double *multiply_coordinates_by_matrix(double coordinates[3], double matrix[3][3])
{
	int	i;
	int	j;
	double	sum;
	double	*result;
	result = malloc(3 * sizeof(double));
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

double ***multiply_arr_by_matrix(double ***tab, double matrix[3][3])
{
	int	i;
	int	j;
	int	k;
	double *result;

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

double *rotate_coordinates_by_matrix(double coordinates[3], double matrix[3][3])
{
	int	i;
	int	j;
	double	sum;
	double	*result;
	result = malloc(3 * sizeof(double));
	if (!result)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		j = 0;
		sum = 0;
		while (j < 3)
		{
			sum += (coordinates[j] - 400) * matrix[i][j];
			j++;
		}
		result[i] = sum;
		// printf("i: %d, val: %f", i, result[i]);
		i++;
	}
	return (result);
}

double ***flatten_arr(double ***tab)
{
	double ***copy;
	double flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	copy = multiply_arr_by_matrix(isometric_projection(copy_int_arr(tab)), flatten);
	return (copy);
}
double ***rotate_arr_by_matrix(double ***tab, double matrix[3][3])
{
	int	i;
	int	j;
	int	k;
	double *result;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			result = rotate_coordinates_by_matrix(tab[i][j], matrix);
			// free(tab[i][j]);
			tab[i][j] = result;
			j++;
		}
		i++;
	}
	return (tab);
}

void print_tab(double ***tab)
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
		printf("\n");
		i++;
	}
	printf("=======================================================");
}

void draw_tab(int ***tab)
{	
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			j++;
		}
		printf("\n");
		i++;
	} 
}

double ***isometric_projection(double ***tab)
{
	// print_tab(tab);
	double firstiso[3][3] = {{cos(BETA), 0.0, (-1 * sin(BETA))}, {0.0, 1.0, 0.0},{sin(BETA), 0.0, cos(BETA)}};
	double secondiso[3][3] = {{1.0, 0.0, 0.0}, {0.0, cos(ALPHA), sin(ALPHA)},{0.0, (-1 * sin(ALPHA)), cos(ALPHA)}};
	double flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	tab = multiply_arr_by_matrix(multiply_arr_by_matrix(tab, firstiso), secondiso);
	// double ***projected_tab = multiply_arr_by_matrix(tab, flatten);
	// printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	// // draw_tab(projected_tab);
	// print_tab(projected_tab);
	// return (projected_tab);
	return (tab);
}