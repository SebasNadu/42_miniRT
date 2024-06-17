#include "groups.h"

static bool		intersect_group(t_hit **xs, t_shape *shape, t_ray *r);
static t_vector	*normal_at_group(t_shape *shape, t_point *local_point,
					t_vector *normal);
static void		group_bounds(t_shape *shape);

t_shape	*new_group(t_shape *shape)
{
	new_shape(shape);
	shape->group.count = 0;
	shape->group.root = NULL;
	shape->intersect_fn = intersect_group;
	shape->normal_at = normal_at_group;
	shape->bounds_of = group_bounds;
	shape->is_group = true;
	return (shape);
}

static bool	intersect_group(t_hit **xs, t_shape *shape, t_ray *r)
{
	if (!shape->is_bounds_precal)
		shape->bounds_of(shape);
	if (!intersect_bounds(&shape->bounds, r))
		return (false);
	intersect_group_shapes(&shape->group.root, xs, r);
	return (true);
}

static t_vector	*normal_at_group(t_shape *shape, t_point *local_point,
					t_vector *normal)
{
	(void)shape;
	(void)local_point;
	printf("Exception: Attempted to get a normal from a group object.\n");
	*normal = (t_vector){0, 0, 0, 0};
	return (normal);
}

static void	group_bounds(t_shape *shape)
{
	if (!shape)
		return ;
	shape->is_bounds_precal = true;
	shape->bounds = (t_bounds){(t_point){MAXFLOAT, MAXFLOAT, MAXFLOAT, 1},
		(t_point){-MAXFLOAT, -MAXFLOAT, -MAXFLOAT, 1}};
	get_group_bounds(shape->group.root, &shape->bounds);
	get_bounds(shape, &shape->bounds);
}
