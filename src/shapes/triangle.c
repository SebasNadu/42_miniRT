#include "shapes.h"
#include "groups.h"

static t_vector	*normal_at_triangle(t_shape *shape, t_point *local_point,
					t_vector *normal);
static bool		intersect_triangle(t_hit **xs, t_shape *shape, t_ray *r);

t_shape	*new_triangle(t_point *p1, t_point *p2, t_point *p3, t_shape *shape)
{
	new_shape(shape);
	shape->tri.p1 = *p1;
	shape->tri.p2 = *p2;
	shape->tri.p3 = *p3;
	subtract(p2, p1, &shape->tri.e1);
	subtract(p3, p1, &shape->tri.e2);
	normalize(cross(&shape->tri.e2, &shape->tri.e1, &shape->tri.n1),
		&shape->tri.n1);
	shape->tri.n2 = shape->tri.n1;
	shape->tri.n3 = shape->tri.n1;
	shape->tri.u = 0.0;
	shape->tri.v = 0.0;
	shape->normal_at = normal_at_triangle;
	shape->intersect_fn = intersect_triangle;
	shape->bounds_of = triangle_bounds;
	return (shape);
}

t_shape	*new_smooth_triangle(t_point v[3], t_vector n[3], t_shape *shape)
{
	new_shape(shape);
	shape->tri.p1 = v[0];
	shape->tri.p2 = v[1];
	shape->tri.p3 = v[2];
	subtract(&v[1], &v[0], &shape->tri.e1);
	subtract(&v[2], &v[0], &shape->tri.e2);
	shape->tri.n1 = n[0];
	shape->tri.n2 = n[1];
	shape->tri.n3 = n[2];
	shape->tri.u = 0.0;
	shape->tri.v = 0.0;
	shape->normal_at = normal_at_triangle;
	shape->intersect_fn = intersect_triangle;
	shape->bounds_of = triangle_bounds;
	return (shape);
}

static t_vector	*normal_at_triangle(t_shape *shape, t_point *local_point,
					t_vector *normal)
{
	t_tuple	tmp[2];

	(void)local_point;
	return (add(add(multiply(&shape->tri.n2, shape->tri.u, &tmp[0]),
				multiply(&shape->tri.n3, shape->tri.v, &tmp[1]), &tmp[0]),
			multiply(&shape->tri.n1, 1.0 - shape->tri.u - shape->tri.v,
				&tmp[1]), normal));
}

static bool	intersect_triangle(t_hit **xs, t_shape *shape, t_ray *r)
{
	t_intersect_tri_params	p;

	cross(&r->direction, &shape->tri.e2, &p.dir_cross_e2);
	p.det = dot(&shape->tri.e1, &p.dir_cross_e2);
	if (fabs(p.det) < EPSILON)
		return (false);
	p.f = 1.0 / p.det;
	subtract(&r->origin, &shape->tri.p1, &p.p1_to_origin);
	p.u = p.f * dot(&p.p1_to_origin, &p.dir_cross_e2);
	if (p.u < 0 || p.u > 1)
		return (false);
	cross(&p.p1_to_origin, &shape->tri.e1, &p.origin_cross_e1);
	p.v = p.f * dot(&r->direction, &p.origin_cross_e1);
	if (p.v < 0 || p.u + p.v > 1)
		return (false);
	p.t = p.f * dot(&shape->tri.e2, &p.origin_cross_e1);
	shape->tri.u = p.u;
	shape->tri.v = p.v;
	insert_intersection(xs, intersection(p.t, shape));
	return (true);
}
