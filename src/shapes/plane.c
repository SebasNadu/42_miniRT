#include "shapes.h"
#include "groups.h"

static t_vector	*normal_at_plain(t_shape *plane, t_point *local_point,
					t_vector *normal);
static bool		intersect_plane(t_hit **xs, t_shape *shape, t_ray *r);

t_shape	*new_plane(t_shape *shape)
{
	new_shape(shape);
	new_point(0, 0, 0, &shape->plane.origin);
	shape->normal_at = normal_at_plain;
	shape->intersect_fn = intersect_plane;
	shape->bounds_of = plane_bounds;
	shape->material.pattern.texture_map.uv_mapping_fn = planar_map;
	shape->material.pattern.texture_map.uv_pattern.width = 2;
	shape->material.pattern.texture_map.uv_pattern.height = 2;
	return (shape);
}

static t_vector	*normal_at_plain(t_shape *plane, t_point *local_point,
					t_vector *normal)
{
	(void)local_point;
	(void)plane;
	new_vector(0, 1, 0, normal);
	return (normal);
}

static bool	intersect_plane(t_hit **xs, t_shape *shape, t_ray *r)
{
	double	t;

	if (fabs(r->direction.y) < EPSILON)
		return (false);
	t = -r->origin.y / r->direction.y;
	insert_intersection(xs, intersection(t, shape));
	return (true);
}
