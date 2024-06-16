#include "patterns.h"

static t_color	*checkers_at(t_pattern *pattern, t_point *shape_point,
					t_color *out);
static t_color	*uv_checkers_at(t_pattern *pattern, t_point *shape_point,
					t_color *out);

t_pattern	*new_checkers_pattern(t_pattern *a, t_pattern *b,
		t_pattern *pattern)
{
	if (!pattern)
		return (NULL);
	pattern->a = malloc(sizeof(t_pattern));
	if (!pattern->a)
		return (pattern);
	pattern->b = malloc(sizeof(t_pattern));
	if (!pattern->b)
		return (pattern);
	*pattern->a = *a;
	*pattern->b = *b;
	pattern->pattern_at = checkers_at;
	pattern->has_pattern = true;
	return (pattern);
}

t_pattern	*new_uv_checkers_pattern(t_pattern *a, t_pattern *b,
				t_pattern *pattern)
{
	if (!pattern)
		return (NULL);
	pattern->a = malloc(sizeof(t_pattern));
	if (!pattern->a)
		return (pattern);
	pattern->b = malloc(sizeof(t_pattern));
	if (!pattern->b)
		return (pattern);
	*pattern->a = *a;
	*pattern->b = *b;
	pattern->pattern_at = uv_checkers_at;
	pattern->has_pattern = true;
	pattern->texture_map.uv_pattern.a = pattern->a;
	pattern->texture_map.uv_pattern.b = pattern->b;
	return (pattern);
}

static t_color	*checkers_at(t_pattern *pattern, t_point *shape_point,
					t_color *out)
{
	t_point	pattern_point;

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	if (((int)floor(pattern_point.x) + (int)floor(pattern_point.y)
			+ (int)floor(pattern_point.z)) & 1)
		return (pattern->b->pattern_at(pattern->b, &pattern_point, out));
	return (pattern->a->pattern_at(pattern->a, &pattern_point, out));
}

static t_color	*uv_checkers_at(t_pattern *pattern, t_point *shape_point,
					t_color *out)
{
	t_point		pattern_point;
	t_pattern	*result;
	double		uv[2];

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	pattern->texture_map.uv_mapping_fn(&pattern_point, uv);
	result = uv_pattern_at(&pattern->texture_map.uv_pattern, &uv[0], &uv[1]);
	return (result->pattern_at(result, &pattern_point, out));
}
