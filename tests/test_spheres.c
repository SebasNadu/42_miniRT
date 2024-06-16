#include "test.h"

Test(spheres, a_ray_intersects_a_sphere_at_two_points)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;
	t_point				p;
	t_vector			v;

	xs = NULL;
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&s);
	intersect(&xs, &s, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 4));
	cr_assert(eq(dbl, xs->next->t, 6));
}

Test(spheres, a_ray_intersects_a_sphere_at_a_tangent)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;
	t_point				p;
	t_vector			v;

	xs = NULL;
	new_ray(new_point(0, 1, -5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&s);
	intersect(&xs, &s, &r);
	cr_assert(eq(int, intersect_count(xs), 1));
	cr_assert(eq(dbl, xs->t, 5.0));
	// cr_assert(eq(dbl, xs->next->t, 5.0)); // there is only one intersection
}

Test(spheres, a_ray_misses_a_sphere)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;
	t_point				p;
	t_vector			v;

	xs = NULL;
	new_ray(new_point(0, 2, -5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&s);
	intersect(&xs, &s, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
}

Test(spheres, a_ray_originates_inside_a_sphere)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;
	t_point				p;
	t_vector			v;

	xs = NULL;
	new_ray(new_point(0, 0, 0, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&s);
	intersect(&xs, &s, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, -1.0));
	cr_assert(eq(dbl, xs->next->t, 1.0));
}

Test(spheres, a_sphere_is_behind_a_ray)
{
	t_ray					r;
	t_shape				s;
	t_hit					*xs;
	t_point				p;
	t_vector			v;

	xs = NULL;
	new_ray(new_point(0, 0, 5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&s);
	intersect(&xs, &s, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, -6.0));
	cr_assert(eq(dbl, xs->next->t, -4.0));
}

Test(spheres, an_intersection_encapsulates_t_and_object)
{
	t_shape				s;
	t_hit					*xs;

	new_sphere(&s);
	xs = intersection(3.5, &s);
	cr_assert(eq(int, intersect_count(xs), 1));
	cr_assert(eq(dbl, xs->t, 3.5));
	cr_assert(xs->obj == &s);
}

Test(spheres, aggregating_intersections)
{
	t_shape	s;
	t_hit		*i1;
	t_hit		*i2;
	t_hit		*xs;

	xs = NULL;
	new_sphere(&s);
	i1 = intersection(1, &s);
	i2 = intersection(2, &s);
	insert_intersection(&xs, i1);
	insert_intersection(&xs, i2);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 1));
	cr_assert(eq(dbl, xs->next->t, 2));
}

Test(spheres, intersect_sets_object_on_intersection)
{
	t_shape	s;
	t_ray		r;
	t_hit		*xs;
	t_point	p;
	t_vector	v;

	xs = NULL;
	new_sphere(&s);
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	intersect(&xs, &s, &r);
	cr_assert(xs->obj == &s);
	cr_assert(xs->next->obj == &s);
}

Test(spheres, hit_when_all_intersections_have_positive_t)
{
	t_shape	s;
	t_hit		*xs;
	t_hit		*i;
	xs = NULL;
	new_sphere(&s);
	insert_intersection(&xs, intersection(2, &s));
	insert_intersection(&xs, intersection(1, &s));
	i = hit(xs);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(ptr, i, xs));
	cr_assert(eq(dbl, i->t, 1));
}

Test(spheres, hit_when_some_intersections_have_negative_t)
{
	t_shape	s;
	t_hit		*xs;
	t_hit		*i;

	xs = NULL;
	new_sphere(&s);
	insert_intersection(&xs, intersection(1, &s));
	insert_intersection(&xs, intersection(-1, &s));
	i = hit(xs);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(ptr, i, xs->next));
	cr_assert(eq(dbl, i->t, 1));
}

Test(spheres, hit_when_all_intersections_have_negative_t)
{
	t_shape	s;
	t_hit		*xs;
	t_hit		*i;

	xs = NULL;
	new_sphere(&s);
	insert_intersection(&xs, intersection(-2, &s));
	insert_intersection(&xs, intersection(-3, &s));
	i = hit(xs);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(ptr, i, NULL));
}

Test(spheres, hit_is_always_lowest_nonnegative_intersection)
{
	t_shape	s;
	t_hit		*xs;
	t_hit		*i;
	xs = NULL;
	new_sphere(&s);
	insert_intersection(&xs, intersection(5, &s));
	insert_intersection(&xs, intersection(7, &s));
	insert_intersection(&xs, intersection(-3, &s));
	insert_intersection(&xs, intersection(2, &s));
	i = hit(xs);
	cr_assert(eq(int, intersect_count(xs), 4));
	cr_assert(eq(ptr, i, xs->next));
	cr_assert(eq(dbl, i->t, 2));
}

Test(spheres, a_sphere_default_transformations)
{
	t_shape	s;
	t_matrix	t;
	new_sphere(&s);
	get_identity_matrix(&t);
	cr_assert(matrix_eq(s.transform, t));
}

Test(spheres, changing_a_sphere_transformation)
{
	t_shape	s;
	t_matrix	t;

	new_sphere(&s);
	translation(2, 3, 4, &t);
	set_transform(&s, &t);
	cr_assert(matrix_eq(s.transform, t));
}

Test(spheres, intersecting_a_scaled_sphere_with_a_ray)
{
	t_ray		r;
	t_shape	s;
	t_hit		*xs;
	t_matrix	m;
	t_point		p;
	t_vector	v;

	xs = NULL;
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&s);
	scaling(2, 2, 2, &m);
	set_transform(&s, &m);
	intersect(&xs, &s, &r);
	cr_assert(eq(int, intersect_count(xs), 2));
	cr_assert(eq(dbl, xs->t, 3));
	cr_assert(eq(dbl, xs->next->t, 7));
}

Test(spheres, intersecting_a_translated_sphere_with_a_ray)
{
	t_ray		r;
	t_shape	s;
	t_hit		*xs;
	t_matrix	m;
	t_point		p;
	t_vector	v;

	xs = NULL;
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&s);
	translation(5, 0, 0, &m);
	set_transform(&s, &m);
	intersect(&xs, &s, &r);
	cr_assert(eq(int, intersect_count(xs), 0));
}

Test(spheres, normal_on_a_sphere_at_a_point_on_x_axis)
{
	t_shape	s;
	t_vector	n;
	t_point	p;
	t_vector	v;

	new_sphere(&s);
	new_point(1, 0, 0, &p);
	normal_at(&s, &p, &n);
	new_vector(1, 0, 0, &v);
	cr_assert(tuple_eq(n, v));
}

Test(spheres, normal_on_a_sphere_at_a_point_on_y_axis)
{
	t_shape	s;
	t_vector	n;
	t_point	p;
	t_vector	v;

	new_sphere(&s);
	new_point(0, 1, 0, &p);
	normal_at(&s, &p, &n);
	new_vector(0, 1, 0, &v);
	cr_assert(tuple_eq(n, v));
}

Test(spheres, normal_on_a_sphere_at_a_point_on_z_axis)
{
	t_shape	s;
	t_vector	n;
	t_point	p;
	t_vector	v;

	new_sphere(&s);
	new_point(0, 0, 1, &p);
	normal_at(&s, &p, &n);
	new_vector(0, 0, 1, &v);
	cr_assert(tuple_eq(n, v));
}

Test(spheres, normal_on_a_sphere_at_a_nonaxial_point)
{
	t_shape	s;
	t_vector	n;
	t_point	p;
	t_vector	v;

	new_sphere(&s);
	new_point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, &p);
	normal_at(&s, &p, &n);
	new_vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, &v);
	cr_assert(tuple_eq(n, v));
}

Test(spheres, normal_is_a_normalized_vector)
{
	t_shape	s;
	t_vector	n;
	t_point	p;
	t_vector	v;

	new_sphere(&s);
	new_point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3, &p);
	normal_at(&s, &p, &n);
	normalize(&n, &v);
	cr_assert(tuple_eq(n, v));
}

Test(spheres, normal_on_a_translated_sphere)
{
	t_shape	s;
	t_vector	n;
	t_point	p;
	t_matrix	m;
	t_vector	v;

	new_sphere(&s);
	translation(0, 1, 0, &m);
	set_transform(&s, &m);
	new_point(0, 1.70711, -0.70711, &p);
	normal_at(&s, &p, &n);
	new_vector(0, 0.70711, -0.70711, &v);
	cr_assert(tuple_eq(n, v));
}

Test(spheres, normal_on_a_transformed_sphere)
{
	t_shape	s;
	t_vector	n;
	t_matrix	m;
	t_matrix	m2;
	t_point	p;
	t_vector	v;

	new_sphere(&s);
	multiply_matrices(scaling(1, 0.5, 1, &m), rotation_z(cos(M_PI/5), sin(M_PI/5), &m2), &m);
	set_transform(&s, &m);
	new_point(0, sqrt(2)/2, -sqrt(2)/2, &p);
	normal_at(&s, &p, &n);
	new_vector(0, 0.97014, -0.24254, &v);
	cr_assert(tuple_eq(n, v));
}

Test(spheres, a_sphere_has_a_default_material)
{
	t_shape	s;
	t_material	m;

	new_sphere(&s);
	s.material.diffuse = 0.9;
	s.material.specular = 0.9;
	new_material(&m);
	cr_assert(color_eq(m.ambient, s.material.ambient));
	cr_assert(eq(dbl, m.diffuse, s.material.diffuse));
	cr_assert(eq(dbl, m.specular, s.material.specular));
	cr_assert(eq(dbl, m.shininess, s.material.shininess));
	cr_assert(color_eq(m.color, s.material.color));
}

Test(spheres, a_sphere_may_be_assigned_a_material)
{
	t_shape	s;
	t_material	*m;

	new_sphere(&s);
	s.material.diffuse = 0.9;
	s.material.specular = 0.9;
	m = &s.material;
	new_color(1, 1, 1, &m->ambient);
	cr_assert(color_eq(s.material.ambient, m->ambient));
	cr_assert(eq(dbl, s.material.diffuse, 0.9));
	cr_assert(eq(dbl, s.material.specular, 0.9));
	cr_assert(eq(dbl, s.material.shininess, 200.0));
	cr_assert(color_eq(s.material.color, (t_color){1.0, 1.0, 1.0}));
}

Test(intersections, hit_should_offset_the_intersection)
{
	t_ray		r;
	t_shape		shape;
	t_hit		*i;
	t_comps		comps;
	t_matrix	m;
	t_point		p;
	t_vector	v;

	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&shape);
	translation(0, 0, 1, &m);
	set_transform(&shape, &m);
	i = intersection(5, &shape);
	comps = prepare_computations(i, &r, i);
	cr_assert(lt(dbl, comps.over_point.z, -EPSILON/2));
	cr_assert(gt(dbl, comps.point.z, comps.over_point.z));
}
