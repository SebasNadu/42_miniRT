#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	800
#define HEIGHT	600
#define N_OBJS	1

void	create_scene(t_world *world)
{
	t_matrix	m[2];
	t_shape		floor;
	t_shape		ceiling;
	t_shape		s1;
	t_shape		s2;
	t_shape		s3;
	t_shape		s4;
	t_color		c;
	t_pattern	tmp[2];

	world->objs = malloc(6 * sizeof(t_shape));
	world->objs_count = 6;
	new_cube(&floor);
	new_checkers_pattern(
		new_solid_pattern(new_color(0.1, 0.1, 0.1, &c), &tmp[0]),
		new_solid_pattern(new_color(0.9, 0.9, 0.9, &c), &tmp[1]), &floor.material.pattern);
	set_pattern_transform(&floor.material.pattern, scaling(0.2, 0.2, 0.2, &m[0]));
	floor.material.specular = 0;
	set_transform(&floor, scaling(10, 0.01, 10, &m[0]));
	new_cube(&ceiling);
	new_color(0.9, 0.9, 1.0, &ceiling.material.color);
	ceiling.material.specular = 0;
	ceiling.material.diffuse = 1.0;
	multiply_matrices(translation(0, 12, 0, &m[0]), scaling(10, 0.01, 10, &m[1]), &m[0]);
	set_transform(&ceiling, &m[0]);
	new_sphere(&s1);
	set_transform(&s1, translation(-1, 1, 0, &m[0]));
	new_color(1.0, 0.1, 0.5, &s1.material.color);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.3;
	new_sphere(&s2);
	set_transform(&s2, translation(-5, 1, 7, &m[0]));
	new_color(0.1, 1, 0.5, &s2.material.color);
	s2.material.diffuse = 0.7;
	s2.material.specular = 0.3;
	new_sphere(&s3);
	set_transform(&s3, translation(2, 1, -3, &m[0]));
	new_color(0.5, 0.1, 1, &s3.material.color);
	s3.material.diffuse = 0.7;
	s3.material.specular = 0.3;
	new_sphere(&s4);
	set_transform(&s4, translation(1, 1, 5, &m[0]));
	new_color(0, 0, 0, &s4.material.color);
	s4.material.diffuse = 0;
	s4.material.specular = 1;
	s4.material.reflective = 1;
	world->objs[0] = floor;
	world->objs[1] = ceiling;
	world->objs[2] = s1;
	world->objs[3] = s2;
	world->objs[4] = s3;
	world->objs[5] = s4;
}

void	create_lights(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	new_point(-10, 10, -10, &p);
	new_color(0.5, 0.5, 0.5, &c);
	new_light(&p, &c, &world->lights[0]);
	new_point(-10, 10, 10, &p);
	new_color(0.5, 0.5, 0.5, &c);
	new_light(&p, &c, &world->lights[1]);
}

void	create_camera(t_camera *camera)
{
	t_point			from;
	t_point			to;
	t_vector		up;

	new_camera(camera, WIDTH, HEIGHT, M_PI / 3);
	camera->aperture_size = 0.25;
	camera->focal_length = 10.0;
	camera->samples = 64;
	camera->supersampling = true;
	camera->color_variance_limit = 0.01;
	new_point(0, 1.5, -10, &from);
	new_point(0, 0.5, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&camera->transform));
}

int	main(void)
{
	t_mini_rt	rt;

	srand(time(NULL));
	new_world(&rt.world);
	create_lights(&rt.world);
	create_camera(&rt.camera);
	create_scene(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Bonus Super Sampling & Focal Blur");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free_world(&rt.world);
	mlx_terminate(rt.canvas.mlx);
}
