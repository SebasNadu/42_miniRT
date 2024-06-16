#include "test.h"

Test(canvas, create_a_canvas)
{
	t_canvas	canvas;

	new_canvas(&canvas, 10, 20, "Test");
	cr_assert(eq(u32, canvas.mlx->width, 10));
	cr_assert(eq(u32, canvas.mlx->height, 20));
	mlx_delete_image(canvas.mlx, canvas.img);
	mlx_terminate(canvas.mlx);
}

Test(canvas, write_a_pixel)
{
	t_canvas	canvas;
	t_color		c;

	new_canvas(&canvas, 10, 20, "Test");
	new_color(1, 0, 0, &c);
	write_pixel(canvas.img, 2, 3, &c);
	read_pixel(canvas.img, 2, 3, &c);
	cr_assert(epsilon_eq(flt, c.r, 1, EPSILON));
	cr_assert(epsilon_eq(flt, c.g, 0, EPSILON));
	cr_assert(epsilon_eq(flt, c.b, 0, EPSILON));
	mlx_delete_image(canvas.mlx, canvas.img);
	mlx_terminate(canvas.mlx);
}

Test(canvas, save_canvas_to_ppm)
{
	t_canvas	canvas;
	t_color		c;

	new_canvas(&canvas, 10, 20, "Test");
	new_color(1, 0, 0, &c);
	write_pixel(canvas.img, 2, 3, &c);
	new_color(0, 1, 0, &c);
	write_pixel(canvas.img, 4, 5, &c);
	new_color(0, 0, 1, &c);
	write_pixel(canvas.img, 6, 7, &c);
	canvas_to_ppm(&canvas, "test_canvas");
	mlx_delete_image(canvas.mlx, canvas.img);
	mlx_terminate(canvas.mlx);
}
