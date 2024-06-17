#ifndef MATRICES_H
# define MATRICES_H

# include <math.h>
# include <stdarg.h>

# include "libft.h"
# include "tuples.h"

# define MAX 4
# define SIZE 16

typedef struct s_matrix {
	double	mx[MAX][MAX];
	int		size;
}	t_matrix;

typedef struct s_shearing {
	double	p1;
	double	p2;
}	t_shearing;

/* mx.c */
t_matrix	*new_matrix(const double table[MAX][MAX], size_t size, t_matrix *m);
bool		is_eq_mx(t_matrix m1, t_matrix m2);
bool		is_invertible(t_matrix *m);
/* matrix operations 	*/
t_matrix	*multiply_matrices(t_matrix *m1, t_matrix *m2, t_matrix *out);
t_tuple		*multiply_matrix_by_tuple(t_matrix *m, t_tuple *t, t_tuple *out);
t_matrix	*transpose_matrix(t_matrix *m, t_matrix *out);
t_matrix	*inverse_matrix(t_matrix *m, t_matrix *out);
t_matrix	*inverse_matrix(t_matrix *m, t_matrix *out);
/*  matrix attributes */
double		get_determinant(t_matrix *m);
t_matrix	*get_submatrix(t_matrix *m, int *del_row, int *del_col,
				t_matrix *out);
double		get_minor(t_matrix *m, int *row, int *col);
double		get_cofactor(t_matrix *m, int row, int col);
t_matrix	*get_identity_matrix(t_matrix *m);
/* matrix transformations */
t_matrix	*transformations(int length, ...);
t_matrix	*translation(double x, double y, double z, t_matrix *m);
t_matrix	*scaling(double x, double y, double z, t_matrix *m);
t_matrix	*shearing(t_shearing x, t_shearing y, t_shearing z, t_matrix *m);
/* matrix rotations  */
t_matrix	*rotation_x(double cos_rad, double sin_rad, t_matrix *out);
t_matrix	*rotation_y(double cos_rad, double sin_rad, t_matrix *out);
t_matrix	*rotation_z(double cos_rad, double sin_rad, t_matrix *out);

#endif
