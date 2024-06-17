#include "test.h"

Test(view_transformations, transformation_matrix_for_the_default_orientation)
{
	t_point from;
	t_point to;
	t_vector up;
	t_matrix t;
	t_matrix expected;

	new_point(0, 0, 0, &from);
	new_point(0, 0, -1, &to);
	new_vector(0, 1, 0, &up);
	view_transform(&from, &to, &up, &t);
	get_identity_matrix(&expected);
	cr_assert(matrix_eq(t, expected));
}

Test(view_transformations, view_transformation_matrix_looking_in_positive_z_direction)
{
	t_point from;
	t_point to;
	t_vector up;
	t_matrix t;
	t_matrix expected;

	new_point(0, 0, 0, &from);
	new_point(0, 0, 1, &to);
	new_vector(0, 1, 0, &up);
	view_transform(&from, &to, &up, &t);
	scaling(-1, 1, -1, &expected);
	cr_assert(matrix_eq(t, expected));
}

Test(view_transformations, view_transformation_moves_the_world)
{
	t_point from;
	t_point to;
	t_vector up;
	t_matrix t;
	t_matrix expected;

	new_point(0, 0, 8, &from);
	new_point(0, 0, 0, &to);
	new_vector(0, 1, 0, &up);
	view_transform(&from, &to, &up, &t);
	translation(0, 0, -8, &expected);
	cr_assert(matrix_eq(t, expected));
}

Test(view_transformations, arbitrary_view_transformation)
{
	t_point from;
	t_point to;
	t_vector up;
	t_matrix t;
	t_matrix m;
	const double	expected[MAX][MAX] = {
		{-0.50709, 0.50709,  0.67612, -2.36643},
		{ 0.76772, 0.60609,  0.12122, -2.82843},
		{-0.35857, 0.59761, -0.71714,  0.00000},
		{ 0.00000, 0.00000,  0.00000,  1.00000},
	};

	new_point(1, 3, 2, &from);
	new_point(4, -2, 8, &to);
	new_vector(1, 1, 0, &up);
	view_transform(&from, &to, &up, &t);
	new_matrix(expected, 4, &m);
	cr_assert(matrix_eq(t, m));
}
