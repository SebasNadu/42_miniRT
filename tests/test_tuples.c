#include "test.h"

/*
Test if the function tuple create correctly a tuple with the given arguments.
*/
Test(tuples, create_a_tuple)
{
	t_tuple a;

	a = new_tuple(4.2, -4.2, 3.2, 1.0);
	cr_assert(eq(dbl, a.x, 4.2));
	cr_assert(eq(dbl, a.y, -4.2));
	cr_assert(eq(dbl, a.z, 3.2));
	cr_assert(eq(dbl, a.w, 1.0));
}

/*
Test if the function point create correctly a tuple with the given arguments
w is set to 1.0 by default.
*/
Test(tuples, create_a_point)
{
	t_tuple a;

	new_point(4.2, -4.2, 3.2, &a);
	cr_assert(eq(dbl, a.x, 4.2));
	cr_assert(eq(dbl, a.y, -4.2));
	cr_assert(eq(dbl, a.z, 3.2));
	cr_assert(eq(dbl, a.w, 1.0));
}

/*
Test if the function vector create correctly a tuple with the given arguments
w is set to 0.0 by befault.
*/
Test(tuples, create_a_vector)
{
	t_tuple a;

	new_vector(4.2, -4.2, 3.2, &a);
	cr_assert(eq(dbl, a.x, 4.2));
	cr_assert(eq(dbl, a.y, -4.2));
	cr_assert(eq(dbl, a.z, 3.2));
	cr_assert(eq(dbl, a.w, 0.0));
}

/* Test if the function "add", adds two tuples correctly. */
Test(tuples, adding_a_tuples)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple result;

	a = new_tuple(3, -2, 5, 1.0);
	b = new_tuple(-2, 3, 1, 0.0);
	add(&a, &b, &result);
	cr_assert(eq(dbl, result.x, 1));
	cr_assert(eq(dbl, result.y, 1));
	cr_assert(eq(dbl, result.z, 6));
	cr_assert(eq(dbl, result.w, 1));
}

Test(tuples, adding_a_tuples_2)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple result;

	a = new_tuple(6, 5, 4, 1.0);
	b = new_tuple(-2, 6, 4, 0.0);
	add(&a, &b, &result);
	cr_assert(eq(dbl, result.x, 4));
	cr_assert(eq(dbl, result.y, 11));
	cr_assert(eq(dbl, result.z, 8));
	cr_assert(eq(dbl, result.w, 1));
}

/* test if the function "subtract", subtracts two tuples correctly. */
Test(tuples, subtracting_a_tuples)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple result;

	new_point(3, 2, 1, &a);       
	new_point(5, 6, 7, &b);
	subtract(&a, &b, &result);
	cr_assert(eq(dbl, result.x, -2));
	cr_assert(eq(dbl, result.y, -4));
	cr_assert(eq(dbl, result.z, -6));
	cr_assert(eq(dbl, result.w, 0));
	new_point(3, 2, 1, &a);
	new_vector(5, 6, 7, &b);
	cr_assert(eq(dbl, result.x, -2));
	cr_assert(eq(dbl, result.y, -4));
	cr_assert(eq(dbl, result.z, -6));
	cr_assert(eq(dbl, result.w, -0));
	new_vector(3, 2, 1, &a);
	new_vector(5, 6, 7, &b);
	cr_assert(eq(dbl, result.x, -2));
	cr_assert(eq(dbl, result.y, -4));
	cr_assert(eq(dbl, result.z, -6));
	cr_assert(eq(dbl, result.w, 0));
}

/* Test if the function "negate", negates a tuple correctly. */
Test(tuples, negating_a_tuple)
{
	t_tuple result;

	result = new_tuple(1, -2, 3, -4);
	negate(&result, &result);
	cr_assert(eq(dbl, result.x, -1));
	cr_assert(eq(dbl, result.y, 2));
	cr_assert(eq(dbl, result.z, -3));
	cr_assert(eq(dbl, result.w, 4));
}

/* Test if the function "multiply", multiplies a tuple by a scalar correctly. */
Test(tuples, multiplying_a_tuple_by_a_scalar)
{
	t_tuple	result;

	result = new_tuple(1, -2, 3, -4);
	multiply(&result, 3.5, &result);
	cr_assert(eq(dbl, result.x, 3.5));
	cr_assert(eq(dbl, result.y, -7));
	cr_assert(eq(dbl, result.z, 10.5));
	cr_assert(eq(dbl, result.w, -14));
	result = new_tuple(1, -2, 3, -4);
	multiply(&result, 0.5, &result);
	cr_assert(eq(dbl, result.x, 0.5));
	cr_assert(eq(dbl, result.y, -1));
	cr_assert(eq(dbl, result.z, 1.5));
	cr_assert(eq(dbl, result.w, -2));
}

/* test if the function "divide", divides a tuple by a scalar correctly. */
Test(tuples, dividing_a_tuple_by_a_scalar)
{
	t_tuple	result;

	result = new_tuple(1, -2, 3, -4);
	divide(&result, 2, &result);
	cr_assert(eq(dbl, result.x, 0.5));
	cr_assert(eq(dbl, result.y, -1));
	cr_assert(eq(dbl, result.z, 1.5));
	cr_assert(eq(dbl, result.w, -2));
}

/* Test if the function "magnitude", computes the magnitude of a vector correctly. */
Test(tuples, computing_the_magnitude_of_a_vector)
{
	double length;
	t_vector v;

	new_vector(1, 0, 0, &v);
	length = sqrt(magnitude_squared(&v));
	new_vector(0, 1, 0, &v);
	cr_assert(eq(dbl, length, 1));
	new_vector(0, 0, 1, &v);
	length = sqrt(magnitude_squared(&v));
	cr_assert(eq(dbl, length, 1));
	new_vector(0, 0, 1, &v);
	length = sqrt(magnitude_squared(&v));
	cr_assert(eq(dbl, length, 1));
	new_vector(1, 2, 3, &v);
	length = sqrt(magnitude_squared(&v));
	cr_assert(eq(dbl, length, sqrt(14)));
	new_vector(-1, -2, -3, &v);
	length = sqrt(magnitude_squared(&v));
	cr_assert(eq(dbl, length, sqrt(14)));
}

/* Test if the function "normalize" correctly normalizes a vector. */
Test(tuples, normalizing_vectors)
{
	t_tuple	v;
	t_tuple	normal;

	new_vector(4, 0, 0, &v);
	normalize(&v, &normal);
	cr_assert(epsilon_eq(dbl, sqrt(magnitude_squared(&normal)), 1, DBL_EPSILON));

	new_vector(1, 2, 3, &v);
	normalize(&v, &normal);
	cr_assert(epsilon_eq(dbl, sqrt(magnitude_squared(&normal)), 1, DBL_EPSILON));
}

/* Test if the function "dot" computes the dot product of two vectors correctly. */
Test(tuples, dot_product_of_two_vectors)
{
	t_vector	a;
	t_vector	b;
	double		result;

	new_vector(1, 2, 3, &a);
	new_vector(2, 3, 4, &b);
	result = dot(&a, &b);
	cr_assert(eq(dbl, result, 20));
}

/* Test the function "cross" computes the cross product of two vectors
 * correctly */
Test(tuples, cross_product_of_two_vectors)
{
	t_vector	a;
	t_vector	b;
	t_vector	result;

	new_vector(1, 2, 3, &a);
	new_vector(2, 3, 4, &b);
	cross(&a, &b, &result);
	cr_assert(eq(dbl, result.x, -1));
	cr_assert(eq(dbl, result.y, 2));
	cr_assert(eq(dbl, result.z, -1));
	cross(&b, &a, &result);
	cr_assert(eq(dbl, result.x, 1));
	cr_assert(eq(dbl, result.y, -2));
	cr_assert(eq(dbl, result.z, 1));
}

Test(tuples, reflecting_a_vector_approaching_at_45_degrees)
{
	t_vector	v;
	t_vector	n;
	t_vector	r;

	new_vector(1, -1, 0, &v);
	new_vector(0, 1, 0, &n);
	reflect(&v, &n, &r);
	cr_assert(eq(dbl, r.x, 1));
	cr_assert(eq(dbl, r.y, 1));
	cr_assert(eq(dbl, r.z, 0));
}

Test(tuples, reflecting_a_vector_off_a_slanted_surface)
{
	t_vector	v;
	t_vector	n;
	t_vector	r;

	new_vector(0, -1, 0, &v);
	new_vector(sqrt(2)/2, sqrt(2)/2, 0, &n);
	reflect(&v, &n, &r);
	cr_assert(epsilon_eq(dbl, r.x, 1, EPSILON));
	cr_assert(epsilon_eq(dbl, r.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, r.z, 0, EPSILON));
}
