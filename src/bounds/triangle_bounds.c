#include "groups.h"

static void	get_triangle_bounds(t_shape *shape)
{
	if (shape->tri.p2.x < shape->bounds.min.x)
		shape->bounds.min.x = shape->tri.p2.x;
	if (shape->tri.p2.y < shape->bounds.min.y)
		shape->bounds.min.y = shape->tri.p2.y;
	if (shape->tri.p2.z < shape->bounds.min.z)
		shape->bounds.min.z = shape->tri.p2.z;
	if (shape->tri.p2.x > shape->bounds.max.x)
		shape->bounds.max.x = shape->tri.p2.x;
	if (shape->tri.p2.y > shape->bounds.max.y)
		shape->bounds.max.y = shape->tri.p2.y;
	if (shape->tri.p2.z > shape->bounds.max.z)
		shape->bounds.max.z = shape->tri.p2.z;
	if (shape->tri.p3.x < shape->bounds.min.x)
		shape->bounds.min.x = shape->tri.p3.x;
	if (shape->tri.p3.y < shape->bounds.min.y)
		shape->bounds.min.y = shape->tri.p3.y;
	if (shape->tri.p3.z < shape->bounds.min.z)
		shape->bounds.min.z = shape->tri.p3.z;
	if (shape->tri.p3.x > shape->bounds.max.x)
		shape->bounds.max.x = shape->tri.p3.x;
	if (shape->tri.p3.y > shape->bounds.max.y)
		shape->bounds.max.y = shape->tri.p3.y;
	if (shape->tri.p3.z > shape->bounds.max.z)
		shape->bounds.max.z = shape->tri.p3.z;
}

void	triangle_bounds(t_shape *shape)
{
	if (!shape)
		return ;
	shape->is_bounds_precal = true;
	new_bounds(&shape->tri.p1, &shape->tri.p1, &shape->bounds);
	get_triangle_bounds(shape);
}
