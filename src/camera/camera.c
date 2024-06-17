#include "camera.h"

t_camera	*new_camera(t_camera *camera, double hsize, double vsize,
		double fov)
{
	double		aspect;
	double		half_view;

	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	get_identity_matrix(&camera->transform);
	camera->inverse = camera->transform;
	half_view = tan(camera->fov / 2.0);
	aspect = hsize / vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2.0) / hsize;
	return (camera);
}

t_ray	*ray_for_pixel(t_camera *camera, double px, double py, t_ray *ray)
{
	double		world_x;
	double		world_y;
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	world_x = camera->half_width - ((px + 0.5) * camera->pixel_size);
	world_y = camera->half_height - ((py + 0.5) * camera->pixel_size);
	new_point(world_x, world_y, -1.0, &pixel);
	multiply_matrix_by_tuple(&camera->inverse, &pixel, &pixel);
	new_point(0, 0, 0, &origin);
	multiply_matrix_by_tuple(&camera->inverse, &origin, &origin);
	normalize(subtract(&pixel, &origin, &direction), &direction);
	return (new_ray(&origin, &direction, ray));
}

void	set_transform_camera(t_camera *camera, t_matrix *transform)
{
	inverse_matrix(transform, &camera->inverse);
}
