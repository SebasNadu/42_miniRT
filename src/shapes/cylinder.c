#include "shapes.h"
#include "groups.h"

static bool		intersect_cylinder(t_hit **xs, t_shape *cyl, t_ray *r);
static t_vector	*normal_at_cylinder(t_shape *shape, t_point *local_point,
					t_vector *normal);

t_shape	*new_cylinder(t_shape *shape)
{
	new_shape(shape);
	new_point(0, 0, 0, &shape->cyl.origin);
	shape->cyl.min = -MAXFLOAT;
	shape->cyl.max = MAXFLOAT;
	shape->cyl.closed = false;
	shape->intersect_fn = intersect_cylinder;
	shape->normal_at = normal_at_cylinder;
	shape->bounds_of = cylinder_bounds;
	shape->material.pattern.texture_map.uv_mapping_fn = cylindrical_map;
	shape->material.pattern.texture_map.uv_pattern.width = 16;
	shape->material.pattern.texture_map.uv_pattern.height = 8;
	return (shape);
}

static bool	check_cap(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return ((x * x) + (z * z) <= 1.0);
}

static void	intersect_caps(t_hit **xs, t_shape *shape, t_ray *ray)
{
	double			t;

	if (!shape->cyl.closed || eq_dbl(ray->direction.y, 0))
		return ;
	t = (shape->cyl.min - ray->origin.y) / ray->direction.y;
	if (check_cap(ray, t))
		insert_intersection(xs, intersection(t, shape));
	t = (shape->cyl.max - ray->origin.y) / ray->direction.y;
	if (check_cap(ray, t))
		insert_intersection(xs, intersection(t, shape));
}

static bool	intersect_cylinder(t_hit **xs, t_shape *shape, t_ray *r)
{
	t_intersect_params	p;
	double				y_pos;

	intersect_caps(xs, shape, r);
	cylinder_discriminant(r, &p);
	if (eq_dbl(0, p.a) || p.discriminant < 0)
		return (false);
	if (p.t1 > p.t2)
		ft_swap(&p.t1, &p.t2);
	y_pos = r->origin.y + p.t2 * r->direction.y;
	if (shape->cyl.min < y_pos && y_pos < shape->cyl.max)
		insert_intersection(xs, intersection(p.t2, shape));
	y_pos = r->origin.y + p.t1 * r->direction.y;
	if (shape->cyl.min < y_pos && y_pos < shape->cyl.max)
		insert_intersection(xs, intersection(p.t1, shape));
	return (true);
}

static t_vector	*normal_at_cylinder(t_shape *shape, t_point *local_point,
					t_vector *normal)
{
	double	dist;

	dist = (local_point->x * local_point->x)
		+ (local_point->z * local_point->z);
	if (dist < 1.0 && local_point->y >= shape->cyl.max - EPSILON)
		return (new_vector(0, 1, 0, normal));
	else if (dist < 1.0 && local_point->y <= shape->cyl.min + EPSILON)
		return (new_vector(0, -1, 0, normal));
	else
		return (new_vector(local_point->x, 0, local_point->z, normal));
}
