#include "patterns.h"

double	*spherical_map(t_point *point, double uv[2])
{
	double		theta;
	t_vector	vec;
	double		radius;
	double		phi;
	double		raw_u;

	theta = atan2(point->x, point->z);
	new_vector(point->x, point->y, point->z, &vec);
	radius = sqrt(magnitude_squared(&vec));
	phi = acos(point->y / radius);
	raw_u = theta / (2 * M_PI);
	uv[0] = 1 - (raw_u + 0.5);
	uv[1] = 1 - phi / M_PI;
	return (uv);
}

double	*planar_map(t_point *point, double uv[2])
{
	uv[1] = fmod(point->z, 1);
	uv[0] = fmod(point->x, 1);
	if (uv[1] < 0)
		uv[1] = 1 + uv[1];
	if (uv[0] < 0)
		uv[0] = 1 + uv[0];
	return (uv);
}

double	*cylindrical_map(t_point *point, double uv[2])
{
	double	theta;
	double	raw_u;

	theta = atan2(point->x, point->z);
	raw_u = theta / (2 * M_PI);
	uv[0] = 1 - (raw_u + 0.5);
	uv[1] = fmod(point->y, 1);
	if (uv[1] < 0)
		uv[1] = 1 + uv[1];
	return (uv);
}
