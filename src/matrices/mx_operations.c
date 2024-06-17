#include "matrices.h"

t_matrix	*multiply_matrices(t_matrix *m1, t_matrix *m2, t_matrix *out)
{
	double	result[MAX][MAX];
	int		row;
	int		col;

	row = -1;
	while (++row < MAX)
	{
		col = -1;
		while (++col < MAX)
		{
			result[row][col] = m1->mx[row][0] * m2->mx[0][col]
				+ m1->mx[row][1] * m2->mx[1][col]
				+ m1->mx[row][2] * m2->mx[2][col]
				+ m1->mx[row][3] * m2->mx[3][col];
		}
	}
	return (new_matrix(result, MAX, out));
}

t_tuple	*multiply_matrix_by_tuple(t_matrix *m, t_tuple *t, t_tuple *out)
{
	double	result[MAX];
	int		row;

	row = -1;
	while (++row < MAX)
	{
		result[row] = m->mx[row][0] * t->x
			+ m->mx[row][1] * t->y
			+ m->mx[row][2] * t->z
			+ m->mx[row][3] * t->w;
	}
	*out = (t_tuple){result[0], result[1], result[2], result[3]};
	return (out);
}

t_matrix	*transpose_matrix(t_matrix *m, t_matrix *out)
{
	double	result[MAX][MAX];
	int		row;
	int		col;

	row = -1;
	while (++row < MAX)
	{
		col = -1;
		while (++col < MAX)
			result[col][row] = m->mx[row][col];
	}
	return (new_matrix(result, MAX, out));
}

t_matrix	*inverse_matrix(t_matrix *m, t_matrix *out)
{
	double	inverse_det;
	double	result[MAX][MAX];
	int		row;
	int		col;

	inverse_det = 1.0 / get_determinant(m);
	if (!is_invertible(m) || inverse_det == 0)
		return (get_identity_matrix(out));
	row = -1;
	while (++row < m->size)
	{
		col = -1;
		while (++col < m->size)
			result[col][row] = get_cofactor(m, row, col) * inverse_det;
	}
	return (new_matrix(result, m->size, out));
}
