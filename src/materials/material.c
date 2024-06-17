#include "materials.h"

t_material	*new_material(t_material *material)
{
	material->color = new_color(1.0, 1.0, 1.0);
	material->ambient = new_color(0.1, 0.1, 0.1);
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200.0;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive_index = VACUUM;
	new_pattern(&material->pattern);
	return (material);
}
