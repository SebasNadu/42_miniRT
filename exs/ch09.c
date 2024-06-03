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
	t_shape		front; 
	t_shape		r_top;
	t_shape		l_top;
	t_shape		r_bottom; 
	t_shape		l_bottom;
	t_shape		back;
	t_matrix	multi;

	new_plane(&floor);
	floor.material.color = new_color(1, 0.9, 0.9);
	floor.material.specular = 0;
	new_plane(&front);
	front.material = floor.material;
	multi = transformations(2, 
			rotation_x(cos(M_PI / 2), sin(M_PI / 2)), translation(0, 0, 12));
	set_transform(&front, multi);
	new_plane(&l_top);
	l_top.material = floor.material;
	multi = transformations(3, rotation_x(cos(M_PI / 2), sin(M_PI / 2)),
			rotation_y(cos(-M_PI / 4), sin(-M_PI / 4)), translation(-12, 0, 12));
	set_transform(&l_top, multi);
	new_plane(&r_top);
	multi = transformations(3, rotation_x(cos(M_PI / 2), sin(M_PI / 2)),
			rotation_y(cos(M_PI / 4), sin(M_PI / 4)), translation(12, 0, 12));
	set_transform(&r_top, multi);
	r_top.material = floor.material;
	new_plane(&l_bottom);
	l_bottom.material = floor.material;
	multi = transformations(3, rotation_x(cos(M_PI / 2), sin(M_PI / 2)),
			rotation_y(cos(-M_PI * 0.75), sin(-M_PI * 0.75)), translation(-12, 0, -12));
	set_transform(&l_bottom, multi);
	new_plane(&r_bottom);
	r_bottom.material = floor.material;
	multi = transformations(3, rotation_x(cos(M_PI / 2), sin(M_PI / 2)),
			rotation_y(cos(M_PI * 0.75), sin(M_PI * 0.75)), translation(12, 0, -12));
	set_transform(&r_bottom, multi);
	new_plane(&back);
	back.material = floor.material;
	multi = transformations(2, 
			rotation_x(cos(M_PI / 2), sin(M_PI / 2)), translation(0, 0, -12));
	set_transform(&back, multi);
	world->objs[0] = floor;
	world->objs[1] = front; 
	world->objs[2] = l_top;
	world->objs[3] = r_top; 
	world->objs[4] = l_bottom; 
	world->objs[5] = r_bottom; 
	world->objs[6] = back; 
}

void	create_spheres(t_world *world)
{
	t_shape		middle;
	t_shape		right;
	t_shape		left;

	new_sphere(&middle);
	middle.material.color = new_color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	set_transform(&middle, translation(-0.5, 1, 0.5));
	new_sphere(&right);
	set_transform(&right, transformations(2, scaling(0.5, 0.5, 0.5),
			translation(1.5, 0.5, -0.5)));
	right.material.color = new_color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;
	new_sphere(&left);
	set_transform(&left, transformations(2, scaling(0.33, 0.33, 0.33),
			translation(-1.5, 0.33, -0.75)));
	left.material.color = new_color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;
	world->objs[7] = middle;
	world->objs[8] = right;
	world->objs[9] = left;
}

void	create_ligts(t_world *world)
{
	world->lights = malloc(sizeof(t_light));
	world->lights_count = 1;
	world->lights[0] = new_light(new_point(-10, 10, -10), new_color(1, 1, 1));
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 3);
	from = new_point(0, 12, -2);
	to = new_point(0, -6, 0);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

int	main(void)
{
	t_mini_rt	rt;

	rt.world = new_world();
	rt.world.objs = malloc(sizeof(t_shape) * 10);
	rt.world.objs_count = 10;
	create_background(&rt.world);
	create_spheres(&rt.world);
	create_ligts(&rt.world);
	create_camera(&rt.camera);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 9");
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
