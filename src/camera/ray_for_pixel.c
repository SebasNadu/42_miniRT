#include "camera.h"

static void	generate_random_aperture_point(t_camera *camera, t_point *point)
{
	double	angle;
	double	radius;
	double	offset_x;
	double	offset_y;

	angle = rand_dbl() * 2.0 * M_PI;
	radius = camera->aperture_size * sqrt(rand_dbl());
	offset_x = radius * cos(angle);
	offset_y = radius * sin(angle);
	new_vector(offset_x, offset_y, 0, point);
}

static t_ray	*ray_with_depth_of_field(t_camera *camera, t_ray *ray,
		t_point *pixel)
{
	t_point		aperture_point;
	t_point		focal_point;
	t_vector	direction;

	position(ray, camera->focal_length, &focal_point);
	generate_random_aperture_point(camera, &aperture_point);
	add(pixel, &aperture_point, &aperture_point);
	normalize(subtract(&focal_point, &aperture_point, &direction),
		&direction);
	new_ray(&aperture_point, &direction, ray);
	return (ray);
}

t_ray	*ray_for_pixel(t_camera *camera, double xy_offset[2], t_ray *ray)
{
	double		world_x;
	double		world_y;
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	world_x = camera->half_width - xy_offset[0] * camera->pixel_size;
	world_y = camera->half_height - xy_offset[1] * camera->pixel_size;
	new_point(world_x, world_y, -1.0, &pixel);
	multiply_matrix_by_tuple(&camera->inverse, &pixel, &pixel);
	new_point(0, 0, 0, &origin);
	multiply_matrix_by_tuple(&camera->inverse, &origin, &origin);
	normalize(subtract(&pixel, &origin, &direction), &direction);
	new_ray(&origin, &direction, ray);
	if (camera->aperture_size > 0.0)
		ray_with_depth_of_field(camera, ray, &pixel);
	return (ray);
}
