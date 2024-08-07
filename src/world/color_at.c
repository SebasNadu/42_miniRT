/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:18:04 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:18:06 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	get_map_displacement(t_shape *shape, t_point *point, t_vector *normal)
{
	t_color		disp_color;
	double		disp_value;
	t_vector	displacement;

	set_interpolate_uv(&shape->material.pattern, shape);
	uv_texture_color_at(shape->material.pattern.texture[7],
		&shape->material.pattern.uv.u, &shape->material.pattern.uv.v,
		&disp_color);
	disp_value = disp_color.r * shape->material.pattern.disp_intensity;
	multiply(normal, disp_value, &displacement);
	add(point, &displacement, point);
}

t_comps	prepare_computations(t_hit *intersect, t_ray *ray, t_hit *xs)
{
	t_comps	c;

	c.t = intersect->t;
	c.obj = intersect->obj;
	position(ray, c.t, &c.point);
	negate(normalize(&ray->direction, &c.view.eye_v), &c.view.eye_v);
	if (c.obj->material.pattern.is_tri && c.obj->material.pattern.texture[7])
		get_map_displacement(c.obj, &c.point, &c.view.normal_v);
	normalize(normal_at(c.obj, &c.point, &c.view.normal_v), &c.view.normal_v);
	c.n1 = 1;
	c.n2 = 1;
	if (dot(&c.view.normal_v, &c.view.eye_v) < 0)
	{
		c.inside = true;
		negate(&c.view.normal_v, &c.view.normal_v);
	}
	else
		c.inside = false;
	if (xs != NULL)
		find_refractive_indices(&c, intersect, xs);
	reflect(&ray->direction, &c.view.normal_v, &c.reflect_v);
	add(&c.point, multiply(&c.view.normal_v, EPSILON,
			&c.over_point), &c.over_point);
	return (subtract(&c.point, multiply(&c.view.normal_v, EPSILON,
				&c.under_point), &c.under_point), c);
}

static t_shape	*check_parents(t_shape *shape)
{
	t_shape	*current;
	t_shape	*found;
	t_color	default_color;

	current = shape;
	found = NULL;
	new_color(1.0, 1.0, 1.0, &default_color);
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

t_color	*shade_hit(t_world *world, t_comps *comps, t_color *surface)
{
	int		i;
	t_shape	*parent;
	t_color	tmp;

	i = -1;
	parent = check_parents(comps->obj);
	while (++i < world->lights_count)
	{
		world->lights[i].intensity_ratio = intensity_at(
				world, &comps->over_point, i);
		if (world->lights[i].is_area_light == false)
		{
			tmp = lighting(parent, &world->lights[i], &comps->over_point,
					&comps->view);
			add_color(surface, &tmp, surface);
		}
		else
		{
			tmp = area_lighting(parent, &world->lights[i], &comps->over_point,
					&comps->view);
			add_color(surface, &tmp, surface);
		}
	}
	return (reflec_and_refrac(world, comps, surface));
}

t_color	*color_at(t_world *world, t_ray *ray, t_color *color)
{
	t_hit	*intersect;
	t_comps	comps;

	*color = (t_color){0, 0, 0};
	intersect_world(world, ray);
	intersect = hit(world->xs);
	if (!intersect)
		return (&world->ambient);
	comps = prepare_computations(intersect, ray, world->xs);
	return (shade_hit(world, &comps, color));
}
