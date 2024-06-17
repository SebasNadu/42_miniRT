#include "tuples.h"
#include "utils.h"

double	magnitude_squared(t_vector *a)
{
	return (
		a->x * a->x
		+ a->y * a->y
		+ a->z * a->z
		+ a->w * a->w
	);
}

t_vector	*normalize(t_vector *a, t_vector *out)
{
	double	magnitude;
	double	inverse_magnitude;

	magnitude = sqrt(magnitude_squared(a));
	if (eq_dbl(0, magnitude))
	{
		*out = (t_vector){0, 0, 0, 0};
		return (out);
	}
	inverse_magnitude = 1.0 / magnitude;
	out->x = a->x * inverse_magnitude;
	out->y = a->y * inverse_magnitude;
	out->z = a->z * inverse_magnitude;
	out->w = a->w * inverse_magnitude;
	return (out);
}

double	dot(t_vector *a, t_vector *b)
{
	return (
		a->x * b->x
		+ a->y * b->y
		+ a->z * b->z
		+ a->w * b->w
	);
}

t_vector	*cross(t_vector *a, t_vector *b, t_vector *out)
{
	out->x = a->y * b->z - a->z * b->y;
	out->y = a->z * b->x - a->x * b->z;
	out->z = a->x * b->y - a->y * b->x;
	out->w = 0;
	return (out);
}

t_tuple	*reflect(t_vector *in, t_vector *normal, t_tuple *out)
{
	subtract(in, multiply(normal, 2.0 * dot(in, normal), out), out);
	return (out);
}
