#ifndef CAMERA_H
# define CAMERA_H

# include "tuples.h"
# include "matrices.h"
# include "rays.h"
# include "utils.h"

# define BASE_CAMERA_SAMPLES	4
# define MAX_CAMERA_SAMPLES	16

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		fov;
	double		half_width;
	double		half_height;
	double		pixel_size;
	t_matrix	transform;
	t_matrix	inverse;
	double		aperture_size;
	double		focal_length;
	int			samples;
	bool		supersampling;
	double		color_variance_limit;
}	t_camera;

// View transform
t_matrix	*view_transform(t_point *from, t_point *to, t_vector *up,
				t_matrix *out);
// Camera
t_camera	*new_camera(t_camera *camera, double hsize, double vsize,
				double fov);
// t_ray		*ray_for_pixel(t_camera *camera, double xy[2], t_ray *ray);
t_ray		*ray_for_pixel(t_camera *camera, double xy_offset[2], t_ray *ray);
void		set_transform_camera(t_camera *camera, t_matrix *transform);
t_matrix	*view_transform_with_direction(t_point *from, t_vector *direction,
				t_vector *up, t_matrix *out);

#endif
