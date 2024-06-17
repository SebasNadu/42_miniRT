#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"

#define WIDTH	800
#define HEIGHT	600
#define N_OBJS	17

void	create_scene(t_world *world)
{
	t_shape		floor;
	t_shape		ceiling;
	t_shape		backwall;
	t_shape		table_top;
	t_shape		leg1;
	t_shape		leg2;
	t_shape		leg3;
	t_shape		leg4;
	t_shape		mirror;
	t_shape		cube;
	t_shape		cone;
	t_shape		icecream1;
	t_shape		icecream2;
	t_shape		icecream3;
	t_shape		ring1;
	t_shape		ring2;
	t_shape		cone2;
	t_matrix	m[2];

	new_cube(&floor);
	new_checkers_pattern(
		new_solid_pattern(new_color(0.1, 0.1, 0.1)),
		new_solid_pattern(new_color(0.9, 0.9, 0.9)), &floor.material.pattern);
	floor.material.reflective = 0.5;
	set_pattern_transform(&floor.material.pattern, scaling(0.2, 0.2, 0.2, &m[0]));
	set_transform(&floor, scaling(10, 0.01, 10, &m[0]));
	new_cube(&ceiling);
	ceiling.material.color = new_color(0.9, 0.9, 0.95);
	multiply_matrices(translation(0, 5, 0, &m[0]), scaling(10, 0.01, 10, &m[1]), &m[0]);
	set_transform(&ceiling, &m[0]);
	new_cube(&backwall);
	backwall.material.pattern = new_solid_pattern(new_color(0.6, 0.1, 0.05));
	backwall.material.reflective = 0.2;
	multiply_matrices(translation(0, 0, 4, &m[0]), scaling(10, 10, 0.01, &m[1]), &m[0]);
	set_transform(&backwall, &m[0]);
	new_cube(&table_top);
	table_top.material.color = new_color(0.6, 0.3, 0.1);
	multiply_matrices(translation(0, 1, 0, &m[0]), scaling(2, 0.01, 1, &m[1]), &m[0]);
	set_transform(&table_top, &m[0]);
	new_cube(&leg1);
	leg1.material.color = new_color(0.6, 0.3, 0.1);
	multiply_matrices(translation(-1.7, 0, -0.9, &m[0]), scaling(0.1, 1, 0.1, &m[1]), &m[0]);
	set_transform(&leg1, &m[0]);
	new_cube(&leg2);
	leg2.material.color = new_color(0.6, 0.3, 0.1);
	multiply_matrices(translation(1.7, 0, -0.9, &m[0]), scaling(0.1, 1, 0.1, &m[1]), &m[0]);
	set_transform(&leg2, &m[0]);
	new_cube(&leg3);
	leg3.material.color = new_color(0.6, 0.3, 0.1);
	multiply_matrices(translation(1.7, 0, 0.9, &m[0]), scaling(0.1, 1, 0.1, &m[1]), &m[0]);
	set_transform(&leg3, &m[0]);
	new_cube(&leg4);
	leg4.material.color = new_color(0.6, 0.3, 0.1);
	multiply_matrices(translation(-1.7, 0, 0.9, &m[0]), scaling(0.1, 1, 0.1, &m[1]), &m[0]);
	set_transform(&leg4, &m[0]);
	new_cube(&mirror);
	mirror.material.color = new_color(0.1, 0.1, 0.1);
	mirror.material.reflective = 1;
	multiply_matrices(translation(0, 2.1, 3.99, &m[0]), scaling(2.5, 1.3, 0.01, &m[1]), &m[0]);
	set_transform(&mirror, &m[0]);
	new_cube(&cube);
	cube.material.color = new_color(0.6, 0.7, 0.8);
	cube.material.reflective = 0.8;
	cube.material.transparency = 0.8;
	cube.material.refractive_index = DIAMOND;
	cube.material.shininess = 1800;
	cube.material.diffuse = 0.1;
	cube.material.specular = 1.0;
	multiply_matrices(translation(0, 1.11, 0, &m[0]),
		rotation_y(cos(M_PI / 4), sin(M_PI / 4), &m[1]), &m[0]);
	multiply_matrices(&m[0], scaling(0.1, 0.1, 0.1, &m[1]), &m[0]);
	set_transform(&cube, &m[0]);
	new_cone(&cone);
	cone.cone.min = 0;
	cone.cone.max = 1.0;
	new_checkers_pattern(
		new_solid_pattern(new_color(0.957, 0.80, 0.604)),
		new_solid_pattern(new_color(0.925, 0.663, 0.333)), &cone.material.pattern);
	multiply_matrices(translation(-1.0, 1.0, 0.0, &m[0]), scaling(0.22, 0.58, 0.22, &m[1]), &m[0]);
	set_transform(&cone, &m[0]);
	set_pattern_transform(&cone.material.pattern, m);
	new_sphere(&icecream1);
	icecream1.material.color = new_color(0.957, 0.604, 0.761);
	multiply_matrices(translation(-1.0, 1.7, 0.0, &m[0]), scaling(0.24, 0.24, 0.24, &m[1]), &m[0]);
	set_transform(&icecream1, &m[0]);
	new_sphere(&icecream2);
	icecream2.material.color = new_color(0.604, 0.957, 0.624);
	multiply_matrices(translation(-1.0, 1.9, 0.0, &m[0]), scaling(0.19, 0.19, 0.19, &m[1]), &m[0]);
	set_transform(&icecream2, &m[0]);
	new_sphere(&icecream3);
	icecream3.material.color = new_color(0.604, 0.937, 0.957);
	multiply_matrices(translation(-1.0, 2.1, 0.0, &m[0]), scaling(0.14, 0.14, 0.14, &m[1]), &m[0]);
	set_transform(&icecream3, &m[0]);
	new_cylinder(&ring1);
	ring1.cyl.min = 0.0;
	ring1.cyl.max = 1.0;
	ring1.material.color = new_color(0.957, 0.604, 0.761);
	ring1.material.reflective = 0.9;
	ring1.material.shininess = 1800;
	multiply_matrices(translation(1.0, 2.0, 0.0, &m[0]),
		rotation_x(cos(M_PI / 4), sin(M_PI / 4), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_z(cos(M_PI / 4), sin(M_PI / 4), &m[1]), &m[0]);
	multiply_matrices(&m[0], scaling(0.5, 0.015, 0.5, &m[1]), &m[0]);
	set_transform(&ring1, &m[0]);
	new_cylinder(&ring2);
	ring2.cyl.min = 0.0;
	ring2.cyl.max = 1.0;
	ring2.material.color = new_color(0.957, 0.604, 0.761);
	ring2.material.reflective = 0.9;
	ring2.material.shininess = 1800;
	multiply_matrices(translation(1.0, 2.0, 0.0, &m[0]),
		rotation_x(cos(-M_PI / 5), sin(-M_PI / 5), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_z(cos(-M_PI / 5), sin(-M_PI / 5), &m[1]), &m[0]);
	multiply_matrices(&m[0], scaling(0.5, 0.015, 0.5, &m[1]), &m[0]);
	set_transform(&ring2, &m[0]);
	new_cone(&cone2);
	cone2.cone.min = -1.0;
	cone2.cone.max = 1.0;
	cone2.material.color = new_color(0.757, 0.404, 0.561);
	cone2.material.reflective = 0.4;
	cone2.material.shininess = 1800;
	cone2.cone.closed = true;
	multiply_matrices(translation(1.0, 1.99, -0.1, &m[0]),
		rotation_x(cos(-M_PI / 4), sin(-M_PI / 4), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_z(cos(-M_PI / 4), sin(-M_PI / 4), &m[1]), &m[0]);
	multiply_matrices(&m[0], scaling(0.1, 0.2, 0.1, &m[1]), &m[0]);
	set_transform(&cone2, &m[0]);
	world->objs[0] = floor;
	world->objs[1] = ceiling;
	world->objs[2] = backwall;
	world->objs[3] = table_top;
	world->objs[4] = leg1;
	world->objs[5] = leg2;
	world->objs[6] = leg3;
	world->objs[7] = leg4;
	world->objs[8] = mirror;
	world->objs[9] = cube;
	world->objs[10] = cone;
	world->objs[11] = icecream1;
	world->objs[12] = icecream2;
	world->objs[13] = icecream3;
	world->objs[14] = ring1;
	world->objs[15] = ring2;
	world->objs[16] = cone2;
}

void	create_ligts(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	new_point(-4, 4, -3, &p);
	c = new_color(0.4, 1.0, 0.7);
	new_light(&p, &c, &world->lights[0]);
	new_point(4, 0.5, -3, &p);
	c = new_color(0.5, 0.4, 0.7);
	new_light(&p, &c, &world->lights[1]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI / 3);
	new_point(0, 2, -5, &from);
	new_point(0, 0, 4, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&camera->transform));
}

int	main(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	rt.world.objs = malloc(sizeof(t_shape) * N_OBJS);
	rt.world.objs_count = N_OBJS;
	create_scene(&rt.world);
	create_ligts(&rt.world);
	create_camera(&rt.camera);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 13");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free(rt.world.objs);
	free(rt.world.lights);
	mlx_terminate(rt.canvas.mlx);
	return (0);
}
