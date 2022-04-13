
#include "fdf.h"
void mouse_hook(int x,int y, t_vars *frame)
{
	double flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	frame->flattab = multiply_arr_by_matrix(isometric_projection(copy_int_arr(frame->xyztab)), flatten);
	translate(frame->flattab, x, y);

}


void mouse_rotate(int button, int x,int y, t_vars *frame)
{
	// print_tab(frame->flattab);
	// rotate(frame->flattab, x, y);
	print_tab(frame->xyztab);
	double ***test;
	double flatten[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};
	double angle = 0.5;
	double rotate_matrix[3][3] =  {{cos(angle), 0, sin(angle)},
									{0.0, 1, 0}, 
									{-sin(angle), 0, cos(angle)}};
	// double rotate_matrix[3][3] =  {{cos(angle), (-1 * sin(angle)), 0.0}, {sin(angle), cos(angle), 0.0}, {0.0, 0.0, 1.0}};
	frame->xyztab = multiply_arr_by_matrix(frame->xyztab, rotate_matrix);
	frame->flattab = multiply_arr_by_matrix(isometric_projection(copy_int_arr(frame->xyztab)), flatten);
	print_tab(frame->xyztab);

}

int	render_next_frame(t_vars *frame)
{
	t_data	newimg;
	// printf("franem");
	draw_square(frame->img, 1920, 0x0000000);
	draw_rows(frame->flattab, frame->img);
	draw_cols(frame->flattab, frame->img);
	mlx_put_image_to_window(frame->mlx, frame->win, frame->img->img, 0, 0);
	return (1);
}
