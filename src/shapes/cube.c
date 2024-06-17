#include "shapes.h"
#include "groups.h"

static bool		intersect_cube(t_hit **xs, t_shape *shape, t_ray *r);
static t_vector	*normal_at_cube(t_shape *shape, t_point *local_point,
					t_vector *normal);

t_shape	*new_cube(t_shape *shape)
{
	new_shape(shape);
	new_point(0, 0, 0, &shape->cube.origin);
	shape->intersect_fn = intersect_cube;
	shape->normal_at = normal_at_cube;
	shape->bounds_of = cube_bounds;
	shape->material.pattern.texture_map.uv_mapping_fn = cube_map;
	return (shape);
}

static void	check_axis(double origin, double direction, t_range *t)
{
	t_range	t_numerator;

	t_numerator.min = (-1 - origin);
	t_numerator.max = (1 - origin);
	if (fabs(direction) >= EPSILON)
	{
		t->min = t_numerator.min / direction;
		t->max = t_numerator.max / direction;
	}
	else
	{
		t->min = t_numerator.min * INFINITY;
		t->max = t_numerator.max * INFINITY;
	}
	if (t->min > t->max)
		ft_swap(&t->min, &t->max);
}

static bool	intersect_cube(t_hit **xs, t_shape *shape, t_ray *r)
{
	t_range	xt;
	t_range	yt;
	t_range	zt;
	t_range	t;

	check_axis(r->origin.x, r->direction.x, &xt);
	check_axis(r->origin.y, r->direction.y, &yt);
	check_axis(r->origin.z, r->direction.z, &zt);
	t.min = ft_max(xt.min, yt.min, zt.min);
	t.max = ft_min(xt.max, yt.max, zt.max);
	if (t.min > t.max)
		return (false);
	insert_intersection(xs, intersection(t.min, shape));
	insert_intersection(xs, intersection(t.max, shape));
	return (true);
}

static t_vector	*normal_at_cube(t_shape *shape, t_point *local_point,
					t_vector *normal)
{
	double	maxc;
	double	absx;
	double	absy;
	double	absz;

	(void)shape;
	absx = fabs(local_point->x);
	absy = fabs(local_point->y);
	absz = fabs(local_point->z);
	maxc = ft_max(absx, absy, absz);
	if (eq_dbl(maxc, absx))
		return (new_vector(local_point->x, 0, 0, normal));
	if (eq_dbl(maxc, absy))
		return (new_vector(0, local_point->y, 0, normal));
	return (new_vector(0, 0, local_point->z, normal));
}
