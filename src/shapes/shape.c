#include "shapes.h"

t_shape	*new_shape(t_shape *shape)
{
	get_identity_matrix(&shape->transform);
	get_identity_matrix(&shape->inverse);
	get_identity_matrix(&shape->transpose);
	new_material(&shape->material);
	shape->cast_shadow = true;
	shape->parent = NULL;
	shape->is_bounds_precal = false;
	shape->is_group = false;
	shape->next = NULL;
	shape->is_csg = false;
	return (shape);
}

void	set_transform(t_shape *shape, t_matrix *transform)
{
	t_shape	*parent;

	shape->transform = *transform;
	inverse_matrix(transform, &shape->inverse);
	transpose_matrix(&shape->inverse, &shape->transpose);
	if (shape->is_bounds_precal)
		shape->is_bounds_precal = false;
	parent = shape->parent;
	while (parent)
	{
		parent->is_bounds_precal = false;
		parent = parent->parent;
	}
}

t_point	world_to_object(t_shape *shape, t_point world_point)
{
	if (shape->parent)
		world_point = world_to_object(shape->parent, world_point);
	multiply_matrix_by_tuple(&shape->inverse, &world_point, &world_point);
	return (world_point);
}

t_vector	normal_to_world(t_shape *shape, t_vector *object_normal)
{
	multiply_matrix_by_tuple(&shape->transpose, object_normal, object_normal);
	object_normal->w = 0.0;
	normalize(object_normal, object_normal);
	if (shape->parent)
		*object_normal = normal_to_world(shape->parent, object_normal);
	return (*object_normal);
}

t_vector	*normal_at(t_shape *shape, t_point *world_point,
		t_vector *world_normal)
{
	t_point		object_point;
	t_vector	object_normal;

	object_point = world_to_object(shape, *world_point);
	shape->normal_at(shape, &object_point, &object_normal);
	*world_normal = normal_to_world(shape, &object_normal);
	return (world_normal);
}
