/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:07:53 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:07:58 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "lights.h"

static double	get_map_color_double(t_pattern *pattern, t_color *color, int i)
{
	if (i == 2)
		uv_texture_full_color_at(pattern->texture[i], &pattern->uv.u,
			&pattern->uv.v, color);
	else
		uv_texture_color_at(pattern->texture[i], &pattern->uv.u,
			&pattern->uv.v, color);
	return (color->r);
}

static void	get_map_color_vector(t_pattern *pattern, t_color *color,
		t_vector *t_normal, t_vector *normal_v)
{
	uv_texture_color_at(pattern->texture[4], &pattern->uv.u,
		&pattern->uv.v, color);
	multiply_color(color, pattern->bump_map_scale, color);
	new_vector(color->r, color->g, color->b, t_normal);
	normalize(add(t_normal, normal_v, normal_v), normal_v);
}

void	prepare_material(t_lighting_params *lp, t_shape *s,
			t_point *point, t_eye_normal *view)
{
	if (s->material.pattern.has_pattern == true)
		pattern_at_shape(&s->material.pattern, s, point, &lp->color);
	else
		lp->color = s->material.color;
	if (s->material.pattern.is_tri)
	{
		if (s->material.pattern.texture[1])
			s->material.specular = get_map_color_double(
					&s->material.pattern, &lp->t_color, 1);
		if (s->material.pattern.texture[2])
			s->material.shininess = get_map_color_double(
					&s->material.pattern, &lp->t_color, 2);
		if (s->material.pattern.texture[3])
			s->material.transparency = get_map_color_double(
					&s->material.pattern, &lp->t_color, 3);
		if (s->material.pattern.texture[4])
			get_map_color_vector(&s->material.pattern, &lp->t_color,
				&lp->t_normal, &view->normal_v);
		if (s->material.pattern.texture[5])
			s->material.reflective = get_map_color_double(
					&s->material.pattern, &lp->t_color, 5);
		if (s->material.pattern.texture[6])
			get_map_color_double(&s->material.pattern, &s->material.ambient, 6);
	}
}
