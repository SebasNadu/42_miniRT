#include "materials.h"
#include "shapes.h"

static t_color	darken(t_material *m, t_lighting_params *lp);
static t_color	lighten(t_material *m, t_lighting_params *lp, t_light *light,
					t_eye_normal *view);

t_material	new_material(void)
{
	return ((t_material){
		.color = new_color(1.0, 1.0, 1.0),
		.ambient = new_color(0.1, 0.1, 0.1),
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200.0,
		.pattern.has_pattern = false,
	});
}

t_color	lighting(t_shape *shape, t_light *light, t_point *point,
	t_eye_normal *view)
{
	t_lighting_params	lp;
	t_color				color;

	if (shape->material.pattern.has_pattern == true)
		color = pattern_at_shape(&shape->material.pattern, shape, point);
	else
		color = shape->material.color;
	lp.effective_color = hadamard_product(color, light->intensity);
	lp.light_v = normalize(subtract(light->position, *point));
	lp.light_dot_normal = dot(lp.light_v, view->normal_v);
	if (lp.light_dot_normal < 0 || light->in_shadow)
		return (darken(&shape->material, &lp));
	return (lighten(&shape->material, &lp, light, view));
}

static t_color	darken(t_material *m, t_lighting_params *lp)
{
	lp->ambient = hadamard_product(lp->effective_color, m->ambient);
	lp->diffuse = new_color(0, 0, 0);
	lp->specular = new_color(0, 0, 0);
	return (add_color(lp->ambient, add_color(lp->diffuse, lp->specular)));
}

static t_color	lighten(t_material *m, t_lighting_params *lp, t_light *light,
					t_eye_normal *view)
{
	lp->ambient = hadamard_product(lp->effective_color, m->ambient);
	lp->diffuse = multiply_color(lp->effective_color,
			m->diffuse * lp->light_dot_normal);
	lp->reflect_v = reflect(negate(lp->light_v), view->normal_v);
	lp->reflect_dot_eye = dot(lp->reflect_v, view->eye_v);
	if (lp->reflect_dot_eye <= 0)
		lp->specular = new_color(0, 0, 0);
	else
		lp->specular = multiply_color(light->intensity, m->specular
				* pow(lp->reflect_dot_eye, m->shininess));
	return (add_color(lp->ambient, add_color(lp->diffuse, lp->specular)));
}