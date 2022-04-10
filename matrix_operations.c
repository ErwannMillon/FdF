#include "fdf.h"
float *multiply_coordinates_by_matrix(float *x, float **y)
{
	int	i;
	int	j;
	float	sum;
	float	*result;
	float matrix[3][3] = {{1.0, 2.0 ,3.0},{4.0, 0.0, 3.0},{1.0, 9.0, 11.0}};
	float coordinates[3] = {5.0, 6.0 ,7.0};
	result = malloc(3 * sizeof(float));
	if (!result)
		return (NULL);
	i = 0;
	// j = 0;
	// sum = 0;
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
		printf("i: %d, val: %f", i, result[i]);
		i++;
	}

	return (result);
}