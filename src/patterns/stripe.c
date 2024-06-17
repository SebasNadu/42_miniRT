#include "patterns.h"

static t_color	stripe_at(t_pattern *pattern, t_point *shape_point);

t_pattern	*new_stripe_pattern(t_pattern a, t_pattern b, t_pattern *pattern)
{
	if (!pattern)
		return (NULL);
	pattern->a = malloc(sizeof(t_pattern));
	if (!pattern->a)
		return (pattern);
	pattern->b = malloc(sizeof(t_pattern));
	if (!pattern->b)
	{
		free(pattern->a);
		return (pattern);
	}
	*pattern->a = a;
	*pattern->b = b;
	pattern->pattern_at = stripe_at;
	pattern->has_pattern = true;
	return (pattern);
}

static t_color	stripe_at(t_pattern *pattern, t_point *shape_point)
{
	t_point	pattern_point; 

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	if (((int)floor(pattern_point.x)) & 1)
		return (pattern->b->pattern_at(pattern->b, &pattern_point));
	return (pattern->a->pattern_at(pattern->a, &pattern_point));
}
