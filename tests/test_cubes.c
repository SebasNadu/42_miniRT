#include "test.h"

Test(cubes, a_ray_intersects_a_cube)
{
	t_ray		r;
	t_shape	c;
	t_hit		*xs;
	t_point	p;
	t_vector	v;

	xs = NULL;
	new_cube(&c); 
	new_ray(new_point(5, 0.5, 0, &p), new_vector(-1, 0, 0, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(dbl, xs->next->t, 6));
	xs = NULL;
	new_ray(new_point(-5, 0.5, 0, &p), new_vector(1, 0, 0, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(dbl, xs->next->t, 6));
	xs = NULL;
	new_ray(new_point(0.5, 5, 0, &p), new_vector(0, -1, 0, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(dbl, xs->next->t, 6));
	xs = NULL;
	new_ray(new_point(0.5, -5, 0, &p), new_vector(0, 1, 0, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(dbl, xs->next->t, 6));
	xs = NULL;
	new_ray(new_point(0.5, 0, 5, &p), new_vector(0, 0, -1, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(dbl, xs->next->t, 6));
	xs = NULL;
	new_ray(new_point(0.5, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(dbl, xs->next->t, 6));
	xs = NULL;
	new_ray(new_point(0, 0.5, 0, &p), new_vector(0, 0, 1, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, -1));
	cr_assert(eq(dbl, xs->next->t, 1));
}

Test(cubes, a_ray_misses_a_cube)
{
	t_ray		r;
	t_shape	c;
	t_hit		*xs;
	t_point	p;
	t_vector	v;

	xs = NULL;
	new_cube(&c); 
	new_ray(new_point(-2, 0, 0, &p), new_vector(0.2673, 0.5345, 0.8018, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
	new_ray(new_point(0, -2, 0, &p), new_vector(0.8018, 0.2673, 0.5345, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
	new_ray(new_point(0, 0, -2, &p), new_vector(0.5345, 0.8018, 0.2673, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
	new_ray(new_point(2, 0, 2, &p), new_vector(0, 0, -1, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
	new_ray(new_point(0, 2, 2, &p), new_vector(0, -1, 0, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
	new_ray(new_point(2, 2, 0, &p), new_vector(-1, 0, 0, &v), &r);
	intersect(&xs, &c, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
}

Test(cubes, the_normal_on_the_surface_of_a_cube)
{
	t_shape	c;
	t_vector	normal;
	t_point	p;

	new_cube(&c); 
	new_point(1, 0.5, -0.8, &p);
	c.normal_at(&c, &p, &normal);
	cr_assert(eq(dbl, normal.x, 1));
	cr_assert(eq(dbl, normal.y, 0));
	cr_assert(eq(dbl, normal.z, 0));
	new_point(-1, -0.2, 0.9, &p);
	c.normal_at(&c, &p, &normal);
	cr_assert(eq(dbl, normal.x, -1));
	cr_assert(eq(dbl, normal.y, 0));
	cr_assert(eq(dbl, normal.z, 0));
	new_point(-0.4, 1, -0.1, &p);
	c.normal_at(&c, &p, &normal);
	cr_assert(eq(dbl, normal.x, 0));
	cr_assert(eq(dbl, normal.y, 1));
	cr_assert(eq(dbl, normal.z, 0));
	new_point(0.3, -1, -0.7, &p);
	c.normal_at(&c, &p, &normal);
	cr_assert(eq(dbl, normal.x, 0));
	cr_assert(eq(dbl, normal.y, -1));
	cr_assert(eq(dbl, normal.z, 0));
	new_point(-0.6, 0.3, 1, &p);
	c.normal_at(&c, &p, &normal);
	cr_assert(eq(dbl, normal.x, 0));
	cr_assert(eq(dbl, normal.y, 0));
	cr_assert(eq(dbl, normal.z, 1));
	new_point(0.4, 0.4, -1, &p);
	c.normal_at(&c, &p, &normal);
	cr_assert(eq(dbl, normal.x, 0));
	cr_assert(eq(dbl, normal.y, 0));
	cr_assert(eq(dbl, normal.z, -1));
	new_point(1, 1, 1, &p);
	c.normal_at(&c, &p, &normal);
	cr_assert(eq(dbl, normal.x, 1));
	cr_assert(eq(dbl, normal.y, 0));
	cr_assert(eq(dbl, normal.z, 0));
	new_point(-1, -1, -1, &p);
	c.normal_at(&c, &p, &normal);
	cr_assert(eq(dbl, normal.x, -1));
	cr_assert(eq(dbl, normal.y, 0));
	cr_assert(eq(dbl, normal.z, 0));
}
