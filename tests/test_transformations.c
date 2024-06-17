#include "test.h"

Test(transformations, mult_by_a_translation_matrix)
{
	t_matrix	transform;
	t_point		p;
	t_point		result;

	translation(5, -3, 2, &transform);
	new_point(-3, 4, 5, &p);
	multiply_matrix_by_tuple(&transform, &p, &result);

	cr_assert(eq(dbl, result.x, 2));
	cr_assert(eq(dbl, result.y, 1));
	cr_assert(eq(dbl, result.z, 7));
}

Test(transformations, mult_by_inverse_translation)
{
	t_matrix	inverse;
	t_point		result;

	inverse_matrix(translation(5, -3, 2, &inverse), &inverse);
	multiply_matrix_by_tuple(&inverse, new_point(-3, 4, 5, &result), &result);

	cr_assert(eq(dbl, result.x, -8));
	cr_assert(eq(dbl, result.y, 7));
	cr_assert(eq(dbl, result.z, 3));
}

Test(transformations, translation_doesnt_affect_vectors)
{
	t_matrix	transform; 
	t_vector	result;

	translation(5, -3, 2, &transform);
	multiply_matrix_by_tuple(&transform, new_vector(-3, 4, 5, &result), &result);

	cr_assert(eq(dbl, result.x, -3));
	cr_assert(eq(dbl, result.y, 4));
	cr_assert(eq(dbl, result.z, 5));
}

Test(transformations, scaling_matrix_applied_to_point)
{
	t_matrix	transform; 
	t_point		result;

	scaling(2, 3, 4, &transform);
	multiply_matrix_by_tuple(&transform, new_point(-4, 6, 8, &result), &result);

	cr_assert(eq(dbl, result.x, -8));
	cr_assert(eq(dbl, result.y, 18));
	cr_assert(eq(dbl, result.z, 32));
}

Test(transformations, scaling_matrix_applied_to_vector)
{
	t_matrix	transform; 
	t_vector	result;

	scaling(2, 3, 4, &transform);
	multiply_matrix_by_tuple(&transform, new_vector(-4, 6, 8, &result), &result);

	cr_assert(eq(dbl, result.x, -8));
	cr_assert(eq(dbl, result.y, 18));
	cr_assert(eq(dbl, result.z, 32));
}

Test(transformations, mult_inverse_of_scaling_matrix)
{
	t_matrix	inverse; 
	t_vector	result;

	inverse_matrix(scaling(2, 3, 4, &inverse), &inverse);
	multiply_matrix_by_tuple(&inverse, new_vector(-4, 6, 8, &result), &result);

	cr_assert(eq(dbl, result.x, -2));
	cr_assert(eq(dbl, result.y, 2));
	cr_assert(eq(dbl, result.z, 2));
}

Test(transformations, reflection_is_scaling_by_negative_values)
{
	t_matrix	trans; 
	t_point	result;

	scaling(-1, 1, 1, &trans);
	multiply_matrix_by_tuple(&trans, new_point(2, 3, 4, &result), &result);

	cr_assert(eq(dbl, result.x, -2));
	cr_assert(eq(dbl, result.y, 3));
	cr_assert(eq(dbl, result.z, 4));
}

Test(transformations, rotating_point_around_x)
{
	t_point		p;
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_point		result;

	new_point(0, 1, 0, &p);
	rotation_x(cos(M_PI_4), sin(M_PI_4), &half_quarter);
	rotation_x(cos(M_PI_2), sin(M_PI_2), &full_quarter);
	multiply_matrix_by_tuple(&half_quarter, &p, &result);
	cr_assert(epsilon_eq(dbl, result.x, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, sqrt(2)/2, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, sqrt(2)/2, EPSILON));
	multiply_matrix_by_tuple(&full_quarter, &p, &result);
	cr_assert(epsilon_eq(dbl, result.x, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, 1, EPSILON));
}

Test(transformations, inverse_of_x_rotation)
{
	t_point		p;
	t_matrix	half_quarter_i;
	t_point		result;

	new_point(0, 1, 0, &p);
	inverse_matrix(rotation_x(cos(M_PI_4), sin(M_PI_4), &half_quarter_i), &half_quarter_i);
	multiply_matrix_by_tuple(&half_quarter_i, &p, &result);
	cr_assert(epsilon_eq(dbl, result.x, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, sqrt(2)/2, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, -sqrt(2)/2, EPSILON));
}

Test(transformations, rotating_poin_around_y)
{
	t_point		p;
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_point		result;

	new_point(0, 0, 1, &p);
	rotation_y(cos(M_PI_4), sin(M_PI_4), &half_quarter);
	rotation_y(cos(M_PI_2), sin(M_PI_2), &full_quarter);
	multiply_matrix_by_tuple(&half_quarter, &p, &result);
	cr_assert(epsilon_eq(dbl, result.x, sqrt(2)/2, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, sqrt(2)/2, EPSILON));
	multiply_matrix_by_tuple(&full_quarter, &p, &result);
	cr_assert(epsilon_eq(dbl, result.x, 1, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, 0, EPSILON));
}

Test(transformations, rotating_poin_around_z)
{
	t_point		p;
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_point		result;

	new_point(0, 1, 0, &p);
	rotation_z(cos(M_PI_4), sin(M_PI_4), &half_quarter);
	rotation_z(cos(M_PI_2), sin(M_PI_2), &full_quarter);
	multiply_matrix_by_tuple(&half_quarter, &p, &result);
	multiply_matrix_by_tuple(&half_quarter, &p, &result);
	cr_assert(epsilon_eq(dbl, result.x, -sqrt(2)/2, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, sqrt(2)/2, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, 0, EPSILON));
	multiply_matrix_by_tuple(&full_quarter, &p, &result);
	cr_assert(epsilon_eq(dbl, result.x, -1, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, 0, EPSILON));
}

Test(transformations, shering_move_x_in_proportion_to_y)
{
	t_matrix	trans;
	t_point		result;

	shearing((t_shearing){1, 0}, (t_shearing){0}, (t_shearing){0}, &trans);
	multiply_matrix_by_tuple(&trans, new_point(2, 3, 4, &result), &result);
	cr_assert(eq(dbl, result.x, 5));
	cr_assert(eq(dbl, result.y, 3));
	cr_assert(eq(dbl, result.z, 4));
}

Test(transformations, shering_move_x_in_proportion_to_z)
{
	t_matrix	trans;
	t_point		result;

	shearing((t_shearing){0, 1}, (t_shearing){0}, (t_shearing){0}, &trans);
	multiply_matrix_by_tuple(&trans, new_point(2, 3, 4, &result), &result);
	cr_assert(eq(dbl, result.x, 6));
	cr_assert(eq(dbl, result.y, 3));
	cr_assert(eq(dbl, result.z, 4));
}

Test(transformations, shering_move_y_in_proportion_to_x)
{
	t_matrix	trans;
	t_point		result;

	shearing((t_shearing){0}, (t_shearing){1, 0}, (t_shearing){0}, &trans);
	multiply_matrix_by_tuple(&trans, new_point(2, 3, 4, &result), &result);
	cr_assert(eq(dbl, result.x, 2));
	cr_assert(eq(dbl, result.y, 5));
	cr_assert(eq(dbl, result.z, 4));
}

Test(transformations, shering_move_y_in_proportion_to_z)
{
	t_matrix	trans;
	t_point		result;

	shearing((t_shearing){0}, (t_shearing){0, 1}, (t_shearing){0}, &trans);
	multiply_matrix_by_tuple(&trans, new_point(2, 3, 4, &result), &result);
	cr_assert(eq(dbl, result.x, 2));
	cr_assert(eq(dbl, result.y, 7));
	cr_assert(eq(dbl, result.z, 4));
}

Test(transformations, shering_move_z_in_proportion_to_x)
{
	t_matrix	trans;
	t_point		result;

	shearing((t_shearing){0}, (t_shearing){0}, (t_shearing){1, 0}, &trans);
	multiply_matrix_by_tuple(&trans, new_point(2, 3, 4, &result), &result);
	cr_assert(eq(dbl, result.x, 2));
	cr_assert(eq(dbl, result.y, 3));
	cr_assert(eq(dbl, result.z, 6));
}

Test(transformations, shering_move_z_in_proportion_to_y)
{
	t_matrix	trans;
	t_point		result;

	shearing((t_shearing){0}, (t_shearing){0}, (t_shearing){0, 1}, &trans);
	multiply_matrix_by_tuple(&trans, new_point(2, 3, 4, &result), &result);
	cr_assert(eq(dbl, result.x, 2));
	cr_assert(eq(dbl, result.y, 3));
	cr_assert(eq(dbl, result.z, 7));
}

Test(transformations, individual_transformations_in_sequence)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;
	t_point		p;
	t_point		p2;
	t_point		p3;
	t_point		p4;

	new_point(1, 0, 1, &p);
	rotation_x(cos(M_PI_2), sin(M_PI_2), &a);
	scaling(5, 5, 5, &b);
	translation(10, 5, 7, &c);
	multiply_matrix_by_tuple(&a, &p, &p2);
	cr_assert(epsilon_eq(dbl, p2.x, 1, EPSILON));
	cr_assert(epsilon_eq(dbl, p2.y, -1, EPSILON));
	cr_assert(epsilon_eq(dbl, p2.z, 0, EPSILON));
	multiply_matrix_by_tuple(&b, &p2, &p3);
	cr_assert(epsilon_eq(dbl, p3.x, 5, EPSILON));
	cr_assert(epsilon_eq(dbl, p3.y, -5, EPSILON));
	cr_assert(epsilon_eq(dbl, p3.z, 0, EPSILON));
	multiply_matrix_by_tuple(&c, &p3, &p4);
	cr_assert(epsilon_eq(dbl, p4.x, 15, EPSILON));
	cr_assert(epsilon_eq(dbl, p4.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, p4.z, 7, EPSILON));
}

Test(transformations, chained_transformations_must_in_reverse_order)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;
	t_point		p;
	t_matrix	m;

	new_point(1, 0, 1, &p);
	rotation_x(cos(M_PI_2), sin(M_PI_2), &a);
	scaling(5, 5, 5, &b);
	translation(10, 5, 7, &c);
	multiply_matrices(multiply_matrices(&c, &b, &m), &a, &m);
	multiply_matrix_by_tuple(&m, &p, &p);
	cr_assert(epsilon_eq(dbl, p.x, 15, EPSILON));
	cr_assert(epsilon_eq(dbl, p.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, p.z, 7, EPSILON));
}

Test(transformations, chained_transformations_with_transformations_func)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;
	t_point		p;
	t_matrix	*m;

	new_point(1, 0, 1, &p);
	rotation_x(cos(M_PI_2), sin(M_PI_2), &a);
	scaling(5, 5, 5, &b);
	translation(10, 5, 7, &c);
	m = transformations(3, &a, &b, &c);
	multiply_matrix_by_tuple(m, &p, &p);
	cr_assert(epsilon_eq(dbl, p.x, 15, EPSILON));
	cr_assert(epsilon_eq(dbl, p.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, p.z, 7, EPSILON));
}
