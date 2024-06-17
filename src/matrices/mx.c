#include "matrices.h"

bool	is_eq_mx(t_matrix m1, t_matrix m2)
{
	return (ft_memcmp(m1.mx, m2.mx, sizeof(double) * SIZE) == 0);
}

t_matrix	*new_matrix(const double table[MAX][MAX], size_t size, t_matrix *m)
{
	int		i;

	m->size = size;
	while (size--)
	{
		i = -1;
		while (++i < m->size)
			m->mx[size][i] = table[size][i];
	}
	return (m);
}

bool	is_invertible(t_matrix *m)
{
	return (get_determinant(m) != 0);
}
