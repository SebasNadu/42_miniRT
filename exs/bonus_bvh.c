#include "shapes.h"
#include "canvas.h"
#include "materials.h"
#include "patterns.h"
#include "groups.h"
#include "obj_loader.h"

#define WIDTH	1000
#define HEIGHT	400

void	create_bbox(t_shape *bbox)
{
	t_matrix	m[2];

	new_cube(bbox);
	bbox->cast_shadow = false;
	set_transform(bbox, multiply_matrices(translation(0, 0.8, 0, &m[0]), scaling(1, 0.7, 0.4, &m[1]), &m[0]));
}

void	create_pedestal(t_shape *pedestal)
{
	new_cylinder(pedestal);
	pedestal->cyl.min = -0.15;
	pedestal->cyl.max = 0;
	pedestal->cyl.closed = true;
	new_color(0.2, 0.2, 0.2, &pedestal->material.color);
	new_color(0, 0, 0, &pedestal->material.ambient);
	pedestal->material.diffuse = 0.8;
	pedestal->material.specular = 0;
	pedestal->material.reflective = 0.2;
}

void	create_dragon(t_shape *dragon, size_t	*obj_count)
{
	t_obj_loader	loader;
	t_matrix		m[2];

	new_obj_loader(&loader, dragon);
	parse_obj_file(&loader, "../obj_files/dragon.obj");
	*obj_count += loader.t_count + loader.gp_count;
	multiply_matrices(translation(0, 0.1217, 0, &m[0]), scaling(0.268, 0.268, 0.268, &m[1]), &m[0]);
	set_transform(dragon, &m[0]);
}

void	create_scene(t_world *world)
{
	t_shape			*tmp;
	t_shape			*tmp2;
	t_matrix		m[2];
	int				obj_i;
	int				obj_in_i;

	world->objs = malloc(6 * sizeof(t_shape));
	world->objs_count = 6;
	world->objs_inside = malloc(22 * sizeof(t_shape));
	world->objs_inside_count = 22;
	obj_i = 0;
	obj_in_i = 0;
	new_group(&world->objs[obj_i]);
	tmp = &world->objs[obj_i];
	set_transform(tmp, translation(0, 2, 0, &m[0]));
	obj_i++;
	create_pedestal(&world->objs_inside[obj_in_i]);
	add_child(tmp, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	new_group(&world->objs_inside[obj_in_i]);
	tmp2 = &world->objs_inside[obj_in_i];
	obj_in_i++;
	create_dragon(&world->objs_inside[obj_in_i], &world->objs_ext_count);
	new_color(1, 0, 0.1, &world->objs_inside[obj_in_i].material.color);
	new_color(0.1, 0.1, 0.1, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.6;
	world->objs_inside[obj_in_i].material.specular = 0.3;
	world->objs_inside[obj_in_i].material.shininess = 15;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	create_bbox(&world->objs_inside[obj_in_i]);
	new_color(0, 0, 0, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.4;
	world->objs_inside[obj_in_i].material.specular = 0;
	world->objs_inside[obj_in_i].material.transparency = 0.6;
	world->objs_inside[obj_in_i].material.refractive_index = 1;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	add_child(tmp, tmp2);
	obj_in_i++;
	new_group(&world->objs[obj_i]);
	tmp = &world->objs[obj_i];
	set_transform(tmp, translation(2, 1, -1, &m[0]));
	obj_i++;
	create_pedestal(&world->objs_inside[obj_in_i]);
	add_child(tmp, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	new_group(&world->objs_inside[obj_in_i]);
	tmp2 = &world->objs_inside[obj_in_i];
	set_transform(tmp2, multiply_matrices(rotation_y(cos(4), sin(4), &m[1]), scaling(0.75, 0.75, 0.75, &m[0]), &m[0]));
	obj_in_i++;
	create_dragon(&world->objs_inside[obj_in_i], &world->objs_ext_count);
	new_color(1, 0.5, 0.1, &world->objs_inside[obj_in_i].material.color);
	new_color(0.1, 0.1, 0.1, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.6;
	world->objs_inside[obj_in_i].material.specular = 0.3;
	world->objs_inside[obj_in_i].material.shininess = 15;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	create_bbox(&world->objs_inside[obj_in_i]);
	new_color(0, 0, 0, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.2;
	world->objs_inside[obj_in_i].material.specular = 0;
	world->objs_inside[obj_in_i].material.transparency = 0.8;
	world->objs_inside[obj_in_i].material.refractive_index = 1;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	add_child(tmp, tmp2);
	new_group(&world->objs[obj_i]);
	tmp = &world->objs[obj_i];
	set_transform(tmp, translation(-2, 0.75, -1, &m[0]));
	obj_i++;
	create_pedestal(&world->objs_inside[obj_in_i]);
	add_child(tmp, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	new_group(&world->objs_inside[obj_in_i]);
	tmp2 = &world->objs_inside[obj_in_i];
	set_transform(tmp2, multiply_matrices(rotation_y(cos(-0.4), sin(-0.4), &m[1]), scaling(0.75, 0.75, 0.75, &m[0]), &m[0]));
	obj_in_i++;
	create_dragon(&world->objs_inside[obj_in_i], &world->objs_ext_count);
	new_color(0.9, 0.5, 0.1, &world->objs_inside[obj_in_i].material.color);
	new_color(0.1, 0.1, 0.1, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.6;
	world->objs_inside[obj_in_i].material.specular = 0.3;
	world->objs_inside[obj_in_i].material.shininess = 15;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	create_bbox(&world->objs_inside[obj_in_i]);
	new_color(0, 0, 0, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.2;
	world->objs_inside[obj_in_i].material.specular = 0;
	world->objs_inside[obj_in_i].material.transparency = 0.8;
	world->objs_inside[obj_in_i].material.refractive_index = 1;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	add_child(tmp, tmp2);
	new_group(&world->objs[obj_i]);
	tmp = &world->objs[obj_i];
	set_transform(tmp, translation(-4, 0, -2, &m[0]));
	obj_i++;
	create_pedestal(&world->objs_inside[obj_in_i]);
	add_child(tmp, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	new_group(&world->objs_inside[obj_in_i]);
	tmp2 = &world->objs_inside[obj_in_i];
	set_transform(tmp2, multiply_matrices(rotation_y(cos(-0.2), sin(-0.2), &m[1]), scaling(0.5, 0.5, 0.5, &m[0]), &m[0]));
	obj_in_i++;
	create_dragon(&world->objs_inside[obj_in_i], &world->objs_ext_count);
	new_color(1, 0.9, 0.1, &world->objs_inside[obj_in_i].material.color);
	new_color(0.1, 0.1, 0.1, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.6;
	world->objs_inside[obj_in_i].material.specular = 0.3;
	world->objs_inside[obj_in_i].material.shininess = 15;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	create_bbox(&world->objs_inside[obj_in_i]);
	new_color(0, 0, 0, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.1;
	world->objs_inside[obj_in_i].material.specular = 0;
	world->objs_inside[obj_in_i].material.transparency = 0.9;
	world->objs_inside[obj_in_i].material.refractive_index = 1;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	add_child(tmp, tmp2);
	new_group(&world->objs[obj_i]);
	tmp = &world->objs[obj_i];
	set_transform(tmp, translation(4, 0, -2, &m[0]));
	obj_i++;
	create_pedestal(&world->objs_inside[obj_in_i]);
	add_child(tmp, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	new_group(&world->objs_inside[obj_in_i]);
	tmp2 = &world->objs_inside[obj_in_i];
	set_transform(tmp2, multiply_matrices(rotation_y(cos(3.3), sin(3.3), &m[1]), scaling(0.5, 0.5, 0.5, &m[0]), &m[0]));
	obj_in_i++;
	create_dragon(&world->objs_inside[obj_in_i], &world->objs_ext_count);
	new_color(0.9, 1, 0.1, &world->objs_inside[obj_in_i].material.color);
	new_color(0.1, 0.1, 0.1, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.6;
	world->objs_inside[obj_in_i].material.specular = 0.3;
	world->objs_inside[obj_in_i].material.shininess = 15;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	create_bbox(&world->objs_inside[obj_in_i]);
	new_color(0, 0, 0, &world->objs_inside[obj_in_i].material.ambient);
	world->objs_inside[obj_in_i].material.diffuse = 0.1;
	world->objs_inside[obj_in_i].material.specular = 0;
	world->objs_inside[obj_in_i].material.transparency = 0.9;
	world->objs_inside[obj_in_i].material.refractive_index = 1;
	add_child(tmp2, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	add_child(tmp, tmp2);
	new_group(&world->objs[obj_i]);
	tmp = &world->objs[obj_i];
	set_transform(tmp, translation(0, 0.5, -4, &m[0]));
	obj_i++;
	create_pedestal(&world->objs_inside[obj_in_i]);
	add_child(tmp, &world->objs_inside[obj_in_i]);
	obj_in_i++;
	create_dragon(&world->objs_inside[obj_in_i], &world->objs_ext_count);
	tmp2 = &world->objs_inside[obj_in_i];
	new_color(0.95, 0.95, 0.95, &tmp2->material.color);
	new_color(0.1, 0.1, 0.1, &tmp2->material.ambient);
	tmp2->material.diffuse = 0.6;
	tmp2->material.specular = 0.3;
	tmp2->material.shininess = 15;
	set_transform(tmp2, multiply_matrices(rotation_y(cos(M_PI), sin(M_PI), &m[1]), scaling(0.25, 0.25, 0.25, &m[0]), &m[0]));
	add_child(tmp, tmp2);
	obj_i++;
}

void	create_lights(t_world *world)
{
	t_point		p;
	t_color		c;

	world->lights = malloc(4 * sizeof(t_light));
	world->lights_count = 4;
	new_point(-10, 100, -100, &p);
	new_color(1, 1, 1, &c);
	new_light(&p, &c, &world->lights[0]);
	new_point(0, 100, 0, &p);
	new_color(0.1, 0.1, 0.1, &c);
	new_light(&p, &c, &world->lights[1]);
	new_point(100, 10, -25, &p);
	new_color(0.2, 0.2, 0.2, &c);
	new_light(&p, &c, &world->lights[2]);
	new_point(-100, 10, -25, &p);
	new_color(0.2, 0.2, 0.2, &c);
	new_light(&p, &c, &world->lights[3]);
}

void	create_camera(t_camera *camera)
{
	t_point		from;
	t_point		to;
	t_vector	up;

	new_camera(camera, WIDTH, HEIGHT, 1.2);
	new_point(0, 2.5, -10, &from);
	new_point(0, 1, 0, &to);
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
	new_canvas(&rt.canvas, WIDTH, HEIGHT, "Bonus BVH");
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
