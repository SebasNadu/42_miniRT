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
	t_matrix	m[2];
	t_shape		light;
	t_shape		plane;
	t_shape		cyl;
	t_shape		sph;

	world->objs = malloc(4 * sizeof(t_shape));
	world->objs_count = 4;
	new_sphere(&light);
	light.material.color = new_color(1.5, 1.5, 1.5);
	light.material.ambient = new_color(1, 1, 1);
	light.material.diffuse = 0;
	light.material.specular = 0;
	light.cast_shadow = false;
	set_transform(&light, translation(-100, 100, -100, &m[0]));
	new_plane(&plane);
	plane.material.color = new_color(1, 1, 1);
	plane.material.ambient = new_color(0, 0, 0);
	plane.material.diffuse = 0.1;
	plane.material.specular = 0;
	plane.material.reflective = 0.4;
	new_cylinder(&cyl);
	cyl.cyl.min = 0;
	cyl.cyl.max = 0.1;
	cyl.cyl.closed = true;
	cyl.material.color = new_color(1, 1, 1);
	cyl.material.ambient = new_color(0, 0, 0);
	cyl.material.diffuse = 0.2;
	cyl.material.specular = 0;
	cyl.material.reflective = 0.1;
	new_sphere(&sph);
	new_texture_map(&sph.material.pattern, "../textures/earth.png");
	sph.material.diffuse = 0.9;
	sph.material.specular = 0.1;
	sph.material.shininess = 10;
	multiply_matrices(translation(0, 1.1, 0, &m[0]), rotation_y(cos(1.9), sin(1.9), &m[1]), &m[0]);
	set_transform(&sph, &m[0]);
	world->objs[0] = light;
	world->objs[1] = plane;
	world->objs[2] = cyl;
	world->objs[3] = sph;
}

void	create_lights(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(1 * sizeof(t_light));
	world->lights_count = 1;
	new_point(-100, 100, -100, &p);
	c = new_color(1, 1, 1);
	new_light(&p, &c, &world->lights[0]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI_2);
	new_point(1, 2, -10, &from);
	new_point(0, 1.1, 0, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(camera, view_transform(&from, &to, &up,
			&camera->transform));
}

int	main(void)
{
	t_mini_rt	rt;

	new_world(&rt.world);
	create_lights(&rt.world);
	create_camera(&rt.camera);
	create_scene(&rt.world);
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Bonus texture mapping");
	create_bvh(&rt.world);
	render(&rt);
	mlx_image_to_window(rt.canvas.mlx, rt.canvas.img, 0, 0);
	mlx_close_hook(rt.canvas.mlx, &quit, &rt.canvas);
	mlx_key_hook(rt.canvas.mlx, &handle_keyhook, &rt.canvas);
	mlx_loop(rt.canvas.mlx);
	free_world(&rt.world);
	mlx_terminate(rt.canvas.mlx);
	return (0);
}
