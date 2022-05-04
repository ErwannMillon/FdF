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
	float	winheight;
	float	winwidth;
}				t_data;


typedef struct	s_vars {
	void	*mlx;
	void	*win;
	float	***flattab;
	float	***xyztab;
	t_data	*img;
	float	color;
	int disco;
	int framenum;
	float	winheight;
	float	winwidth;
}				t_vars;

typedef struct	s_frame
{
	float	***flattab;
	float	***xyztab;
	t_data	*img;
	t_vars	*vars;
	float	winheight;
	float	winwidth;
}				t_frame;


# define ORIGIN_X 200
# define ORIGIN_Y 100
# define INIT_SCALE 80
# define VERTICAL_SCALE 5
// # define MARGIN_SIDE 240
// # define MARGIN_TOP 90

# define PI 3.1415926535
# define ALPHA 0.615472907
# define BETA 0.785398

//DRAW_FUNCTIONS
void 	draw_rotated_square(t_data *data, int *a, int size, int color);
void	draw_straight_line(t_data *data, float *a, float *b, int color);
void 	draw_wireframe(float ***tab, float ***xyztab, t_data *data);
void	draw_square(t_data *data, int size, int color);
void 	draw_rows(float ***tab, t_data *img, float color);
void 	draw_cols(float ***tab, t_data *img, float color);

//MEASUREMENTS
int	tab_height(float ***tab);
int	tab_width(float ***tab);

//MOVEMENT AND TRANSFORMATIONS
float 	***isometric_projection(float ***tab);
float	***flatten_arr(float ***tab);
void	translate(float ***tab, int x, int y);
void 	zoom(int button, int x,int y, t_vars *frame);
void 	key_rotate(int keycode, t_vars *frame);
void	scale_z(float ***arr, float scale);

//HOOKS
void	translate_hook(int keycode, t_vars *frame);
int		key_hook(int keycode, t_vars *frame);
void	zoom_mouse_hook(int button, int x, int y, t_vars *frame);

//MATRIX OPERATIONS AND PARSING
float	*multiply_coordinates_by_matrix(float coordinates[3], float matrix[3][3]);
float	***multiply_arr_by_matrix(float ***tab, float matrix[3][3]);
float 	***str_arr_atoi(char *filepath);

//FREEING
void 	free_split(char **strs);
void	free_triple_arr(float ***arr);
int		close_win(int keycode, t_vars *vars);

//ARRAY UTILS
void 	print_tab(float ***tab);
float	***copy_int_arr(float ***arr);
// float 	***twod_to_three(float ***tab);

//MLX STUFF
int		render_next_frame(t_vars *frame);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		cross_exit(t_vars *vars);

#endif