#include "test.h"

Test(patterns, checker_pattern_in_2D)
{
	t_checker	checkers;
	t_pattern		*res;
	t_color		expected;
	double		uv[2];
	t_pattern black;
	t_pattern white;

	black = new_solid_pattern(new_color(0, 0, 0, &expected));
	white = new_solid_pattern(new_color(1, 1, 1, &expected));
	checkers = uv_checkers(2, 2, &black, &white);
	uv[0] = 0.0;
	uv[1] = 0.0;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	new_color(0, 0, 0, &expected);
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
	uv[0] = 0.5;
	uv[1] = 0.0;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	new_color(1, 1, 1, &expected);
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
	uv[0] = 0.0;
	uv[1] = 0.5;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	new_color(1, 1, 1, &expected);
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
	uv[0] = 0.5;
	uv[1] = 0.5;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	new_color(0, 0, 0, &expected);
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
	uv[0] = 1.0;
	uv[1] = 1.0;
	res = uv_pattern_at(&checkers, &uv[0], &uv[1]);
	new_color(0, 0, 0, &expected);
	cr_assert(eq(dbl, res->color.r, expected.r));
	cr_assert(eq(dbl, res->color.g, expected.g));
	cr_assert(eq(dbl, res->color.b, expected.b));
}

Test(patterns, sphere_mapping_3D_point)
{
	t_point		p;
	double		uv[2];
	
	new_point(0, 0, -1, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(1, 0, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0, 0, 1, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.5));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(-1, 0, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0, 1, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.5));
	cr_assert(eq(dbl, uv[1], 1.0));
	new_point(0, -1, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.5));
	cr_assert(eq(dbl, uv[1], 0.0));
	new_point(sqrt(2)/2, sqrt(2)/2, 0, &p);
	spherical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
}

Test(patterns, using_texture_map_pattern_with_spherical_map)
{
	t_pattern	pattern;
	t_color		res;
	t_point		p;
	t_color		black;
	t_color		white;

	new_color(0, 0, 0, &black);
	new_color(1, 1, 1, &white);
	new_pattern(&pattern);
	new_uv_checkers_pattern(new_solid_pattern(&black), new_solid_pattern(&white), &pattern);
	pattern.texture_map.uv_pattern = uv_checkers(16, 8, pattern.a, pattern.b);
	texture_map(&pattern, &pattern.texture_map.uv_pattern, spherical_map);
	new_point(0.4315, 0.4670, 0.7719, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, white), true));
	new_point(-0.9654, 0.2552, -0.0534, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, black), true));
	new_point(0.1039, 0.7090, 0.6975, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, white), true));
	new_point(-0.4986, -0.7856, -0.3663, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, black), true));
	new_point(-0.0317, -0.9395, 0.3411, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, black), true));
	new_point(0.4809, -0.7721, 0.4154, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, black), true));
	new_point(0.0285, -0.9612, -0.2745, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, black), true));
	new_point(-0.5734, -0.2162, -0.7903, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, white), true));
	new_point(0.7688, -0.1470, 0.6223, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, black), true));
	new_point(-0.7652, 0.2175, 0.6060, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, black), true));
}

Test(patterns, using_planar_mapping_on_3D_point)
{
	t_point		p;
	double		uv[2];

	new_point(0.25, 0, 0.5, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0.25, 0, -0.25, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(0.25, 0.5, -0.25, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(1.25, 0, 0.5, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0.25, 0, -1.75, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.25));
	new_point(1, 0, -1, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.0));
	new_point(0, 0, 0, &p);
	planar_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.0));
}

Test(patterns, using_cylindrical_mapping_on_3D_point)
{
  t_point		p;
  double		uv[2];

	new_point(0, 0, -1, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.0));
	new_point(0, 0.5, -1, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0, 1, -1, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.0));
	cr_assert(eq(dbl, uv[1], 0.0));
	new_point(0.70711, 0.5, -0.70711, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.125));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(1, 0.5, 0, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0.70711, 0.5, 0.70711, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.375));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(0, -0.25, 1, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.5));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(-0.70711, 0.5, 0.70711, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.625));
	cr_assert(eq(dbl, uv[1], 0.5));
	new_point(-1, 1.25, 0, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.25));
	new_point(-0.70711, 0.5, -0.70711, &p);
	cylindrical_map(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.875));
	cr_assert(eq(dbl, uv[1], 0.5));
}

Test(patterns, layout_of_the_align_checke_pattern)
{
	t_color		colors[5];
	t_pattern	pattern;
	t_color		c;
	double		uv[2];

	new_color(1, 1, 1, &colors[0]);
	new_color(1, 0, 0, &colors[1]);
	new_color(1, 1, 0, &colors[2]);
	new_color(0, 1, 0, &colors[3]);
	new_color(0, 1, 1, &colors[4]);
	new_uv_align_check_pattern(&pattern, colors);
	uv[0] = 0.5;
	uv[1] = 0.5;
	c = uv_pattern_color_at(&pattern.align_colors, &uv[0], &uv[1]);
	cr_assert(eq(int, color_eq(c, colors[0]), true));
	uv[0] = 0.1;
	uv[1] = 0.9;
	c = uv_pattern_color_at(&pattern.align_colors, &uv[0], &uv[1]);
	cr_assert(eq(int, color_eq(c, colors[1]), true));
	uv[0] = 0.9;
	uv[1] = 0.9;
	c = uv_pattern_color_at(&pattern.align_colors, &uv[0], &uv[1]);
	cr_assert(eq(int, color_eq(c, colors[2]), true));
	uv[0] = 0.1;
	uv[1] = 0.1;
	c = uv_pattern_color_at(&pattern.align_colors, &uv[0], &uv[1]);
	cr_assert(eq(int, color_eq(c, colors[3]), true));
	uv[0] = 0.9;
	uv[1] = 0.1;
	c = uv_pattern_color_at(&pattern.align_colors, &uv[0], &uv[1]);
	cr_assert(eq(int, color_eq(c, colors[4]), true));
}

Test(patterns, Identifying_the_face_of_a_cube_from_a_point)
{
	t_point			p;
	t_cube_face	face;

	new_point(-1, 0.5, -0.25, &p);
	face = face_from_point(&p);
	cr_assert_eq(face, LEFT);
	new_point(1.1, -0.75, 0.8, &p);
	face = face_from_point(&p);
	cr_assert_eq(face, RIGHT);
	new_point(0.1, 0.6, 0.9, &p);
	face = face_from_point(&p);
	cr_assert_eq(face, FRONT);
	new_point(-0.7, 0, -2, &p);
	face = face_from_point(&p);
	cr_assert_eq(face, BACK);
	new_point(0.5, 1, 0.9, &p);
	face = face_from_point(&p);
	cr_assert_eq(face, UP);
	new_point(-0.2, -1.3, 1.1, &p);
	face = face_from_point(&p);
	cr_assert_eq(face, DOWN);
}

Test(patterns, uv_mapping_the_front_face_of_cube)
{
	double		uv[2];
	t_point		p;

	new_point(-0.5, 0.5, 1, &p);
	cube_uv_front(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(0.5, -0.5, 1, &p);
	cube_uv_front(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.25));
}

Test(pattern, uv_mapping_the_back_face_of_cube)
{
	double		uv[2];
	t_point		p;

	new_point(0.5, 0.5, -1, &p);
	cube_uv_back(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(-0.5, -0.5, -1, &p);
	cube_uv_back(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.25));
}

Test(pattern, uv_mapping_the_left_face_of_cube)
{
  double		uv[2];
  t_point		p;

	new_point(-1, 0.5, -0.5, &p);
	cube_uv_left(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(-1, -0.5, 0.5, &p);
	cube_uv_left(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.25));
}

Test(pattern, uv_mapping_the_right_face_of_cube)
{
	double		uv[2];
	t_point		p;

	new_point(1, 0.5, 0.5, &p);
	cube_uv_right(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(1, -0.5, -0.5, &p);
	cube_uv_right(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.25));
}

Test(pattern, uv_mapping_the_upper_face_of_cube)
{
	double		uv[2];
	t_point		p;

	new_point(-0.5, 1, -0.5, &p);
	cube_uv_up(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(0.5, 1, 0.5, &p);
	cube_uv_up(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.25));
}

Test(pattern, uv_mapping_the_lower_face_of_cube)
{
	double		uv[2];
	t_point		p;

	new_point(-0.5, -1, 0.5, &p);
	cube_uv_down(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.25));
	cr_assert(eq(dbl, uv[1], 0.75));
	new_point(0.5, -1, -0.5, &p);
	cube_uv_down(&p, uv);
	cr_assert(eq(dbl, uv[0], 0.75));
	cr_assert(eq(dbl, uv[1], 0.25));
}

Test(pattern, finding_the_colors_on_mapped_cube)
{
	t_color		red;
	t_color		yellow;
	t_color		brown;
	t_color		green;
	t_color		cyan;
	t_color		blue;
	t_color		purple;
	t_color		white;
	t_color		colors[5];
	t_pattern	align_checkers[6];
	t_pattern pattern;
	t_point		p;
	t_color		res;

	new_color(1, 0, 0, &red);
	new_color(1, 1, 0, &yellow);
	new_color(1, 0.5, 0, &brown);
	new_color(0, 1, 0, &green);
	new_color(0, 1, 1, &cyan);
	new_color(0, 0, 1, &blue);
	new_color(1, 0, 1, &purple);
	new_color(1, 1, 1, &white);
	colors[0] = yellow;
	colors[1] = cyan;
	colors[2] = red;
	colors[3] = blue;
	colors[4] = brown;
	new_uv_align_check_pattern(&align_checkers[0], colors);
	colors[0] = cyan;
	colors[1] = red;
	colors[2] = yellow;
	colors[3] = brown;
	colors[4] = green;
	new_uv_align_check_pattern(&align_checkers[1], colors);
	colors[0] = red;
	colors[1] = yellow;
	colors[2] = purple;
	colors[3] = green;
	colors[4] = white;
	new_uv_align_check_pattern(&align_checkers[2], colors);
	colors[0] = green;
	colors[1] = purple;
	colors[2] = cyan;
	colors[3] = white;
	colors[4] = blue;
	new_uv_align_check_pattern(&align_checkers[3], colors);
	colors[0] = brown;
	colors[1] = cyan;
	colors[2] = purple;
	colors[3] = red;
	colors[4] = yellow;
	new_uv_align_check_pattern(&align_checkers[4], colors);
	colors[0] = purple;
	colors[1] = brown;
	colors[2] = green;
	colors[3] = blue;
	colors[4] = white;
	new_uv_align_check_pattern(&align_checkers[5], colors);
	new_pattern(&pattern);
	pattern.texture_map.uv_mapping_fn = cube_map;
	new_cube_align_check_pattern(&pattern, align_checkers);
	// LEFT
	new_point(-1, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, yellow), true));
	new_point(-1, 0.9, -0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, cyan), true));
	new_point(-1, 0.9, 0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, red), true));
	new_point(-1, -0.9, -0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, blue), true));
	new_point(-1, -0.9, 0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, brown), true));
	// // FRONT
	new_point(0, 0, 1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, cyan), true));
	new_point(-0.9, 0.9, 1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, red), true));
	new_point(0.9, 0.9, 1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, yellow), true));
	new_point(-0.9, -0.9, 1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, brown), true));
	new_point(0.9, -0.9, 1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, green), true));
	// // RIGHT
	new_point(1, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, red), true));
	new_point(1, 0.9, 0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, yellow), true));
	new_point(1, 0.9, -0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, purple), true));
	new_point(1, -0.9, 0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, green), true));
	new_point(1, -0.9, -0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, white), true));
	// // BACK
	new_point(0, 0, -1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, green), true));
	new_point(0.9, 0.9, -1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, purple), true));
	new_point(-0.9, 0.9, -1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, cyan), true));
	new_point(0.9, -0.9, -1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, white), true));
	new_point(-0.9, -0.9, -1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, blue), true));
	// // UP
	new_point(0, 1, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, brown), true));
	new_point(-0.9, 1, -0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, cyan), true));
	new_point(0.9, 1, -0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, purple), true));
	new_point(-0.9, 1, 0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, red), true));
	new_point(0.9, 1, 0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, yellow), true));
	// // DOWN
	new_point(0, -1, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, purple), true));
	new_point(-0.9, -1, 0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, brown), true));
	new_point(0.9, -1, 0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, green), true));
	new_point(-0.9, -1, -0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, blue), true));
	new_point(0.9, -1, -0.9, &p);
	pattern.pattern_at(&pattern, &p, &res);
	cr_assert(eq(int, color_eq(res, white), true));
}
