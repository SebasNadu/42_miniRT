#include "world.h"

t_hit	*intersect_world(t_world *world, t_ray *ray)
{
	int		i;

	i = -1;
	world->xs = NULL;
	while (++i < world->objs_count && world->objs)
		intersect(&world->xs, &world->objs[i], ray);
	return (world->xs);
}

t_comps	prepare_computations(t_hit *intersect, t_ray *ray, t_hit *xs)
{
	t_comps	comps;

	comps.t = intersect->t;
	comps.obj = intersect->obj;
	comps.point = position(ray, comps.t);
	comps.view.eye_v = negate(normalize(ray->direction));
	comps.view.normal_v = normalize(normal_at(comps.obj, &comps.point));
	comps.n1 = 1;
	comps.n2 = 1;
	if (dot(comps.view.normal_v, comps.view.eye_v) < 0)
	{
		comps.inside = true;
		comps.view.normal_v = negate(comps.view.normal_v);
	}
	else
		comps.inside = false;
	if (xs != NULL)
		find_refractive_indices(&comps, intersect, xs);
	comps.reflect_v = reflect(ray->direction, comps.view.normal_v);
	comps.over_point = add(comps.point, multiply(comps.view.normal_v, EPSILON));
	comps.under_point = subtract(comps.point,
			multiply(comps.view.normal_v, EPSILON));
	return (comps);
}

static t_shape	*check_parents(t_shape *shape)
{
	t_shape	*current;
	t_shape	*found;
	t_color	default_color;

	current = shape;
	found = NULL;
	default_color = new_color(1.0, 1.0, 1.0);
	while (current->parent)
	{
		current = current->parent;
		if (current->material.pattern.has_pattern
			|| (current->material.color.r != default_color.r
				|| current->material.color.g != default_color.g
				|| current->material.color.b != default_color.b))
			found = current;
	}
	if (found)
		return (found);
	else
		return (shape);
}

t_color	shade_hit(t_world *world, t_comps *comps)
{
	int		i;
	t_color	surface; 
	t_shape	*parent;

	i = -1;
	surface = new_color(0, 0, 0);
	parent = check_parents(comps->obj);
	while (++i < world->lights_count)
	{
		world->lights[i].intensity_ratio = intensity_at(
				world, &comps->over_point, i);
		if (world->lights[i].is_area_light == false)
			surface = add_color(surface, lighting(parent,
						&world->lights[i], &comps->over_point, &comps->view));
		else
			surface = add_color(surface, area_lighting(parent,
						&world->lights[i], &comps->over_point, &comps->view));
	}
	return (reflec_and_refrac(world, comps, &surface));
}

t_color	color_at(t_world *world, t_ray *ray)
{
	t_hit	*intersect;
	t_comps	comps;

	intersect_world(world, ray);
	intersect = hit(world->xs);
	if (!intersect)
		return (new_color(0, 0, 0));
	comps = prepare_computations(intersect, ray, world->xs);
	return (shade_hit(world, &comps));
}
