#include "shapes.h"

void	intersect(t_hit **xs, t_shape *s, t_ray *r)
{
	t_ray	local_ray;

	transform(r, &s->inverse, &local_ray);
	s->intersect_fn(xs, s, &local_ray);
}

/*  To increase performance, we keep an array of MAX_NODES intersections
 *  that we can use to build up the list. Also to avoid overflows use
 *  modulo MAX_NODES, to improve the performance it use a bit mask instead
 *  of modulo. MAX_NODES should be a power of 2. */
t_hit	*intersection(double t, t_shape	*shape)
{
	static t_hit	pool[MAX_NODES];
	static size_t	index = 0;
	t_hit			*hit;

	hit = &pool[index++];
	if (index >= MAX_NODES)
		index = 0;
	hit->t = t;
	hit->obj = shape;
	hit->next = NULL;
	return (hit);
}

void	insert_intersection(t_hit **xs, t_hit *hit)
{
	t_hit	**current;

	if (*xs == NULL)
		*xs = hit;
	else
	{
		current = xs;
		while (*current && (*current)->t < hit->t)
			current = &((*current)->next);
		hit->next = *current;
		*current = hit;
	}
}

int	intersect_count(t_hit	*xs)
{
	int	count;

	count = 0;
	while (xs)
	{
		count++;
		xs = xs->next;
	}
	return (count);
}

t_hit	*hit(t_hit *xs)
{
	while (xs && xs->t < EPSILON)
		xs = xs->next;
	return (xs);
}
