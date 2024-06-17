#include "test.h"

Test(csg, csg_is_created_with_an_operation_and_two_shapes)
{
	t_shape	left;
	t_shape	right;
	t_shape	csg;

	new_sphere(&left);
	new_cube(&right);
	new_csg(UNION, &left, &right, &csg);
	cr_assert(eq(int, csg.is_csg, true));
	cr_assert(eq(int, csg.csg.op, UNION));
	cr_assert(eq(ptr, csg.csg.left, &left));
	cr_assert(eq(ptr, csg.csg.right, &right));
	cr_assert(eq(ptr, left.parent, &csg));
	cr_assert(eq(ptr, right.parent, &csg));
}

Test(csg, evaluating_the_rule_for_a_csg_operation)
{
	bool		result;

	result = intersect_allowed(UNION, true, true, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(UNION, true, true, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(UNION, true, false, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(UNION, true, false, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(UNION, false, true, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(UNION, false, true, false);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(UNION, false, false, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(UNION, false, false, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, true, true, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, true, true, false);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(INTERSECT, true, false, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, true, false, false);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(INTERSECT, false, true, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, false, true, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(INTERSECT, false, false, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(INTERSECT, false, false, false);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(DIFFERENCE, true, true, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(DIFFERENCE, true, true, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(DIFFERENCE, true, false, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(DIFFERENCE, true, false, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(DIFFERENCE, false, true, true);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(DIFFERENCE, false, true, false);
	cr_assert(eq(int, result, true));
	result = intersect_allowed(DIFFERENCE, false, false, true);
	cr_assert(eq(int, result, false));
	result = intersect_allowed(DIFFERENCE, false, false, false);
  cr_assert(eq(int, result, false));
}

Test(csg, filtering_a_list_of_intersections)
{
	t_shape		s1;
	t_shape		s2;
	t_shape		csg;
	t_hit		*xs;
	t_hit		*result;

	new_sphere(&s1);
	new_cube(&s2);
	new_csg(UNION, &s1, &s2, &csg);
	xs = NULL;
	result = NULL;
	insert_intersection(&xs, intersection(1, &s1));
	insert_intersection(&xs, intersection(2, &s2));
	insert_intersection(&xs, intersection(3, &s1));
  insert_intersection(&xs, intersection(4, &s2));
  filter_intersections(xs, &csg, &result);
	cr_assert(eq(int, intersect_count(result), 2));
	cr_assert(eq(dbl, result->t, 1));
  cr_assert(eq(dbl, result->next->t, 4));
	csg.csg.op = INTERSECT;
	result = NULL;
	filter_intersections(xs, &csg, &result);
	cr_assert(eq(int, intersect_count(result), 2));
	cr_assert(eq(dbl, result->t, 2));
	cr_assert(eq(dbl, result->next->t, 3));
	csg.csg.op = DIFFERENCE;
	result = NULL;
  filter_intersections(xs, &csg, &result);
  cr_assert(eq(int, intersect_count(result), 2));
	cr_assert(eq(dbl, result->t, 1));
	cr_assert(eq(dbl, result->next->t, 2));
}

Test(csg, a_ray_misses_a_CSG_object)
{
	t_shape	c;
	t_shape	s;
	t_shape	csg;
	t_ray		r;
  t_hit		*xs;
	t_point	p;
	t_vector	v;

	xs = NULL;
	new_sphere(&s);
  new_cube(&c);
  new_csg(UNION, &c, &s, &csg);
	new_ray(new_point(0, 2, -5, &p), new_vector(0, 0, 1, &v), &r);
	csg.intersect_fn(&xs, &csg, &r);
  cr_assert(eq(ptr, xs, NULL));
}

Test(csg, a_ray_hits_a_CSG_object)
{
  t_shape	s1;
  t_shape	s2;
  t_shape	csg;
  t_ray		r;
  t_hit		*xs;
	t_matrix	m;
	t_point	p;
	t_vector	v;

	new_sphere(&s1);
	new_sphere(&s2);
	set_transform(&s2, translation(0, 0, 0.5, &m));
	new_csg(UNION, &s1, &s2, &csg);
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
  xs = NULL;
  csg.intersect_fn(&xs, &csg, &r);
  cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(ptr, xs->obj, &s1));
  cr_assert(eq(dbl, xs->next->t, 6.5));
	cr_assert(eq(ptr, xs->next->obj, &s2));
}
