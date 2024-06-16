#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	1080
#define HEIGHT 720

void	create_scene(t_world *world)
{
	t_shape		c;
	t_shape		c1;
	t_shape		s1;
	t_shape		s2;
	t_shape		p;
	t_matrix	m[2];

	world->objs = malloc(5 * sizeof(t_shape));
	world->objs_count = 5;
	new_sphere(&c);
	new_color(1.5, 0.5, 0.5, &c.material.color);
	new_color(1, 1, 1, &c.material.ambient);
	c.material.diffuse = 0;
	c.material.specular = 0;
	multiply_matrices(translation(-4, 3, 5, &m[0]), scaling(0.5, 0.5, 0.01, &m[1]), &m[0]);
	set_transform(&c, &m[0]);
	c.cast_shadow = false;
	new_sphere(&c1);
	new_color(0.5, 1.5, 0.5, &c1.material.color);
	new_color(1, 1, 1, &c1.material.ambient);
	c1.material.diffuse = 0;
	c1.material.specular = 0;
	multiply_matrices(translation(4, 3, 5, &m[0]), scaling(0.5, 0.5, 0.01, &m[1]), &m[0]);
	set_transform(&c1, &m[0]);
	c1.cast_shadow = false;
	new_plane(&p);
	new_color(1, 1, 1, &p.material.color);
	new_color(0.025, 0.025, 0.025, &p.material.ambient);
	p.material.diffuse = 0.67;
	p.material.specular = 0;
	new_sphere(&s1);
	new_color(1, 0, 0, &s1.material.color);
	s1.material.specular = 0;
	s1.material.diffuse = 0.6;
	s1.material.reflective = 0.3;
	multiply_matrices(translation(0.5, 0.5, 0, &m[1]), scaling(0.5, 0.5, 0.5, &m[0]), &m[1]);
	set_transform(&s1, &m[1]);
	new_sphere(&s2);
	new_color(0.5, 0.5, 1, &s2.material.color);
	s2.material.specular = 0;
	s2.material.diffuse = 0.6;
	s2.material.reflective = 0.3;
	multiply_matrices(translation(-0.25, 0.33, 0, &m[0]), scaling(0.33, 0.33, 0.33, &m[1]), &m[0]);
	set_transform(&s2, &m[0]);
	world->objs[0] = c;
	world->objs[1] = c1;
	world->objs[2] = p;
	world->objs[3] = s1;
	world->objs[4] = s2;
}

void	create_aspotlights(t_world *world)
{
	t_aspotlight_params	asp;
	t_point				to;
	t_point				from;

	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	new_point(-5, 2, 5, &asp.corner);
	new_vector(2, 0, 0, &asp.full_uvec);
	new_vector(0, 2, 0, &asp.full_vvec);
	asp.usteps = 10;
	asp.vsteps = 10;
	new_color(1.5, 0.5, 0.5, &asp.intensity);
	new_point(0, 0, 0, &to);
	new_point(-4, 3, 5, &from);
	subtract(&to, &from, &asp.direction);
	asp.center_radian = M_PI_4 / 32; 
	asp.fade_radian = M_PI_4 / 2;
	new_area_spotlight(&asp, &world->lights[0]);
	new_point(5, 2, 5, &asp.corner);
	new_vector(-2, 0, 0, &asp.full_uvec);
	new_vector(0, 2, 0, &asp.full_vvec);
	asp.usteps = 10;
	asp.vsteps = 10;
	new_color(0.5, 1.5, 0.5, &asp.intensity);
	new_point(0, 0, 0, &to);
	new_point(4, 3, 5, &from);
	subtract(&to, &from, &asp.direction);
	asp.center_radian = M_PI_4 / 32; 
	asp.fade_radian = M_PI_4 / 2;
	new_area_spotlight(&asp, &world->lights[1]);
}

void	create_spotlights(t_world *world)
{
	t_spotlight_params	sp;
	t_point				to;

	world->lights = malloc(2 * sizeof(t_light));
	world->lights_count = 2;
	new_point(-2, 2, 2, &sp.position);
	new_point(0, 0, 0, &to);
	subtract(&to, &sp.position, &sp.direction);
	new_color(1.5, 0.5, 0.5, &sp.intensity);
	sp.center_radian = M_PI_4 / 32; 
	sp.fade_radian = M_PI / 6;
	new_spotlight(&sp, &world->lights[0]);
	new_point(2, 2, 2, &sp.position);
	new_point(0, 0, 0, &to);
	subtract(&to, &sp.position, &sp.direction);
	new_color(0.5, 1.5, 0.5, &sp.intensity);
	sp.center_radian = M_PI_4 / 32; 
	sp.fade_radian = M_PI / 6;
	new_spotlight(&sp, &world->lights[1]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI_4);
	new_point(0, 5, 10, &from);
	new_point(0, 2, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up, &camera->transform));
}

int	main(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	// create_spotlights(&rt.world);
	create_aspotlights(&rt.world);
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
