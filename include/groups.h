#ifndef GROUPS_H
# define GROUPS_H

# include "shapes.h"
# include "world.h"

// Group
t_shape		*new_group(t_shape *shape);
// Group utils
void		add_child(t_shape *group, t_shape *child);
void		insert_node(t_shape **root, t_shape *child);
void		get_group_bounds(t_shape *root, t_bounds *b);
void		intersect_group_shapes(t_shape **root, t_hit **xs, t_ray *r);
void		btree_insert(t_shape **root, t_shape *shape);
// Bounds
t_bounds	*new_bounds(t_point *min, t_point *max, t_bounds *new_bounds);
bool		intersect_bounds(t_bounds *b, t_ray *r);
void		get_bounds(t_shape *s, t_bounds *new_bounds);
double		bounds_volume(t_bounds *bounds);
// Local bounds
void		sphere_bounds(t_shape *shape);
void		cylinder_bounds(t_shape *shape);
void		cone_bounds(t_shape *shape);
void		cube_bounds(t_shape *shape);
void		plane_bounds(t_shape *shape);
void		triangle_bounds(t_shape *shape);
// Bounding_boxes.c
bool		box_contains_point(t_bounds *box, t_point *p);
bool		box_contains_box(t_bounds *box, t_bounds *box2);
void		add_point_to_bounds(t_bounds **box, t_point *p);
// bvh.c
void		create_bvh(t_world *world);
void		split_bounds(t_bounds s_box[2]);
void		partition_children(t_shape *group, t_shape **left, t_shape **right);
void		make_subgroup(t_shape *group, t_shape **container);
void		divide_groups(t_shape *group, int threshold);

#endif
