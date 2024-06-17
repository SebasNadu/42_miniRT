#include "matrices.h"

t_matrix	*rotation_x(double cos_rad, double sin_rad, t_matrix *out)
{
	double const	table[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, cos_rad, -sin_rad, 0},
	{0, sin_rad, cos_rad, 0},
	{0, 0, 0, 1},
	};

	return (new_matrix(table, MAX, out));
}

t_matrix	*rotation_y(double cos_rad, double sin_rad, t_matrix *out)
{
	double const	table[MAX][MAX] = {
	{cos_rad, 0, sin_rad, 0},
	{0, 1, 0, 0},
	{-sin_rad, 0, cos_rad, 0},
	{0, 0, 0, 1},
	};

	return (new_matrix(table, MAX, out));
}

t_matrix	*rotation_z(double cos_rad, double sin_rad, t_matrix *out)
{
	double const	table[MAX][MAX] = {
	{cos_rad, -sin_rad, 0, 0},
	{sin_rad, cos_rad, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (new_matrix(table, MAX, out));
}
