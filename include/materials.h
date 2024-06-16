#ifndef MATERIALS_H
# define MATERIALS_H

// # include "lights.h"
# include "patterns.h"

# define VACUUM 1.0
# define AIR 1.00029
# define WATER 1.333
# define GLASS 1.52
# define DIAMOND 2.417

typedef struct s_material
{
	t_color		color;
	t_color		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	t_pattern	pattern;
	double		reflective;
	double		transparency;
	double		refractive_index;
}	t_material;

typedef struct s_lighting_params
{
	t_color		effective_color;
	t_vector	light_v;
	t_vector	reflect_v;
	double		light_dot_normal;
	double		reflect_dot_eye;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_color		tmp_color;
}	t_lighting_params;

t_material	*new_material(t_material *material);

#endif
