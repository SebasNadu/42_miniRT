/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:08:16 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:08:20 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"
#include "world.h"

t_point	*point_on_light(t_light *light, double u, double v, t_point *p)
{
	t_point	tmp;

	add(&light->corner, add(multiply(&light->uvec, u + rand_dbl(), &tmp),
			multiply(&light->vvec, v + rand_dbl(), p), p), p);
	return (p);
}

bool	is_shadowed(t_world *world, t_point *light_pos, t_point *point,
		double *ratio)
{
	t_vector	v;
	t_vector	tmp;
	double		distance;
	t_ray		r;
	t_hit		*xs;

	subtract(light_pos, point, &v);
	new_ray(point, normalize(&v, &tmp), &r);
	xs = intersect_world(world, &r);
	if (!xs)
		return (false);
	xs = hit(xs);
	if (xs && xs->obj->cast_shadow == false)
		return (false);
	distance = sqrt(magnitude_squared(&v));
	if (xs && xs->obj->cast_shadow == true && xs->t < distance)
	{
		if (xs->obj->material.transparency > 0)
			*ratio += 0.4 * xs->obj->material.transparency;
		return (true);
	}
	return (false);
}

static double	spotlight_intensity_ratio(t_light *light, t_point *point)
{
	t_vector	v;
	double		cos_angle_between;
	double		intensity_factor;

	subtract(point, &light->position, &v);
	normalize(&v, &v);
	cos_angle_between = dot(&v, &light->direction);
	if (cos_angle_between < light->fade_radian)
		return (0.0);
	if (cos_angle_between >= light->center_radian)
		return (1.0);
	intensity_factor = (cos_angle_between - light->fade_radian)
		/ light->delta_cos;
	return (intensity_factor);
}

static double	area_intensity_at(t_world *world, t_point *point, int index)
{
	double	total;
	double	u;
	double	v;
	t_point	light_position;

	total = 0.0;
	v = -1;
	while (++v < world->lights[index].vsteps)
	{
		u = -1;
		while (++u < world->lights[index].usteps)
		{
			point_on_light(&world->lights[index], u, v, &light_position);
			if (!is_shadowed(world, &light_position, point, &total))
			{
				if (world->lights[index].is_spotlight)
					total += spotlight_intensity_ratio(&world->lights[index],
							point);
				else
					total += 1.0;
			}
		}
	}
	return (total * world->lights[index].inverse_samples);
}

double	intensity_at(t_world *world, t_point *point, int index)
{
	double	total;

	total = 0.0;
	if (world->lights[index].is_area_light == false)
	{
		if (world->lights[index].is_spotlight)
		{
			if (is_shadowed(world, &world->lights[index].position, point,
					&total))
				return (total);
			return (spotlight_intensity_ratio(&world->lights[index], point));
		}
		else
		{
			if (is_shadowed(world, &world->lights[index].position, point,
					&total))
				return (total);
			return (1.0);
		}
	}
	return (area_intensity_at(world, point, index));
}
