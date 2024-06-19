#include "camera.h"

static void	set_half_sizes(t_camera *camera, double *hsize, double *vsize)
{
	double	aspect;
	double	half_view;

	half_view = tan(camera->fov / 2.0);
	aspect = *hsize / *vsize;
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
}

t_camera	*new_camera(t_camera *camera, double hsize, double vsize,
		double fov)
{
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	set_half_sizes(camera, &hsize, &vsize);
	camera->pixel_size = (camera->half_width * 2.0) / hsize;
	get_identity_matrix(&camera->transform);
	camera->inverse = camera->transform;
	camera->aperture_size = 0.0;
	camera->focal_length = 1.0;
	camera->samples = 32;
	camera->supersampling = false;
	camera->color_variance_limit = 0.01;
	return (camera);
}

void	set_transform_camera(t_camera *camera, t_matrix *transform)
{
	camera->transform = *transform;
	inverse_matrix(transform, &camera->inverse);
}
