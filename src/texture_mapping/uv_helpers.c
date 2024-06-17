#include "patterns.h"
#include "canvas.h"

t_checker	uv_checkers(double width, double height, t_pattern *a,
				t_pattern *b)
{
	return ((t_checker){width, height, a, b});
}

t_pattern	*uv_pattern_at(t_checker *checkers, double *u, double *v)
{
	int	u2;
	int	v2;

	u2 = (int)(*u * checkers->width);
	v2 = (int)(*v * checkers->height);
	if (((u2 + v2) & 1) == 0)
		return (checkers->a);
	else
		return (checkers->b);
}

t_color	uv_pattern_color_at(t_align_colors *align_colors, double *u, double *v)
{
	if (*v > 0.8)
	{
		if (*u < 0.2)
			return (align_colors->ul);
		else if (*u > 0.8)
			return (align_colors->ur);
	}
	else if (*v < 0.2)
	{
		if (*u < 0.2)
			return (align_colors->bl);
		else if (*u > 0.8)
			return (align_colors->br);
	}
	return (align_colors->main);
}

t_color	*uv_texture_color_at(mlx_texture_t *texture, double *u, double *v,
			t_color *color)
{
	double		x;
	double		y;

	*v = 1 - *v;
	x = *u * (texture->width - 1);
	y = *v * (texture->height - 1);
	pixel_at(texture, round(x), round(y), color);
	return (color);
}

void	texture_map(t_pattern *pattern, t_checker *checkers,
		t_uv_mapping uv_mapping_fn)
{
	pattern->texture_map.uv_pattern = *checkers;
	pattern->texture_map.uv_mapping_fn = uv_mapping_fn;
}
