#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include <stdio.h>

#define WIDTH	1024
#define HEIGHT	1024

typedef struct s_params {
	double			wall_x;
	double			wall_y;
	double			wall_z;
	double			wall_size;
	double			pixel_size;
	double			half;
	t_point			ray_origin;
	t_shape			sphere;
	t_color			sphere_color;
	uint32_t		bg_color;
	t_light			light;
	t_eye_normal	view;
	t_hit			*hits;
	t_ray			ray;
}	t_params;

void	light_and_shading(t_canvas *rt, t_params *params, int xy[2])
{
	t_point		pos;

	if (params->hits)
	{
		position(&params->ray, params->hits->t, &pos);
		normal_at(&params->sphere, &pos, &params->view.normal_v);
		params->view.eye_v = params->ray.direction;
		negate(&params->view.eye_v, &params->view.eye_v);
		params->sphere_color = lighting(&params->sphere,
				&params->light, &pos, &params->view);
		write_pixel(rt->img, xy[0], xy[1], &params->sphere_color);
	}
	else
		write_pixel_32(rt->img, xy[0], xy[1], params->bg_color);
}

void	render_sphere(t_canvas *rt, t_params *params)
{
	int				xy[2];
	t_hit			*xs;
	t_point			position;

	xy[1] = -1;
	while (++xy[1] < HEIGHT)
	{
		params->wall_y = params->half - params->pixel_size * xy[1];
		xy[0] = -1;
		while (++xy[0] < WIDTH)
		{
			xs = NULL;
			params->wall_x = -params->half + params->pixel_size * xy[0];
			new_point(params->wall_x, params->wall_y, params->wall_z,
				&position);
			new_ray(&params->ray_origin,
				normalize(subtract(&position, &params->ray_origin, &position),
					&position), &params->ray);
			intersect(&xs, &params->sphere, &params->ray);
			params->hits = hit(xs);
			light_and_shading(rt, params, xy);
		}
	}
}

void	set_params(t_params *params)
{
	t_point	p;
	t_color	c;

	params->wall_x = 0;
	params->wall_y = 0;
	params->wall_z = 10;
	params->wall_size = 7;
	params->pixel_size = params->wall_size / HEIGHT;
	params->half = params->wall_size * 0.5;
	new_point(0, 0, -5, &params->ray_origin);
	new_color(0.6, 0.1, 0.1, &params->sphere_color);
	params->bg_color = 0xFF000000;
	new_sphere(&params->sphere);
	params->sphere.material.color.g = 0.2;
	new_point(-10, 10, -10, &p);
	new_color(1, 1, 1, &c);
	new_light(&p, &c, &params->light);
	new_color(0.1, 0.1, 0.1, &params->sphere.material.ambient);
	params->sphere.material.diffuse = 0.8;
	params->sphere.material.specular = 0.8;
}

void	set_transformations(t_params *params)
{
	t_matrix	tmp;

	set_transform(&params->sphere, scaling(0.9, 0.9, 0.9, &tmp));
	// set_transform(&params->sphere, scaling(1, 0.5, 1));
	// set_transform(&params->sphere, scaling(0.5, 1, 1));
	// set_transform(&params->sphere, multiply_matrices(
	// 		rotation_z(cos(M_PI / 4), sin(M_PI / 4)), scaling(0.5, 1, 1)));
	// set_transform(&params->sphere, transformations(2,
	// 		scaling(0.5, 1, 1), rotation_z(cos(M_PI_4), sin(M_PI_4))));
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

	if (!new_canvas(&rt, WIDTH, HEIGHT, "Chapter 06"))
		return (1);
	set_params(&params);
	set_transformations(&params);
	render_sphere(&rt, &params);
	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	mlx_close_hook(rt.mlx, &quit, &rt);
	mlx_key_hook(rt.mlx, &handle_keyhook, &rt);
	mlx_loop(rt.mlx);
	mlx_terminate(rt.mlx);
	return (0);
}
