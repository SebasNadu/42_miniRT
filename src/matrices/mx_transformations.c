#include "matrices.h"

t_matrix	*translation(double x, double y, double z, t_matrix *m)
{
	double const	table[MAX][MAX] = {
	{1, 0, 0, x},
	{0, 1, 0, y},
	{0, 0, 1, z},
	{0, 0, 0, 1}};

	return (new_matrix(table, MAX, m));
}

t_matrix	*scaling(double x, double y, double z, t_matrix *m)
{
	double const	table[MAX][MAX] = {
	{x, 0, 0, 0},
	{0, y, 0, 0},
	{0, 0, z, 0},
	{0, 0, 0, 1}};

	return (new_matrix(table, MAX, m));
}

t_matrix	*shearing(t_shearing x, t_shearing y, t_shearing z, t_matrix *m)
{
	double const	table[MAX][MAX] = {
	{1, x.p1, x.p2, 0},
	{y.p1, 1, y.p2, 0},
	{z.p1, z.p2, 1, 0},
	{0, 0, 0, 1}};

	return (new_matrix(table, MAX, m));
}

t_matrix	*transformations(int length, ...)
{
	va_list		args;
	t_matrix	*result;
	t_matrix	*tmp;

	va_start(args, length);
	result = va_arg(args, t_matrix *);
	while (0 < --length)
	{
		tmp = va_arg(args, t_matrix *);
		multiply_matrices(tmp, result, result);
	}
	va_end(args);
	return (result);
}
