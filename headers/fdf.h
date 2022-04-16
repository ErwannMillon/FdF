#ifndef FDF_H
#define FDF_H
# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <math.h>

// KEYCODE DEFINES
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124


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

# define ORIGIN_X 200
# define ORIGIN_Y 100
# define INIT_SCALE 80
# define VERTICAL_SCALE 5
// # define MARGIN_SIDE 240
// # define MARGIN_TOP 90
// # define 

# define PI 3.1415926535
# define ALPHA 0.615472907
# define BETA (PI / 4)

//DRAW_FUNCTIONS
void 	draw_rotated_square(t_data *data, int *a, int size, int color);
void	draw_straight_line(t_data *data, double *a, double *b, int color);
void 	draw_wireframe(double ***tab, double ***xyztab, t_data *data);
void	draw_square(t_data *data, int size, int color);
void 	draw_rows(double ***tab, t_data *img);
void 	draw_cols(double ***tab, t_data *img);

//MEASUREMENTS
int	tab_height(double ***tab);
int	tab_width(double ***tab);

//MOVEMENT AND TRANSFORMATIONS
double 	***isometric_projection(double ***tab);
double	***flatten_arr(double ***tab);
void	translate(double ***tab, int x, int y);
void 	zoom(int button, int x,int y, t_vars *frame);
void 	key_rotate(int keycode, t_vars *frame);
void	scale_z(double ***arr, double scale);

//HOOKS
void	translate_hook(int keycode, t_vars *frame);
int		key_hook(int keycode, t_vars *frame);
void	zoom_mouse_hook(int button, int x, int y, t_vars *frame);

// void	mouse_hook(int x,int y, t_vars *frame);

//MATRIX OPERATIONS AND PARSING
double	*multiply_coordinates_by_matrix(double coordinates[3], double matrix[3][3]);
double	***multiply_arr_by_matrix(double ***tab, double matrix[3][3]);
double 	***str_arr_atoi(char *filepath);

// double ***rotate_arr_by_matrix(double ***tab, double matrix[3][3]);

//FREEING
void 	free_split(char **strs);
void	free_triple_arr(double ***arr);

//ARRAY UTILS
void 	print_tab(double ***tab);
double	***copy_int_arr(double ***arr);
// double 	***twod_to_three(double ***tab);

//MLX STUFF
int		render_next_frame(t_vars *frame);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif