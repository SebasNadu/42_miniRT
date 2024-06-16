#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	800
#define HEIGHT	600
#define N_OBJS	1

void	create_scene1(t_world *world)
{
	t_obj_loader	loader;
	t_matrix		m;

	world->objs = malloc(1 * sizeof(t_shape));
	world->objs_count = 1;
	new_obj_loader(&loader, &world->objs[0]);
	parse_obj_file(&loader, "../obj_files/teapot.obj");
	world->objs_ext_count += loader.t_count + loader.gp_count;
	set_transform(loader.default_group,
		rotation_x(cos(-M_PI / 2.0), sin(-M_PI / 2.0), &m));
}

void	create_lights1(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	new_point(-45, -45, -45, &p);
	new_color(0.3, 0.6, 0.95, &c);
	new_light(&p, &c, &world->lights[0]);
	new_point(45, 15, -45, &p);
	new_color(0.95, 0.6, 0.3, &c);
	new_light(&p, &c, &world->lights[1]);
}

void	create_camera1(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;
	t_matrix	m;

	new_camera(camera, WIDTH, HEIGHT, M_PI / 3);
	new_point(0, 15, -45, &from);
	new_point(0, 10, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&m));
}

void	render_teapot(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	create_lights1(&rt.world);
	create_camera1(&rt.camera);
	create_scene1(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Chapter 15");
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
	render_teapot();
	return (0);
}
