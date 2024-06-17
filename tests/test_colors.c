#include "test.h"

/* Test the creation of a color struct.  */
Test(colors, create_a_color)
{
	t_color	c;

	c = new_color(-0.5, 0.4, 1.7);
	cr_assert(eq(dbl, c.r, -0.5));
	cr_assert(eq(dbl, c.g, 0.4));
	cr_assert(eq(dbl, c.b, 1.7));
}

/* Test the addition of two colors.  */
Test(colors, adding_colors)
{
	t_color	c;

	c = add_color(new_color(0.9, 0.6, 0.75), new_color(0.7, 0.1, 0.25));
	cr_assert(epsilon_eq(dbl, c.r, 1.6, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, 0.7, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, 1.0, DBL_EPSILON));
}

/* Test the subtraction of two colors.  */
Test(colors, subtracting_colors)
{
	t_color	c;

	c = subtract_color(new_color(0.9, 0.6, 0.75), new_color(0.7, 0.1, 0.25));
	cr_assert(epsilon_eq(dbl, c.r, 0.2, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, 0.5, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, 0.5, DBL_EPSILON));
}

/* Test the multiplication of a color by a scalar.  */
Test(colors, multiplying_a_color_by_a_scalar)
{
	t_color	c;

	c = multiply_color(new_color(0.2, 0.3, 0.4), 2);
	cr_assert(epsilon_eq(dbl, c.r, 0.4, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, 0.6, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, 0.8, DBL_EPSILON));
}

/* Test the multiplication of two colors.  */
Test(colors, multiply_colors)
{
	t_color	c;
	t_color c1;
	t_color c2;

	c1 = new_color(1, 0.2, 0.4);
	c2 = new_color(0.9, 1, 0.1);
	hadamard_product(&c1, &c2, &c);
	cr_assert(epsilon_eq(dbl, c.r, 0.9, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, 0.2, DBL_EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, 0.04, DBL_EPSILON));
}
