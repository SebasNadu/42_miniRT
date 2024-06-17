#include "patterns.h"

t_cube_face	face_from_point(t_point *point)
{
	double	abs_x;
	double	abs_y;
	double	abs_z;
	double	coord; 

	abs_x = fabs(point->x);
	abs_y = fabs(point->y);
	abs_z = fabs(point->z);
	coord = ft_max(abs_x, abs_y, abs_z);
	if (coord == point->x)
		return (RIGHT);
	if (coord == -point->x)
		return (LEFT);
	if (coord == point->y)
		return (UP);
	if (coord == -point->y)
		return (DOWN);
	if (coord == point->z)
		return (FRONT);
	return (BACK);
}

double	*cube_map(t_point *point, double face_uv[3])
{
	if (face_uv[0] == LEFT)
		cube_uv_left(point, &face_uv[1]);
	else if (face_uv[0] == FRONT)
		cube_uv_front(point, &face_uv[1]);
	else if (face_uv[0] == RIGHT)
		cube_uv_right(point, &face_uv[1]);
	else if (face_uv[0] == BACK)
		cube_uv_back(point, &face_uv[1]);
	else if (face_uv[0] == UP)
		cube_uv_up(point, &face_uv[1]);
	else
		cube_uv_down(point, &face_uv[1]);
	return (face_uv);
}

double	*cube_uv_left(t_point *point, double uv[2])
{
	uv[0] = fmod(point->z + 1, 2) * 0.5; 
	if (uv[0] < 0)
		uv[0] += 0.5;
	uv[1] = fmod(point->y + 1, 2) * 0.5;
	if (uv[1] < 0)
		uv[1] += 0.5;
	return (uv);
}

double	*cube_uv_front(t_point *point, double uv[2])
{
	uv[0] = fmod(point->x + 1, 2) * 0.5; 
	if (uv[0] < 0)
		uv[0] += 0.5;
	uv[1] = fmod(point->y + 1, 2) * 0.5;
	if (uv[1] < 0)
		uv[1] += 0.5;
	return (uv);
}

double	*cube_uv_right(t_point *point, double uv[2])
{
	uv[0] = fmod(1 - point->z, 2) * 0.5; 
	if (uv[0] < 0)
		uv[0] += 0.5;
	uv[1] = fmod(point->y + 1, 2) * 0.5;
	if (uv[1] < 0)
		uv[1] += 0.5;
	return (uv);
}
