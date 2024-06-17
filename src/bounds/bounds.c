#include "groups.h"

t_bounds	*new_bounds(t_point *min, t_point *max, t_bounds *new_bounds)
{
	new_bounds->min = *min;
	new_bounds->max = *max;
	return (new_bounds);
}

void	get_bounds(t_shape *s, t_bounds *new_bounds)
{
	t_point		box[8];
	t_point		tmp;
	int			i;

	box[0] = s->bounds.min;
	new_point(s->bounds.min.x, s->bounds.min.y, s->bounds.max.z, &box[1]);
	new_point(s->bounds.min.x, s->bounds.max.y, s->bounds.min.z, &box[2]);
	new_point(s->bounds.min.x, s->bounds.max.y, s->bounds.max.z, &box[3]);
	new_point(s->bounds.max.x, s->bounds.min.y, s->bounds.min.z, &box[4]);
	new_point(s->bounds.max.x, s->bounds.min.y, s->bounds.max.z, &box[5]);
	new_point(s->bounds.max.x, s->bounds.max.y, s->bounds.min.z, &box[6]);
	box[7] = s->bounds.max;
	i = -1;
	while (++i < 8)
		add_point_to_bounds(&new_bounds,
			multiply_matrix_by_tuple(&s->transform, &box[i], &tmp));
	s->bounds = *new_bounds;
}

static t_range	check_axis(double origin, double direction,
					double min, double max)
{
	t_range	t;
	t_range	t_numerator;

	t_numerator.min = (min - origin);
	t_numerator.max = (max - origin);
	if (fabs(direction) >= EPSILON)
	{
		t.min = t_numerator.min / direction;
		t.max = t_numerator.max / direction;
	}
	else
	{
		t.min = t_numerator.min * INFINITY;
		t.max = t_numerator.max * INFINITY;
	}
	if (t.min > t.max)
		ft_swap(&t.min, &t.max);
	return (t);
}

bool	intersect_bounds(t_bounds *b, t_ray *r)
{
	t_range	xt;
	t_range	yt;
	t_range	zt;
	t_range	t;

	xt = check_axis(r->origin.x, r->direction.x, b->min.x, b->max.x);
	yt = check_axis(r->origin.y, r->direction.y, b->min.y, b->max.y);
	zt = check_axis(r->origin.z, r->direction.z, b->min.z, b->max.z);
	t.min = ft_max(xt.min, yt.min, zt.min);
	t.max = ft_min(xt.max, yt.max, zt.max);
	if (t.min > t.max)
		return (false);
	return (true);
}

double	bounds_volume(t_bounds *bounds)
{
	return ((bounds->max.x - bounds->min.x)
		* (bounds->max.y - bounds->min.y)
		* (bounds->max.z - bounds->min.z));
}
