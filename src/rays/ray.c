#include "rays.h"

t_ray	*new_ray(t_point	*origin, t_point	*direction, t_ray *out)
{
	out->origin = *origin;
	out->direction = *direction;
	return (out);
}

t_point	*position(t_ray *r, double t, t_point *pos)
{
	return (add(&r->origin, multiply(&r->direction, t, pos), pos));
}

t_ray	*transform(t_ray *r, t_matrix *m, t_ray *out)
{
	multiply_matrix_by_tuple(m, &r->origin, &out->origin);
	multiply_matrix_by_tuple(m, &r->direction, &out->direction);
	return (out);
}
