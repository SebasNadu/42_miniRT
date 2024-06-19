#include "parser.h"

int	main(int argc, char **argv)
{
	t_mini_rt	minirt;
	// t_shape	*s;

	if (parser(argc, argv, &minirt))
		return (1);
	// printf("camera 	pos:       h: %f v: %f fov: %f \n",minirt.camera.hsize, minirt.camera.vsize,  minirt.camera.fov);
    // printf("----- Sphere :     r: %f g: %f b: %f \n", minirt.world.objs[0].material.color.r,minirt.world.objs[0].material.color.g , minirt.world.objs[0].material.color.b);
	// printf("Ambient:           r: %f g: %f b: %f \n", minirt.world.ambient.r, minirt.world.ambient.g, minirt.world.ambient.b);
	// printf("Light rgb:         r: %f g: %f b: %f \n", minirt.world.lights[0].intensity.r, minirt.world.lights[0].intensity.g, minirt.world.lights[0].intensity.b);
	// printf("Light pos:         x: %f y: %f z: %f \n", minirt.world.lights[0].position.x, minirt.world.lights[0].position.y, minirt.world.lights[0].position.z);
	// printf("Sphere :           x: %f y: %f z: %f \n", minirt.world.objs[0].sphere.origin.x, minirt.world.objs[0].sphere.origin.y , minirt.world.objs[0].sphere.origin.z);
	// (void)argc;
	// (void)argv;
	new_canvas(&minirt.canvas, WIDTH, HEIGHT, "Chapter 16");
	// minirt.world = new_world();
	// minirt.world.objs = malloc(sizeof(t_shape));
	// minirt.world.objs_count = 1;
	// s = &minirt.world.objs[0];
	// new_sphere(s);
	t_point from;
    t_point to;
    t_vector up;
	new_camera(&minirt.camera ,WIDTH, HEIGHT, M_PI_2);
	new_point(0, 10, -10, &from);
	new_point(0, 9, -10, &to);
	new_vector(0, 1, 0, &up);
	set_transform_camera(&minirt.camera, view_transform(&from, &to, &up, &minirt.camera.transform));
	// minirt.world.lights = malloc(1 * sizeof(t_light));
	// minirt.world.lights_count = 1;
	// minirt.world.lights[0] = new_light(new_point(-10, 10, -10), new_color(0.9, 0.9, 0.9));
	render(&minirt);
	mlx_image_to_window(minirt.canvas.mlx, minirt.canvas.img, 0, 0);
	mlx_close_hook(minirt.canvas.mlx, &quit, &minirt.canvas);
	mlx_key_hook(minirt.canvas.mlx, &handle_keyhook, &minirt.canvas);
	mlx_loop(minirt.canvas.mlx);
	free_world(&minirt.world);
	mlx_terminate(minirt.canvas.mlx);
	return (0);
}
