#include "lights.h"

t_light	*new_light(t_point *position, t_color *intensity, t_light *light)
{
	light->position = *position;
	light->intensity = *intensity;
	light->intensity_ratio = 1;
	light->is_area_light = false;
	light->is_spotlight = false;
	light->corner = (t_point){0, 0, 0, 1};
	light->uvec = (t_vector){0, 0, 0, 0};
	light->vvec = (t_vector){0, 0, 0, 0};
	light->usteps = 1;
	light->vsteps = 1;
	light->inverse_samples = 1;
	light->direction = (t_vector){0, 0, 0, 0};
	light->center_radian = 0;
	light->fade_radian = 0;
	light->delta_cos = 0;
	return (light);
}

t_light	*new_area_light(t_alight_params *lp, t_light *light)
{
	t_point	tmp;

	light->is_area_light = true;
	light->is_spotlight = false;
	light->corner = lp->corner;
	multiply(&lp->full_uvec, 1.0 / lp->usteps, &light->uvec);
	light->usteps = lp->usteps;
	multiply(&lp->full_vvec, 1.0 / lp->vsteps, &light->vvec);
	light->vsteps = lp->vsteps;
	light->inverse_samples = 1.0 / (lp->usteps * lp->vsteps);
	light->intensity = lp->intensity;
	add(&lp->corner, add(multiply(&lp->full_uvec, 0.5, &tmp), multiply(
				&lp->full_vvec, 0.5, &light->position), &light->position),
		&light->position);
	light->intensity_ratio = 1;
	new_sequencer(&light->jitter_by);
	light->center_radian = 0;
	light->fade_radian = 0;
	light->delta_cos = 0;
	light->direction = (t_vector){0, 0, 0, 0};
	return (light);
}

t_light	*new_spotlight(t_spotlight_params *sp, t_light *light)
{
	light->is_area_light = false;
	light->is_spotlight = true;
	light->intensity_ratio = 1;
	light->position = sp->position;
	light->intensity = sp->intensity;
	normalize(&sp->direction, &light->direction);
	light->corner = (t_point){0, 0, 0, 1};
	light->uvec = (t_vector){0, 0, 0, 0};
	light->vvec = (t_vector){0, 0, 0, 0};
	light->usteps = 1;
	light->vsteps = 1;
	light->inverse_samples = 1;
	light->center_radian = cos(sp->center_radian);
	light->fade_radian = cos(sp->fade_radian);
	light->delta_cos = light->center_radian - light->fade_radian;
	return (light);
}

t_light	*new_area_spotlight(t_aspotlight_params *asp, t_light *light)
{
	t_point	tmp;

	light->is_area_light = true;
	light->is_spotlight = true;
	light->corner = asp->corner;
	multiply(&asp->full_uvec, 1.0 / asp->usteps, &light->uvec);
	light->usteps = asp->usteps;
	multiply(&asp->full_vvec, 1.0 / asp->vsteps, &light->vvec);
	light->vsteps = asp->vsteps;
	light->inverse_samples = 1.0 / (asp->usteps * asp->vsteps);
	light->intensity = asp->intensity;
	add(&asp->corner, add(multiply(&asp->full_uvec, 0.5, &tmp), multiply(
				&asp->full_vvec, 0.5, &light->position), &light->position),
		&light->position);
	light->intensity_ratio = 1;
	new_sequencer(&light->jitter_by);
	normalize(&asp->direction, &light->direction);
	light->center_radian = cos(asp->center_radian);
	light->fade_radian = cos(asp->fade_radian);
	light->delta_cos = light->center_radian - light->fade_radian;
	return (light);
}
