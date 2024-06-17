#include "matrices.h"

double	get_determinant(t_matrix *m)
{
	double	det;
	int		col;

	det = 0;
	if (m->size == 2)
		det = m->mx[0][0] * m->mx[1][1]
			- m->mx[0][1] * m->mx[1][0];
	else
	{
		col = -1;
		while (++col < m->size)
			det += m->mx[0][col] * get_cofactor(m, 0, col);
	}
	return (det);
}

t_matrix	*get_submatrix(t_matrix *m, int *del_row, int *del_col, t_matrix *out)
{
	double	sub_matrix[MAX][MAX];
	int		row;
	int		col;

	row = -1;
	while (++row < m->size - 1)
	{
		col = -1;
		while (++col < m->size - 1)
			sub_matrix[row][col]
				= m->mx[row + (row >= *del_row)][col + (col >= *del_col)];
	}
	return (new_matrix(sub_matrix, m->size - 1, out));
}

double	get_minor(t_matrix *m, int *row, int *col)
{
	t_matrix	sub;
	double		minor;

	get_submatrix(m, row, col, &sub);
	minor = get_determinant(&sub);
	return (minor);
}

double	get_cofactor(t_matrix *m, int row, int col)
{
	double	cofactor;

	cofactor = get_minor(m, &row, &col);
	if ((row + col) & 1)
		cofactor *= -1;
	return (cofactor);
}

t_matrix	*get_identity_matrix(t_matrix *m)
{
	double const	table[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (new_matrix(table, MAX, m));
}
