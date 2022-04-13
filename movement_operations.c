#include "fdf.h"

void rotate(double ***tab, int x, int y)
{
	// double ***test;
	// double flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	// double angle = 0.872665;
	// double rotate_matrix[3][3] =  {{1, 0, 0},
	// 								{0.0, cos(angle), -sin(angle)}, 
	// 								{0.0, cos(angle), -sin(angle)}};
	// // double rotate_matrix[3][3] =  {{cos(angle), (-1 * sin(angle)), 0.0}, {sin(angle), cos(angle), 0.0}, {0.0, 0.0, 1.0}};
	// multiply_arr_by_matrix(, rotate_matrix);
	// multiply_arr_by_matrix(tab, flatten);
}

void zoom(int button, int x,int y, t_vars *frame)
{
	int		i;
	int		j;
	double	***arr;
	static double scale = 1;
	double flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	static int oldbutton = 0;
	if (button != oldbutton)
		scale = 1;
	if (button == 4)
		scale += 0.1;
	if (button == 5)
		scale -= 0.1;
	arr = frame->xyztab;
	i = 0;
	printf("adfkladsfj\n");
	while (arr[i] && (button == 4 || button == 5))
	{
		j = 0;
		while (arr[i][j] && (button == 4 || button == 5))
		{
			arr[i][j][0] *= scale;
			arr[i][j][1] *= scale;
			arr[i][j][2] *= scale;
			// printf("index: %d, arr[%f, %f, %f]\n", j, arr[i][j][0],arr[i][j][1],arr[i][j][2]);
			j++;
		}
		i++;
	}
	oldbutton = button;
	frame->flattab = multiply_arr_by_matrix(isometric_projection(copy_int_arr(frame->xyztab)), flatten);
}

void	translate(double ***tab, int x, int y)
{
	static float oldposx = 0;
	static float oldposy = 0;
	int	i;
	int	j;
	// printf("oldposx: %d, oldposy: %d, x: %d, y: %d", oldposx, oldposy, x, y);
	if (oldposx && oldposy)
	{
		i = 0;
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				tab[i][j][0] += ((ORIGIN_X - x) * fabs((x / oldposx)) / 5);
				tab[i][j][1] += ((ORIGIN_Y - y) * fabs((y / oldposy)) / 5);
				j++;
			}
			i++;
		}
	}
	oldposx = x;
	oldposy = y;
}
