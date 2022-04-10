#include "fdf.h"
void free_split(char **strs)
{
	while(*strs)
	{
		free(*strs);
		strs++;
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