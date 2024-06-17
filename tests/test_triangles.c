#include "test.h"

Test(triangles, constructing_a_triangle)
{
	t_shape	s;
	t_point	p[3];

	new_triangle(new_point(0, 1, 0, &p[0]), new_point(-1, 0, 0, &p[1]),
			new_point(1, 0, 0, &p[2]), &s);
	cr_assert(eq(dbl, s.tri.p1.x, 0));
	cr_assert(eq(dbl, s.tri.p1.y, 1));
	cr_assert(eq(dbl, s.tri.p1.z, 0));
	cr_assert(eq(dbl, s.tri.p2.x, -1));
	cr_assert(eq(dbl, s.tri.p2.y, 0));
	cr_assert(eq(dbl, s.tri.p2.z, 0));
	cr_assert(eq(dbl, s.tri.p3.x, 1));
	cr_assert(eq(dbl, s.tri.p3.y, 0));
  cr_assert(eq(dbl, s.tri.p3.z, 0));
	cr_assert(eq(dbl, s.tri.e1.x, -1));
	cr_assert(eq(dbl, s.tri.e1.y, -1));
	cr_assert(eq(dbl, s.tri.e1.z, 0));
	cr_assert(eq(dbl, s.tri.e2.x, 1));
	cr_assert(eq(dbl, s.tri.e2.y, -1));
	cr_assert(eq(dbl, s.tri.e2.z, 0));
	cr_assert(eq(dbl, s.tri.n1.x, 0));
  cr_assert(eq(dbl, s.tri.n1.y, 0));
  cr_assert(eq(dbl, s.tri.n1.z, -1));
}

Test(triangle, finding_the_normal_on_a_triangle)
{
  t_shape	s;
	t_vector	n1;
	t_vector	n2;
  t_vector	n3;
	t_point	p[3];

	new_triangle(new_point(0, 1, 0, &p[0]), new_point(-1, 0, 0, &p[1]),
			new_point(1, 0, 0, &p[2]), &s);
	new_point(0, 0.5, 0, &p[0]);
	s.normal_at(&s, &p[0], &n1);
	new_point(-0.5, 0.75, 0, &p[1]);
	s.normal_at(&s, &p[1], &n2);
	new_point(0.5, 0.25, 0, &p[2]);
	s.normal_at(&s, &p[2], &n3);
	cr_assert(eq(dbl, n1.x, s.tri.n1.x));
	cr_assert(eq(dbl, n1.y, s.tri.n1.y));
	cr_assert(eq(dbl, n1.z, s.tri.n1.z));
	cr_assert(eq(dbl, n2.x, s.tri.n1.x));
	cr_assert(eq(dbl, n2.y, s.tri.n1.y));
	cr_assert(eq(dbl, n2.z, s.tri.n1.z));
	cr_assert(eq(dbl, n3.x, s.tri.n1.x));
	cr_assert(eq(dbl, n3.y, s.tri.n1.y));
	cr_assert(eq(dbl, n3.z, s.tri.n1.z));
}

Test(triangle, intresecting_a_ray_parallel_to_the_triangle)
{
	t_shape	s;
	t_ray	r;
	t_hit	*xs;
	t_point	p[3];

	xs = NULL;
	new_triangle(new_point(0, 1, 0, &p[0]), new_point(-1, 0, 0, &p[1]),
			new_point(1, 0, 0, &p[2]), &s);
	new_ray(new_point(0, -1, -2, &p[0]), new_vector(0, 1, 0, &p[1]), &r);
	intersect(&xs, &s, &r);
	cr_assert(eq(ptr, xs, NULL));
}

Test(triangle, a_ray_misses_the_p1_p3_edge)
{
	t_shape	s;
	t_ray	r;
	t_hit	*xs;
	t_point	p[3];

	xs = NULL;
	new_triangle(new_point(0, 1, 0, &p[0]), new_point(-1, 0, 0, &p[1]),
			new_point(1, 0, 0, &p[2]), &s);
	new_ray(new_point(1, 1, -2, &p[0]), new_vector(0, 0, 1, &p[1]), &r);
	intersect(&xs, &s, &r);
	cr_assert(eq(ptr, xs, NULL));
}

Test(triangles, a_ray_misses_the_p1_p2_edge)
{
	t_shape	s;
	t_ray	r;
	t_hit	*xs;
	t_point	p[3];

	xs = NULL;
	new_triangle(new_point(0, 1, 0, &p[0]), new_point(-1, 0, 0, &p[1]),
			new_point(1, 0, 0, &p[2]), &s);
	new_ray(new_point(-1, 1, -2, &p[0]), new_vector(0, 0, 1, &p[1]), &r);
	intersect(&xs, &s, &r);
	cr_assert(eq(ptr, xs, NULL));
}

Test(triangles, a_ray_misses_the_p2_p3_edge)
{
  t_shape	s;
  t_ray	r;
  t_hit	*xs;
	t_point	p[3];

	xs = NULL;
	new_triangle(new_point(0, 1, 0, &p[0]), new_point(-1, 0, 0, &p[1]),
			new_point(1, 0, 0, &p[2]), &s);
	new_ray(new_point(0, -1, -2, &p[0]), new_vector(0, 0, 1, &p[1]), &r);
  intersect(&xs, &s, &r);
  cr_assert(eq(ptr, xs, NULL));
}

Test(triangles, a_ray_strikes_a_triangle)
{
	t_shape	s;
	t_ray	r;
	t_hit	*xs;
	t_point	p[3];

	xs = NULL;
	new_triangle(new_point(0, 1, 0, &p[0]), new_point(-1, 0, 0, &p[1]),
			new_point(1, 0, 0, &p[2]), &s);
	new_ray(new_point(0, 0.5, -2, &p[0]), new_vector(0, 0, 1, &p[1]), &r);
	intersect(&xs, &s, &r);
	cr_assert(eq(int, intersect_count(xs), 1));
	cr_assert(eq(dbl, xs->t, 2));
}
