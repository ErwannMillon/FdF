#ifndef FDF_H
#define FDF_H
# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <math.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
int	close_win(int keycode, t_vars *vars);

# define ORIGIN_X 960
# define ORIGIN_Y 540
// # define MARGIN_SIDE 240
// # define MARGIN_TOP 90
// # define 

# define PI 3.1415926535
float *multiply_coordinates_by_matrix(float *x, float **y);
double ***str_arr_atoi(char *filepath);



#endif