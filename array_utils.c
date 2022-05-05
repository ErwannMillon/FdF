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
	int		file;
	int		counter;
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

void	z_min_max(float ***arr, float *min, float *max)
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
			if (arr[i][j][2] < *min)
				*min = arr[i][j][2];
			if (arr[i][j][2] > *max)
				*max = arr[i][j][2];
			j++;
		}
		i++;
	}
}

void	scale_z(float ***arr, float scale)
{
	float	min;
	float	max;
	float	z_scale;
	int		i;
	int		j;

	i = 0;
	j = 0;
	z_min_max(arr, &min, &max);
	if (min == 0)
		min++;
	z_scale = ((max / min)) * 10;
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
