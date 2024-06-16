#include "shapes.h"
#include "canvas.h"
#include <stdio.h>

#define WIDTH	512
#define HEIGHT	512

typedef struct s_params {
	double		world_x;
	double		world_y;
	double		world_z;
	double		wall_size;
	double		pixel_size;
	double		half;
	t_point		ray_origin;
	t_shape		sphere;
	t_color		sphere_color;
	t_color		bg_color;
}	t_params;

void	render_sphere(t_canvas *rt, t_params *params)
{
	int		xy[2];
	t_hit	*xs;
	t_point	position;
	t_ray	ray;

	xy[1] = -1;
	while (++xy[1] < HEIGHT)
	{
		params->world_y = params->half - params->pixel_size * xy[1];
		xy[0] = -1;
		while (++xy[0] < WIDTH)
		{
			xs = NULL;
			params->world_x = -params->half + params->pixel_size * xy[0];
			new_point(params->world_x, params->world_y, params->world_z,
				&position);
			new_ray(&params->ray_origin, normalize(subtract(&position,
						&params->ray_origin, &position), &position), &ray);
			intersect(&xs, &params->sphere, &ray);
			if (hit(xs))
				write_pixel(rt->img, xy[0], xy[1], &params->sphere_color);
			else
				write_pixel(rt->img, xy[0], xy[1], &params->bg_color);
		}
	}
}

void	set_params(t_params *params)
{
	t_matrix	m[2];

	params->world_x = 0;
	params->world_y = 0;
	params->world_z = 10;
	params->wall_size = 7;
	params->pixel_size = params->wall_size / HEIGHT;
	params->half = params->wall_size * 0.5;
	new_point(0, 0, -5, &params->ray_origin);
	new_color(0.6, 0.1, 0.1, &params->sphere_color);
	new_color(0.1, 0.2, 0.3, &params->bg_color);
	new_sphere(&params->sphere);
	// set_transform(&params->sphere, scaling(1, 0.5, 1));
	// set_transform(&params->sphere, scaling(0.5, 1, 1));
	// set_transform(&params->sphere, multiply_matrices(
	// 		rotation_z(cos(M_PI / 4), sin(M_PI / 4)), scaling(0.5, 1, 1)));
	set_transform(&params->sphere, transformations(2,
			scaling(0.5, 1, 1, &m[0]), rotation_z(cos(M_PI_4), sin(M_PI_4), &m[1])));
	// set_transform(&params->sphere, multiply_matrices(
	// 		shearing((t_shearing){1, 0}, (t_shearing){0}, (t_shearing){0}),
	// 		scaling(0.5, 1, 1)));
	// set_transform(&params->sphere, transformations(2, scaling(0.5, 1, 1),
	// 			shearing((t_shearing){1, 0}, (t_shearing){0, 0}, (t_shearing){0, 0})));
}

int	main(void)
{
	t_canvas	rt;
	t_params	params;

	if (!new_canvas(&rt, WIDTH, HEIGHT, "Chapter 05"))
		return (1);
	set_params(&params);
	render_sphere(&rt, &params);
	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	mlx_close_hook(rt.mlx, &quit, &rt);
	mlx_key_hook(rt.mlx, &handle_keyhook, &rt);
	mlx_loop(rt.mlx);
	mlx_terminate(rt.mlx);
	return (0);
}
