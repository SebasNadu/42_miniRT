#include "materials.h"

t_material	*new_material(t_material *material)
{
	new_color(1.0, 1.0, 1.0, &material->color);
	new_color(0.1, 0.1, 0.1, &material->ambient);
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200.0;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive_index = VACUUM;
	new_pattern(&material->pattern);
	return (material);
}
