#include "shapes.h"
#include "groups.h"

static bool	is_left_hit(t_shape *left, t_shape *shape);
static bool	is_group_hit(t_shape **root, t_shape *shape);

bool	intersect_allowed(t_operation op, bool lhit, bool inl, bool inr)
{
	if (op == UNION)
		return ((lhit && !inr) || (!lhit && !inl));
	else if (op == INTERSECT)
		return ((lhit && inr) || (!lhit && inl));
	else if (op == DIFFERENCE)
		return ((lhit && !inr) || (!lhit && inl));
	return (false);
}

static bool	is_group_hit(t_shape **root, t_shape *shape)
{
	t_shape	*tmp;

	tmp = *root;
	while (tmp)
	{
		if (tmp == shape)
			return (true);
		if (tmp->is_csg)
		{
			if (is_left_hit(tmp->csg.left, shape))
				return (true);
			if (is_left_hit(tmp->csg.right, shape))
				return (true);
		}
		if (tmp->is_group && is_group_hit(&tmp->group.root, shape))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static bool	is_left_hit(t_shape *left, t_shape *shape)
{
	if (left == shape)
		return (true);
	if (left->is_csg)
	{
		if (is_left_hit(left->csg.left, shape))
			return (true);
		if (is_left_hit(left->csg.right, shape))
			return (true);
	}
	if (left->is_group && is_group_hit(&left->group.root, shape))
		return (true);
	return (false);
}

t_hit	*filter_intersections(t_hit *xs, t_shape *csg, t_hit **result)
{
	bool	inl;
	bool	inr;
	bool	lhit;

	inl = false;
	inr = false;
	while (xs)
	{
		lhit = is_left_hit(csg->csg.left, xs->obj);
		if (intersect_allowed(csg->csg.op, lhit, inl, inr))
			insert_intersection(result, intersection(xs->t, xs->obj));
		xs = xs->next;
		if (lhit)
			inl = !inl;
		else
			inr = !inr;
	}
	return (*result);
}

void	get_csg_bounds(t_shape *current, t_bounds *b)
{
	if (current)
	{
		if (current->is_csg)
		{
			get_csg_bounds(current->csg.left, b);
			get_csg_bounds(current->csg.right, b);
		}
		if (current->is_group)
			get_group_bounds(current->group.root, b);
		if (!current->is_bounds_precal)
			current->bounds_of(current);
		if (current->bounds.min.x < b->min.x)
			b->min.x = current->bounds.min.x;
		if (current->bounds.min.y < b->min.y)
			b->min.y = current->bounds.min.y;
		if (current->bounds.min.z < b->min.z)
			b->min.z = current->bounds.min.z;
		if (current->bounds.max.x > b->max.x)
			b->max.x = current->bounds.max.x;
		if (current->bounds.max.y > b->max.y)
			b->max.y = current->bounds.max.y;
		if (current->bounds.max.z > b->max.z)
			b->max.z = current->bounds.max.z;
	}
}
