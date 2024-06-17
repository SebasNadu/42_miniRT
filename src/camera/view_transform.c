#include "camera.h"

t_matrix	*view_transform(t_point *from, t_point *to, t_vector *up,
	t_matrix *out)
{
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix	orientation_transform;

	normalize(subtract(to, from, &forward), &forward);
	cross(&forward, normalize(up, up), &left);
	cross(&left, &forward, &true_up);
	new_matrix((double [MAX][MAX]){
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1}}, 4, &orientation_transform);
	translation(-from->x, -from->y, -from->z, out);
	return (multiply_matrices(&orientation_transform, out, out));
}

t_matrix	*view_transform_with_direction(t_point *from, t_vector *direction,
	t_vector *up, t_matrix *out)
{
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix	orientation_transform;

	normalize(direction, &forward);
	cross(&forward, normalize(up, up), &left);
	cross(&left, &forward, &true_up);
	new_matrix((double [MAX][MAX]){
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1}}, 4, &orientation_transform);
	translation(-from->x, -from->y, -from->z, out);
	return (multiply_matrices(&orientation_transform, out, out));
}
