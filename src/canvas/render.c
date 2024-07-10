#include "canvas.h"

#ifdef THREADS

static void	pixel_color(t_mini_rt *rt, double xy_offset[4], t_ray *ray,
		t_color *color)
{
	t_hit	*xs;

	xs = NULL;
	xy_offset[2] = (xy_offset[0] + 0.5);
	xy_offset[3] = (xy_offset[1] + 0.5);
	if (!rt->camera.supersampling && !rt->camera.aperture_size)
	{
		ray_for_pixel(&rt->camera, &xy_offset[2], ray);
		color_at(&rt->world, ray, color, &xs);
	}
	else if (rt->camera.supersampling)
		multisample(rt, xy_offset, ray, color);
	else
		multisample_only_dof(rt, &xy_offset[2], ray, color);
}

static void	*render_per_thread(void *data)
{
	t_thread_data	*td;
	t_mini_rt		*rt;
	double			xy_offset[4];
	t_ray			ray;
	t_color			color;

	td = (t_thread_data *)data;
	if (!td || !td->data)
		return (ft_putendl_fd("minirt: set_max_values: Wrong arguments",
				STDERR_FILENO), NULL);
	rt = (t_mini_rt *)td->data;
	if (!rt->canvas.img || td->start < 0 || td->end < 0 || td->start >= td->end)
		return (ft_putendl_fd("minirt: render_per_thread: Wrong arguments",
				STDERR_FILENO), NULL);
	xy_offset[1] = td->start - 1;
	while (++xy_offset[1] < td->end)
	{
		xy_offset[0] = -1;
		while (++xy_offset[0] < rt->canvas.img->width)
		{
			pixel_color(rt, xy_offset, &ray, &color);
			write_pixel(rt->canvas.img, xy_offset[0], xy_offset[1], &color);
		}
	}
	return (data);
}

bool	render(t_mini_rt *rt)
{
	int		i;
	void	*status;
	double	start;

	start = mlx_get_time();
	if (!rt || !rt->canvas.threads || !rt->canvas.tdata
		|| !rt->canvas.nb_threads)
		return (ft_putendl_fd("minirt: render: Wrong arguments",
				STDERR_FILENO), false);
	i = -1;
	while (++i < rt->canvas.nb_threads)
	{
		if (pthread_create(&rt->canvas.threads[i], NULL,
				render_per_thread, &rt->canvas.tdata[i]) != 0)
			return (perror("minirt: pthread_create: "), false);
	}
	i = -1;
	while (++i < rt->canvas.nb_threads)
	{
		pthread_join(rt->canvas.threads[i], &status);
		if (!status)
			return (perror("minirt: render: "), false);
	}
	printf("Render time: %f's\n", mlx_get_time() - start);
	return (true);
}

#else

static void	pixel_color(t_mini_rt *rt, double xy_offset[4], t_ray *ray,
		t_color *color)
{
	xy_offset[2] = (xy_offset[0] + 0.5);
	xy_offset[3] = (xy_offset[1] + 0.5);
	if (!rt->camera.supersampling && !rt->camera.aperture_size)
	{
		ray_for_pixel(&rt->camera, &xy_offset[2], ray);
		color_at(&rt->world, ray, color, &rt->world.xs);
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
	while (++xy_offset[1] < rt->canvas.img->height)
	{
		ft_printf("\rRendering: %d%%",
			(int)(xy_offset[1] / (rt->camera.vsize - 1) * 100));
		xy_offset[0] = -1;
		while (++xy_offset[0] < rt->canvas.img->width)
		{
			pixel_color(rt, xy_offset, &ray, &color);
			write_pixel(rt->canvas.img, xy_offset[0], xy_offset[1], &color);
		}
	}
	ft_printf("\rRendering: 100%%\n");
	return (true);
}
#endif
