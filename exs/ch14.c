#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include <time.h>

#define WIDTH	1080
#define HEIGHT	720
#define N_OBJS	1

double	random_double(double min, double max)
{
	return (min + (rand() / (RAND_MAX / (max - min))));
}

t_matrix	*random_translation(t_bounds bounds, t_matrix *m)
{
	t_point		p;

	new_point(
		random_double(bounds.min.x, bounds.max.x),
		random_double(bounds.min.y, bounds.max.y),
		random_double(bounds.min.z, bounds.max.z), &p);
	translation(p.x, p.y, p.z, m);
	return (m);
}

t_color	random_color(void)
{
	t_color	c;

	new_color(random_double(0.01, 0.99), random_double(0.01, 0.99),
		random_double(0.01, 0.99), &c);
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
	t_matrix	m[2];
	t_point		p[2];

	num_spheres = 5;
	offset = 10;
	new_bounds(new_point(0, 0, 0, &p[0]), new_point(10, 10, 10, &p[1]), &bounds);
	s = malloc(((num_spheres * num_spheres) * num_spheres) * sizeof(t_shape));
	world->objs = malloc(((num_spheres * num_spheres) + 1) * sizeof(t_shape));
	world->objs_count = (num_spheres * num_spheres) + 1;
	for (int x = 0; x < num_spheres; x++)
	{
		for (int y = 0; y < num_spheres; y++)
		{
			g = &world->objs[x * num_spheres + y];
			new_group(g);
			set_transform(g, translation(x * offset, y * offset, 0, &m[0]));
      for (int i = 0; i < num_spheres; i++)
      {
        tmp = &s[x * num_spheres * num_spheres + y * num_spheres + i];
				new_sphere(tmp);
				set_transform(tmp, random_translation(bounds, &m[0]));
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
	new_plane(&plane);
	new_color(0.5, 0.5, 0.5, &plane.material.color);
	multiply_matrices(rotation_x(cos(-M_PI / 8), sin(-M_PI / 8), &m[0]),
			translation(0, -10, 0, &m[1]), &m[0]);
	set_transform(&plane, &m[0]);
	world->objs[num_spheres * num_spheres] = plane;
}

void	hexagon_side(t_shape *side)
{
	t_shape		*corner;
	t_shape		*edge;
	t_matrix	m[3];

	corner = malloc(1 * sizeof(t_shape));
	new_sphere(corner);
	corner->material.diffuse = 0.9;
	corner->material.specular = 0.9;
	multiply_matrices(translation(0, 0, -1, &m[0]), scaling(0.25, 0.25, 0.25, &m[1]), &m[2]);
	set_transform(corner, &m[2]);
	edge = malloc(1 * sizeof(t_shape));
	new_cylinder(edge);
	edge->cyl.min = 0;
	edge->cyl.max = 1;
	multiply_matrices(translation(0, 0, -1, &m[0]),
		rotation_y(cos(M_PI / -6), sin(M_PI / -6), &m[1]), &m[2]);
	multiply_matrices(&m[2], rotation_z(cos(M_PI / -2), sin(M_PI / -2), &m[1]), &m[0]);
	multiply_matrices(&m[0], scaling(0.25, 1.0, 0.25, &m[1]), &m[2]);
	set_transform(edge, &m[2]);
	new_group(side);
	add_child(side, corner);
	add_child(side, edge);
}
void	create_scene2(t_world *world)
{
	t_shape		*sides;
	t_shape		*hexagon;
	t_matrix	m;
	t_color		c;

	world->objs = malloc(1 * sizeof(t_shape));
	world->objs_count = 1;
	hexagon = world->objs;
	new_group(hexagon);
	sides = malloc(6 * sizeof(t_shape));
	for (int i = 0; i < 6; i++)
	{
		hexagon_side(&sides[i]);
		set_transform(&sides[i],
			rotation_y(cos(i * M_PI / 3), sin(i * M_PI / 3), &m));
		add_child(hexagon, &sides[i]);
	}
	new_radial_gradient_pattern(
		new_solid_pattern(new_color(0.5, 0.7, 0.9, &c)),
		new_solid_pattern(new_color(0.6, 0.3, 0.1, &c)), &hexagon->material.pattern);
	set_pattern_transform(&hexagon->material.pattern,
		scaling(0.33, 0.33, 0.33, &m));
}

void	create_lights1(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(1 * sizeof(t_light));
	world->lights_count = 1;
	new_point(0, 50, -25, &p);
	new_color(1, 1, 1, &c);
	new_light(&p, &c, &world->lights[0]);
}

void	create_camera1(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI / 3);
	new_point(25, -16, -25, &from);
	new_point(25, 30, 25, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&camera->transform));
}

void	create_camera2(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI / 3);
	new_point(0, 2, -2, &from);
	new_point(0, 0, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&camera->transform));
}

void	render_lots_of_spheres(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	create_scene1(&rt.world);
	create_lights1(&rt.world);
	create_camera1(&rt.camera);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 14 - Lots of Spheres");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free_world(&rt.world);
	mlx_terminate(rt.canvas.mlx);
}

void	render_hexagon(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	create_lights1(&rt.world);
	create_camera2(&rt.camera);
	create_scene2(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 14 - Hexagon");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free_world(&rt.world);
	mlx_terminate(rt.canvas.mlx);
}

int	main(void)
{
	srand(time(NULL));
	// render_lots_of_spheres();
	render_hexagon();
	return (0);
}
