#include "patterns.h"
#include "shapes.h"

t_pattern	*new_pattern(t_pattern *pattern)
{
	if (!pattern)
		return (NULL);
	pattern->a = NULL;
	pattern->b = NULL;
	pattern->has_pattern = false;
	get_identity_matrix(&pattern->transform);
	get_identity_matrix(&pattern->inverse);
	pattern->texture = NULL;
	pattern->texture_map.uv_pattern.a = NULL;
	pattern->texture_map.uv_pattern.b = NULL;
	return (pattern);
}

t_color	pattern_at_shape(t_pattern *pattern, t_shape *shape,
								t_point *world_point)
{
	t_point		shape_point;

	multiply_matrix_by_tuple(&shape->inverse, world_point, &shape_point);
	return (pattern->pattern_at(pattern, &shape_point));
}

void	set_pattern_transform(t_pattern *pattern, t_matrix *transform)
{
	pattern->transform = *transform;
	inverse_matrix(transform, &pattern->inverse);
}
