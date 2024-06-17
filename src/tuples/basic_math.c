#include "tuples.h"

t_tuple	*add(t_tuple *t1, t_tuple *t2, t_tuple *res)
{
	res->x = t1->x + t2->x;
	res->y = t1->y + t2->y;
	res->z = t1->z + t2->z;
	res->w = t1->w + t2->w;
	return (res);
}

t_tuple	*subtract(t_tuple *t1, t_tuple *t2, t_tuple *res)
{
	res->x = t1->x - t2->x;
	res->y = t1->y - t2->y;
	res->z = t1->z - t2->z;
	res->w = t1->w - t2->w;
	return (res);
}

t_tuple	*negate(t_tuple *t, t_tuple *res)
{
	res->x = -t->x;
	res->y = -t->y;
	res->z = -t->z;
	res->w = -t->w;
	return (res);
}

t_tuple	*multiply(t_tuple *t, double scalar, t_tuple *res)
{
	if (scalar == 0)
		*res = (t_tuple){0, 0, 0, 0};
	else if (scalar == 1)
		*res = *t;
	else
	{
		res->x = t->x * scalar;
		res->y = t->y * scalar;
		res->z = t->z * scalar;
		res->w = t->w * scalar;
	}
	return (res);
}

t_tuple	*divide(t_tuple *t, double scalar, t_tuple *res)
{
	double	inverse_scalar;

	if (scalar == 0)
		*res = (t_tuple){0, 0, 0, 0};
	else if (scalar == 1)
		*res = *t;
	else
	{
		inverse_scalar = 1.0 / scalar;
		res->x = t->x * inverse_scalar;
		res->y = t->y * inverse_scalar;
		res->z = t->z * inverse_scalar;
		res->w = t->w * inverse_scalar;
	}
	return (res);
}
