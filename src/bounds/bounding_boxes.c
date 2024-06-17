#include "groups.h"

bool	box_contains_point(t_bounds *box, t_point *p)
{
	return (p->x >= box->min.x && p->x <= box->max.x
		&& p->y >= box->min.y && p->y <= box->max.y
		&& p->z >= box->min.z && p->z <= box->max.z);
}

bool	box_contains_box(t_bounds *box, t_bounds *box2)
{
	return (box_contains_point(box, &box2->min)
		&& box_contains_point(box, &box2->max));
}

void	add_point_to_bounds(t_bounds **box, t_point *p)
{
	if (p->x < (*box)->min.x)
		(*box)->min.x = p->x;
	if (p->y < (*box)->min.y)
		(*box)->min.y = p->y;
	if (p->z < (*box)->min.z)
		(*box)->min.z = p->z;
	if (p->x > (*box)->max.x)
		(*box)->max.x = p->x;
	if (p->y > (*box)->max.y)
		(*box)->max.y = p->y;
	if (p->z > (*box)->max.z)
		(*box)->max.z = p->z;
}
