#include "test.h"

Test(materials, create_a_material)
{
	t_material	m;

	new_material(&m);
	cr_assert(color_eq(m.ambient, (t_color){0.1, 0.1, 0.1}));
	cr_assert(eq(dbl, m.diffuse, 0.9));
	cr_assert(eq(dbl, m.specular, 0.9));
	cr_assert(eq(dbl, m.shininess, 200.0));
	cr_assert(color_eq(m.color, (t_color){1.0, 1.0, 1.0}));
}

Test(materials, lighting_with_the_eye_between_the_light_and_the_surface)
{
	t_shape		s;
	t_point		position;
	t_eye_normal	eye_normal;
	t_light		light;
	t_color		result;
	t_point		p;
	t_color  	c;

	new_shape(&s); 
	new_point(0.0, 0.0, 0.0, &position);
	new_vector(0.0, 0.0, -1.0, &eye_normal.eye_v);
	new_vector(0.0, 0.0, -1.0, &eye_normal.normal_v);
	new_point(0.0, 0.0, -10.0, &p);
	new_color(1.0, 1.0, 1.0, &c);
	new_light(&p, &c, &light);
	result = lighting(&s, &light, &position, &eye_normal);
	cr_assert(epsilon_eq(dbl, result.r, 1.9, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, 1.9, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, 1.9, EPSILON));
}

Test(materials, lighting_with_the_eye_between_light_and_surface_offset_45)
{
	t_shape		s;
	t_point		position;
	t_eye_normal	eye_normal;
	t_light		light;
	t_color		result;
	t_point		p;
	t_color  	c;

	new_shape(&s); 
	new_point(0.0, 0.0, 0.0, &position);
	new_vector(0.0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0, &eye_normal.eye_v);
	new_vector(0.0, 0.0, -1.0, &eye_normal.normal_v);
	new_point(0.0, 0.0, -10.0, &p);
	new_color(1.0, 1.0, 1.0, &c);
	new_light(&p, &c, &light);
	result = lighting(&s, &light, &position, &eye_normal);
	cr_assert(epsilon_eq(dbl, result.r, 1.0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, 1.0, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, 1.0, EPSILON));
}

Test(materials, lighting_with_eye_opposite_surface_light_offset_45)
{
	t_shape		s;
	t_point		position;
	t_eye_normal	eye_normal;
	t_light		light;
	t_color		result;
	t_point		p;
	t_color  	c;

	new_shape(&s); 
	new_point(0.0, 0.0, 0.0, &position);
	new_vector(0.0, 0.0, -1.0, &eye_normal.eye_v);
	new_vector(0.0, 0.0, -1.0, &eye_normal.normal_v);
	new_point(0.0, 10.0, -10.0, &p);
	new_color(1.0, 1.0, 1.0, &c);
	new_light(&p, &c, &light);
	result = lighting(&s, &light, &position, &eye_normal);
	cr_assert(epsilon_eq(dbl, result.r, 0.7364, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, 0.7364, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, 0.7364, EPSILON));
}

Test(materials, lighting_with_eye_in_the_path_of_the_light)
{
	t_shape		s;
	t_point		position;
	t_eye_normal	eye_normal;
	t_light		light;
	t_color		result;
	t_point		p;
	t_color  	c;

	new_shape(&s); 
	new_point(0.0, 0.0, 0.0, &position);
	new_vector(0.0, -sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0, &eye_normal.eye_v);
	new_vector(0.0, 0.0, -1.0, &eye_normal.normal_v);
	new_point(0.0, 10.0, -10.0, &p);
	new_color(1.0, 1.0, 1.0, &c);
	new_light(&p, &c, &light);
	result = lighting(&s, &light, &position, &eye_normal);
	cr_assert(epsilon_eq(dbl, result.r, 1.6364, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, 1.6364, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, 1.6364, EPSILON));
}

Test(materials, lighting_with_the_light_behind_the_surface)
{
	t_shape		s;
	t_point		position;
	t_eye_normal	eye_normal;
	t_light		light;
	t_color		result;
	t_point		p;
  t_color  	c;

	new_shape(&s); 
	new_point(0.0, 0.0, 0.0, &position);
	new_vector(0.0, 0.0, -1.0, &eye_normal.eye_v);
	new_vector(0.0, 0.0, -1.0, &eye_normal.normal_v);
	new_point(0.0, 0.0, 10.0, &p);
	new_color(1.0, 1.0, 1.0, &c);
	new_light(&p, &c, &light);
	result = lighting(&s, &light, &position, &eye_normal);
	cr_assert(epsilon_eq(dbl, result.r, 0.1, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, 0.1, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, 0.1, EPSILON));
}

Test(materials, lighting_with_the_surface_in_shadow)
{
	t_eye_normal	eye;
	t_light			light;
	t_color			result;
	t_color			expected;
	t_shape			s;
	t_tuple			position;
	t_point			p;
	t_color			c;

	new_shape(&s); 
	new_vector(0, 0, -1, &eye.eye_v);
	new_vector(0, 0, -1, &eye.normal_v);
	new_point(0, 0, 0, &position);
	new_point(0, 0, -10, &p);
	new_color(1.0, 1.0, 1.0, &c);
	new_light(&p, &c, &light);
	light.intensity_ratio = 0.0;
	result = lighting(&s, &light, &position, &eye);
	new_color(0.1, 0.1, 0.1, &expected);
	cr_assert(epsilon_eq(dbl, result.r, expected.r, EPSILON));
	cr_assert(epsilon_eq(dbl, result.g, expected.g, EPSILON));
	cr_assert(epsilon_eq(dbl, result.b, expected.b, EPSILON));
}
