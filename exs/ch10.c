#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"

#define WIDTH	1024
#define HEIGHT	1024
#define N_OBJS	7

void	create_background(t_world *world)
{
	t_shape		floor;
	t_shape		front_wall;
	t_shape		left_wall;
	t_shape		right_wall;
	t_color		a;
	t_color		b;
	t_color		c;
	t_color		d;
	t_matrix	multi[3];

	new_color(0.5, 0.5, 0.5, &a);
	new_color(0.7, 0.7, 0.7, &b);
	new_plane(&floor);
	floor.material.specular = 0;
	new_checkers_pattern(new_solid_pattern(&a),
		new_solid_pattern(&b), &floor.material.pattern);
	new_stripe_pattern(
		new_solid_pattern(new_color(0.9, 0.3, 0.3, &c)),
		new_solid_pattern(new_color(0.6, 0.3, 0.3, &d)), floor.material.pattern.a);
	set_pattern_transform(floor.material.pattern.a, scaling(0.1, 0.1, 0.1, &multi[0]));
	new_stripe_pattern(
		new_solid_pattern(&a), new_solid_pattern(&b), floor.material.pattern.b);
	set_pattern_transform(floor.material.pattern.b, scaling(0.1, 0.1, 0.1, &multi[0]));
	new_plane(&front_wall);
	front_wall.material = floor.material;
	new_blended_pattern(
		new_solid_pattern(&a), new_solid_pattern(&b), &front_wall.material.pattern);
	new_stripe_pattern(
		new_solid_pattern(new_color(0, 0.5, 0.1, &c)),
		new_solid_pattern(new_color(0.8, 0.8, 0.8, &d)), front_wall.material.pattern.a);
	new_stripe_pattern(
		new_solid_pattern(new_color(0, 0.5, 0.1, &c)),
		new_solid_pattern(new_color(0.8, 0.8, 0.8, &d)), front_wall.material.pattern.b);
	set_transform(&front_wall, transformations(2, rotation_x(cos(M_PI / 2),
				sin(M_PI / 2), &multi[0]), translation(0, 0, 5, &multi[1])));
	set_pattern_transform(&front_wall.material.pattern, multi);
	set_pattern_transform(front_wall.material.pattern.a, rotation_z(cos(M_PI / 4), sin(M_PI / 4), &multi[0]));
	set_pattern_transform(front_wall.material.pattern.b, rotation_z(cos(-M_PI / 4), sin(-M_PI / 4), &multi[0]));
	new_plane(&right_wall);
	right_wall.material = floor.material;
	new_checkers_pattern(new_solid_pattern(&a),
		new_solid_pattern(&b), &right_wall.material.pattern);
	set_transform(&right_wall, transformations(3, rotation_x(cos(M_PI / 2),
				sin(M_PI / 2), &multi[0]), rotation_y(
				cos(M_PI / 3), sin(M_PI / 3), &multi[1]),
			translation(5, 0, 5, &multi[2])));
	new_plane(&left_wall);
	new_checkers_pattern(new_solid_pattern(&a),
		new_solid_pattern(&b), &left_wall.material.pattern);
	set_transform(&left_wall, transformations(3, rotation_x(cos(M_PI / 2),
				sin(M_PI / 2), &multi[0]), rotation_y(cos(-M_PI / 3),
				sin(-M_PI / 3), &multi[1]), translation(-5, 0, 5, &multi[2])));
	world->objs[0] = floor;
	world->objs[1] = front_wall;
	world->objs[2] = right_wall;
	world->objs[3] = left_wall;
}

void	create_spheres(t_world *world)
{
	t_shape		middle;
	t_shape		right;
	t_shape		left;
	t_color		a;
	t_matrix	m[2];

	new_color(1, 1, 1, &a);
	new_sphere(&middle);
	new_color(0.1, 1, 0.5, &middle.material.color);
	new_uv_checkers_pattern(new_solid_pattern(&a),
		new_solid_pattern(&middle.material.color), &middle.material.pattern);
	translation(-0.5, 1, 0.5, &m[0]);
	set_transform(&middle, m);
	scaling(0.4, 0.4, 0.4, &m[0]);
	set_pattern_transform(&middle.material.pattern, &m[0]);
	new_sphere(&right);
	new_color(0.5, 1, 0.1, &right.material.color);
	new_ring_pattern(new_solid_pattern(&a),
		new_solid_pattern(&right.material.color), &right.material.pattern);
	multiply_matrices(translation(1.5, 0.5, -0.5, &m[0]), scaling(0.5, 0.5, 0.5, &m[1]), &m[0]);
	set_transform(&right, &m[0]);
	set_pattern_transform(&right.material.pattern, &m[0]);
	new_sphere(&left);
	new_color(1, 0.8, 0.1, &left.material.color);
	new_full_gradient_pattern(new_solid_pattern(&a),
		new_solid_pattern(&left.material.color), &left.material.pattern);
	multiply_matrices(translation(-1.5, 0.33, -0.75, &m[0]), scaling(0.33, 0.33, 0.33, &m[1]), &m[0]);
	set_transform(&left, &m[0]);
	set_pattern_transform(&left.material.pattern, &m[0]);
	world->objs[4] = middle;
	world->objs[5] = right;
	world->objs[6] = left;
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

	new_camera(camera, WIDTH, HEIGHT, M_PI_2);
	new_point(0, 1, -5, &from);
	new_point(0, 1, 0, &to);
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
	create_background(&rt.world);
	create_spheres(&rt.world);
	create_ligts(&rt.world);
	create_camera(&rt.camera);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 10");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free(rt.world.objs[0].material.pattern.a);
	free(rt.world.objs[0].material.pattern.b);
	free(rt.world.objs[1].material.pattern.a);
	free(rt.world.objs[1].material.pattern.b);
	free(rt.world.objs[2].material.pattern.a);
	free(rt.world.objs[2].material.pattern.b);
	free(rt.world.objs[3].material.pattern.a);
	free(rt.world.objs[3].material.pattern.b);
	free(rt.world.objs[4].material.pattern.a);
	free(rt.world.objs[4].material.pattern.b);
	free(rt.world.objs[5].material.pattern.a);
	free(rt.world.objs[5].material.pattern.b);
	free(rt.world.objs[6].material.pattern.a);
	free(rt.world.objs[6].material.pattern.b);
	free(rt.world.objs);
	free(rt.world.lights);
	mlx_terminate(rt.canvas.mlx);
	return (0);
}
