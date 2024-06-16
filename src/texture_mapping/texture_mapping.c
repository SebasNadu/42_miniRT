#include "patterns.h"

static t_color	*uv_texture_map_at(t_pattern *pattern, t_point *shape_point,
					t_color *out);
static t_color	*uv_cubic_texture_map_at(t_pattern *pattern,
					t_point *shape_point, t_color *out);

t_pattern	*new_texture_map(t_pattern *pattern, char const *path)
{
	if (!pattern)
		return (NULL);
	pattern->texture[0] = mlx_load_png(path);
	if (!pattern->texture[0])
		return (NULL);
	pattern->has_pattern = true;
	pattern->pattern_at = uv_texture_map_at;
	return (pattern);
}

// NOTE: The cube faces ore ordered as follows:
// left, front, right, back, up, down
t_pattern	*new_cubic_texture_map(t_pattern *pattern, char const *paths[6])
{
	int	i;

	if (!pattern)
		return (NULL);
	i = -1;
	while (++i < 6)
	{
		pattern->texture[i] = mlx_load_png(paths[i]);
		if (!pattern->texture[i])
		{
			while (--i >= 0)
				mlx_delete_texture(pattern->texture[i]);
			return (NULL);
		}
	}
	pattern->has_pattern = true;
	pattern->pattern_at = uv_cubic_texture_map_at;
	return (pattern);
}

static t_color	*uv_texture_map_at(t_pattern *pattern, t_point *shape_point,
					t_color *out)
{
	t_point		pattern_point;
	double		uv[2];

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	pattern->texture_map.uv_mapping_fn(&pattern_point, uv);
	uv_texture_color_at(pattern->texture[0], &uv[0], &uv[1], out);
	return (out);
}

static t_color	*uv_cubic_texture_map_at(t_pattern *pattern,
					t_point *shape_point, t_color *out)
{
	t_point		pattern_point;
	double		face_uv[3];

	multiply_matrix_by_tuple(&pattern->inverse, shape_point, &pattern_point);
	face_uv[0] = face_from_point(&pattern_point);
	pattern->texture_map.uv_mapping_fn(&pattern_point, face_uv);
	uv_texture_color_at(pattern->texture[(int)face_uv[0]], &face_uv[1],
		&face_uv[2], out);
	return (out);
}
