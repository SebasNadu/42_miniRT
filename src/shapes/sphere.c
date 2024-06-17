#include "shapes.h"
#include "groups.h"

static bool		intersect_sphere(t_hit **xs, t_shape *shape, t_ray *r);
static t_vector	*normal_at_sphere(t_shape *sphere, t_point *local_point,
					t_vector *normal);

t_shape	*new_sphere(t_shape *shape)
{
	new_shape(shape);
	new_point(0, 0, 0, &shape->sphere.origin);
	shape->sphere.radius = 1.0;
	shape->material.diffuse = 0.9;
	shape->material.specular = 0.6;
	shape->intersect_fn = intersect_sphere;
	shape->normal_at = normal_at_sphere;
	shape->bounds_of = sphere_bounds;
	shape->material.pattern.texture_map.uv_mapping_fn = spherical_map;
	shape->material.pattern.texture_map.uv_pattern.width = 20;
	shape->material.pattern.texture_map.uv_pattern.height = 10;
	return (shape);
}

t_shape	*new_glass_sphere(t_shape *shape)
{
	new_sphere(shape);
	shape->material.transparency = 1.0;
	shape->material.refractive_index = GLASS;
	return (shape);
}

static bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray *r)
{
	t_intersect_params	p;
	t_vector			sphere_to_ray;
	double				sqrt_d;

	subtract(&r->origin, &shape->sphere.origin, &sphere_to_ray);
	p.a = dot(&r->direction, &r->direction);
	p.b = 2.0 * dot(&r->direction, &sphere_to_ray);
	p.c = dot(&sphere_to_ray, &sphere_to_ray) - 1.0;
	p.discriminant = (p.b * p.b) - (4.0 * p.a * p.c);
	if (p.discriminant < 0)
		return (false);
	sqrt_d = sqrt(p.discriminant);
	p.t1 = (-p.b - sqrt_d) / (2.0 * p.a);
	p.t2 = (-p.b + sqrt_d) / (2.0 * p.a);
	insert_intersection(xs, intersection(p.t1, shape));
	if (p.discriminant != 0)
		insert_intersection(xs, intersection(p.t2, shape));
	return (true);
}

static t_vector	*normal_at_sphere(t_shape *sphere, t_point *local_point,
					t_vector *normal)
{
	(void)sphere;
	return (subtract(local_point, &sphere->sphere.origin, normal));
}
