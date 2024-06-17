#include "world.h"
#include "lights.h"

static t_color	darken(t_material *m, t_lighting_params *lp);
static t_color	lighten(t_material *m, t_lighting_params *lp, t_light *light,
					t_eye_normal *view);

static void	prepare_color(t_color *color, t_shape *shape, t_point *point)
{
	if (shape->material.pattern.has_pattern == true)
		*color = pattern_at_shape(&shape->material.pattern, shape, point);
	else
		*color = shape->material.color;
}

t_color	area_lighting(t_shape *s, t_light *l, t_point *p, t_eye_normal *v)
{
	t_lighting_params	lp;
	t_color				color;
	int					i[2];
	t_point				tmp;

	prepare_color(&color, s, p);
	hadamard_product(&color, &l->intensity, &lp.effective_color);
	color = new_color(0, 0, 0);
	i[1] = -1;
	while (++i[1] < l->vsteps)
	{
		i[0] = -1;
		while (++i[0] < l->usteps)
		{
			normalize(subtract(point_on_light(l, i[0], i[1], &tmp),
					p, &tmp), &lp.light_v);
			lp.light_dot_normal = dot(&lp.light_v, &v->normal_v);
			if (lp.light_dot_normal < 0 || l->intensity_ratio <= 0)
				color = add_color(color, darken(&s->material, &lp));
			else
				color = add_color(color, lighten(&s->material, &lp, l, v));
		}
	}
	return (multiply_color(color, l->inverse_samples));
}

t_color	lighting(t_shape *shape, t_light *light, t_point *point,
	t_eye_normal *view)
{
	t_lighting_params	lp;
	t_color				color;

	prepare_color(&color, shape, point);
	hadamard_product(&color, &light->intensity, &lp.effective_color);
	normalize(subtract(&light->position, point, &lp.light_v), &lp.light_v);
	lp.light_dot_normal = dot(&lp.light_v, &view->normal_v);
	if (lp.light_dot_normal < 0 || light->intensity_ratio <= 0)
		return (darken(&shape->material, &lp));
	return (lighten(&shape->material, &lp, light, view));
}

static t_color	darken(t_material *m, t_lighting_params *lp)
{
	(void)m;
	hadamard_product(&lp->effective_color, &m->ambient, &lp->ambient);
	lp->diffuse = new_color(0, 0, 0);
	lp->specular = new_color(0, 0, 0);
	return (add_color(lp->ambient, add_color(lp->diffuse, lp->specular)));
}

static t_color	lighten(t_material *m, t_lighting_params *lp, t_light *light,
					t_eye_normal *view)
{
	t_vector	tmp;

	hadamard_product(&lp->effective_color, &m->ambient, &lp->ambient);
	lp->diffuse = multiply_color(lp->effective_color,
			m->diffuse * lp->light_dot_normal);
	reflect(negate(&lp->light_v, &tmp), &view->normal_v, &lp->reflect_v);
	lp->reflect_dot_eye = dot(&lp->reflect_v, &view->eye_v);
	if (lp->reflect_dot_eye <= 0)
		lp->specular = new_color(0, 0, 0);
	else
		lp->specular = multiply_color(light->intensity, m->specular
				* pow(lp->reflect_dot_eye, m->shininess));
	return (add_color(lp->ambient, multiply_color(add_color(
					lp->diffuse, lp->specular), light->intensity_ratio)));
}
