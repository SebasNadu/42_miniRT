#include "patterns.h"

static t_color	radial_gradient_at(t_pattern *pattern, t_point *shape_point);

t_pattern	new_radial_gradient_pattern(t_pattern a, t_pattern b)
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
	pattern.pattern_at = radial_gradient_at;
	pattern.has_pattern = true;
	return (pattern);
}

static t_color	radial_gradient_at(t_pattern *pattern, t_point *shape_point)
{
	t_point	pattern_point;
	double	distance;
	double	fraction;

	pattern_point = multiply_matrix_by_tuple(pattern->inverse, *shape_point);
	distance = sqrt(magnitude_squared(pattern_point));
	fraction = distance - floor(distance);
	return (add_color(pattern->a->pattern_at(pattern->a, &pattern_point),
			multiply_color(subtract_color(pattern->b->pattern_at(pattern->b,
						&pattern_point), pattern->a->pattern_at(pattern->a,
						&pattern_point)), fraction)));
}
