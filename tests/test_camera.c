#include "test.h"

Test(camera, create_a_camera)
{
	t_camera	c;
	t_matrix	m;

	new_camera(&c, 160, 120, M_PI / 2);
	cr_assert(epsilon_eq(dbl, c.hsize, 160, EPSILON));
	cr_assert(epsilon_eq(dbl, c.vsize, 120, EPSILON));
	cr_assert(epsilon_eq(dbl, c.fov, M_PI / 2, EPSILON));
	get_identity_matrix(&m);
	cr_assert(matrix_eq(c.transform, m));
}

Test(camera, pixel_size_for_horizontal_canvas)
{
	t_camera	c;

	new_camera(&c, 200, 125, M_PI / 2);
	cr_assert(epsilon_eq(dbl, c.pixel_size, 0.01, EPSILON));
}

Test(camera, pixel_size_for_vertical_canvas)
{
	t_camera	c;

	new_camera(&c, 125, 200, M_PI / 2);
	cr_assert(epsilon_eq(dbl, c.pixel_size, 0.01, EPSILON));
}

Test(camera, ray_through_the_center_of_the_canvas)
{
	t_camera	c;
	t_ray		r;
	t_tuple		p;

	new_camera(&c, 201, 101, M_PI / 2);
	ray_for_pixel(&c, 100, 50, &r);
	new_point(0, 0, 0, &p);
	cr_assert(eq(int, tuple_eq(r.origin, p), true));
	new_vector(0, 0, -1, &p);
	cr_assert(eq(int, tuple_eq(r.direction, p), true));
}

Test(camera, ray_through_a_corner_of_the_canvas)
{
	t_camera	c;
	t_ray		r;
	t_tuple		t;

	new_camera(&c, 201, 101, M_PI / 2);
	ray_for_pixel(&c, 0, 0, &r);
	new_point(0, 0, 0, &t);
	cr_assert(eq(int, tuple_eq(r.origin, t), true));
	new_vector(0.66519, 0.33259, -0.66851, &t);
	cr_assert(eq(int, tuple_eq(r.direction, t), true));
}

Test(camera, ray_when_camera_is_transformed)
{
	t_camera	c;
	t_ray		r;
	t_matrix m1;
	t_matrix m2;
	t_tuple	t;

	new_camera(&c, 201, 101, M_PI / 2);
	set_transform_camera(&c,
		multiply_matrices(rotation_y(cos(M_PI / 4), sin(M_PI / 4), &m1), translation(0, -2, 5, &m2), &m1));
	ray_for_pixel(&c, 100, 50, &r);
	new_point(0, 2, -5, &t);
	cr_assert(eq(int, tuple_eq(r.origin, t), true));
	new_vector(sqrt(2) / 2, 0, -sqrt(2) / 2, &t);
	cr_assert(eq(int, tuple_eq(r.direction, t), true));
}

// The precision of the test is not good enough.
// TODO: check if convert double to float will help.
Test(camera, rendering_a_world_with_a_camera)
{
	t_mini_rt	rt;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_color		result;
	t_color		expected;
	t_matrix	m;

	rt.world = default_world();
	new_point(0, 0, -5, &from);
	new_point(0, 0, 0, &to);
	new_vector(0, 1, 0, &up);
	new_camera(&rt.camera, 11, 11, M_2_PI);
	set_transform_camera(&rt.camera, view_transform(&from, &to, &up, &m));
	new_canvas(&rt.canvas, 11, 11, "test_camera");
	render(&rt);
	result = read_pixel(rt.canvas.img, 5, 5);
	expected = new_color(0.38066, 0.47583, 0.2855);
	mlx_delete_image(rt.canvas.mlx, rt.canvas.img);
	mlx_terminate(rt.canvas.mlx);
	cr_assert(epsilon_eq(dbl, result.r, expected.r, 0.01));
	cr_assert(epsilon_eq(dbl, result.g, expected.g, 0.01));
	cr_assert(epsilon_eq(dbl, result.b, expected.b, 0.01));
}
