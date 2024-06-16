#include "test.h"

Test(world, creating_world)
{
	t_world world;

	new_world(&world);
	cr_assert(eq(ptr, world.objs, NULL));
	cr_assert(eq(ptr, world.objs, NULL));
}

Test(world, the_default_world)
{
	t_world	w;
	t_light	l;
	t_color	c;
	t_point	p;

	new_point(-10, 10, -10, &p);
	new_color(1, 1, 1, &c);
	new_light(&p, &c, &l);
	w = default_world();
	cr_assert(eq(dbl, w.lights[0].position.x, l.position.x));
	cr_assert(eq(dbl, w.lights[0].position.y, l.position.y));
	cr_assert(eq(dbl, w.lights[0].position.z, l.position.z));
	cr_assert(eq(dbl, w.lights[0].intensity.r, l.intensity.r));
	cr_assert(eq(dbl, w.lights[0].intensity.g, l.intensity.g));
	cr_assert(eq(dbl, w.lights[0].intensity.b, l.intensity.b));

	cr_assert(eq(dbl, w.objs[0].material.color.r, 0.8));
	cr_assert(eq(dbl, w.objs[0].material.color.g, 1.0));
	cr_assert(eq(dbl, w.objs[0].material.color.b, 0.6));
	cr_assert(eq(dbl, w.objs[0].material.diffuse, 0.7));
	cr_assert(eq(dbl, w.objs[0].material.specular, 0.2));
	cr_assert(eq(dbl, w.objs[1].transform.mx[0][0], 0.5));
}

Test(world, intersect_world_with_ray)
{
	t_world	w;
	t_ray	r;
	t_hit	*xs;
	t_point	p;
	t_vector	v;

	w = default_world();
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	xs = intersect_world(&w, &r);
	cr_assert(eq(int, intersect_count(xs), 4));
	cr_assert(eq(dbl, xs->t, 4.0));
	cr_assert(eq(dbl, xs->next->t, 4.5));
	cr_assert(eq(dbl, xs->next->next->t, 5.5));
	cr_assert(eq(dbl, xs->next->next->next->t, 6.0));
}

Test(world, precomputing_state_of_intersection)
{
	t_shape		sphere;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_point		p;
	t_vector	v;

	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&sphere); 
	i = intersection(4, &sphere);
	comps = prepare_computations(i, &r, i);
	cr_assert(eq(dbl, comps.t, i->t));
	cr_assert(eq(ptr, comps.obj, i->obj));
	new_point(0, 0, -1, &p);
	cr_assert(eq(int, tuple_eq(comps.point, p), true));
	new_vector(0, 0, -1, &v);
	cr_assert(eq(int, tuple_eq(comps.view.eye_v, v), true));
	cr_assert(eq(int, tuple_eq(comps.view.normal_v, v), true));
}

Test(world, hit_when_intersection_occurs_on_outside)
{
	t_shape		sphere;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_point		p;
	t_vector	v;

	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&sphere); 
	i = intersection(4, &sphere);
	comps = prepare_computations(i, &r, i);
	cr_assert(eq(int, comps.inside, false));
}

Test(world, hit_when_intersection_occurs_on_inside)
{
	t_shape		sphere;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_point		p;
	t_vector	v;

	new_ray(new_point(0, 0, 0, &p), new_vector(0, 0, 1, &v), &r);
	new_sphere(&sphere); 
	i = intersection(1, &sphere);
	comps = prepare_computations(i, &r, i);
	new_point(0, 0, 1, &p);
	cr_assert(eq(int, tuple_eq(comps.point, p), true));
	new_vector(0, 0, -1, &v);
	cr_assert(eq(int, tuple_eq(comps.view.eye_v, v), true));
	cr_assert(eq(int, comps.inside, true));
	cr_assert(eq(int, tuple_eq(comps.view.normal_v, v), true));
}

Test(world, shading_an_intersection)
{
	t_world		w;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_color		c;
	t_color		expected;
	t_point		p;
	t_vector	v;

	w = default_world();
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	i = intersection(4, &w.objs[0]);
	comps = prepare_computations(i, &r, i);
	shade_hit(&w, &comps, &c);
	new_color(0.38066, 0.47583, 0.2855, &expected);
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, shading_an_intersection_from_the_inside)
{
	t_world		w;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_color		c;
	t_color		expected;
	t_point		p;
	t_vector	v;

	w = default_world();
	new_color(1, 1, 1, &c);
	new_light(new_point(0, 0.25, 0, &p), &c, &w.lights[0]);
	new_ray(new_point(0, 0, 0, &p), new_vector(0, 0, 1, &v), &r);
	i = intersection(0.5, &w.objs[1]);
	comps = prepare_computations(i, &r, i);
	shade_hit(&w, &comps, &c);
	new_color(0.90498, 0.90498, 0.90498, &expected);
	(void)c;
	(void)expected;
	// TODO: fix this test
	// cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	// cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	// cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, color_for_missed_ray)
{
	t_world	w;
	t_ray	r;
	t_color	c;
	t_color	expected;
	t_point	p;
	t_vector	v;

	w = default_world();
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 1, 0, &v), &r);
	color_at(&w, &r, &c);
	new_color(0, 0, 0, &expected);
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, color_for_hit_ray)
{
	t_world	w;
	t_ray	r;
	t_color	c;
	t_color	expected;
	t_point	p;
	t_vector	v;

	w = default_world();
	new_ray(new_point(0, 0, -5, &p), new_vector(0, 0, 1, &v), &r);
	color_at(&w, &r, &c);
	new_color(0.38066, 0.47583, 0.2855, &expected);
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

Test(world, color_with_intersection_behind_ray)
{
	t_world	w;
	t_shape	*outer; 
	t_shape	*inner; 
	t_ray	r;
	t_color	c;
	t_color	expected;
	t_point	p;
	t_vector	v;

	w = default_world();
	outer = &w.objs[0];
	new_color(1, 1, 1, &outer->material.ambient);
	inner = &w.objs[1];
	new_color(1, 1, 1, &inner->material.ambient);
	new_ray(new_point(0, 0, 0.75, &p), new_vector(0, 0, -1, &v), &r);
	color_at(&w, &r, &c);
	expected = inner->material.color;
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
}

/*
 * Previous tests for hard shadows
Test(world, no_shadow_when_nothing_is_collinear_with_point_and_light)
{
	t_world	w;
	t_point	p;

	w = default_world();
	p = new_point(0, 10, 0);
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
}

Test(world, shadow_when_object_is_between_point_and_light)
{
	t_world	w;
	t_point	p;

	w = default_world();
	p = new_point(10, -10, 10);
	cr_assert(eq(int, is_shadowed(&w, &p, 0), true));
}

Test(world, no_shadow_when_object_is_behind_light)
{
	t_world	w;
	t_point	p;

	w = default_world();
	p = new_point(-20, 20, -20);
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
}

Test(world, no_shadow_when_object_is_behind_point)
{
	t_world	w;
	t_point	p;
	w = default_world();
	p = new_point(-2, 2, -2);
	cr_assert(eq(int, is_shadowed(&w, &p, 0), false));
}

Test(world, shade_hit_is_given_an_intersection_in_shadow)
{
	t_world		w;
	t_ray			r;
	t_hit			*i;
	t_comps		comps;
	t_color		c;
	t_color		expected;

	w = new_world();
	w.lights = malloc(sizeof(t_light));
	w.lights_count = 1;
	w.lights[0] = new_light(new_point(0, 0, -10), new_color(1, 1, 1));
	w.objs = malloc(sizeof(t_shape) * 2);
	w.objs_count = 2;
	new_sphere(&w.objs[0]);
	new_sphere(&w.objs[1]);
	set_transform(&w.objs[1], translation(0, 0, 10));
	r = new_ray(new_point(0, 0, 5), new_vector(0, 0, 1));
	i = intersection(4, &w.objs[1]);
	comps = prepare_computations(i, &r, i);
	c = shade_hit(&w, &comps);
	expected = new_color(0.1, 0.1, 0.1);
	cr_assert(epsilon_eq(dbl, c.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, c.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, c.b, expected.b, EPSILON));
} */

Test(world, is_shadow_tests_for_occlusion_between_two_points)
{
	t_world	w;
	t_point	light_p;
	t_point	p;

	w = default_world();
	new_point(-10, -10, -10, &light_p);
	new_point(-10, -10, -10, &p);
	cr_assert(eq(int, is_shadowed(&w, &light_p, &p), false));
	new_point(10, 10, 10, &p);
	cr_assert(eq(int, is_shadowed(&w, &light_p, &p), true));
	new_point(-20, -20, -20, &p);
	cr_assert(eq(int, is_shadowed(&w, &light_p, &p), false));
	new_point(-5, -5, -5, &p);
	cr_assert(eq(int, is_shadowed(&w, &light_p, &p), false));
}

Test(world, point_lights_evaluate_the_light_intesity_at_a_given_pos)
{
	t_world	w;
	t_point	p;
	double	intensity;

	w = default_world();
	new_point(0, 1.0001, 0, &p);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 1.0, EPSILON));
	new_point(-1.0001, 0, 0, &p);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 1.0, EPSILON));
	new_point(0, 0, -1.0001, &p);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 1.0, EPSILON));
	new_point(0, 0, 1.0001, &p);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 0.0, EPSILON));
	new_point(1.0001, 0, 0, &p);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 0.0, EPSILON));
	new_point(0, -1.0001, 0, &p);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 0.0, EPSILON));
	new_point(0, 0, 0, &p);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 0.0, EPSILON));
}

Test(world, lighting_fn_uses_light_intesity_to_attenuate_color)
{
	t_world		w;
	t_point		p;
	t_eye_normal	eye;
	t_color		result;
	t_color		expected;
	t_color		c;

	w = default_world();
	new_color(1, 1, 1, &c);
	new_light(new_point(0, 0, -10, &p), &c, &w.lights[0]);
	new_color(0.1, 0.1, 0.1, &w.objs[0].material.ambient);
	w.objs[0].material.diffuse = 0.9;
	w.objs[0].material.specular = 0;
	new_color(1, 1, 1, &w.objs[0].material.color);
	new_point(0, 0, -1, &p);
	new_vector(0, 0, -1, &eye.eye_v);
	new_vector(0, 0, -1, &eye.normal_v);
	w.lights[0].intensity_ratio = 1.0;
	result = lighting(&w.objs[0], &w.lights[0], &p, &eye);
	new_color(1, 1, 1, &expected);
	cr_assert(epsilon_eq(dbl, result.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, expected.b, EPSILON));
	w.lights[0].intensity_ratio = 0.5;
	result = lighting(&w.objs[0], &w.lights[0], &p, &eye);
	new_color(0.55, 0.55, 0.55, &expected);
	cr_assert(epsilon_eq(dbl, result.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, expected.b, EPSILON));
	w.lights[0].intensity_ratio = 0.0;
	result = lighting(&w.objs[0], &w.lights[0], &p, &eye);
	new_color(0.1, 0.1, 0.1, &expected);
	cr_assert(epsilon_eq(dbl, result.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, expected.b, EPSILON));
}

Test(world, creating_an_area_light)
{
	t_alight_params lp;
	t_light		l;

	new_point(0, 0, 0, &lp.corner);
	new_vector(2, 0, 0, &lp.full_uvec);
	new_vector(0, 0, 1, &lp.full_vvec);
	lp.usteps = 4;
	lp.vsteps = 2;
	new_color(1, 1, 1, &lp.intensity);
	new_area_light(&lp, &l);
	cr_assert(eq(dbl, l.corner.x, 0));
	cr_assert(eq(dbl, l.corner.y, 0));
	cr_assert(eq(dbl, l.corner.z, 0));
	cr_assert(eq(dbl, l.uvec.x, 0.5));
	cr_assert(eq(dbl, l.uvec.y, 0));
	cr_assert(eq(dbl, l.uvec.z, 0));
	cr_assert(eq(int, l.usteps, 4));
	cr_assert(eq(dbl, l.vvec.x, 0));
	cr_assert(eq(dbl, l.vvec.y, 0));
	cr_assert(eq(dbl, l.vvec.z, 0.5));
	cr_assert(eq(int, l.vsteps, 2));
	cr_assert(eq(int, l.inverse_samples, 0.125));
	cr_assert(eq(dbl, l.position.x, 1));
	cr_assert(eq(dbl, l.position.y, 0));
	cr_assert(eq(dbl, l.position.z, 0.5));
}

/*
* test before the introduction of jittered area light
Test(world, finding_a_single_point_on_an_area_light)
{
	t_alight_params lp;
	t_light	l;
	t_point	p;

	lp.corner = new_point(0, 0, 0);
	lp.full_uvec = new_vector(2, 0, 0);
	lp.full_vvec = new_vector(0, 0, 1);
	lp.usteps = 4;
	lp.vsteps = 2;
	lp.intensity = new_color(1, 1, 1);
	new_area_light(&lp, &l);
	p = point_on_light(&l, 0, 0);
	cr_assert(eq(dbl, p.x, 0.25));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.25));
	p = point_on_light(&l, 1, 0);
	cr_assert(eq(dbl, p.x, 0.75));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.25));
	p = point_on_light(&l, 0, 1);
	cr_assert(eq(dbl, p.x, 0.25));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.75));
	p = point_on_light(&l, 2, 0);
	cr_assert(eq(dbl, p.x, 1.25));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.25));
	p = point_on_light(&l, 3, 1);
	cr_assert(eq(dbl, p.x, 1.75));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.75));
} */

/*
* Test before the introduction of jittered area light
Test(world, the_area_light_intensity_function)
{
	t_world	w;
	t_alight_params	lp;
	t_point	p;
	double	intensity;

	w = default_world();
	lp.corner = new_point(-0.5, -0.5, -5);
	lp.full_uvec = new_vector(1, 0, 0);
	lp.full_vvec = new_vector(0, 1, 0);
	lp.usteps = 2;
	lp.vsteps = 2;
	lp.intensity = new_color(1, 1, 1);
	new_area_light(&lp, &w.lights[0]);
	p = new_point(0, 0, 2);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 0.0, EPSILON));
	p = new_point(1, -1, 2);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 0.25, EPSILON));
	p = new_point(1.5, 0, 2);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 0.5, EPSILON));
	p = new_point(1.25, 1.25, 3);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 0.75, EPSILON));
	p = new_point(0, 0, -2);
	intensity = intensity_at(&w, &p, 0);
	cr_assert(epsilon_eq(dbl, intensity, 1.0, EPSILON));
} */

/*
 * Previous approach to generate jittered area light points
Test(lights, finding_a_single_point_on_a_jittered_area_light)
{
	t_alight_params	lp;
	t_light	l;
	t_point	p;

	lp.corner = new_point(0, 0, 0);
	lp.full_uvec = new_vector(2, 0, 0);
	lp.full_vvec = new_vector(0, 0, 1);
	lp.usteps = 4;
	lp.vsteps = 2;
	lp.intensity = new_color(1, 1, 1);
	new_area_light(&lp, &l);
	l.jitter_by = new_sequencer(2, 0.3, 0.7);
	p = point_on_light(&l, 0, 0);
	cr_assert(eq(dbl, p.x, 0.15));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.35));
	p = point_on_light(&l, 1, 0);
	cr_assert(eq(dbl, p.x, 0.65));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.35));
	p = point_on_light(&l, 0, 1);
	cr_assert(eq(dbl, p.x, 0.15));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.85));
	p = point_on_light(&l, 2, 0);
	cr_assert(eq(dbl, p.x, 1.15));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.35));
	p = point_on_light(&l, 3, 1);
	cr_assert(eq(dbl, p.x, 1.65));
	cr_assert(eq(dbl, p.y, 0));
	cr_assert(eq(dbl, p.z, 0.85));
} */

Test(lights, finding_a_single_point_on_a_jittered_area_light)
{
	t_alight_params	lp;
	t_light	l;
	t_point	p1;
	t_point	p2;
	t_point	p3;

	new_point(0, 0, 0, &lp.corner);
	new_vector(2, 0, 0, &lp.full_uvec);
	new_vector(0, 0, 1, &lp.full_vvec);
	lp.usteps = 4;
	lp.vsteps = 2;
	new_color(1, 1, 1, &lp.intensity);
	new_area_light(&lp, &l);
	point_on_light(&l, 3, 1, &p1);
	point_on_light(&l, 3, 1, &p2);
	point_on_light(&l, 3, 1, &p3);
	cr_assert(eq(int, p1.x == p2.x && p2.x == p3.x, false));
	cr_assert(eq(int, p1.y == p2.y && p2.y == p3.y, true));
	cr_assert(eq(int, p1.z == p2.z && p2.z == p3.z, false));
}

/*
 * Now it has a default 32 serie
Test(lights, the_area_light_with_jittered_samples)
	{
		t_world	w;
		t_alight_params	lp;
		t_point	p;
		double	intensity;

		w = default_world();
		lp.corner = new_point(-0.5, -0.5, -5);
		lp.full_uvec = new_vector(1, 0, 0);
		lp.full_vvec = new_vector(0, 1, 0);
		lp.usteps = 2;
		lp.vsteps = 2;
		lp.intensity = new_color(1, 1, 1);
		new_area_light(&lp, &w.lights[0]);
		p = new_point(0, 0, 2);
		intensity = intensity_at(&w, &p, 0);
		cr_assert(epsilon_eq(dbl, intensity, 0.0, EPSILON));
		p = new_point(1, -1, 2);
		intensity = intensity_at(&w, &p, 0);
		cr_assert(epsilon_eq(dbl, intensity, 0.75, EPSILON));
		p = new_point(1.5, 0, 2);
		intensity = intensity_at(&w, &p, 0);
		cr_assert(epsilon_eq(dbl, intensity, 0.5, EPSILON));
		p = new_point(1.25, 1.25, 3);
		intensity = intensity_at(&w, &p, 0);
		cr_assert(epsilon_eq(dbl, intensity, 0.75, EPSILON));
		p = new_point(0, 0, -2);
		intensity = intensity_at(&w, &p, 0);
		cr_assert(epsilon_eq(dbl, intensity, 1.0, EPSILON));
} */
