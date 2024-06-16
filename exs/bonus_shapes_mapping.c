#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	1080
#define HEIGHT 720

void	create_cubes(t_shape *objs)
{
	t_color		red;
	t_color		yellow;
	t_color		brown;
	t_color		green;
	t_color		cyan;
	t_color		blue;
	t_color		purple;
	t_color		white;
	t_color		colors[5];
	t_pattern	align_checkers[6];
	t_shape		cubes[8];
	t_matrix	m[2];

	new_color(1, 0, 0, &red);
	new_color(1, 1, 0, &yellow);
	new_color(1, 0.5, 0, &brown);
	new_color(0, 1, 0, &green);
	new_color(0, 1, 1, &cyan);
	new_color(0, 0, 1, &blue);
	new_color(1, 0, 1, &purple);
	new_color(1, 1, 1, &white);
	colors[0] = yellow;
	colors[1] = cyan;
	colors[2] = red;
	colors[3] = blue;
	colors[4] = brown;
	new_uv_align_check_pattern(&align_checkers[0], colors);
	colors[0] = cyan;
	colors[1] = red;
	colors[2] = yellow;
	colors[3] = brown;
	colors[4] = green;
	new_uv_align_check_pattern(&align_checkers[1], colors);
	colors[0] = red;
	colors[1] = yellow;
	colors[2] = purple;
	colors[3] = green;
	colors[4] = white;
	new_uv_align_check_pattern(&align_checkers[2], colors);
	colors[0] = green;
	colors[1] = purple;
	colors[2] = cyan;
	colors[3] = white;
	colors[4] = blue;
	new_uv_align_check_pattern(&align_checkers[3], colors);
	colors[0] = brown;
	colors[1] = cyan;
	colors[2] = purple;
	colors[3] = red;
	colors[4] = yellow;
	new_uv_align_check_pattern(&align_checkers[4], colors);
	colors[0] = purple;
	colors[1] = brown;
	colors[2] = green;
	colors[3] = blue;
	colors[4] = white;
	new_uv_align_check_pattern(&align_checkers[5], colors);
	new_cube(&cubes[0]);
	new_cube_align_check_pattern(&cubes[0].material.pattern, align_checkers);
	new_color(0.2, 0.2, 0.2, &cubes[0].material.ambient);
	cubes[0].material.specular = 0;
	cubes[0].material.diffuse = 0.8;
	multiply_matrices(translation(-6, 4, 10, &m[0]), rotation_x(cos(0.7854), sin(0.7854), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_y(cos(0.7854), sin(0.7854), &m[1]), &m[0]);
	set_transform(&cubes[0], &m[0]);
	new_cube(&cubes[1]);
	new_cube_align_check_pattern(&cubes[1].material.pattern, align_checkers);
	new_color(0.2, 0.2, 0.2, &cubes[1].material.ambient);
	cubes[1].material.specular = 0;
	cubes[1].material.diffuse = 0.8;
	multiply_matrices(translation(-2, 4, 10, &m[0]), rotation_x(cos(0.7854), sin(0.7854), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_y(cos(2.3562), sin(2.3562), &m[1]), &m[0]);
	set_transform(&cubes[1], &m[0]);
	new_cube(&cubes[2]);
	new_cube_align_check_pattern(&cubes[2].material.pattern, align_checkers);
	new_color(0.2, 0.2, 0.2, &cubes[2].material.ambient);
	cubes[2].material.specular = 0;
	cubes[2].material.diffuse = 0.8;
	multiply_matrices(translation(2, 4, 10, &m[0]), rotation_x(cos(0.7854), sin(0.7854), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_y(cos(3.927), sin(3.927), &m[1]), &m[0]);
	set_transform(&cubes[2], &m[0]);
	new_cube(&cubes[3]);
	new_cube_align_check_pattern(&cubes[3].material.pattern, align_checkers);
	new_color(0.2, 0.2, 0.2, &cubes[2].material.ambient);
	cubes[3].material.specular = 0;
	cubes[3].material.diffuse = 0.8;
	multiply_matrices(translation(6, 4, 10, &m[0]), rotation_x(cos(0.7854), sin(0.7854), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_y(cos(5.4978), sin(5.4978), &m[1]), &m[0]);
	set_transform(&cubes[3], &m[0]);
	new_cube(&cubes[4]);
	new_cube_align_check_pattern(&cubes[4].material.pattern, align_checkers);
	new_color(0.2, 0.2, 0.2, &cubes[3].material.ambient);
	cubes[4].material.specular = 0;
	cubes[4].material.diffuse = 0.8;
	multiply_matrices(translation(-6, 0, 10, &m[0]), rotation_x(-cos(0.7854), -sin(0.7854), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_y(cos(0.7854), sin(0.7854), &m[1]), &m[0]);
	set_transform(&cubes[4], &m[0]);
	new_cube(&cubes[5]);
	new_cube_align_check_pattern(&cubes[5].material.pattern, align_checkers);
	new_color(0.2, 0.2, 0.2, &cubes[4].material.ambient);
	cubes[5].material.specular = 0;
	cubes[5].material.diffuse = 0.8;
	multiply_matrices(translation(-2, 0, 10, &m[0]), rotation_x(-cos(0.7854), -sin(0.7854), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_y(cos(2.3562), sin(2.3562), &m[1]), &m[0]);
	set_transform(&cubes[5], &m[0]);
	new_cube(&cubes[6]);
	new_cube_align_check_pattern(&cubes[6].material.pattern, align_checkers);
	new_color(0.2, 0.2, 0.2, &cubes[5].material.ambient);
	cubes[6].material.specular = 0;
	cubes[6].material.diffuse = 0.8;
	multiply_matrices(translation(2, 0, 10, &m[0]), rotation_x(-cos(0.7854), -sin(0.7854), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_y(cos(3.927), sin(3.927), &m[1]), &m[0]);
	set_transform(&cubes[6], &m[0]);
	new_cube(&cubes[7]);
	new_cube_align_check_pattern(&cubes[7].material.pattern, align_checkers);
	new_color(0.2, 0.2, 0.2, &cubes[6].material.ambient);
	cubes[7].material.specular = 0;
	cubes[7].material.diffuse = 0.8;
	multiply_matrices(translation(6, 0, 10, &m[0]), rotation_x(-cos(0.7854), -sin(0.7854), &m[1]), &m[0]);
	multiply_matrices(&m[0], rotation_y(cos(5.4978), sin(5.4978), &m[1]), &m[0]);
	set_transform(&cubes[7], &m[0]);
	objs[0] = cubes[0];
	objs[1] = cubes[1];
	objs[2] = cubes[2];
	objs[3] = cubes[3];
	objs[4] = cubes[4];
	objs[5] = cubes[5];
	objs[6] = cubes[6];
	objs[7] = cubes[7];
}

void	create_scene(t_world *world)
{
	t_shape		s;
	t_shape		floor;
	t_shape		cyl;
	t_shape		cone;
	t_matrix	m[2];
	t_color		colors[5];
	t_shape		light;
	t_color		tmp;
	t_pattern p[2];  

	world->objs = malloc(13 * sizeof(t_shape));
	world->objs_count = 13;
	new_sphere(&s);
	new_uv_checkers_pattern(new_solid_pattern(new_color(0, 0.5, 0, &tmp), &p[0]),
		new_solid_pattern(new_color(1, 1, 1, &tmp), &p[1]), &s.material.pattern);
	s.material.specular = 0.4;
	s.material.shininess = 10;
	s.material.diffuse = 0.6;
	world->objs[0] = s;
	new_plane(&floor);
	new_color(1, 1, 1, &colors[0]);
	new_color(1, 0, 0, &colors[1]);
	new_color(1, 1, 0, &colors[2]);
	new_color(0, 1, 0, &colors[3]);
	new_color(0, 1, 1, &colors[4]);
	// new_uv_align_check_pattern(&floor.material.pattern, colors);
	new_uv_checkers_pattern(new_solid_pattern(new_color(0, 0.5, 0, &tmp), &p[0]),
		new_solid_pattern(new_color(1, 1, 1, &tmp), &p[1]), &floor.material.pattern);
	s.material.specular = 0;
	s.material.diffuse = 0.9;
	set_transform(&floor, translation(0, -2, 0, &floor.transform));
	world->objs[1] = floor;
	new_cylinder(&cyl);
	cyl.cyl.min = 0;
	cyl.cyl.max = 0.5;
	cyl.cyl.closed = true;
	multiply_matrices(translation(-3, -0.5, 0, &m[0]), scaling(1, 3.1415, 1, &m[1]), &m[0]);
	set_transform(&cyl, &m[0]);
	new_uv_checkers_pattern(new_solid_pattern(new_color(0, 0.5, 0, &tmp), &p[0]),
		new_solid_pattern(new_color(1, 1, 1, &tmp), &p[1]), &cyl.material.pattern);
	s.material.specular = 0.6;
	s.material.shininess = 15;
	s.material.diffuse = 0.8;
	world->objs[2] = cyl;
	new_cone(&cone);
	cone.cone.min = 0;
	cone.cone.max = 1;
	cone.cone.closed = true;
	multiply_matrices(translation(3, 0.5, 0, &m[0]), rotation_x(cos(-M_PI), sin(-M_PI), &m[1]), &m[0]);
	set_transform(&cone, &m[0]);
	new_uv_checkers_pattern(new_solid_pattern(new_color(0, 0.5, 0, &tmp), &p[0]),
		new_solid_pattern(new_color(1, 1, 1, &tmp), &p[1]), &cone.material.pattern);
	s.material.specular = 0.6;
	s.material.shininess = 15;
	s.material.diffuse = 0.8;
	world->objs[3] = cone;
	create_cubes(world->objs + 4);
	new_sphere(&light);
	new_color(1.5, 1.5, 1.5, &light.material.color);
	new_color(1, 1, 1, &light.material.ambient);
	light.material.diffuse = 0;
	light.material.specular = 0;
	set_transform(&light, translation(0, 5, 2, &m[0]));
	light.cast_shadow = false;
	world->objs[12] = light;
}

void	create_lights(t_world *world)
{
	t_alight_params	lp;

	world->lights = malloc(1 * sizeof(t_light));
	world->lights_count = 1;
	new_point(-1, 4, 2, &lp.corner);
	new_vector(2, 0, 2, &lp.full_uvec);
	new_vector(0, 2, 2, &lp.full_vvec);
	lp.usteps = 10;
	lp.vsteps = 10;
	new_color(1.5, 1.5, 1.5, &lp.intensity);
	new_area_light(&lp, &world->lights[0]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, M_PI_2);
	new_point(2, 2, -5, &from);
	new_point(1, 1, 0, &to);
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
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Bonus shape mapping");
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
