#ifndef FDF_H
#define FDF_H
# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <math.h>


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct	s_vars {
	void	*mlx;
	void	*win;
	double	***flattab;
	double	***xyztab;
	t_data	*img;

}				t_vars;

typedef struct	s_frame
{
	double	***flattab;
	double	***xyztab;
	t_data	*img;
	t_vars	*vars;
}				t_frame;


int	close_win(int keycode, t_vars *vars);

// # define ORIGIN_X 200
// # define ORIGIN_Y 200

# define ORIGIN_X 920
# define ORIGIN_Y 540
# define INIT_SCALE 60
# define VERTICAL_SCALE 5
// # define MARGIN_SIDE 240
// # define MARGIN_TOP 90
// # define 

# define PI 3.1415926535
# define ALPHA 0.615472907
# define BETA (PI / 4)
double	*multiply_coordinates_by_matrix(double coordinates[3], double matrix[3][3]);
double 	***str_arr_atoi(char *filepath);
void	draw_straight_line(t_data *data, double *a, double *b, int color);
void 	draw_rotated_square(t_data *data, int *a, int size, int color);
void	draw_square(t_data *data, int size, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
double 	***isometric_projection(double ***tab);
void 	draw_wireframe(double ***tab, double ***xyztab, t_data *data);
void 	print_tab(double ***tab);
double	***multiply_arr_by_matrix(double ***tab, double matrix[3][3]);
double	***flatten(double ***tab);
void	translate(double ***tab, int x, int y);
void 	rotate(double ***tab, int x, int y);
double	***copy_int_arr(double ***arr);
void 	zoom(int button, int x,int y, t_vars *frame);
void	mouse_rotate(int button, int x,int y, t_vars *frame);
void	mouse_hook(int x,int y, t_vars *frame);
int		render_next_frame(t_vars *frame);
void 	draw_cols(double ***tab, t_data *img);
void 	draw_rows(double ***tab, t_data *img);

#endif