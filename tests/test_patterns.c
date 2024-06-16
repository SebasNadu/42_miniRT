#include "test.c"

Test(patterns, create_stripe_feature)
{
	t_pattern	pattern;
	t_color		white;
	t_color		black;
	t_color		res;
	t_point		p;
	
	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	pattern.a = malloc(sizeof(t_pattern));
	pattern.b = malloc(sizeof(t_pattern));
	*pattern.a = new_solid_pattern(&white);
	*pattern.b = new_solid_pattern(&black);
	new_point(0, 0, 0, &p);

	pattern.a->pattern_at(pattern.a, &p, &res);
	cr_assert(eq(dbl, res.r, white.r));
	cr_assert(eq(dbl, res.g, white.g));
	cr_assert(eq(dbl, res.b, white.b));
	pattern.b->pattern_at(pattern.b, &p, &res);
	cr_assert(eq(dbl, res.r, black.r));
	cr_assert(eq(dbl, res.g, black.g));
	cr_assert(eq(dbl, res.b, black.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_y_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_point(0, 0, 0, &p);
	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_y_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_point(0, 1, 0, &p);
	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_y_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(0, 2, 0, &p);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

/* A stripe pattern is constant in z */
Test(patterns, new_pattern_constant_in_z_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(0, 0, 0, &p);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_z_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(0, 0, 1, &p);
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_z_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(0, 0, 2, &p);
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

/* A stripe pattern is constant in x */
Test(patterns, new_pattern_constant_in_x_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(0, 0, 0, &p);
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(0.9, 0, 0, &p);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(1, 0, 0, &p);
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_4)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(-0.1, 0, 0, &p);
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_5)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(-1, 0, 0, &p);
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, new_pattern_constant_in_x_6)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_point(-1.1, 0, 0, &p);
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, lighting_with_stripe_pattern_applied)
{
	t_material	m;
	t_eye_normal view; 
	t_light		light;
	t_color		c1;
	t_color		c2;
	t_shape		shape;
	t_point		p;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_sphere(&shape);
	new_material(&m);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &m.pattern);
	new_color(1, 1, 1, &m.ambient);
	m.diffuse = 0;
	m.specular = 0;
	shape.material = m;
	new_vector(0, 0, -1, &view.eye_v);
	new_vector(0, 0, -1, &view.normal_v);
	new_point(0, 0, -10, &p);
	new_color(1, 1, 1, &c1);
	new_light(&p, &c1, &light);
	light.intensity_ratio = 1.0;
	new_point(0.9, 0, 0, &p);
	c1 = lighting(&shape, &light, &p, &view);
	new_point(1.1, 0, 0, &p);
	c2 = lighting(&shape, &light, &p, &view);
	
	cr_assert(eq(dbl, c1.r, 1));
	cr_assert(eq(dbl, c1.g, 1));
	cr_assert(eq(dbl, c1.b, 1));

	cr_assert(eq(dbl, c2.r, 0));
	cr_assert(eq(dbl, c2.g, 0));
	cr_assert(eq(dbl, c2.b, 0));
	free(m.pattern.a);
	free(m.pattern.b);
}

Test(patterns, stripes_with_object_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	t_matrix	m;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_sphere(&object);
	set_transform(&object, scaling(2, 2, 2, &m));
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
	new_solid_pattern(&black), &pattern);
	new_point(1.5, 0, 0, &p);
	pattern_at_shape(&pattern, &object, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, stripes_with_pattern_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	t_matrix	m;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_sphere(&object); 
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	set_pattern_transform(&pattern, scaling(2, 2, 2, &m));
	new_point(1.5, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;

	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, stripes_with_object_and_pattern_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	t_matrix	m;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_sphere(&object); 
	set_transform(&object, scaling(2, 2, 2, &m));
	new_pattern(&pattern);
	new_stripe_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	set_pattern_transform(&pattern, translation(0.5, 0, 0, &m));
	new_point(2.5, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;

	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, gradient_linear_interpolation)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_pattern(&pattern);
	new_gradient_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	new_point(0, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0.25, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	new_color(0.75, 0.75, 0.75, &expected);
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0.5, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	new_color(0.5, 0.5, 0.5, &expected);
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0.75, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	new_color(0.25, 0.25, 0.25, &expected);
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, ring_pattern)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_pattern(&pattern);
	new_ring_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	new_point(0, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(1, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0, 0, 1, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0.708, 0, 0.708, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, checkers_should_repeat_in_x)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_pattern(&pattern);
	new_checkers_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	new_point(0, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0.99, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(1.01, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, checkers_should_repeat_in_y)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_pattern(&pattern);
	new_checkers_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	new_point(0, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0, 0.99, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0, 1.01, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}

Test(patterns, checkers_should_repeat_in_z)
{
	t_pattern	pattern;
	t_color		res;
	t_color		expected;
	t_point		p;
	t_color		white;
	t_color		black;

	new_color(1, 1, 1, &white);
	new_color(0, 0, 0, &black);
	new_pattern(&pattern);
	new_checkers_pattern(new_solid_pattern(&white),
		new_solid_pattern(&black), &pattern);
	new_point(0, 0, 0, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0, 0, 0.99, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = white;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	new_point(0, 0, 1.01, &p);
	pattern.pattern_at(&pattern, &p, &res);
	expected = black;
	cr_assert(eq(dbl, res.r, expected.r));
	cr_assert(eq(dbl, res.g, expected.g));
	cr_assert(eq(dbl, res.b, expected.b));
	free(pattern.a);
	free(pattern.b);
}
