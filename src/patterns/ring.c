#include "patterns.h"

static t_color	ring_at(t_pattern *pattern, t_point *shape_point);

t_pattern	new_ring_pattern(t_pattern a, t_pattern b)
{
	t_pattern	pattern;

	pattern = new_pattern();
	pattern.a = malloc(sizeof(t_pattern));
	if (!pattern.a)
		return (pattern);
	pattern.b = malloc(sizeof(t_pattern));
	if (!pattern.b)
		return (pattern);
	*pattern.a = a;
	*pattern.b = b;
	pattern.pattern_at = ring_at;
	pattern.has_pattern = true;
	return (pattern);
}

static t_color	ring_at(t_pattern *pattern, t_point *shape_point)
{
	double	distance;
	t_point	pattern_point;

	pattern_point = multiply_matrix_by_tuple(pattern->inverse, *shape_point);
	distance = sqrt(pattern_point.x * pattern_point.x
			+ pattern_point.z * pattern_point.z);
	if ((int)floor(distance) & 1)
		return (pattern->b->pattern_at(pattern->b, &pattern_point));
	return (pattern->a->pattern_at(pattern->a, &pattern_point));
}
