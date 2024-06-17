#include "test.h"

Test(matrices, create_4x4_matrix)
{
	t_matrix	m;
	const double	table[MAX][MAX] = {
		{1, 2, 3, 4},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5},
	};

	new_matrix(table, MAX, &m);
	cr_assert(eq(dbl, m.mx[0][0], 1));
	cr_assert(eq(dbl, m.mx[0][1], 2));
	cr_assert(eq(dbl, m.mx[0][2], 3));
	cr_assert(eq(dbl, m.mx[0][3], 4));

	cr_assert(eq(dbl, m.mx[1][0], 5.5));
	cr_assert(eq(dbl, m.mx[1][1], 6.5));
	cr_assert(eq(dbl, m.mx[1][2], 7.5));
	cr_assert(eq(dbl, m.mx[1][3], 8.5));

	cr_assert(eq(dbl, m.mx[2][0], 9));
	cr_assert(eq(dbl, m.mx[2][1], 10));
	cr_assert(eq(dbl, m.mx[2][2], 11));
	cr_assert(eq(dbl, m.mx[2][3], 12));

	cr_assert(eq(dbl, m.mx[3][0], 13.5));
	cr_assert(eq(dbl, m.mx[3][1], 14.5));
	cr_assert(eq(dbl, m.mx[3][2], 15.5));
	cr_assert(eq(dbl, m.mx[3][3], 16.5));
}

Test(matrices, create_2x2_matrix)
{
	t_matrix	m;
	const double	table[MAX][MAX] = {
		{-3, 5},
		{1, -2},
	};

	new_matrix(table, 2, &m);
	cr_assert(eq(dbl, m.mx[0][0], -3));
	cr_assert(eq(flt, m.mx[0][1], 5));
	cr_assert(eq(flt, m.mx[1][0], 1));
	cr_assert(eq(flt, m.mx[1][1], -2));
}

Test(matrices, create_matrix_3x3)
{
	t_matrix	m;

	const double	table[MAX][MAX] = {
		{-3, 5, 0},
		{1, -2, -7},
		{0, 1, 1},
	};

	new_matrix(table, 3, &m);
	cr_assert(eq(dbl, m.mx[0][0], -3));
	cr_assert(eq(dbl, m.mx[0][1], 5));
	cr_assert(eq(dbl, m.mx[0][2], 0));

	cr_assert(eq(dbl, m.mx[1][0], 1));
	cr_assert(eq(dbl, m.mx[1][1], -2));
	cr_assert(eq(dbl, m.mx[1][2], -7));

	cr_assert(eq(dbl, m.mx[2][0], 0));
	cr_assert(eq(dbl, m.mx[2][1], 1));
	cr_assert(eq(dbl, m.mx[2][2], 1));
}

Test(matrices, is_equal_matrix)
{
	t_matrix	a;
	t_matrix	b;
	bool			result;
	const double	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};
	const double	table_b[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	new_matrix(table_a, MAX, &a);
	new_matrix(table_b, MAX, &b);
	result = is_eq_mx(a, b);
	cr_assert(eq(int, result, 1));
}

Test(matrices, is_not_equal_matrix)
{
	t_matrix	a;
	t_matrix	b;
	bool			result;
	const double	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{8, 7, 6, 5},
		{4, 3, 2, 1},
	};
	const double	table_b[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	new_matrix(table_a, MAX, &a);
	new_matrix(table_b, MAX, &b);
	result = is_eq_mx(a, b);
	cr_assert(ne(int, result, 1));
}

Test(matrices, multiply_matrices)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;

	const double	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	const double	table_b[MAX][MAX] = {
		{-2, 1, 2, 3},
		{3, 2, 1, -1},
		{4, 3, 6, 5},
		{1, 2, 7, 8},
	};

	new_matrix(table_a, MAX, &a);
	new_matrix(table_b, MAX, &b);
	multiply_matrices(&a, &b, &c);

	cr_assert(eq(dbl, c.mx[0][0], 20));
	cr_assert(eq(dbl, c.mx[0][1], 22));
	cr_assert(eq(dbl, c.mx[0][2], 50));
	cr_assert(eq(dbl, c.mx[0][3], 48));

	cr_assert(eq(dbl, c.mx[1][0], 44));
	cr_assert(eq(dbl, c.mx[1][1], 54));
	cr_assert(eq(dbl, c.mx[1][2], 114));
	cr_assert(eq(dbl, c.mx[1][3], 108));

	cr_assert(eq(dbl, c.mx[2][0], 40));
	cr_assert(eq(dbl, c.mx[2][1], 58));
	cr_assert(eq(dbl, c.mx[2][2], 110));
	cr_assert(eq(dbl, c.mx[2][3], 102));

	cr_assert(eq(dbl, c.mx[3][0], 16));
	cr_assert(eq(dbl, c.mx[3][1], 26));
	cr_assert(eq(dbl, c.mx[3][2], 46));
	cr_assert(eq(dbl, c.mx[3][3], 42));
}

Test(matrices, multiply_mx_by_tuple)
{
	t_matrix	a;
	t_tuple		b;
	t_tuple		c;
	double const	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{2, 4, 4, 2},
		{8, 6, 4, 1},
		{0, 0, 0, 1},
	};

	new_matrix(table_a, MAX, &a);
	b = new_tuple(1, 2, 3, 1);
	multiply_matrix_by_tuple(&a, &b, &c);
	cr_assert(eq(dbl, c.x, 18));
	cr_assert(eq(dbl, c.y, 24));
	cr_assert(eq(dbl, c.z, 33));
	cr_assert(eq(dbl, c.w, 1));
}

Test(matrices, multiply_by_identity_matrix)
{
	t_matrix	a;
	t_matrix	id;
	t_matrix	result;
	double const	table_a[MAX][MAX] = {
		{0, 1, 2, 4},
		{1, 2, 4, 8},
		{2, 4, 8, 16},
		{4, 8, 16, 32},
	};
	double const table_id[MAX][MAX] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};

	new_matrix(table_a, MAX, &a);
	new_matrix(table_id, MAX, &id);
	multiply_matrices(&a, &id, &result);

	cr_assert(eq(dbl, result.mx[0][0], 0));
	cr_assert(eq(dbl, result.mx[0][1], 1));
	cr_assert(eq(dbl, result.mx[0][2], 2));
	cr_assert(eq(dbl, result.mx[0][3], 4));

	cr_assert(eq(dbl, result.mx[1][0], 1));
	cr_assert(eq(dbl, result.mx[1][1], 2));
	cr_assert(eq(dbl, result.mx[1][2], 4));
	cr_assert(eq(dbl, result.mx[1][3], 8));

	cr_assert(eq(dbl, result.mx[2][0], 2));
	cr_assert(eq(dbl, result.mx[2][1], 4));
	cr_assert(eq(dbl, result.mx[2][2], 8));
	cr_assert(eq(dbl, result.mx[2][3], 16));

	cr_assert(eq(dbl, result.mx[3][0], 4));
	cr_assert(eq(dbl, result.mx[3][1], 8));
	cr_assert(eq(dbl, result.mx[3][2], 16));
	cr_assert(eq(dbl, result.mx[3][3], 32));
}

Test(matrices, transpose_matrix)
{
	t_matrix	a;
	t_matrix	result;
	double const	table_a[MAX][MAX] = {
		{0, 9, 3, 0},
		{9, 8, 0, 8},
		{1, 8, 5, 3},
		{0, 0, 5, 8},
	};

	new_matrix(table_a, MAX, &a);
	transpose_matrix(&a, &result);

	cr_assert(eq(dbl, result.mx[0][0], 0));
	cr_assert(eq(dbl, result.mx[0][1], 9));
	cr_assert(eq(dbl, result.mx[0][2], 1));
	cr_assert(eq(dbl, result.mx[0][3], 0));

	cr_assert(eq(dbl, result.mx[1][0], 9));
	cr_assert(eq(dbl, result.mx[1][1], 8));
	cr_assert(eq(dbl, result.mx[1][2], 8));
	cr_assert(eq(dbl, result.mx[1][3], 0));

	cr_assert(eq(dbl, result.mx[2][0], 3));
	cr_assert(eq(dbl, result.mx[2][1], 0));
	cr_assert(eq(dbl, result.mx[2][2], 5));
	cr_assert(eq(dbl, result.mx[2][3], 5));

	cr_assert(eq(dbl, result.mx[3][0], 0));
	cr_assert(eq(dbl, result.mx[3][1], 8));
	cr_assert(eq(dbl, result.mx[3][2], 3));
	cr_assert(eq(dbl, result.mx[3][3], 8));
}

Test(matrices, determinant_2x2)
{
	t_matrix	a;
	int				result;
	double const	table_a[MAX][MAX] = {
		{1, 5},
		{-3, 2},
	};

	new_matrix(table_a, 2, &a);
	result = get_determinant(&a);
	cr_assert(eq(int, result, 17));
}

Test(matrices, submatrix_3x3)
{
	t_matrix	a;
	t_matrix	result;
	int				n[2];
	double const	table_a[MAX][MAX] = {
		{1, 5, 0},
		{-3, 2, 7},
		{0, 6, -3},
	};

	new_matrix(table_a, 3, &a);
	n[0] = 0;
	n[1] = 2;
	get_submatrix(&a, &n[0], &n[1], &result);

	cr_assert(eq(dbl, result.mx[0][0], -3));
	cr_assert(eq(dbl, result.mx[0][1], 2));

	cr_assert(eq(dbl, result.mx[1][0], 0));
	cr_assert(eq(dbl, result.mx[1][1], 6));
}

Test(matrices, submatrix_4x4)
{
	t_matrix	a;
	t_matrix	result;
	double const	table_a[MAX][MAX] = {
		{-6, 1, 1, 6},
		{-8, 5, 8, 6},
		{-1, 0, 8, 2},
		{-7, 1, -1, 1},
	};

	new_matrix(table_a, 4, &a);
	int	n[2];
	n[0] = 2;
	n[1] = 1;
	get_submatrix(&a, &n[0], &n[1], &result);

	cr_assert(eq(dbl, result.mx[0][0], -6));
	cr_assert(eq(dbl, result.mx[0][1], 1));
	cr_assert(eq(dbl, result.mx[0][2], 6));

	cr_assert(eq(dbl, result.mx[1][0], -8));
	cr_assert(eq(dbl, result.mx[1][1], 8));
	cr_assert(eq(dbl, result.mx[1][2], 6));

	cr_assert(eq(dbl, result.mx[2][0], -7));
	cr_assert(eq(dbl, result.mx[2][1], -1));
	cr_assert(eq(dbl, result.mx[2][2], 1));
}

Test(matrices, minor_3x3_matrix)
{
	t_matrix	a;
	double		result;
	double const	table_a[MAX][MAX] = {
		{3, 5, 0},
		{2, -1, 7},
		{6, -1, 5},
	};

	new_matrix(table_a, 3, &a);
	int n[2];
	n[0] = 0;
	n[1] = 0;
	result = get_minor(&a, &n[0], &n[1]);
	cr_assert(eq(dbl, result, 2));

	n[0] = 1;
	n[1] = 0;
	result = get_minor(&a, &n[0], &n[1]);
	cr_assert(eq(dbl, result, 25));
}

Test(matrices, cofactor_3x3_matrix)
{
	t_matrix	a;
	double		result;
	double const	table_a[MAX][MAX] = {
		{3, 5, 0},
		{2, -1, 7},
		{6, -1, 5},
	};

	new_matrix(table_a, 3, &a);
	result = get_cofactor(&a, 0, 0);
	cr_assert(eq(dbl, result, 2));
	result = get_cofactor(&a, 1, 0);
	cr_assert(eq(dbl, result, -25));
}

Test(matrices, determinant_3x3_matrix)
{
	t_matrix	a;
	double		result;
	double const	table_a[MAX][MAX] = {
		{1, 2, 6},
		{-5, 8, -4},
		{2, 6, 4},
	};

	new_matrix(table_a, 3, &a);
	result = get_cofactor(&a, 0, 0);
	cr_assert(eq(dbl, result, 56));
	result = get_cofactor(&a, 0, 1);
	cr_assert(eq(dbl, result, 12));
	result = get_cofactor(&a, 0, 2);
	cr_assert(eq(dbl, result, -46));
	result = get_determinant(&a);
	cr_assert(eq(dbl, result, -196));
}

Test(matrices, determinant_4x4_matrix)
{
	t_matrix	a;
	double		result;
	double const	table_a[MAX][MAX] = {
		{-2, -8, 3, 5},
		{-3, 1, 7, 3},
		{1, 2, -9, 6},
		{-6, 7, 7, -9},
	};

	new_matrix(table_a, 4, &a);
	result = get_cofactor(&a, 0, 0);
	cr_assert(eq(dbl, result, 690));
	result = get_cofactor(&a, 0, 1);
	cr_assert(eq(dbl, result, 447));
	result = get_cofactor(&a, 0, 2);
	cr_assert(eq(dbl, result, 210));
	result = get_cofactor(&a, 0, 3);
	cr_assert(eq(dbl, result, 51));
	result = get_determinant(&a);
	cr_assert(eq(dbl, result, -4071));
}

Test(matrices, is_invertible_4x4_matrix)
{
	t_matrix	a;
	double		result;
	double const	table_a[MAX][MAX] = {
		{6, 4, 4, 4},
		{5, 5, 7, 6},
		{4, -9, 3, -7},
		{9, 1, 7, -6},
	};

	new_matrix(table_a, 4, &a);
	result = get_determinant(&a);
	cr_assert(eq(dbl, result, -2120));
	cr_assert(eq(int, is_invertible(&a), true));
}

Test(matrices, is_not_invertible_4x4_matrix)
{
	t_matrix	a;
	double		result;
	double const	table_a[MAX][MAX] = {
		{-4, 2, -2, -3},
		{9, 6, 2, 6},
		{0, -5, 1, -5},
		{0, 0, 0, 0},
	};
	new_matrix(table_a, 4, &a); 
	result = get_determinant(&a);
	cr_assert(eq(dbl, result, 0));
	cr_assert(eq(int, is_invertible(&a), false));
}

Test(matrices, inverse_4x4_matrix)
{
	t_matrix	a;
	t_matrix	b;
	double		result;
	double const	table_a[MAX][MAX] = {
		{-5, 2, 6, -8},
		{1, -5, 1, 8},
		{7, 7, -6, -7},
		{1, -3, 7, 4},
	};

	new_matrix(table_a, 4, &a); 
	inverse_matrix(&a, &b);

	result = get_determinant(&a);
cr_assert(eq(dbl, result, 532));

	result = get_cofactor(&a, 2, 3);
	cr_assert(eq(dbl, result, -160));
	cr_assert(eq(flt, b.mx[3][2], (double)-160 / 532));

	result = get_cofactor(&a, 3, 2);
	cr_assert(eq(dbl, result, 105));
	cr_assert(eq(flt, b.mx[2][3], (double)105 / 532));

	cr_assert(epsilon_eq(dbl, b.mx[0][0], 0.21805, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][1], 0.45113, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][2], 0.24060, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][3], -0.04511, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[1][0], -0.80827, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][1], -1.45677, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][2], -0.44361, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][3], 0.52068, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[2][0], -0.07895, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][1], -0.22368, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][2], -0.05263, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][3], 0.19737, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[3][0], -0.52256, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][1], -0.81391, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][2], -0.30075, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][3], 0.30639, EPSILON));
}

Test(matrices, inverse_4x4_matrix_2)
{
	t_matrix	a;
	t_matrix	b;
	const double	table_a[MAX][MAX] = {
		{8, -5, 9, 2},
		{7, 5, 6, 1},
		{-6, 0, 9, 6},
		{-3, 0, -9, -4},
	};
	
	new_matrix(table_a, 4, &a);
	inverse_matrix(&a, &b);

	cr_assert(epsilon_eq(dbl, b.mx[0][0], -0.15385, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][1], -0.15385, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][2], -0.28205, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][3], -0.53846, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[1][0], -0.07692, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][1], 0.12308, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][2], 0.02564, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][3], 0.03077, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[2][0], 0.35897, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][1], 0.35897, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][2], 0.43590, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][3], 0.92308, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[3][0], -0.69231, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][1], -0.69231, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][2], -0.76923, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][3], -1.92308, EPSILON));
}

Test(matrices, inverse_4x4_matrix_3)
{
	t_matrix	a;
	t_matrix	b;
	const double	table_a[MAX][MAX] = {
		{9, 3, 0, 9},
		{-5, -2, -6, -3},
		{-4, 9, 6, 4},
		{-7, 6, 6, 2},
	};
	
	new_matrix(table_a, 4, &a);
	inverse_matrix(&a, &b);

	cr_assert(epsilon_eq(dbl, b.mx[0][0], -0.04074, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][1], -0.07778, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][2], 0.14444, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[0][3], -0.22222, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[1][0], -0.07778, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][1], 0.03333, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][2], 0.36667, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[1][3], -0.33333, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[2][0], -0.02901, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][1], -0.14630, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][2], -0.10926, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[2][3], 0.12963, EPSILON));

	cr_assert(epsilon_eq(dbl, b.mx[3][0], 0.17778, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][1], 0.06667, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][2], -0.26667, EPSILON));
	cr_assert(epsilon_eq(dbl, b.mx[3][3], 0.33333, EPSILON));
}

Test(matrices, multiplying_a_product_by_its_inverse)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;
	t_matrix	result;
	const double	table_a[MAX][MAX] = {
		{3, -9, 7, 3},
		{3, -8, 2, -9},
		{-4, 4, 4, 1},
		{-6, 5, -1, 1},
	};
	const double	table_b[MAX][MAX] = {
		{8, 2, 2, 2},
		{3, -1, 7, 0},
		{7, 0, 5, 4},
		{6, -2, 0, 5},
	};
	
	new_matrix(table_a, 4, &a);
	new_matrix(table_b, 4, &b);
	multiply_matrices(&a, &b, &c);
	inverse_matrix(&b, &b);
	multiply_matrices(&c, &b, &result);

	cr_assert(epsilon_eq(dbl, result.mx[0][0], 3, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[0][1], -9, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[0][2], 7, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[0][3], 3, EPSILON));

	cr_assert(epsilon_eq(dbl, result.mx[1][0], 3, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[1][1], -8, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[1][2], 2, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[1][3], -9, EPSILON));

	cr_assert(epsilon_eq(dbl, result.mx[2][0], -4, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[2][1], 4, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[2][2], 4, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[2][3], 1, EPSILON));

	cr_assert(epsilon_eq(dbl, result.mx[3][0], -6, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[3][1], 5, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[3][2], -1, EPSILON));
	cr_assert(epsilon_eq(dbl, result.mx[3][3], 1, EPSILON));
}
