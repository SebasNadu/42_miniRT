#include "canvas.h"

static void	pixel_color(t_mini_rt *rt, double xy_offset[2], t_ray *ray,
		t_color *color)
{
	xy_offset[2] = (xy_offset[0] + 0.5);
	xy_offset[3] = (xy_offset[1] + 0.5);
	if (!rt->camera.supersampling && !rt->camera.aperture_size)
	{
		ray_for_pixel(&rt->camera, &xy_offset[2], ray);
		color_at(&rt->world, ray, color);
	}
	else if (rt->camera.supersampling)
		multisample(rt, xy_offset, ray, color);
	else
		multisample_only_dof(rt, &xy_offset[2], ray, color);
}

bool	render(t_mini_rt	*rt)
{
	double	xy_offset[4];
	t_ray	ray;
	t_color	color;

	xy_offset[1] = -1;
	while (++xy_offset[1] < *rt->canvas.height)
	{
		ft_printf("\rRendering: %d%%",
			(int)(xy_offset[1] / (rt->camera.vsize - 1) * 100));
		xy_offset[0] = -1;
		while (++xy_offset[0] < *rt->canvas.width)
		{
			pixel_color(rt, xy_offset, &ray, &color);
			write_pixel(rt->canvas.img, xy_offset[0], xy_offset[1], &color);
		}
	}
	ft_printf("\rRendering: 100%%\n");
	return (true);
}
