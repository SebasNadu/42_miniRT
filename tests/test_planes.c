#include "test.h"

Test(planes, the_normal_of_a_plane_is_constant_everywhere)
{
	t_shape		plane;
	t_vector	normal_1;
	t_vector	normal_2;
	t_vector	normal_3;
	t_point		p;

	new_plane(&plane); 
	new_point(0, 0, 0, &p);
	plane.normal_at(&plane, &p, &normal_1);
	new_point(10, 0, -10, &p);
	plane.normal_at(&plane, &p, &normal_2);
	new_point(-5, 0, 150, &p);
	plane.normal_at(&plane, &p, &normal_3);
	cr_assert(eq(dbl, normal_1.x, 0));
	cr_assert(eq(dbl, normal_1.y, 1));
	cr_assert(eq(dbl, normal_1.z, 0));
	cr_assert(eq(dbl, normal_2.x, 0));
	cr_assert(eq(dbl, normal_2.y, 1));
	cr_assert(eq(dbl, normal_2.z, 0));
	cr_assert(eq(dbl, normal_3.x, 0));
	cr_assert(eq(dbl, normal_3.y, 1));
	cr_assert(eq(dbl, normal_3.z, 0));
}

Test(planes, intersect_with_a_ray_parallel_to_the_plane)
{
	t_shape	plane;
	t_ray		r;
	t_hit		*xs;
	t_point		p;
	t_vector	v;

	xs = NULL;
	new_plane(&plane); 
	new_ray(new_point(0, 10, 0, &p), new_vector(0, 0, 1, &v), &r);
	intersect(&xs, &plane, &r);
	cr_assert(eq(dbl, intersect_count(xs), 0));
}

Test(planes, intersect_with_a_coplanar_ray)
{
	t_shape	plane;
	t_ray		r;
	t_hit		*xs;
	t_point		p;
	t_vector	v;

	xs = NULL;
	new_plane(&plane); 
	new_ray(new_point(0, 0, 0, &p), new_vector(0, 0, 1, &v), &r);
	intersect(&xs, &plane, &r);
	cr_assert(eq(dbl, intersect_count(xs), 0));
}

Test(plains, a_ray_intersectiong_a_plane_from_above)
{
	t_shape	plane;
	t_ray		r;
	t_hit		*xs;
	t_point		p;
	t_vector	v;

	xs = NULL;
	new_plane(&plane); 
	new_ray(new_point(0, 1, 0, &p), new_vector(0, -1, 0, &v), &r);
	intersect(&xs, &plane, &r);
	cr_assert(eq(dbl, intersect_count(xs), 1));
	cr_assert(eq(dbl, xs->t, 1));
	cr_assert(eq(ptr, xs->obj, &plane));
}

Test(plains, a_ray_intersectiong_a_plane_from_below)
{
	t_shape	plane;
	t_ray		r;
	t_hit		*xs;
	t_point		p;
	t_vector	v;

	xs = NULL;
	new_plane(&plane); 
	new_ray(new_point(0, -1, 0, &p), new_vector(0, 1, 0, &v), &r);
	intersect(&xs, &plane, &r);
	cr_assert(eq(dbl, intersect_count(xs), 1));
	cr_assert(eq(dbl, xs->t, 1));
	cr_assert(eq(ptr, xs->obj, &plane));
}
