#include "patterns.h"

static t_color	*gradient_at(t_pattern *pattern, t_point *shape_point,
					t_color *out);

t_pattern	*new_gradient_pattern(t_pattern a, t_pattern b, t_pattern *pattern)
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
	pattern->pattern_at = gradient_at;
	pattern->has_pattern = true;
	return (pattern);
}

static t_color	*gradient_at(t_pattern *pattern, t_point *shape_point,
					t_color *out)
{
	t_point		pattern_point;
	t_color		distance;
	t_color		tmp;
	double		fraction;

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	subtract_color(pattern->b->pattern_at(pattern->b, &pattern_point, &tmp),
		pattern->a->pattern_at(pattern->a, &pattern_point, &distance),
		&distance);
	fraction = pattern_point.x - floor(pattern_point.x);
	return (add_color(pattern->a->pattern_at(pattern->a, &pattern_point, &tmp),
			multiply_color(&distance, fraction, &distance), out), out);
}
