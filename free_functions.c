/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:23 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/17 00:14:07 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void free_split(char **strs)
{
	int	i;

	i = 0;
	while(strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_triple_float(float ***arr)
{
	int	i;

	i = 0;
	// while (arr)
	// {
	// 	arr[i] = malloc(linelen * sizeof(double *));
	// 	// printf("line %d: %s   ___\n", i + 1, line);
	// 	results = ft_split(line, ' ');
	// 	// print_split(results);
	// 	j = 0;
	// 	while (results[j] && results[j] != '\n')
	// 	{
	// 		arr[i][j] = malloc(4 * sizeof(double));
	// 		arr[i][j][0] = j;
	// 		arr[i][j][1] = i;
	// 		arr[i][j][2] = ft_atoi(results[j]); 
	// 		printf("index: %d, arr[%f, %f, %f]\n", j, arr[i][j][0],arr[i][j][1],arr[i][j][2]);
	// 		j++;
	// 	}
	// 	i++;
	// 	free(line);
	// 	line = get_next_line(file);
	// }
	// while (arr)
	// {
	// 	while (*arr)
	// 	{
	// 		free(**arr);
	// 		*arr++;
	// 	}
	// 	free(*arr);
	// 	arr++;
	// }
}