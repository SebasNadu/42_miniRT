#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"

#define WIDTH	800
#define HEIGHT	600
#define N_OBJS	10

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
	t_matrix	m;

	floor = new_cube();
	floor.material.pattern = new_checkers_pattern(
			new_solid_pattern(new_color(0.1, 0.1, 0.1)),
			new_solid_pattern(new_color(0.9, 0.9, 0.9)));
	floor.material.reflective = 0.5;
	set_pattern_transform(&floor.material.pattern, scaling(0.2, 0.2, 0.2));
	set_transform(&floor, scaling(10, 0.01, 10));
	ceiling = new_cube();
	ceiling.material.color = new_color(0.9, 0.9, 0.95);
	m = multiply_matrices(translation(0, 5, 0), scaling(10, 0.01, 10));
	set_transform(&ceiling, m);
	backwall = new_cube();
	backwall.material.pattern = new_solid_pattern(new_color(0.6, 0.1, 0.05));
	backwall.material.reflective = 0.2;
	m = multiply_matrices(translation(0, 0, 4), scaling(10, 10, 0.01));
	set_transform(&backwall, m);
	table_top = new_cube();
	table_top.material.color = new_color(0.6, 0.3, 0.1);
	m = multiply_matrices(translation(0, 1, 0), scaling(2, 0.01, 1));
	set_transform(&table_top, m);
	leg1 = new_cube();
	leg1.material.color = new_color(0.6, 0.3, 0.1);
	m = multiply_matrices(translation(-1.7, 0, -0.9), scaling(0.1, 1, 0.1));
	set_transform(&leg1, m);
	leg2 = new_cube();
	leg2.material.color = new_color(0.6, 0.3, 0.1);
	m = multiply_matrices(translation(1.7, 0, -0.9), scaling(0.1, 1, 0.1));
	set_transform(&leg2, m);
	leg3 = new_cube();
	leg3.material.color = new_color(0.6, 0.3, 0.1);
	m = multiply_matrices(translation(1.7, 0, 0.9), scaling(0.1, 1, 0.1));
	set_transform(&leg3, m);
	leg4 = new_cube();
	leg4.material.color = new_color(0.6, 0.3, 0.1);
	m = multiply_matrices(translation(-1.7, 0, 0.9), scaling(0.1, 1, 0.1));
	set_transform(&leg4, m);
	mirror = new_cube();
	mirror.material.color = new_color(0.1, 0.1, 0.1);
	mirror.material.reflective = 1;
	m = multiply_matrices(translation(0, 2.1, 3.99), scaling(2.5, 1.3, 0.01));
	set_transform(&mirror, m);
	cube = new_cube();
	cube.material.color = new_color(0.6, 0.7, 0.8);
	cube.material.reflective = 0.8;
	cube.material.transparency = 0.8;
	cube.material.refractive_index = DIAMOND;
	cube.material.shininess = 1800;
	cube.material.diffuse = 0.1;
	cube.material.specular = 1.0;
	m = multiply_matrices(translation(0, 1.11, 0),
			rotation_y(cos(M_PI / 4), sin(M_PI / 4)));
	m = multiply_matrices(m, scaling(0.1, 0.1, 0.1));
	set_transform(&cube, m);
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
}

void	create_ligts(t_world *world)
{
	world->lights = malloc(sizeof(t_light));
	world->lights_count = 1;
	world->lights[0] = new_light(new_point(-4, 4, -3), new_color(1, 1, 1));
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 3);
	from = new_point(0, 2, -5);
	to = new_point(0, 0, 4);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

int	main(void)
{
	t_world		world;
	t_camera	camera;
	t_canvas	canvas;

	world = new_world();
	world.objs = malloc(sizeof(t_shape) * N_OBJS);
	world.objs_count = N_OBJS;
	create_scene(&world);
	create_ligts(&world);
	create_camera(&camera);
	render(&canvas, &world, &camera);
	mlx_image_to_window(canvas.mlx, canvas.img, 0, 0);
	mlx_close_hook(canvas.mlx, &quit, &canvas);
	mlx_key_hook(canvas.mlx, &handle_keyhook, &canvas);
	mlx_loop(canvas.mlx);
	free(world.objs);
	free(world.lights);
	mlx_terminate(canvas.mlx);
	return (0);
}