#include "test.h"

Test(bounding_box, check_all_shapes)
{
	t_shape	s;
	t_shape	p;
	t_shape	c;
	t_shape	cyl;
	t_shape	cone;
	t_shape	tri;
	t_point	t[3];

	new_sphere(&s);
	s.bounds_of(&s);
	cr_assert(eq(dbl, s.bounds.min.x, -1));
	cr_assert(eq(dbl, s.bounds.min.y, -1));
	cr_assert(eq(dbl, s.bounds.min.z, -1));
	cr_assert(eq(dbl, s.bounds.max.x, 1));
	cr_assert(eq(dbl, s.bounds.max.y, 1));
	cr_assert(eq(dbl, s.bounds.max.z, 1));
	new_plane(&p);
	p.bounds_of(&p);
	cr_assert(eq(dbl, p.bounds.min.x, -MAXFLOAT));
	cr_assert(eq(dbl, p.bounds.min.y, 0));
	cr_assert(eq(dbl, p.bounds.min.z, -MAXFLOAT));
	cr_assert(eq(dbl, p.bounds.max.x, MAXFLOAT));
	cr_assert(eq(dbl, p.bounds.max.y, 0));
	cr_assert(eq(dbl, p.bounds.max.z, MAXFLOAT));
	new_cube(&c);
	c.bounds_of(&c);
	cr_assert(eq(dbl, c.bounds.min.x, -1));
	cr_assert(eq(dbl, c.bounds.min.y, -1));
	cr_assert(eq(dbl, c.bounds.min.z, -1));
	cr_assert(eq(dbl, c.bounds.max.x, 1));
	cr_assert(eq(dbl, c.bounds.max.y, 1));
	cr_assert(eq(dbl, c.bounds.max.z, 1));
	new_cylinder(&cyl);
	cyl.cyl.min = -5;
	cyl.cyl.max = 3;
	cyl.bounds_of(&cyl);
	cr_assert(eq(dbl, cyl.bounds.min.x, -1));
	cr_assert(eq(dbl, cyl.bounds.min.y, -5));
	cr_assert(eq(dbl, cyl.bounds.min.z, -1));
	cr_assert(eq(dbl, cyl.bounds.max.x, 1));
	cr_assert(eq(dbl, cyl.bounds.max.y, 3));
	cr_assert(eq(dbl, cyl.bounds.max.z, 1));
	new_cone(&cone);
	cone.cone.min = -5;
	cone.cone.max = 3;
	cone.bounds_of(&cone);
	cr_assert(eq(dbl, cone.bounds.min.x, -5));
	cr_assert(eq(dbl, cone.bounds.min.y, -5));
	cr_assert(eq(dbl, cone.bounds.min.z, -5));
	cr_assert(eq(dbl, cone.bounds.max.x, 5));
	cr_assert(eq(dbl, cone.bounds.max.y, 3));
	cr_assert(eq(dbl, cone.bounds.max.z, 5));
	new_triangle(new_point(-3, 7, 2, &t[0]),
		new_point(6, 2, -4, &t[1]), new_point(2, -1, -1, &t[2]), &tri);
	tri.bounds_of(&tri);
	cr_assert(eq(dbl, tri.bounds.min.x, -3));
  cr_assert(eq(dbl, tri.bounds.min.y, -1));
  cr_assert(eq(dbl, tri.bounds.min.z, -4));
  cr_assert(eq(dbl, tri.bounds.max.x, 6));
  cr_assert(eq(dbl, tri.bounds.max.y, 7));
  cr_assert(eq(dbl, tri.bounds.max.z, 2));
}

Test(bounds, adding_one_bounding_box_to_another)
{
	t_shape	g;
	t_shape	s1;
	t_shape s2;

	new_group(&g);
	new_sphere(&s1);
	new_sphere(&s2);
	s1.bounds_of(&s1);
	s2.bounds_of(&s2);
	new_point(-5, -2, 0, &s1.bounds.min);
	new_point(7, 4, 4, &s1.bounds.max);
	s1.is_bounds_precal = true;
	new_point(8, -7, -2, &s2.bounds.min);
	new_point(14, 2, 8, &s2.bounds.max);
	s2.is_bounds_precal = true;
	add_child(&g, &s1);
	add_child(&g, &s2);
	cr_assert(eq(dbl, g.bounds.min.x, -5));
	cr_assert(eq(dbl, g.bounds.min.y, -7));
	cr_assert(eq(dbl, g.bounds.min.z, -2));
	cr_assert(eq(dbl, g.bounds.max.x, 14));
	cr_assert(eq(dbl, g.bounds.max.y, 4));
	cr_assert(eq(dbl, g.bounds.max.z, 8));
}

Test(bounds, checking_to_see_if_a_box_contains_a_given_point)
{
	t_bounds b;
	t_point	p;
	t_point t[2];

	new_bounds(new_point(5, -2, 0, &t[0]), new_point(11, 4, 7, &t[1]), &b);
	new_point(5, -2, 0, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), true));
	new_point(11, 4, 7, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), true));
	new_point(8, 1, 3, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), true));
	new_point(3, 0, 3, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	new_point(8, -4, 3, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	new_point(8, 1, -1, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	new_point(13, 1, 3, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	new_point(8, 5, 3, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
	new_point(8, 1, 8, &p);
	cr_assert(eq(int, box_contains_point(&b, &p), false));
}

Test(bounds, checking_to_see_if_a_box_contains_a_given_box)
{
	t_bounds b1;
	t_bounds b2;
	t_point t[2];

	new_bounds(new_point(5, -2, 0, &t[0]), new_point(11, 4, 7, &t[1]), &b1);
	new_bounds(new_point(5, -2, 0, &t[0]), new_point(11, 4, 7, &t[1]), &b2);
	cr_assert(eq(int, box_contains_box(&b1, &b2), true));
	new_bounds(new_point(6, -1, 1, &t[0]), new_point(10, 3, 6, &t[1]), &b2);
	cr_assert(eq(int, box_contains_box(&b1, &b2), true));
	new_bounds(new_point(4, -3, -1, &t[0]), new_point(10, 3, 6, &t[1]), &b2);
	cr_assert(eq(int, box_contains_box(&b1, &b2), false));
	new_bounds(new_point(6, -1, 1, &t[0]), new_point(12, 5, 8, &t[1]), &b2);
	cr_assert(eq(int, box_contains_box(&b1, &b2), false));
}

Test(bounds, a_group_has_a_bounding_box_that_contains_its_children)
{
	t_shape	g;
	t_shape	s;
	t_shape	c;
	t_matrix m;
	t_matrix m1;

	new_group(&g);
	new_sphere(&s);
	new_cylinder(&c);
	c.cyl.min = -2;
	c.cyl.max = 2;
	multiply_matrices(translation(2, 5, -3, &m), scaling(2, 2, 2, &m1), &m);
	set_transform(&s, &m);
	multiply_matrices(translation(-4, -1, 4, &m), scaling(0.5, 1, 0.5, &m1), &m);
	set_transform(&c, &m);
	add_child(&g, &s);
	add_child(&g, &c);
	cr_assert(eq(dbl, g.bounds.min.x, -4.5));
	cr_assert(eq(dbl, g.bounds.min.y, -3));
	cr_assert(eq(dbl, g.bounds.min.z, -5));
	cr_assert(eq(dbl, g.bounds.max.x, 4));
	cr_assert(eq(dbl, g.bounds.max.y, 7));
	cr_assert(eq(dbl, g.bounds.max.z, 4.5));
}

Test(bounds, a_csg_shape_has_a_bounding_box_that_contains_its_children)
{
	t_shape	csg;
	t_shape	s1;
	t_shape	s2;
	t_matrix m;

	new_sphere(&s1);
	new_sphere(&s2);
	set_transform(&s2, translation(2, 3, 4, &m));
	new_csg(DIFFERENCE, &s1, &s2, &csg);
	csg.bounds_of(&csg);
	cr_assert(eq(dbl, csg.bounds.min.x, -1));
	cr_assert(eq(dbl, csg.bounds.min.y, -1));
	cr_assert(eq(dbl, csg.bounds.min.z, -1));
	cr_assert(eq(dbl, csg.bounds.max.x, 3));
	cr_assert(eq(dbl, csg.bounds.max.y, 4));
	cr_assert(eq(dbl, csg.bounds.max.z, 5));
}

Test(bounds, intersecting_a_ray_with_a_bounding_box_at_the_origin)
{
	t_bounds b;
	t_ray	r;
	t_vector	d;
	t_point	t[2];

	new_bounds(new_point(-1, -1, -1, &t[0]), new_point(1, 1, 1, &t[1]), &b);
	normalize(new_vector(-1, 0, 0, &d), &d);
	new_ray(new_point(5, 0.5, 0, &t[0]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	normalize(new_vector(1, 0, 0, &d), &d);
	new_ray(new_point(-5, 0.5, 0, &t[1]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	normalize(new_vector(0, -1, 0, &d), &d);
	new_ray(new_point(0.5, 5, 0, &t[0]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	normalize(new_vector(0, 1, 0, &d), &d);
	new_ray(new_point(0.5, -5, 0, &t[1]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	normalize(new_vector(0, 0, -1, &d), &d);
	new_ray(new_point(0.5, 0, 5, &t[0]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	normalize(new_vector(0, 0, 1, &d), &d);
	new_ray(new_point(0.5, 0, -5, &t[1]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	normalize(new_vector(2, 4, 6, &d), &d);
	new_ray(new_point(-2, 0, 0, &t[0]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	normalize(new_vector(6, 2, 4, &d), &d);
	new_ray(new_point(0, -2, 0, &t[1]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	normalize(new_vector(4, 6, 2, &d), &d);
	new_ray(new_point(0, 0, -2, &t[0]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	normalize(new_vector(0, 0, -1, &d), &d);
	new_ray(new_point(2, 0, 2, &t[1]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	normalize(new_vector(0, -1, 0, &d), &d);
	new_ray(new_point(0, 2, 2, &t[0]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	normalize(new_vector(-1, 0, 0, &d), &d);
	new_ray(new_point(2, 2, 0, &t[1]), &d, &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
}

Test(bounds, intersecting_a_ray_with_a_non_cubic_bounding_box)
{
	t_bounds b;
	t_ray	r;
	t_point	t[2];

	new_bounds(new_point(5, -2, 0, &t[0]), new_point(11, 4, 7, &t[1]), &b);
	new_ray(new_point(15, 1, 2, &t[0]), normalize(new_vector(-1, 0, 0, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	new_ray(new_point(-5, -1, 4, &t[0]), normalize(new_vector(1, 0, 0, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	new_ray(new_point(7, 6, 5, &t[0]), normalize(new_vector(0, -1, 0, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	new_ray(new_point(9, -5, 6, &t[0]), normalize(new_vector(0, 1, 0, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	new_ray(new_point(8, 2, 12, &t[0]), normalize(new_vector(0, 0, -1, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	new_ray(new_point(6, 0, -5, &t[0]), normalize(new_vector(0, 0, 1, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	new_ray(new_point(8, 1, 3.5, &t[0]), normalize(new_vector(0, 0, 1, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), true));
	new_ray(new_point(9, -1, -8, &t[0]), normalize(new_vector(2, 4, 6, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	new_ray(new_point(8, 3, -4, &t[0]), normalize(new_vector(6, 2, 4, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	new_ray(new_point(9, -1, -2, &t[0]), normalize(new_vector(4, 6, 2, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	new_ray(new_point(4, 0, 9, &t[0]), normalize(new_vector(0, 0, -1, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	new_ray(new_point(8, 6, -1, &t[0]), normalize(new_vector(0, -1, 0, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
	new_ray(new_point(12, 5, 4, &t[0]), normalize(new_vector(-1, 0, 0, &t[1]), &t[1]), &r);
	cr_assert(eq(int, intersect_bounds(&b, &r), false));
}

Test(bounds, splitting_a_perfect_cube)
{
	t_bounds box[2];
	t_point t[2];

	new_bounds(new_point(-1, -4, -5, &t[0]), new_point(9, 6, 5, &t[1]), &box[0]);
	box[1] = box[0];
	split_bounds(box);
	cr_assert(eq(dbl, box[0].min.x, -1));
	cr_assert(eq(dbl, box[0].min.y, -4));
	cr_assert(eq(dbl, box[0].min.z, -5));
	cr_assert(eq(dbl, box[0].max.x, 4));
	cr_assert(eq(dbl, box[0].max.y, 6));
	cr_assert(eq(dbl, box[0].max.z, 5));
	cr_assert(eq(dbl, box[1].min.x, 4));
	cr_assert(eq(dbl, box[1].min.y, -4));
	cr_assert(eq(dbl, box[1].min.z, -5));
	cr_assert(eq(dbl, box[1].max.x, 9));
	cr_assert(eq(dbl, box[1].max.y, 6));
	cr_assert(eq(dbl, box[1].max.z, 5));
}

Test(bounds, splitting_an_xwide_box)
{
	t_bounds	box[2];
	t_point	t[2];

	new_bounds(new_point(-1, -2, -3, &t[0]), new_point(9, 5.5, 3, &t[1]), &box[0]);
	box[1] = box[0];
	split_bounds(box);
	cr_assert(eq(dbl, box[0].min.x, -1));
	cr_assert(eq(dbl, box[0].min.y, -2));
	cr_assert(eq(dbl, box[0].min.z, -3));
	cr_assert(eq(dbl, box[0].max.x, 4));
	cr_assert(eq(dbl, box[0].max.y, 5.5));
	cr_assert(eq(dbl, box[0].max.z, 3));
	cr_assert(eq(dbl, box[1].min.x, 4));
	cr_assert(eq(dbl, box[1].min.y, -2));
	cr_assert(eq(dbl, box[1].min.z, -3));
	cr_assert(eq(dbl, box[1].max.x, 9));
	cr_assert(eq(dbl, box[1].max.y, 5.5));
	cr_assert(eq(dbl, box[1].max.z, 3));
}

Test(bounds, splitting_a_ywide_box)
{
  t_bounds box[2];
	t_point t[2];

	new_bounds(new_point(-1, -2, -3, &t[0]), new_point(5, 8, 3, &t[1]), &box[0]);
	box[1] = box[0];
	split_bounds(box);
	cr_assert(eq(dbl, box[0].min.x, -1));
	cr_assert(eq(dbl, box[0].min.y, -2));
	cr_assert(eq(dbl, box[0].min.z, -3));
	cr_assert(eq(dbl, box[0].max.x, 5));
	cr_assert(eq(dbl, box[0].max.y, 3));
	cr_assert(eq(dbl, box[0].max.z, 3));
	cr_assert(eq(dbl, box[1].min.x, -1));
	cr_assert(eq(dbl, box[1].min.y, 3));
	cr_assert(eq(dbl, box[1].min.z, -3));
	cr_assert(eq(dbl, box[1].max.x, 5));
	cr_assert(eq(dbl, box[1].max.y, 8));
	cr_assert(eq(dbl, box[1].max.z, 3));
}

Test(bounds, splitting_a_zwide_box)
{
  t_bounds box[2];
	t_point t[2];

	new_bounds(new_point(-1, -2, -3, &t[0]), new_point(5, 3, 7, &t[1]), &box[0]);
	box[1] = box[0];
	split_bounds(box);
	cr_assert(eq(dbl, box[0].min.x, -1));
	cr_assert(eq(dbl, box[0].min.y, -2));
	cr_assert(eq(dbl, box[0].min.z, -3));
	cr_assert(eq(dbl, box[0].max.x, 5));
	cr_assert(eq(dbl, box[0].max.y, 3));
	cr_assert(eq(dbl, box[0].max.z, 2));
	cr_assert(eq(dbl, box[1].min.x, -1));
	cr_assert(eq(dbl, box[1].min.y, -2));
	cr_assert(eq(dbl, box[1].min.z, 2));
	cr_assert(eq(dbl, box[1].max.x, 5));
	cr_assert(eq(dbl, box[1].max.y, 3));
	cr_assert(eq(dbl, box[1].max.z, 7));
}

Test(group, partitioning_a_group_children)
{
	t_shape	g;
	t_shape	s1;
	t_shape	s2;
	t_shape	s3;
	t_shape	*left;
	t_shape	*right;
	t_matrix m;

	left = NULL;
	right = NULL;
	new_group(&g);
	new_sphere(&s1);
	new_sphere(&s2);
	new_sphere(&s3);
	set_transform(&s1, translation(-2, 0, 0, &m));
	set_transform(&s2, translation(2, 0, 0, &m));
	add_child(&g, &s1);
	add_child(&g, &s2);
	add_child(&g, &s3);
	partition_children(&g, &left, &right);
	cr_assert(eq(int, g.group.root == &s3, true));
	cr_assert(eq(int, left == &s1, true));
	cr_assert(eq(int, right == &s2, true));
}

Test(group, creating_subgroup_from_list_of_children)
{
	t_shape	s1;
	t_shape	s2;
	t_shape	g;
	t_shape	*container;

	new_sphere(&s1);
	new_sphere(&s2);
	new_group(&g);
	container = &s1;
	s1.next = &s2;
	make_subgroup(&g, &container);
	cr_assert(eq(int, g.group.count, 1));
	cr_assert(eq(int, g.group.root->is_group, true));
	cr_assert(eq(int, g.group.root->group.count, 2));
	cr_assert(eq(int, g.group.root->group.root == &s2, true));
	cr_assert(eq(int, g.group.root->group.root->next == &s1, true));
}

Test(shapes, subdividing_a_primitive_does_nothing)
{
	t_shape	s;

	new_sphere(&s);
	divide_group(&s, 1);
	cr_assert(eq(int, s.is_group, false));
	cr_assert(eq(ptr, s.next, NULL));
}

Test(groups, subdividing_a_group_divides_its_children)
{
	t_shape	g;
	t_shape	s1;
	t_shape	s2;
	t_shape	s3;
	t_matrix m;

	new_group(&g);
	new_sphere(&s1);
	new_sphere(&s2);
	new_sphere(&s3);
	set_transform(&s1, translation(-2, -2, 0, &m));
	set_transform(&s2, translation(-2, 2, 0, &m));
	set_transform(&s3, scaling(4, 4, 4, &m));
	add_child(&g, &s1);
	add_child(&g, &s2);
	add_child(&g, &s3);
	divide_group(&g, 1);
	cr_assert(eq(int, g.group.count, 2));
	cr_assert(eq(int, g.group.root->is_group, true));
	cr_assert(eq(int, g.group.root->group.count, 2));
	cr_assert(eq(int, g.group.root->group.root->is_group, true));
	cr_assert(eq(int, g.group.root->group.root->group.count, 1));
	cr_assert(eq(int, g.group.root->group.root->group.root == &s2, true));
	cr_assert(eq(int, g.group.root->group.root->next->is_group, true));
	cr_assert(eq(int, g.group.root->group.root->next->group.count, 1));
	cr_assert(eq(int, g.group.root->group.root->next->group.root == &s1, true));
	cr_assert(eq(int, g.group.root->next->is_group, false));
	cr_assert(eq(ptr, g.group.root->next, &s3));
}

Test(groups, subdividing_a_group_with_too_few_children)
{
	t_shape	g;
	t_shape sg;
	t_shape	s1;
	t_shape	s2;
	t_shape	s3;
	t_shape	s4;
	t_matrix m;

	new_group(&g);
	new_group(&sg);
	new_sphere(&s1);
	new_sphere(&s2);
	new_sphere(&s3);
	new_sphere(&s4);
	set_transform(&s1, translation(-2, 0, 0, &m));
	set_transform(&s2, translation(2, 1, 0, &m));
	set_transform(&s3, translation(2, -1, 0, &m));
	add_child(&sg, &s1);
	add_child(&sg, &s2);
	add_child(&sg, &s3);
	add_child(&g, &sg);
	add_child(&g, &s4);
	divide_group(&g, 3);
	cr_assert(eq(int, g.group.count, 2));
	cr_assert(eq(int, g.group.root->is_group, false));
	cr_assert(eq(ptr, g.group.root, &s4));
	cr_assert(eq(ptr, g.group.root->next, &sg));
	cr_assert(eq(int, g.group.root->next->group.count, 2));
	cr_assert(eq(int, g.group.root->next->group.root->is_group, true));
	cr_assert(eq(int, g.group.root->next->group.root->group.count, 2));
	cr_assert(eq(ptr, g.group.root->next->group.root->group.root, &s3));
	cr_assert(eq(ptr, g.group.root->next->group.root->group.root->next, &s2));
	cr_assert(eq(int, g.group.root->next->group.root->next->is_group, true));
	cr_assert(eq(ptr, g.group.root->next->group.root->next->group.root, &s1));
}

Test(csg, subdividing_a_csg_shape_subdivides_its_children)
{
	t_shape	csg;
	t_shape	s1;
	t_shape	s2;
	t_shape	s3;
	t_shape	s4;
	t_shape	right;
	t_shape	left;
	t_matrix m;

	new_sphere(&s1);
	new_sphere(&s2);
	new_sphere(&s3);
	new_sphere(&s4);
	set_transform(&s1, translation(-2, 0, 0, &m));
	set_transform(&s2, translation(2, 0, 0, &m));
	set_transform(&s3, translation(0, 0, -2, &m));
	set_transform(&s4, translation(0, 0, 2, &m));
	new_group(&left);
	new_group(&right);
	add_child(&left, &s1);
	add_child(&left, &s2);
	add_child(&right, &s3);
	add_child(&right, &s4);
	new_csg(DIFFERENCE, &left, &right, &csg);
	divide_group(&csg, 1);
	cr_assert(eq(int, csg.is_group, false));
	cr_assert(eq(ptr, csg.csg.left, &left));
	cr_assert(eq(ptr, csg.csg.right, &right));
	cr_assert(eq(int, csg.csg.left->is_group, true));
	cr_assert(eq(int, csg.csg.left->group.count, 2));
	cr_assert(eq(int, csg.csg.left->group.root->is_group, true));
	cr_assert(eq(int, csg.csg.left->group.root->group.count, 1));
	cr_assert(eq(ptr, csg.csg.left->group.root->group.root, &s2));
	cr_assert(eq(int, csg.csg.left->group.root->next->is_group, true));
	cr_assert(eq(int, csg.csg.left->group.root->next->group.count, 1));
	cr_assert(eq(ptr, csg.csg.left->group.root->next->group.root, &s1));
	cr_assert(eq(int, csg.csg.right->is_group, true));
	cr_assert(eq(int, csg.csg.right->group.count, 2));
	cr_assert(eq(int, csg.csg.right->group.root->is_group, true));
	cr_assert(eq(int, csg.csg.right->group.root->group.count, 1));
	cr_assert(eq(ptr, csg.csg.right->group.root->group.root, &s4));
	cr_assert(eq(int, csg.csg.right->group.root->next->is_group, true));
	cr_assert(eq(int, csg.csg.right->group.root->next->group.count, 1));
	cr_assert(eq(ptr, csg.csg.right->group.root->next->group.root, &s3));
}
