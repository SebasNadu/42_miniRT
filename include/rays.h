#ifndef RAYS_H
# define RAYS_H

# include "matrices.h"

typedef struct s_ray {
	t_point		origin;
	t_vector	direction;
}	t_ray;

t_ray	*new_ray(t_point	*origin, t_point	*direction, t_ray *out);
t_point	*position(t_ray *r, double t, t_point *pos);
t_ray	*transform(t_ray *r, t_matrix *m, t_ray *out);

#endif
