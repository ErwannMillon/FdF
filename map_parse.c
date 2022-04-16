/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:17 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/17 01:21:25 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
int	line_length(char *filepath)
{
	int		i;
	int		file;
	char	*line;
	char	**arr;

	file = open(filepath, O_RDONLY);
	if (file == -1)
	{
		ft_printf("Error opening file\n");
		exit(0);
	}
	line = get_next_line(file);
	if (line)
		arr = ft_split(line, ' ');
	i = 0;
	while (line && arr[i])
		i++;
	close(file);
	return (i);
}

int	arr_length(char *filepath)
{
	int	file;
	int	counter;
	char	*line;

	counter = 0;
	file = open(filepath, O_RDONLY);
	if (file == -1)
	{
		ft_printf("Error opening file\n");
		exit(0);
	}
	line = get_next_line(file);
	while (line)
	{
		line = get_next_line(file);
		counter++;
	}
	close(file);
	return (counter);
}

// void print_split(char **strs)
// {
// 	int i = 0;
// 	while(strs[i])
// 	{
// 		printf("str[%d]: %s___\n", i, strs[i]);
// 		i++;
// 	}
// }

float split_len(char *s)
{
	int		i;
	char	**arr;

	arr = ft_split(s, ' ');
	i = 0;
	while (arr[i++]);
	free_split(arr);
	return((float)i);
}

void z_min_max(double ***arr, double *min, double *max)
{
	int	i;
	int	j;

	*max = 0;
	*min = 0;
	i = 0;
	j = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			// printf("%f, %f, result: %f\n", *min, *max, arr[i][j][2]);
			if (arr[i][j][2] < *min)
				*min = arr[i][j][2];
			if (arr[i][j][2] > *max)
				*max = arr[i][j][2]; 
			j++;
		}
		i++;
	}
}

void scale_z(double ***arr, double scale)
{
	double	min;
	double	max;
	double z_scale;
	int		i;
	int		j;

	i = 0;
	j = 0;
	z_min_max(arr, &min, &max);
	if (min == 0)
		min++;
	z_scale = (1 / (max / min)) * 150;
	if (scale != 1)
		z_scale = 1;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			arr[i][j][2] *= (z_scale * scale);
			j++;
		}
		i++;
	}
}

void fill_int_arr(double ****arr_pointer, int file, int linelen)
{
	double	***arr;
	int		i;
	int		j;
	char	**results;
	char	*line;
	float	scale;

	i = 0;
	j = 0;
	arr = *arr_pointer;
	line = get_next_line(file);
	scale = 7037.684 * ((split_len(line) - 1 )/ 1920);
	i = 0;
	while (line)
	{
		arr[i] = malloc((linelen + 2) * sizeof(double *));
		// printf("line %d: %s   ___\n", i + 1, line);
		results = ft_split(line, ' ');
		// print_split(results);
		j = 0;
		while (results[j] && results[j][0] != '\n')
		{
			arr[i][j] = malloc(4 * sizeof(double));
			arr[i][j][0] = (j * scale);
			arr[i][j][1] = (i * scale);
			arr[i][j][2] = ft_atoi(results[j]); 
			// printf("index: %d, arr[%f, %f, %f]\n", j, arr[i][j][0],arr[i][j][1],arr[i][j][2]);
			j++;
		}
		// printf("Final index: %d," , j);
		arr[i][j] = NULL;
		i++;
		free(line);
		free_split(results);
		line = get_next_line(file);
	}
	arr[i] = NULL;
	scale_z(arr, 1);
}

double ***copy_int_arr(double ***arr)
{
	double	***newarr;
	int	i;
	int	j;
	int linelen;
	char	**results;
	char	*line;

	linelen = 0;
	i = 0;
	j = 0;
	while(arr[i][linelen])
		linelen++;
	while (arr[i])
		i++;
	newarr = malloc((i + 1) * sizeof(double **));
	i = 0;
	while (arr[i])
	{
		newarr[i] = malloc((linelen + 2) * sizeof(double *));
		j = 0;
		while (arr[i][j])
		{
			newarr[i][j] = malloc(4 * sizeof(double));
			ft_memcpy(newarr[i][j], arr[i][j], (sizeof(double) * 3));
			j++;
		}
		newarr[i][j] = NULL;
		i++;
	}
	newarr[i] = NULL;
	return (newarr);
}

double ***str_arr_atoi(char *filepath)
{
	int		arr_len;
	int		line_len;
	double	***atoi_tab;
	char	**str_arr;
	int		file;

	line_len = line_length(filepath);
	arr_len = arr_length(filepath);
	atoi_tab = malloc((arr_len + 1) * sizeof (double **));
	file = open(filepath, O_RDONLY);
	fill_int_arr(&atoi_tab, file, line_len);
	if (!atoi_tab || !*atoi_tab)
	{
		ft_printf("Error: empty file");
		exit(0);
	}
	return (atoi_tab);
}