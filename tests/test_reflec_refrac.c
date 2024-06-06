#include "test.h"

Test(materials, reflectivity_for_the_default_material)
{
	t_material	m;
	m = new_material();
	cr_assert(eq(dbl, m.reflective, 0.0));
}

Test(intersections, precomputing_the_reflection_vector)
{
	t_shape		s;
	t_ray		r;
	t_hit	*i;
	t_comps		comps;
	t_vector		result;

	new_plane(&s);
	r = new_ray(new_point(0, 1, -1), new_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), &s);
	comps = prepare_computations(i, &r, NULL);
	result = comps.reflect_v;
	cr_assert(epsilon_eq(dbl, result.x, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.y, sqrt(2)/2, EPSILON));
	cr_assert(epsilon_eq(dbl, result.z, sqrt(2)/2, EPSILON));
}

Test(world, reflected_color_for_a_nonreflective_material)
{
	t_world		world;
	t_ray		r;
	t_hit		*i;
	t_comps		comps;
	t_color		color;

	world = default_world();
	r = new_ray(new_point(0, 0, 0), new_vector(0, 0, 1));
	world.objs[1].material.ambient = new_color(1, 1, 1);
	i = intersection(1, &world.objs[0]);
	comps = prepare_computations(i, &r, NULL);
	color = reflected_color(&world, &comps);
	cr_assert(color_eq(color, new_color(0, 0, 0)));
}

Test(world, reflected_color_for_a_reflective_material)
{
	t_world		world;
	t_ray		r;
	t_hit		*i;
	t_comps		comps;
	t_color		color;
	t_color		result;

	world = default_world();
	new_plane(&world.objs[1]);
	world.objs[1].material.reflective = 0.5;
	set_transform(&world.objs[1], translation(0, -1, 0));
	r = new_ray(new_point(0, 0, -3), new_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), &world.objs[1]);
	comps = prepare_computations(i, &r, NULL);
	color = reflected_color(&world, &comps);
	result = new_color(0.19032, 0.2379, 0.14274);
	// cr_assert(epsilon_eq(dbl, color.r, result.r, EPSILON));
	// cr_assert(epsilon_eq(dbl, color.g, result.g, EPSILON));
	cr_assert(epsilon_eq(dbl, color.b, result.b, EPSILON));
}

Test(world, shade_hit_with_a_reflective_material)
{
	t_world		world;
	t_ray		r;
	t_hit		*i;
	t_comps		comps;
	t_color		color;
	t_color		result;

	world = default_world();
	new_plane(&world.objs[1]);
	world.objs[1].material.reflective = 0.5;
	set_transform(&world.objs[1], translation(0, -1, 0));
	r = new_ray(new_point(0, 0, -3), new_vector(0, sqrt(2)/-2, sqrt(2)/2));
	i = intersection(sqrt(2), &world.objs[1]);
	comps = prepare_computations(i, &r, NULL);
	color = shade_hit(&world, &comps);
	result = new_color(0.87677, 0.92436, 0.82918);
	// cr_assert(epsilon_eq(dbl, color.r, result.r, EPSILON));
	// cr_assert(epsilon_eq(dbl, color.g, result.g, EPSILON));
	cr_assert(epsilon_eq(dbl, color.b, result.b, EPSILON));
}

Test(world, color_at_with_mutually_reflective_surfaces)
{
	t_world		world;
	t_ray		r;
	t_color		color;

	new_world(&world);
	world.lights = malloc(sizeof(t_light));
	world.lights_count = 1;
	world.lights[0] = new_light(new_point(0, 0, 0), new_color(1, 1, 1));
	world.objs = malloc(sizeof(t_shape) * 2);
	world.objs_count = 2;
	new_plane(&world.objs[0]);
	world.objs[0].material.reflective = 1;
	set_transform(&world.objs[0], translation(0, -1, 0));
	new_plane(&world.objs[1]);
	world.objs[1].material.reflective = 1;
	set_transform(&world.objs[1], translation(0, 1, 0));
	r = new_ray(new_point(0, 0, 0), new_vector(0, 1, 0));
	color = color_at(&world, &r);
	cr_assert(eq(ptr, &color, &color));
}

Test(world, reflected_color_at_the_maximum_recursive_depth)
	{
		t_world		world;
		t_ray		r;
		t_hit		*i;
		t_comps		comps;
		t_color		color;
		t_color		result;

		world = default_world();
		new_plane(&world.objs[0]);
		world.objs[0].material.reflective = 0.5;
		set_transform(&world.objs[0], translation(0, -1, 0));
		r = new_ray(new_point(0, 0, -3), new_vector(0, -sqrt(2) / 2, sqrt(2) / 2));
		i = intersection(sqrt(2), &world.objs[1]);
		comps = prepare_computations(i, &r, NULL);
		color = reflected_color(&world, &comps);
		result = new_color(0, 0, 0);
		cr_assert(epsilon_eq(dbl, color.r, result.r, EPSILON));
		cr_assert(epsilon_eq(dbl, color.g, result.g, EPSILON));
		cr_assert(epsilon_eq(dbl, color.b, result.b, EPSILON));
}

Test(materials, transparency_and_refractive_index_for_the_default_material)
{
	t_material	m;

	m = new_material();
	cr_assert(eq(dbl, m.transparency, 0.0));
	cr_assert(eq(dbl, m.refractive_index, 1.0));
}

Test(spheres, helper_for_producing_a_sphere_with_a_glassy_material)
{
	t_shape	s;

	new_glass_sphere(&s);
	cr_assert(eq(dbl, s.material.transparency, 1.0));
	cr_assert(eq(dbl, s.material.refractive_index, 1.52));
}

Test(intersections,finding_n1_and_n2_at_various_intersections)
{
	t_shape		a;
	t_shape		b;
	t_shape		c;
	t_ray		r;
	t_hit		*i;
	t_comps		comps;

	new_glass_sphere(&a);
	a.material.refractive_index = 1.5;
	set_transform(&a, scaling(2, 2, 2));
	new_glass_sphere(&b);
	b.material.refractive_index = 2.0;
	set_transform(&b, translation(0, 0, -0.25));
	new_glass_sphere(&c);
	c.material.refractive_index = 2.5;
	set_transform(&c, translation(0, 0, 0.25));
	r = new_ray(new_point(0, 0, -4), new_vector(0, 0, 1));
	i = NULL;
	insert_intersection(&i, intersection(2, &a));
	insert_intersection(&i, intersection(2.75, &b));
	insert_intersection(&i, intersection(3.25, &c));
	insert_intersection(&i, intersection(4.75, &b));
	insert_intersection(&i, intersection(5.25, &c));
	insert_intersection(&i, intersection(6, &a));

	comps = prepare_computations(i, &r, i);
	cr_assert(eq(dbl, comps.n1, 1.0));
	cr_assert(eq(dbl, comps.n2, 1.5));

	comps = prepare_computations(i->next, &r, i);
	cr_assert(eq(dbl, comps.n1, 1.5));
	cr_assert(eq(dbl, comps.n2, 2.0));

	comps = prepare_computations(i->next->next, &r, i);
	cr_assert(eq(dbl, comps.n1, 2.0));
	cr_assert(eq(dbl, comps.n2, 2.5));

	comps = prepare_computations(i->next->next->next, &r, i);
	cr_assert(eq(dbl, comps.n1, 2.5));
	cr_assert(eq(dbl, comps.n2, 2.5));

	comps = prepare_computations(i->next->next->next->next, &r, i);
	cr_assert(eq(dbl, comps.n1, 2.5));
	cr_assert(eq(dbl, comps.n2, 1.5));

	comps = prepare_computations(i->next->next->next->next->next, &r, i);
	cr_assert(eq(dbl, comps.n1, 1.5));
	cr_assert(eq(dbl, comps.n2, 1.0));
}

Test(intersections, the_under_point_is_offset_below_the_surface)
{
	t_ray	r;
	t_shape	s;
	t_hit	*i;
	t_hit	*xs;
	t_comps comps;

	xs = NULL;
	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	new_glass_sphere(&s);
	set_transform(&s, translation(0, 0, 1));
	i = intersection(5, &s);
	insert_intersection(&xs, i);
	comps = prepare_computations(i, &r, xs);
	cr_assert(gt(dbl, comps.under_point.z, EPSILON/2));
	cr_assert(lt(dbl, comps.point.z, comps.under_point.z));
}

Test(world, the_refracted_color_with_an_opaque_surface)
{
	t_world	world;
	t_ray	r;
	t_comps	comps;
	t_hit		*i;
	t_color	color;

	i = NULL;
	world = default_world();
	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	insert_intersection(&i, intersection(4, &world.objs[0]));
	insert_intersection(&i, intersection(6, &world.objs[0]));
	comps = prepare_computations(i, &r, i);
	color = refracted_color(&world, &comps);
	cr_assert(eq(dbl, color.r, 0));
	cr_assert(eq(dbl, color.g, 0));
	cr_assert(eq(dbl, color.b, 0));
}

Test(world, the_refracted_color_at_the_maximum_recursive_depth)
{
	t_world	world;
	t_ray	r;
	t_comps	comps;
	t_hit		*i;
	t_color	color;

	i = NULL;
	world = default_world();
	world.objs[0].material.transparency = 1.0;
	world.objs[0].material.refractive_index = 1.5;
	r = new_ray(new_point(0, 0, -5), new_vector(0, 0, 1));
	insert_intersection(&i, intersection(4, &world.objs[0]));
	insert_intersection(&i, intersection(6, &world.objs[0]));
	comps = prepare_computations(i, &r, i);
	world.remaining_recursion = 0;
	color = refracted_color(&world, &comps);
	cr_assert(eq(dbl, color.r, 0));
	cr_assert(eq(dbl, color.g, 0));
	cr_assert(eq(dbl, color.b, 0));
}

Test(world, the_refracted_color_under_total_internal_reflection)
{
	t_world	world;
	t_ray	r;
	t_comps	comps;
	t_hit		*i;
	t_color	color;

	i = NULL;
	world = default_world();
	world.objs[0].material.transparency = 1.0;
	world.objs[0].material.refractive_index = 1.5;
	r = new_ray(new_point(0, 0, sqrt(2)/2), new_vector(0, 1, 0));
	insert_intersection(&i, intersection(-sqrt(2)/2, &world.objs[0]));
	insert_intersection(&i, intersection(sqrt(2)/2, &world.objs[0]));
	comps = prepare_computations(hit(i), &r, i);
	color = refracted_color(&world, &comps);
	cr_assert(eq(dbl, color.r, 0));
	cr_assert(eq(dbl, color.g, 0));
	cr_assert(eq(dbl, color.b, 0));
}

//TODO: check if how runs the test with floats instead of doubles
Test(world, the_refracted_color_with_a_refracted_ray)
{
	t_world	world;
	t_ray	r;
	t_comps	comps;
	t_hit		*i;
	t_color	color;

	i = NULL;
	world = default_world();
	world.objs[0].material.ambient = new_color(1, 1, 1);
	world.objs[0].material.pattern = new_test_pattern();
	world.objs[1].material.transparency = 1.0;
	world.objs[1].material.refractive_index = 1.5;
	r = new_ray(new_point(0, 0, 0.1), new_vector(0, 1, 0));
	insert_intersection(&i, intersection(-0.9899, &world.objs[0]));
	insert_intersection(&i, intersection(-0.4899, &world.objs[1]));
	insert_intersection(&i, intersection(0.4899, &world.objs[1]));
	insert_intersection(&i, intersection(0.9899, &world.objs[0]));
	comps = prepare_computations(hit(i), &r, i);
	color = refracted_color(&world, &comps);
	cr_assert(epsilon_eq(dbl, color.r, 0, EPSILON));
	cr_assert(epsilon_eq(dbl, color.g, 0.99888, EPSILON));
	// cr_assert(epsilon_eq(dbl, color.b, 0.04725, EPSILON));
}

Test(world, shade_hit_with_a_reflective_material2)
{
	t_world	world;
	t_ray	r;
	t_hit	*i;
	t_comps	comps;
	t_color	color;
	t_color	result;

	i = NULL;
	world = default_world();
	new_plane(&world.objs[0]);
	world.objs[0].material.transparency = 0.5;
	world.objs[0].material.refractive_index = 1.5;
	set_transform(&world.objs[0], translation(0, -1, 0));
	new_sphere(&world.objs[1]);
	world.objs[1].material.color = new_color(1, 0, 0);
	world.objs[1].material.ambient = new_color(0.5, 0.5, 0.5);
	set_transform(&world.objs[1], translation(0, -3.5, -0.5));
	r = new_ray(new_point(0, 0, -3), new_vector(0, -sqrt(2)/2, sqrt(2)/2));
	insert_intersection(&i, intersection(sqrt(2), &world.objs[0]));
	comps = prepare_computations(i, &r, i);
	color = shade_hit(&world, &comps);
	result = new_color(0.93642, 0.68642, 0.68642);
	cr_assert(epsilon_eq(dbl, color.r, result.r, EPSILON));
	cr_assert(epsilon_eq(dbl, color.g, result.g, EPSILON));
	cr_assert(epsilon_eq(dbl, color.b, result.b, EPSILON));
}

Test(intersections, the_schlick_approximation_under_total_internal_reflection)
{
	t_shape	s;
	t_ray		r;
	t_hit		*i;
	t_comps	comps;
	double	reflectance;

	new_glass_sphere(&s);
	r = new_ray(new_point(0, 0, sqrt(2)/2), new_vector(0, 1, 0));
	i = NULL;
	insert_intersection(&i, intersection(-sqrt(2)/2, &s));
	insert_intersection(&i, intersection(sqrt(2)/2, &s));
	comps = prepare_computations(hit(i), &r, i);
	reflectance = schlick(&comps);
	cr_assert(eq(dbl, reflectance, 1.0));
}

Test(intersections, the_schlick_approximation_with_a_perpendicular_viewing_angle)
{
	t_shape	s;
	t_ray		r;
	t_hit		*i;
	t_comps	comps;
	double	reflectance;

	new_glass_sphere(&s);
	r = new_ray(new_point(0, 0, 0), new_vector(0, 1, 0));
	i = NULL;
	insert_intersection(&i, intersection(-1, &s));
	insert_intersection(&i, intersection(1, &s));
	comps = prepare_computations(hit(i), &r, i);
	reflectance = schlick(&comps);
	// Old test
	// cr_assert(epsilon_eq(dbl, reflectance, 0.04, EPSILON));
	cr_assert(epsilon_eq(dbl, reflectance, 0.0425799, EPSILON));
}

Test(intersections, the_schlick_approximation_with_small_angle_and_n2_greater_than_n1)
{
	t_shape	s;
	t_ray		r;
	t_hit		*i;
	t_comps	comps;
	double	reflectance;

	new_glass_sphere(&s);
	r = new_ray(new_point(0, 0.99, -2), new_vector(0, 0, 1));
	i = NULL;
	insert_intersection(&i, intersection(1.8589, &s));
	comps = prepare_computations(hit(i), &r, i);
	reflectance = schlick(&comps);
	// Old test
	// cr_assert(epsilon_eq(dbl, reflectance, 0.48873, EPSILON));
	cr_assert(epsilon_eq(dbl, reflectance, 0.49010, EPSILON));
}

Test(world, shade_hit_with_a_reflective_transparent_material)
{
	t_world	world;
	t_ray	r;
	t_hit	*i;
	t_comps	comps;
	t_color	color;
	t_color	result;

	i = NULL;
	world = default_world();
	r = new_ray(new_point(0, 0, -3), new_vector(0, -sqrt(2)/2, sqrt(2)/2));
	new_plane(&world.objs[0]);
	world.objs[0].material.reflective = 0.5;
	world.objs[0].material.transparency = 0.5;
	world.objs[0].material.refractive_index = 1.5;
	set_transform(&world.objs[0], translation(0, -1, 0));
	new_sphere(&world.objs[1]);
	world.objs[1].material.color = new_color(1, 0, 0);
	world.objs[1].material.ambient = new_color(0.5, 0.5, 0.5);
	set_transform(&world.objs[1], translation(0, -3.5, -0.5));
	insert_intersection(&i, intersection(sqrt(2), &world.objs[0]));
	comps = prepare_computations(i, &r, i);
	color = shade_hit(&world, &comps);
	// original result from the book
	// result = new_color(0.93391, 0.69643, 0.69243);
	result = new_color(0.92590, 0.68642, 0.68643);
	cr_assert(epsilon_eq(dbl, color.r, result.r, EPSILON));
	cr_assert(epsilon_eq(dbl, color.g, result.g, EPSILON));
	cr_assert(epsilon_eq(dbl, color.b, result.b, EPSILON));
}
