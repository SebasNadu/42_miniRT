#include "obj_loader.h"

bool	print_ignore_message(char const *filename, int *line_nb)
{
	ft_putstr_fd("minirt: obj files loader: ", STDERR_FILENO);
	ft_putstr_fd((char *)filename, STDERR_FILENO);
	ft_putstr_fd(": Line ", STDERR_FILENO);
	ft_putnbr_fd(*line_nb, STDERR_FILENO);
	ft_putendl_fd(" ignored.", STDERR_FILENO);
	return (true);
}

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

bool	is_float(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
			dot_count++;
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (false);
		i++;
	}
	if (dot_count > 1)
		return (false);
	return (true);
}

bool	are_floats(char *str1, char *str2, char *str3)
{
	if (!is_float(str1) || !is_float(str2) || !is_float(str3))
		return (false);
	return (true);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix[i]);
	matrix[i] = NULL;
	free(matrix);
	matrix = NULL;
}

void	free_3d_array(char ***array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		free_matrix(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}
