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
	t_shape		c;
	t_shape		s1;
	t_shape		s2;
	t_shape		p;
	t_matrix	m[2];
	// t_shape		g;

	world->objs = malloc(4 * sizeof(t_shape));
	world->objs_count = 4;
	new_cube(&c);
	c.material.color = new_color(1.5, 1.5, 1.5);
	c.material.ambient = new_color(1, 1, 1);
	c.material.diffuse = 0;
	c.material.specular = 0;
	multiply_matrices(translation(0, 3, 4, &m[0]), scaling(1, 1, 0.01, &m[1]), &m[0]);
	set_transform(&c, &m[0]);
	c.cast_shadow = false;
	new_plane(&p);
	p.material.color = new_color(1, 1, 1);
	p.material.ambient = new_color(0.025, 0.025, 0.025);
	p.material.diffuse = 0.67;
	p.material.specular = 0;
	new_sphere(&s1);
	s1.material.color = new_color(1, 0, 0);
	s1.material.specular = 0;
	s1.material.diffuse = 0.6;
	s1.material.reflective = 0.3;
	multiply_matrices(translation(0.5, 0.5, 0, &m[1]), scaling(0.5, 0.5, 0.5, &m[0]), &m[1]);
	set_transform(&s1, &m[1]);
	new_sphere(&s2);
	s2.material.color = new_color(0.5, 0.5, 1);
	s2.material.specular = 0;
	s2.material.diffuse = 0.6;
	s2.material.reflective = 0.3;
	multiply_matrices(translation(-0.25, 0.33, 0, &m[0]), scaling(0.33, 0.33, 0.33, &m[1]), &m[0]);
	set_transform(&s2, &m[0]);
	// new_group(&g);
	// add_child(&g, &c);
	// add_child(&g, &p);
	// add_child(&g, &s1);
	// add_child(&g, &s2);
	// world->objs[0] = g;
	world->objs[0] = c;
	world->objs[1] = p;
	world->objs[2] = s1;
	world->objs[3] = s2;
}

void	create_lights(t_world *world)
{
	t_alight_params	lp;

	world->lights = malloc(1 * sizeof(t_light));
	world->lights_count = 1;
	new_point(-1, 2, 4, &lp.corner);
	new_vector(2, 0, 0, &lp.full_uvec);
	new_vector(0, 2, 0, &lp.full_vvec);
	lp.usteps = 10;
	lp.vsteps = 10;
	lp.intensity = new_color(1.5, 1.5, 1.5);
	new_area_light(&lp, &world->lights[0]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI_4);
	new_point(-3, 1, 2.5, &from);
	new_point(0, 0.5, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up, &camera->transform));
}

int	main(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	create_lights(&rt.world);
	create_camera(&rt.camera);
	create_scene(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Bonus Soft Shadows");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free_world(&rt.world);
	mlx_terminate(rt.canvas.mlx);
}
