#include "test.h"

Test(groups, creating_a_new_group)
{
	t_shape	shape;

	new_group(&shape);
	cr_assert(eq(int, shape.next == NULL, 1));
	cr_assert(eq(int, matrix_eq(shape.transform, get_identity_matrix()), 1));
}

Test(groups, a_shape_has_a_parent_attribute)
{
	t_shape	shape;

	new_shape(&shape);
	cr_assert(eq(ptr, shape.parent, NULL));
}

Test(groups, adding_a_child_to_group)
{
	t_shape	group;
	t_shape	child;

	new_group(&group); 
	new_shape(&child);
	add_child(&group, &child);
	cr_assert(eq(ptr, group.root, &child));
	cr_assert(eq(ptr, group.root->next, NULL));
	cr_assert(eq(ptr, child.parent, &group));
}

Test(groups, intersecting_a_ray_with_an_empty_group)
{
	t_shape	group;
	t_ray	ray;
	t_hit	*xs;

	xs = NULL;
	new_group(&group); 
	ray = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	intersect(&xs, &group, &ray); 
	cr_assert(eq(int, intersect_count(xs), 0));
}

Test(groups, intersecting_a_ray_with_a_nonempty_group)
{
	t_shape	group;
	t_shape	s1;
	t_shape	s2;
	t_shape	s3;
	t_ray	ray;
	t_hit	*xs;

	xs = NULL;
	new_group(&group); 
	new_sphere(&s1); 
	new_sphere(&s2);
	new_sphere(&s3);
	set_transform(&s2, translation(0, 0, -3));
	set_transform(&s3, translation(5, 0, 0));
	add_child(&group, &s1);
	add_child(&group, &s2);
	add_child(&group, &s3);
	ray = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	intersect(&xs, &group, &ray); 
	cr_assert(eq(int, intersect_count(xs), 4));
	cr_assert(eq(ptr, xs->obj, &s2));
	cr_assert(eq(ptr, xs->next->obj, &s2));
	cr_assert(eq(ptr, xs->next->next->obj, &s1));
	cr_assert(eq(ptr, xs->next->next->next->obj, &s1));
}

Test(groups, intersecting_a_transformed_group)
{
	t_shape	group;
	t_shape	s1;
	t_ray	ray;
	t_hit	*xs;

	xs = NULL;
	new_group(&group); 
	set_transform(&group, scaling(2, 2, 2));
	new_sphere(&s1); 
	set_transform(&s1, translation(5, 0, 0));
	add_child(&group, &s1);
	ray = new_ray(new_point(10, 0, -10), new_vector(0, 0, 1));
	intersect(&xs, &group, &ray); 
	cr_assert(eq(int, intersect_count(xs), 2));
}

Test(groups, converting_a_point_from_world_to_object_space)
{
	t_shape	g1;
	t_shape	g2;
	t_shape	s1;
	t_point	p;

	new_group(&g1);
	set_transform(&g1, rotation_y(cos(M_PI_2), sin(M_PI_2)));
	new_group(&g2);
	set_transform(&g2, scaling(2, 2, 2));
	add_child(&g1, &g2);
	new_sphere(&s1);
	set_transform(&s1, translation(5, 0, 0));
	add_child(&g2, &s1);
	p = world_to_object(&s1, new_point(-2, 0, -10));
	cr_assert(epsilon_eq(dbl, p.x, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, p.y, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, p.z, -1, EPSILON));
}

Test(groups, converting_a_normal_from_object_to_world_space)
{
  t_shape	g1;
  t_shape	g2;
  t_shape	s;
  t_vector	n;

	new_group(&g1);
	set_transform(&g1, rotation_y(cos(M_PI_2), sin(M_PI_2)));
	new_group(&g2);
	set_transform(&g2, scaling(1, 2, 3));
	add_child(&g1, &g2);
	new_sphere(&s);
	set_transform(&s, translation(5, 0, 0));
	add_child(&g2, &s);
	n = normal_to_world(&s, new_vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
	cr_assert(epsilon_eq(dbl, n.x, 0.28571, EPSILON));
	cr_assert(epsilon_eq(dbl, n.y, 0.42857, EPSILON));
	cr_assert(epsilon_eq(dbl, n.z, -0.85714, EPSILON));
}

Test(groups, finding_the_normal_on_a_child_object)
{
	t_shape	g1;
	t_shape	g2;
	t_shape	s;
	t_vector	n;
	t_point	p;

	new_group(&g1);
	set_transform(&g1, rotation_y(cos(M_PI_2), sin(M_PI_2)));
	new_group(&g2);
	set_transform(&g2, scaling(1, 2, 3));
	add_child(&g1, &g2);
	new_sphere(&s);
	set_transform(&s, translation(5, 0, 0));
	add_child(&g2, &s);
	p = new_point(1.7321, 1.1547, -5.5774);
	n = normal_at(&s, &p);
	cr_assert(epsilon_eq(dbl, n.x, 0.2857, EPSILON));
	cr_assert(epsilon_eq(dbl, n.y, 0.42854, EPSILON));
	cr_assert(epsilon_eq(dbl, n.z, -0.85716, EPSILON));
}

Test(groups, groups_have_bounding_box)
{
	t_shape	g1;
  t_shape	s;
	t_ray		r1;
	t_ray		r2;
	t_ray		r3;
	t_hit		*xs;
	t_ray		trans_r;

	new_group(&g1);
	new_sphere(&s);
  add_child(&g1, &s);
	r1 = new_ray(new_point(0, 0, -2), new_vector(0, 0, 1));
	r2 = new_ray(new_point(0.9, 0.9, -2), new_vector(0, 0, 1));
	r3 = new_ray(new_point(1.1, 1.1, -2), new_vector(0, 0, 1));
	xs = NULL;
	trans_r = transform(&r1, &g1.inverse);
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &trans_r), true));
	xs = NULL;
	intersect(&xs, &g1,	&r1); 
	cr_assert(eq(int, intersect_count(xs), 2));
	xs = NULL;
	trans_r = transform(&r2, &g1.inverse);
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &trans_r), true));
	xs = NULL;
	intersect(&xs, &g1, &r2); 
  cr_assert(eq(int, intersect_count(xs), 0));
  xs = NULL;
	trans_r = transform(&r2, &g1.inverse);
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &trans_r), true));
	xs = NULL;
  intersect(&xs, &g1, &r3); 
  cr_assert(eq(int, intersect_count(xs), 0));
}

Test(groups, groups_have_bounding_box_with_transform)
{
	t_shape	g1;
	t_shape	s;
	t_ray		r1;
	t_ray		r2;
	t_ray		r3;
	t_hit		*xs;

	new_group(&g1);
	new_sphere(&s);
	add_child(&g1, &s);
	set_transform(&g1, translation(3, 3, 0));
	r1 = new_ray(new_point(3, 3, -2), new_vector(0, 0, 1));
	r2 = new_ray(new_point(3.9, 3.9, -2), new_vector(0, 0, 1));
	r3 = new_ray(new_point(5, 5, -2), new_vector(0, 0, 1));
	xs = NULL;
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &r1), true));
	xs = NULL;
	intersect(&xs, &g1, &r1); 
	cr_assert(eq(int, intersect_count(xs), 2));
	xs = NULL;
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &r2), true));
	xs = NULL;
	intersect(&xs, &g1, &r2); 
	cr_assert(eq(int, intersect_count(xs), 0));
  xs = NULL;
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &r3), false));
	xs = NULL;
	intersect(&xs, &g1, &r3); 
	cr_assert(eq(int, intersect_count(xs), 0));
}

Test(groups, groups_have_bounding_box_with_group_transform)
{
	t_shape	g1;
  t_shape	s;
  t_ray		r1;
  t_ray		r2;
  t_ray		r3;
  t_hit		*xs;

	new_group(&g1);
	set_transform(&g1, translation(1, 1, 0));
	new_sphere(&s);
	add_child(&g1, &s);
	set_transform(&s, translation(3, 3, 0));
	r1 = new_ray(new_point(4, 4, -2), new_vector(0, 0, 1));
	r2 = new_ray(new_point(4.9, 4.9, -2), new_vector(0, 0, 1));
	r3 = new_ray(new_point(5.1, 5.1, -2), new_vector(0, 0, 1));
	xs = NULL;
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &r1), true));
	xs = NULL;
  intersect(&xs, &g1, &r1); 
  cr_assert(eq(int, intersect_count(xs), 2));
  xs = NULL;
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &r2), true));
  xs = NULL;
  intersect(&xs, &g1, &r2); 
  cr_assert(eq(int, intersect_count(xs), 0));
	cr_assert(eq(int, g1.intersect_fn(&xs, &g1, &r3), false));
  xs = NULL;
  intersect(&xs, &g1, &r3); 
  cr_assert(eq(int, intersect_count(xs), 0));
}

Test(groups, checking_bounds_values)
{
	t_shape	g;
	t_shape	c;
	t_matrix	m;

	new_group(&g);
	set_transform(&g, translation(2, 0, 0));
  new_cylinder(&c);
	c.cyl.min = 0;
	c.cyl.max = 1;
	c.cyl.closed = true;
	m = multiply_matrices(translation(2, 0, 0), rotation_z(cos(M_PI / -4), sin(M_PI / -4)));
	set_transform(&c, m);
	add_child(&g, &c);
	g.bounds_of(&g);
	cr_assert(epsilon_eq(dbl, g.bounds.min.x, 1.29289, EPSILON));
  cr_assert(epsilon_eq(dbl, g.bounds.min.y, -0.70710, EPSILON));
  cr_assert(epsilon_eq(dbl, g.bounds.min.z, -1.0, EPSILON));
  cr_assert(epsilon_eq(dbl, g.bounds.max.x, 5.41421, EPSILON));
  cr_assert(epsilon_eq(dbl, g.bounds.max.y, 1.41421, EPSILON));
  cr_assert(epsilon_eq(dbl, g.bounds.max.z, 1.0, EPSILON));
}
