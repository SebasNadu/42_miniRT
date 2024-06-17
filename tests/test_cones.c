#include "test.h"

Test(cones, intersecting_a_cone_with_a_ray)
{
	t_shape		cone;
	t_vector	dir;
	t_ray			r;
	t_hit			*xs;
	t_tuple		t;

	xs = NULL;
	new_cone(&cone); 
	normalize(new_vector(0, 0, 1, &t), &dir);
	new_ray(new_point(0, 0, -5, &t), &dir, &r);
	intersect(&xs, &cone, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 5, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 5, EPSILON));
	xs = NULL;
	normalize(new_vector(1, 1, 1, &t), &dir);
	new_ray(new_point(0, 0, -5, &t), &dir, &r);
	intersect(&xs, &cone, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 8.66025404, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 8.66025404, EPSILON));
	xs = NULL;
	normalize(new_vector(-0.5, -1, 1, &t), &dir);
	new_ray(new_point(1, 1, -5, &t), &dir, &r);
	intersect(&xs, &cone, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(epsilon_eq(dbl, xs->t, 4.55006, EPSILON));
	cr_assert(epsilon_eq(dbl, xs->next->t, 49.44994, EPSILON));
}

Test(cones, intersecting_a_cone_with_a_ray_parallel_to_one_of_its_halves)
{
  t_shape		cone;
  t_vector	dir;
  t_ray			r;
  t_hit			*xs;
	t_tuple		t;

	new_cone(&cone); 
	normalize(new_vector(0, 1, 1, &t), &dir);
	new_ray(new_point(0, 0, -1, &t), &dir, &r);
	xs = NULL;
	intersect(&xs, &cone, &r);
	cr_assert(eq(int, intersect_count(xs), 1));
	cr_assert(epsilon_eq(dbl, xs->t, 0.35355, EPSILON));
}

Test(cones, intersecting_a_cone_end_caps)
{
	t_shape		cone;
	t_vector	dir;
	t_ray			r;
	t_hit			*xs;
	t_tuple		t;

	new_cone(&cone); 
	cone.cyl.min = -0.5;
	cone.cyl.max = 0.5;
	cone.cyl.closed = true;
	normalize(new_vector(0, 1, 0, &t), &dir);
	new_ray(new_point(0, 0, -5, &t), &dir, &r);
	xs = NULL;
	intersect(&xs, &cone, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
	xs = NULL;
	normalize(new_vector(0, 1, 1, &t), &dir);
	new_ray(new_point(0, 0, -0.25, &t), &dir, &r);
	intersect(&xs, &cone, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	xs = NULL;
	normalize(new_vector(0, 1, 0, &t), &dir);
	new_ray(new_point(0, 0, -0.25, &t), &dir, &r);
	intersect(&xs, &cone, &r);
	cr_assert(eq(int, intersect_count(xs), 4));
}

Test(cones, computing_the_normal_vector_on_a_cone)
{
	t_shape		cone;
	t_vector	norm;
	t_point		p;

	new_cone(&cone); 
	new_point(0, 0, 0, &p);
	cone.normal_at(&cone, &p, &norm);
	cr_assert(eq(dbl, norm.x, 0));
	cr_assert(eq(dbl, norm.y, 0));
	cr_assert(eq(dbl, norm.z, 0));
	new_point(1, 1, 1, &p);
	cone.normal_at(&cone, &p, &norm);
	cr_assert(eq(dbl, norm.x, 1));
	cr_assert(eq(dbl, norm.y, -sqrt(2)));
	cr_assert(eq(dbl, norm.z, 1));
	new_point(-1, -1, 0, &p);
	cone.normal_at(&cone, &p, &norm);
	cr_assert(eq(dbl, norm.x, -1));
	cr_assert(eq(dbl, norm.y, 1));
	cr_assert(eq(dbl, norm.z, 0));
}
