#ifndef TEST_H
# define TEST_H

# define BLACK new_color(0, 0, 0)
# define WHITE new_color(1, 1, 1)

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
# include "patterns.h"
# include "groups.h"
# include "obj_loader.h"

bool		matrix_eq(t_matrix a, t_matrix b);
bool		tuple_eq(t_tuple a, t_tuple b);
bool		color_eq(t_color a, t_color b);
t_world		default_world(void);
t_pattern	new_test_pattern(void);
void		new_test_shape(t_shape *shape);

#endif
