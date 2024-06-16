#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "groups.h"
#include <stdio.h>

#define WIDTH	1024
#define HEIGHT	1024

void	create_background(t_world *world)
{
	t_shape		floor;
	t_shape		left_wall;
	t_shape		right_wall;
	t_matrix	multi[2];

	new_sphere(&floor);
	set_transform(&floor, scaling(10, 0.01, 10, &multi[0]));
	new_color(1, 0.9, 0.9, &floor.material.color);
	floor.material.specular = 0;
	new_sphere(&left_wall);
	multiply_matrices(
		multiply_matrices(
			multiply_matrices(
				translation(0, 0, 5, &multi[0]), rotation_y(cos(-M_PI / 4),
					sin(-M_PI / 4), &multi[1]), &multi[0]),
			rotation_x(cos(M_PI / 2), sin(M_PI / 2), &multi[1]), &multi[0]),
		scaling(10, 0.01, 10, &multi[1]), &multi[0]);
	set_transform(&left_wall, &multi[0]);
	left_wall.material = floor.material;
	new_sphere(&right_wall);
	multiply_matrices(
		multiply_matrices(
			multiply_matrices(
				translation(0, 0, 5, &multi[0]), rotation_y(cos(M_PI / 4),
					sin(M_PI / 4), &multi[1]), &multi[0]),
			rotation_x(cos(M_PI / 2), sin(M_PI / 2), &multi[1]), &multi[0]),
		scaling(10, 0.01, 10, &multi[1]), &multi[0]);
	set_transform(&right_wall, &multi[0]);
	right_wall.material = floor.material;
	world->objs[0] = floor;
	world->objs[1] = left_wall;
	world->objs[2] = right_wall;
}

void	create_spheres(t_world *world)
{
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_matrix	m[2];

	new_sphere(&middle);
	new_color(0.1, 1, 0.5, &middle.material.color);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	set_transform(&middle, translation(-0.5, 1, 0.5, &m[0]));
	new_sphere(&right);
	right.sphere.radius = 0.5;
	set_transform(&right, translation(0, 2, 0.5, &m[0]));
	new_color(0.5, 1, 0.1, &right.material.color);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;
	new_sphere(&left);
	set_transform(&left, transformations(2, scaling(0.33, 0.33, 0.33, &m[0]),
			translation(-1.5, 1.5, -1, &m[1])));
	new_color(1, 0.8, 0.1, &left.material.color);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;
	world->objs[3] = middle;
	world->objs[4] = right;
	world->objs[5] = left;
}

void	create_ligts(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(sizeof(t_light));
	world->lights_count = 1;
	new_point(-10, 10, -10, &p);
	new_color(1, 1, 1, &c);
	new_light(&p, &c, &world->lights[0]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI / 3);
	new_point(0, 1.5, -5, &from);
	new_point(0, 1, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&camera->transform));
}

int	main(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	rt.world.objs = malloc(sizeof(t_shape) * 6);
	rt.world.objs_count = 6;
	create_background(&rt.world);
	create_spheres(&rt.world);
	create_ligts(&rt.world);
	create_camera(&rt.camera);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 8");
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
