#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include <time.h>

#define WIDTH	600
#define HEIGHT	480
#define N_OBJS	1

double	random_double(double min, double max)
{
	return (min + (rand() / (RAND_MAX / (max - min))));
}

t_matrix	random_translation(t_bounds bounds)
{
	t_matrix	m;
	t_point		p;

	p = new_point(
			random_double(bounds.min.x, bounds.max.x),
			random_double(bounds.min.y, bounds.max.y),
			random_double(bounds.min.z, bounds.max.z));
	m = translation(p.x, p.y, p.z);
	return (m);
}

t_color	random_color(void)
{
	t_color	c;

	c = new_color(random_double(0.01, 0.99), random_double(0.01, 0.99),
			random_double(0.01, 0.99));
	return (c);
}

void	create_scene1(t_world *world)
{
	t_shape		*s;
	t_shape		*tmp;
	t_shape		*g;
	int			offset;
	int			num_spheres;
	t_bounds	bounds;
	t_shape		plane;
	t_matrix	m;

	num_spheres = 5;
	offset = 10;
	bounds = new_bounds(new_point(0, 0, 0), new_point(10, 10, 10));
	s = malloc(((num_spheres * num_spheres) * num_spheres) * sizeof(t_shape));
	world->objs = malloc(((num_spheres * num_spheres) + 1) * sizeof(t_shape));
	world->objs_count = (num_spheres * num_spheres) + 1;
	for (int x = 0; x < num_spheres; x++)
	{
		for (int y = 0; y < num_spheres; y++)
		{
			g = &world->objs[x * num_spheres + y];
			*g = new_group();
			set_transform(g, translation(x * offset, y * offset, 0));
      for (int i = 0; i < num_spheres; i++)
      {
        tmp = &s[x * num_spheres * num_spheres + y * num_spheres + i];
				*tmp = new_sphere();
				set_transform(tmp, random_translation(bounds));
				tmp->material.color = random_color();
				if (i % 2 == 0)
				{
					tmp->material.diffuse = 0.1;
					tmp->material.specular = 1.0;
					tmp->material.reflective = 0.9;
					tmp->material.transparency = 0.9;
					tmp->material.refractive_index = DIAMOND;
					tmp->material.shininess = 1300;
				}
				else
				{
					tmp->material.reflective = 0.9;
				}
				add_child(g, tmp);
			}
		}
	}
	plane = new_plane();
	plane.material.color = new_color(0.5, 0.5, 0.5);
	m = multiply_matrices(rotation_x(cos(-M_PI / 8), sin(-M_PI / 8)),
			translation(0, -10, 0));
	set_transform(&plane, m);
	world->objs[num_spheres * num_spheres] = plane;
}

void	hexagon_side(t_shape *side)
{
	t_shape		*corner;
	t_shape		*edge;
	t_matrix	m;

	corner = malloc(1 * sizeof(t_shape));
	*corner = new_sphere();
	corner->material.diffuse = 0.9;
	corner->material.specular = 0.9;
	m = multiply_matrices(translation(0, 0, -1), scaling(0.25, 0.25, 0.25));
	set_transform(corner, m);
	edge = malloc(1 * sizeof(t_shape));
	*edge = new_cylinder();
	edge->cyl.min = 0;
	edge->cyl.max = 1;
	m = multiply_matrices(translation(0, 0, -1),
			rotation_y(cos(M_PI / -6), sin(M_PI / -6)));
	m = multiply_matrices(m, rotation_z(cos(M_PI / -2), sin(M_PI / -2)));
	m = multiply_matrices(m, scaling(0.25, 1.0, 0.25));
	set_transform(edge, m);
	*side = new_group();
	add_child(side, corner);
	add_child(side, edge);
}
void	create_scene2(t_world *world)
{
	t_shape	*sides;
	t_shape	*hexagon;

	world->objs = malloc(1 * sizeof(t_shape));
	world->objs_count = 1;
	hexagon = world->objs;
	*hexagon = new_group();
	sides = malloc(6 * sizeof(t_shape));
	for (int i = 0; i < 6; i++)
	{
		hexagon_side(&sides[i]);
		set_transform(&sides[i],
			rotation_y(cos(i * M_PI / 3), sin(i * M_PI / 3)));
		add_child(hexagon, &sides[i]);
	}
	hexagon->material.pattern = new_radial_gradient_pattern(
			new_solid_pattern(new_color(0.5, 0.7, 0.9)),
			new_solid_pattern(new_color(0.6, 0.3, 0.1)));
	set_pattern_transform(&hexagon->material.pattern,
		scaling(0.33, 0.33, 0.33));
}

void	create_lights1(t_world *world)
{
	world->lights = malloc(1 * sizeof(t_light));
	world->lights_count = 1;
	world->lights[0] = new_light(new_point(0, 50, -25), new_color(1, 1, 1));
}

void	create_camera1(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 3);
	from = new_point(25, -16, -25);
	to = new_point(25, 30, 25);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

void	create_camera2(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	*camera = new_camera(WIDTH, HEIGHT, M_PI / 3);
	from = new_point(0, 2, -2);
	to = new_point(0, 0, 0);
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
}

void	render_lots_of_spheres(void)
{
	t_world		world;
	t_camera	camera;
	t_canvas	canvas;

	world = new_world();
	create_scene1(&world);
	create_lights1(&world);
	create_camera1(&camera);
	render(&canvas, &world, &camera);
	mlx_image_to_window(canvas.mlx, canvas.img, 0, 0);
	mlx_close_hook(canvas.mlx, &quit, &canvas);
	mlx_key_hook(canvas.mlx, &handle_keyhook, &canvas);
	mlx_loop(canvas.mlx);
	free_world(&world);
	mlx_terminate(canvas.mlx);
}

void	render_hexagon(void)
{
	t_world		world;
	t_camera	camera;
	t_canvas	canvas;

	world = new_world();
	create_lights1(&world);
	create_camera2(&camera);
	create_scene2(&world);
	render(&canvas, &world, &camera);
	mlx_image_to_window(canvas.mlx, canvas.img, 0, 0);
	mlx_close_hook(canvas.mlx, &quit, &canvas);
	mlx_key_hook(canvas.mlx, &handle_keyhook, &canvas);
	mlx_loop(canvas.mlx);
	free_world(&world);
	mlx_terminate(canvas.mlx);
}

int	main(void)
{
	srand(time(NULL));
	// render_lots_of_spheres();
	render_hexagon();
	return (0);
}