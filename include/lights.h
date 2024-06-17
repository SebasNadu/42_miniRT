#ifndef LIGHTS_H
# define LIGHTS_H

# include <stdbool.h>

# include "tuples.h"
# include "utils.h"
# include "shapes.h"

typedef struct s_light
{
	t_point		position;
	t_color		intensity;
	double		intensity_ratio;
	t_point		corner;
	t_vector	uvec;
	int			usteps;
	t_vector	vvec;
	int			vsteps;
	double		inverse_samples;
	t_sequencer	jitter_by;
	bool		is_area_light;
	t_vector	direction;
	double		center_radian;
	double		fade_radian;
	double		delta_cos;
	bool		is_spotlight;
}	t_light;

typedef struct s_eye_normal
{
	t_vector	eye_v;
	t_vector	normal_v;
}	t_eye_normal;

typedef struct s_alight_params
{
	t_point		corner;
	t_vector	full_uvec;
	int			usteps;
	t_vector	full_vvec;
	int			vsteps;
	t_color		intensity;
}	t_alight_params;

typedef struct s_spotlight_params
{
	t_point		position;
	t_vector	direction;
	double		center_radian;
	double		fade_radian;
	double		shaded_radian;
	t_color		intensity;
}	t_spotlight_params;

typedef struct s_aspotlight_params
{
	t_point		corner;
	t_vector	direction;
	double		center_radian;
	double		fade_radian;
	double		shaded_radian;
	t_color		intensity;
	t_vector	full_uvec;
	int			usteps;
	t_vector	full_vvec;
	int			vsteps;
}	t_aspotlight_params;

t_light	*new_light(t_point *position, t_color *intensity, t_light *light);
t_light	*new_area_light(t_alight_params *lp, t_light *light);
// Material.c 
t_color	lighting(t_shape *shape, t_light *light, t_point *point,
			t_eye_normal *view);
t_color	area_lighting(t_shape *s, t_light *l, t_point *p, t_eye_normal *v);
t_light	*new_spotlight(t_spotlight_params *sp, t_light *light);
t_light	*new_area_spotlight(t_aspotlight_params *asp, t_light *light);

#endif
