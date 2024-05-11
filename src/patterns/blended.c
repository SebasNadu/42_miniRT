#include "patterns.h"

static t_color	blended_at(t_pattern *pattern, t_point *shape_point);

t_pattern	new_blended_pattern(t_pattern a, t_pattern b)
{
	t_pattern	pattern;

	pattern = new_pattern();
	pattern.a = malloc(sizeof(t_pattern));
	if (!pattern.a)
		return (pattern);
	pattern.b = malloc(sizeof(t_pattern));
	if (!pattern.b)
	{
		free(pattern.a);
		return (pattern);
	}
	*pattern.a = a;
	*pattern.b = b;
	pattern.pattern_at = blended_at;
	pattern.has_pattern = true;
	return (pattern);
}

static t_color	blended_at(t_pattern *pattern, t_point *shape_point)
{
	double	t;
	t_point	pattern_point;

	pattern_point = multiply_matrix_by_tuple(pattern->inverse, *shape_point);
	t = 0.5;
	return (add_color(
			multiply_color(pattern->a->pattern_at(pattern->a, &pattern_point),
				(1.0 - t)),
			multiply_color(pattern->b->pattern_at(pattern->b, &pattern_point),
				t)));
}
