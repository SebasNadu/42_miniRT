#include "world.h"

t_color	refracted_color(t_world *world, t_comps *comps)
{
	t_refrac_params	p;

	if (world->remaining_recursion == 0
		|| comps->obj->material.transparency < EPSILON)
		return (new_color(0, 0, 0));
	p.n_ratio = comps->n1 / comps->n2;
	p.cos_i = dot(comps->view.eye_v, comps->view.normal_v);
	p.sin2_t = p.n_ratio * p.n_ratio * (1 - (p.cos_i * p.cos_i));
	if (p.sin2_t > 1)
		return (new_color(0, 0, 0));
	world->remaining_recursion--;
	p.cos_t = sqrt(1.0 - p.sin2_t);
	p.direction = subtract(
			multiply(comps->view.normal_v, (p.n_ratio * p.cos_i - p.cos_t)),
			multiply(comps->view.eye_v, p.n_ratio));
	p.refract_ray = new_ray(comps->under_point, p.direction);
	p.refracted_color = color_at(world, &p.refract_ray);
	return (
		multiply_color(p.refracted_color, comps->obj->material.transparency));
}

t_color	reflected_color(t_world *world, t_comps *comps)
{
	t_ray	reflect_ray;

	if (comps->obj->material.reflective < EPSILON
		|| world->remaining_recursion == 0)
		return (new_color(0, 0, 0));
	world->remaining_recursion--;
	reflect_ray = new_ray(comps->over_point, comps->reflect_v);
	return (multiply_color(color_at(world, &reflect_ray),
			comps->obj->material.reflective));
}

double	schlick(t_comps *comps)
{
	double	cos_i;
	double	n_ratio;
	double	sin2_t;
	double	cos_t;
	double	r0[2];

	cos_i = dot(comps->view.eye_v, comps->view.normal_v);
	if (comps->n1 > comps->n2)
	{
		n_ratio = comps->n1 / comps->n2;
		sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
		if (sin2_t > 1.0)
			return (1);
		cos_t = sqrt(1.0 - sin2_t);
		cos_i = cos_t;
	}
	r0[1] = (comps->n1 - comps->n2) / (comps->n1 + comps->n2);
	r0[0] = r0[1] * r0[1];
	return (r0[0] + (1.0 - r0[0]) * pow(1.0 - cos_i, 5));
}

t_color	reflec_and_refrac(t_world *world, t_comps *comps, t_color *surface)
{
	t_color	reflected;
	t_color	refracted;
	double	reflectance;
	int		local_remaining;

	local_remaining = world->remaining_recursion;
	reflected = reflected_color(world, comps);
	world->remaining_recursion = local_remaining;
	refracted = refracted_color(world, comps);
	world->remaining_recursion = local_remaining;
	if (comps->obj->material.reflective > 0
		&& comps->obj->material.transparency > 0)
	{
		reflectance = schlick(comps);
		return (add_color(*surface, add_color(
					multiply_color(reflected, reflectance),
					multiply_color(refracted, 1.0 - reflectance))));
	}
	return (add_color(*surface, add_color(reflected, refracted)));
}
