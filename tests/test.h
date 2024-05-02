#ifndef TEST_H
# define TEST_H

# include <criterion/criterion.h>
# include <criterion/new/assert.h>

# include <math.h>

# include "tuples.h"
# include "canvas.h"
# include "matrices.h"
# include "rays.h"
# include "shapes.h"
# include "lights.h"
# include "materials.h"
# include "world.h"
# include "camera.h"

bool	matrix_eq(t_matrix a, t_matrix b);
bool	tuple_eq(t_tuple a, t_tuple b);
bool	color_eq(t_color a, t_color b);
t_world	default_world(void);

#endif
