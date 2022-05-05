/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:17 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/05 20:49:44 by gmillon          ###   ########.fr       */
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

void	fill_int_arr(float ***arr, int file, int linelen)
{
	int		i;
	int		j;
	char	**results;
	char	*line;
	float	scale;

	line = get_next_line(file);
	scale = 7037.684 * ((split_len(line) - 1) / 1920);
	i = 0;
	while (line)
	{
		arr[i] = malloc((linelen + 2) * sizeof(float *));
		results = ft_split(line, ' ');
		j = 0;
		while (results[j] && results[j][0] != '\n')
		{
			arr[i][j] = malloc(4 * sizeof(float));
			arr[i][j][0] = (j * scale);
			arr[i][j][1] = (i * scale);
			arr[i][j][2] = ft_atoi(results[j]);
			j++;
		}
		arr[i][j] = NULL;
		i++;
		free(line);
		free_split(results);
		line = get_next_line(file);
	}
	arr[i] = NULL;
	scale_z(arr, 1);
}

float	***copy_int_arr(float ***arr, int should_free)
{
	float	***newarr;
	int		i;
	int		j;
	char	**results;
	char	*line;

	newarr = malloc((tab_height(arr) + 1) * sizeof(float **));
	i = 0;
	while (arr[i])
	{
		newarr[i] = malloc((tab_width(arr) + 2) * sizeof(float *));
		j = 0;
		while (arr[i][j])
		{
			newarr[i][j] = malloc(4 * sizeof(float));
			ft_memcpy(newarr[i][j], arr[i][j], (sizeof(float) * 3));
			j++;
		}
		newarr[i][j] = NULL;
		i++;
	}
	newarr[i] = NULL;
	if (should_free)
		free_triple_arr(arr);
	return (newarr);
}

float	***str_arr_atoi(char *filepath)
{
	int		arr_len;
	int		line_len;
	float	***atoi_tab;
	char	**str_arr;
	int		file;

	line_len = line_length(filepath);
	arr_len = arr_length(filepath);
	atoi_tab = malloc((arr_len + 1) * sizeof (float **));
	file = open(filepath, O_RDONLY);
	fill_int_arr(atoi_tab, file, line_len);
	if (!atoi_tab || !*atoi_tab)
	{
		ft_printf("Error: empty file");
		exit(0);
	}
	return (atoi_tab);
}
