#include "canvas.h"

static double	color_variance_of_mean(int *n, t_color *color_sum,
	t_color *color_sum_squares)
{
	t_color			mean_rgb;
	t_color			variance_rgb;
	double			variance;
	double const	inv_3 = 0.3333333333333333;
	double const	inv_n = 1.0 / *n;

	multiply_color(color_sum, inv_n, &mean_rgb);
	hadamard_product(&mean_rgb, &mean_rgb, &mean_rgb);
	variance_rgb.r = color_sum_squares->r / (*n - mean_rgb.r);
	variance_rgb.g = color_sum_squares->g / (*n - mean_rgb.g);
	variance_rgb.b = color_sum_squares->b / (*n - mean_rgb.b);
	variance = (variance_rgb.r + variance_rgb.g + variance_rgb.b) * inv_3;
	return (variance *= inv_n);
}

static void	compute_color(t_mini_rt *rt, double xy_offset[4], t_ray *ray,
	t_color color_t[3])
{
	xy_offset[2] = (xy_offset[0] + (rand_dbl() - 0.5));
	xy_offset[3] = (xy_offset[1] + (rand_dbl() - 0.5));
	ray_for_pixel(&rt->camera, &xy_offset[2], ray);
	color_at(&rt->world, ray, &color_t[0]);
	add_color(&color_t[1], &color_t[0], &color_t[1]);
	add_color(&color_t[2], hadamard_product(&color_t[0],
			&color_t[0], &color_t[0]), &color_t[2]);
}

static void	compute_color_stratified(t_mini_rt *rt, double xy_offset[4],
	int i[3], t_color color_t[3])
{
	t_ray	ray;

	xy_offset[2] = (xy_offset[0] + (i[0] + rand_dbl()) / i[2]);
	xy_offset[3] = (xy_offset[1] + (i[1] + rand_dbl()) / i[2]);
	ray_for_pixel(&rt->camera, &xy_offset[2], &ray);
	color_at(&rt->world, &ray, &color_t[0]);
	add_color(&color_t[1], &color_t[0], &color_t[1]);
}

void	multisample(t_mini_rt *rt, double xy_offset[4], t_ray *ray,
	t_color *color)
{
	int			i[3];
	t_color		color_t[3];

	color_t[1] = (t_color){0, 0, 0};
	i[2] = (int)sqrt(rt->camera.samples);
	i[0] = -1;
	while (++i[0] < i[2])
	{
		i[1] = -1;
		while (++i[1] < i[2])
			compute_color_stratified(rt, xy_offset, i, color_t);
	}
	hadamard_product(&color_t[1], &color_t[1], &color_t[2]);
	i[2] = i[0] * i[1];
	while (color_variance_of_mean(&i[2], &color_t[1], &color_t[2])
		> rt->camera.color_variance_limit)
	{
		compute_color(rt, xy_offset, ray, color_t);
		++i[2];
	}
	multiply_color(&color_t[1], 1.0 / i[2], color);
}

void	multisample_only_dof(t_mini_rt *rt, double xy_offset[2], t_ray *ray,
	t_color *color)
{
	int			n; 
	t_color		color_sum;
	t_color		color_sum_squares;

	color_sum = (t_color){0, 0, 0};
	n = -1;
	while (++n < rt->camera.samples)
	{
		ray_for_pixel(&rt->camera, xy_offset, ray);
		color_at(&rt->world, ray, color);
		add_color(&color_sum, color, &color_sum);
	}
	hadamard_product(&color_sum, &color_sum, &color_sum_squares);
	while (color_variance_of_mean(&n, &color_sum, &color_sum_squares)
		> rt->camera.color_variance_limit)
	{
		ray_for_pixel(&rt->camera, xy_offset, ray);
		color_at(&rt->world, ray, color);
		add_color(&color_sum, color, &color_sum);
		add_color(&color_sum_squares, hadamard_product(color, color, color),
			&color_sum_squares);
		++n;
	}
	multiply_color(&color_sum, 1.0 / n, color);
}
