/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:04:43 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/26 17:49:50 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "shapes.h"
# include "lights.h"
# include "tuples.h"
# include "groups.h"

# define MAX_RECURSION	4
# define BVH_THRESHOLD 8

typedef struct s_world
{
	t_hit		*xs;
	int			objs_count;
	t_shape		*objs;
	int			objs_inside_count;
	t_shape		*objs_inside;
	size_t		objs_ext_count;
	int			lights_count;
	t_light		*lights;
	t_color		ambient;
	int			remaining_recursion;
	t_pattern	**pattern;
	t_shape		**bvh_groups;
}	t_world;

typedef struct s_comps
{
	double				t;
	t_shape				*obj;
	t_point				point;
	t_eye_normal		view;
	t_point				over_point;
	t_point				under_point;
	bool				inside;
	t_vector			reflect_v;
	double				n1;
	double				n2;
}	t_comps;

typedef struct s_refrac_params
{
	double		n_ratio;
	double		cos_i;
	double		sin2_t;
	double		cos_t;
	t_vector	direction;
	t_ray		refract_ray;
}	t_refrac_params;

t_world	*new_world(t_world *world);
t_hit	*intersect_world(t_world *world, t_ray *ray);
t_comps	prepare_computations(t_hit *intersect, t_ray *ray, t_hit *xs);
t_color	*shade_hit(t_world *world, t_comps *comps, t_color *surface);
t_color	*color_at(t_world *world, t_ray *ray, t_color *color);
double	schlick(t_comps *comps);
// reflec_and_reflac
t_color	*reflec_and_refrac(t_world *world, t_comps *comps, t_color *surface);
// reflection
t_color	*reflected_color(t_world *world, t_comps *comps, t_color *color);
// refraction
void	find_refractive_indices(t_comps *comps, t_hit *i, t_hit *xs);
t_color	*refracted_color(t_world *world, t_comps *comps, t_color *color);

void	free_world(t_world *world);

// lights
// shadow_calculations.c
bool	is_shadowed(t_world *world, t_point *light_pos, t_point *point,
			double *ratio);
double	intensity_at(t_world *world, t_point *point, int index);
t_point	*point_on_light(t_light *light, double u, double v, t_point *p);
// bvh.c
void	create_bvh(t_world *world);
void	divide_group(t_shape *group, int threshold, int *bvh_groups_count);
bool	check_group(t_shape *group, int *threshold, int *bvh_groups_count);
void	make_subgroup(t_shape *group, t_shape **container,
			int *bvh_groups_count);
void	partition_children(t_shape *group, t_shape **left, t_shape **right);
void	split_bounds(t_bounds s_box[2]);

#endif
