#include "tuples.h"
#include "canvas.h"
#include "utils.h"
#include "matrices.h"
#include <stdio.h>

void	print_matrix(t_matrix m)
{
	int	row;
	int	col;

	row = -1;
	while (++row < m.size)
	{
		col = -1;
		while (++col < m.size)
			printf("%f ", m.mx[row][col]);
		printf("\n");
	}
}

int	main(void)
{
	t_matrix	m;
	t_matrix	m2;
	double const	table[4][4] = {
		{0, 1, 2, 4},
		{1, 2, 4, 8},
		{2, 4, 8, 16},
		{4, 8, 16, 32}
	};

	// When you inverse the identity matrix, you get the same matrix
	get_identity_matrix(&m);
	printf("Identity matrix:\n");
	print_matrix(m);
	printf("Identity matrix inverse:\n");
	inverse_matrix(&m, &m);
	print_matrix(m);
	printf("\n");
	// When you multiply a matrix by its inverse, you get the same original matrix
	new_matrix(table, 4, &m);
	printf("Matrix:\n");
	print_matrix(m);
	printf("Inverse matrix:\n");
	inverse_matrix(&m, &m);
	print_matrix(m);
	printf("Multiply matrix with the inverse:\n");
	multiply_matrices(&m, inverse_matrix(&m, &m2), &m);
	print_matrix(m);
	printf("\n");
	// The difference between the inverse of the transpose and the transpose of
	// the inverse is the order of operations, only that.
	printf("The inverse of the tronspose of a matrix:\n");
	inverse_matrix(transpose_matrix(&m, &m), &m);
	print_matrix(m);
	printf("The transpose of the inverse of a matrix:\n");
	transpose_matrix(inverse_matrix(&m, &m), &m);
	print_matrix(m);
	printf("\n");
	// Multiplying the identity matrix by a tuple gives the same tuple
	t_tuple	t = new_tuple(1, 2, 3, 4);
	printf("Tuple:\n");
	printf("%f %f %f %f\n", t.x, t.y, t.z, t.w);
	get_identity_matrix(&m);
	multiply_matrix_by_tuple(&m, &t, &t);
	printf("Tuple multiplied by the identity matrix:\n");
	printf("%f %f %f %f\n", t.x, t.y, t.z, t.w);
// When you change some value of the identity matrix, you get a different tuple
// each row of the identity matrix affects a value of the tuple
	m.mx[3][0] = 2;
	multiply_matrix_by_tuple(&m, &t, &t);
	printf("Tuple multiplied by the identity matrix with [3][0]=2:\n");
	printf("%f %f %f %f\n", t.x, t.y, t.z, t.w);
	return (0);
}
