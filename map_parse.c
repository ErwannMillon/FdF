#include "fdf.h"
int	line_length(char *filepath)
{
	int		i;
	int		file;
	char	*line;
	char	**arr;

	file = open(filepath, O_RDONLY);
	line = get_next_line(file);
	// printf("filedes in linelne: %d", file);

	arr = ft_split(line, ' ');
	i = 0;
	while (arr[i])
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
	line = get_next_line(file);
	// printf("filedes in arrlen: %d", file);
	while (line)
	{
		// printf("counter %d, line: %s", counter, line);
		line = get_next_line(file);
		counter++;
	}
	close(file);
	return (counter);
}

void print_split(char **strs)
{
	int i = 0;
	while(strs[i])
	{
		printf("str[%d]: %s___\n", i, strs[i]);
		i++;
	}
}

void fill_int_arr(double ****arr_pointer, int file, int linelen)
{
	double	***arr;
	int	i;
	int	j;
	char	**results;
	char	*line;

	i = 0;
	j = 0;
	arr = *arr_pointer;
	line = get_next_line(file);
	while (line)
	{
		arr[i] = malloc((linelen + 2) * sizeof(double *));
		// printf("line %d: %s   ___\n", i + 1, line);
		results = ft_split(line, ' ');
		// print_split(results);
		j = 0;
		while (results[j] && results[j] != '\n')
		{
			arr[i][j] = malloc(4 * sizeof(double));
			arr[i][j][0] = j;
			arr[i][j][1] = i;
			arr[i][j][2] = ft_atoi(results[j]); 
			printf("index: %d, arr[%f, %f, %f]\n", j, arr[i][j][0],arr[i][j][1],arr[i][j][2]);
			j++;
		}
		arr[j] = NULL;
		i++;
		free(line);
		line = get_next_line(file);
	}
	arr[i] = NULL;
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
	return (atoi_tab);
}