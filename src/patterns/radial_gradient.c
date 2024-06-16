#include "patterns.h"

static t_color	*radial_gradient_at(t_pattern *pattern, t_point *shape_point,
					t_color *out);

t_pattern	*new_radial_gradient_pattern(t_pattern a, t_pattern b,
				t_pattern *pattern)
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
	pattern->pattern_at = radial_gradient_at;
	pattern->has_pattern = true;
	return (pattern);
}

static t_color	*radial_gradient_at(t_pattern *pattern, t_point *shape_point,
					t_color *out)
{
	t_point	pattern_point;
	double	distance;
	double	fraction;
	t_color	diff;

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	distance = sqrt(magnitude_squared(&pattern_point));
	fraction = distance - floor(distance);
	subtract_color(pattern->b->pattern_at(pattern->b, &pattern_point, out),
		pattern->a->pattern_at(pattern->a, &pattern_point, &diff), &diff);
	return (add_color(pattern->a->pattern_at(pattern->a, &pattern_point, out),
			multiply_color(&diff, fraction, &diff), out));
}
