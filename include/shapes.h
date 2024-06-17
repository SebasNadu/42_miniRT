#ifndef SHAPES_H
# define SHAPES_H

# include "rays.h"
# include "materials.h"
# include "patterns.h"
# include "utils.h"
// # include "lights.h"

# define MAX_NODES	512

typedef struct s_sphere {
	t_point	origin;
	double	radius;
}	t_sphere;

typedef struct s_plane {
	t_point	origin;
}	t_plane;

typedef struct s_cube {
	t_point	origin;
}	t_cube;

typedef struct s_cylinder {
	t_point	origin;
	double	min;
	double	max;
	bool	closed;
}	t_cylinder;

typedef struct s_cone {
	t_point	origin;
	double	min;
	double	max;
	bool	closed;
}	t_cone;

typedef struct s_bounds
{
	t_point	min;
	t_point	max;
}	t_bounds;

typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

typedef struct s_triangle
{
	t_point		p1;
	t_point		p2;
	t_point		p3;
	t_vector	e1;
	t_vector	e2;
	t_vector	n1;
	t_vector	n2;
	t_vector	n3;
	double		u;
	double		v;
}	t_triangle;

typedef struct s_hit	t_hit;
typedef struct s_shape	t_shape;
typedef bool			(*t_intersect_fn)(t_hit **, t_shape *, t_ray *);
typedef t_vector		*(*t_normal_fn)(t_shape *, t_point *, t_vector *);
typedef void			(*t_bounds_fn)(t_shape *);

typedef enum e_operation
{
	DIFFERENCE,
	INTERSECT,
	UNION,
}	t_operation;

typedef struct s_csg
{
	t_operation	op;
	t_shape		*left;
	t_shape		*right;
}	t_csg;

typedef struct s_group
{
	int		count;
	t_shape	*root;
}	t_group;

typedef struct s_shape {
	union {
		t_sphere	sphere;
		t_plane		plane;
		t_cube		cube;
		t_cylinder	cyl;
		t_cone		cone;
		t_triangle	tri;
		t_csg		csg;
		t_group		group;
	};
	t_intersect_fn	intersect_fn;
	t_normal_fn		normal_at;
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transpose;
	t_material		material;
	bool			cast_shadow;
	t_shape			*parent;
	t_bounds_fn		bounds_of;
	bool			is_bounds_precal;
	t_bounds		bounds;
	bool			is_group;
	t_shape			*next;
	bool			is_csg;
}	t_shape;

typedef struct s_hit {
	double	t;
	t_shape	*obj;
	t_hit	*next;
}	t_hit;

typedef struct s_intersect_params
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	discriminant;
}	t_intersect_params;

typedef struct s_intersect_tri_params
{
	t_vector	dir_cross_e2;
	double		det;
	double		f;
	t_point		p1_to_origin;
	double		u;
	t_vector	origin_cross_e1;
	double		v;
	double		t;
}	t_intersect_tri_params;

// Shapes
t_shape		*new_shape(t_shape *shape);
void		set_transform(t_shape *shape, t_matrix *transform);
t_vector	*normal_at(t_shape *shape, t_point *world_point,
				t_vector *world_normal);
// Groups checks
t_point		world_to_object(t_shape *shape, t_point world_point);
t_vector	normal_to_world(t_shape *shape, t_vector *object_normal);
// Sphere Shape
t_shape		*new_sphere(t_shape *shape);
t_shape		*new_glass_sphere(t_shape *shape);
// Plane Shape
t_shape		*new_plane(t_shape *shape);
// Cube Shape
t_shape		*new_cube(t_shape *shape);
// Cylinder Shape
t_shape		*new_cylinder(t_shape *shape);
// Cone Shape
t_shape		*new_cone(t_shape *shape);
// Triangle Shape
t_shape		*new_triangle(t_point *p1, t_point *p2, t_point *p3,
				t_shape *shape);
t_shape		*new_smooth_triangle(t_point v[3], t_vector n[3], t_shape *shape);
// CSG Shape
t_shape		*new_csg(t_operation operation, t_shape *left, t_shape *right,
				t_shape *csg);
bool		intersect_allowed(t_operation op, bool lhit, bool inl, bool inr);
t_hit		*filter_intersections(t_hit *xs, t_shape *csg, t_hit **result);
void		get_csg_bounds(t_shape *current, t_bounds *b);
void		merge_intersections(t_hit **all_xs, t_hit *new_xs);
// discriminants
void		cone_discriminant(t_ray *ray, t_intersect_params *p);
void		cylinder_discriminant(t_ray *ray, t_intersect_params *p);
// Intersections general
void		intersect(t_hit **xs, t_shape *s, t_ray *r);
t_hit		*intersection(double t, t_shape	*shape);
void		insert_intersection(t_hit **xs, t_hit *hit);
int			intersect_count(t_hit	*xs);
t_hit		*hit(t_hit *xs);
// pattern.c
t_color		pattern_at_shape(t_pattern *pattern, t_shape *shape,
				t_point *world_point);

#endif
