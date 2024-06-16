#include "patterns.h"

static t_color	*blended_at(t_pattern *pattern, t_point *shape_point,
					t_color *out);

t_pattern	*new_blended_pattern(t_pattern a, t_pattern b, t_pattern *pattern)
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
	pattern->pattern_at = blended_at;
	pattern->has_pattern = true;
	return (pattern);
}

static t_color	*blended_at(t_pattern *pattern, t_point *shape_point,
					t_color *out)
{
	double	t;
	t_point	pattern_point;
	t_color	tmp;

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	t = 0.5;
	return (add_color(
			multiply_color(pattern->a->pattern_at(
					pattern->a, &pattern_point, out), (1.0 - t), &tmp),
			multiply_color(pattern->b->pattern_at(
					pattern->b, &pattern_point, out), t, out), out));
}
