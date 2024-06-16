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
	t_shape		sph;
	t_shape		skybox;
	char const	*paths[6] = {
		"../textures/LancellottiChapel/negx.png",
		"../textures/LancellottiChapel/posz.png",
		"../textures/LancellottiChapel/posx.png",
		"../textures/LancellottiChapel/negz.png",
		"../textures/LancellottiChapel/posy.png",
		"../textures/LancellottiChapel/negy.png"
	};

	world->objs = malloc(2 * sizeof(t_shape));
	world->objs_count = 2;
	new_sphere(&sph);
	new_color(0, 0, 0, &sph.material.ambient);
	sph.material.diffuse = 0.4;
	sph.material.specular = 0.6;
	sph.material.shininess = 20;
	sph.material.reflective = 0.6;
	multiply_matrices(translation(0, 0, 5, &m[0]), scaling(0.75, 0.75, 0.75, &m[1]), &m[0]);
	set_transform(&sph, &m[0]);
	new_cube(&skybox);
	skybox.material.diffuse = 0;
	skybox.material.specular = 0;
	new_color(1, 1, 1, &skybox.material.ambient);
	new_cubic_texture_map(&skybox.material.pattern, paths);
	set_transform(&skybox, scaling(1000, 1000, 1000, &m[0]));
	world->objs[0] = sph;
	world->objs[1] = skybox;
}

void	create_lights(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(1 * sizeof(t_light));
	world->lights_count = 1;
	new_point(0, 100, 0, &p);
	new_color(1, 1, 1, &c);
	new_light(&p, &c, &world->lights[0]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI_2);
	new_point(0, 0, 0, &from);
	new_point(0, 0, 5, &to);
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
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Bonus skybox");
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
