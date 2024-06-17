#include "obj_loader.h"

bool	split_file_in_lines(char **file_content, char ***lines, char ****tokens,
			int *nb_lines)
{
	*lines = ft_split(*file_content, '\n');
	if (!*lines)
		return (perror("minirt: ft_split"), false);
	free(*file_content);
	*file_content = NULL;
	*nb_lines = ft_matrix_len(*lines);
	*tokens = (char ***)malloc(sizeof(char **) * (*nb_lines + 1));
	if (!*tokens)
		return (perror("minirt: malloc"), false);
	(*tokens)[*nb_lines] = NULL;
	return (true);
}

void	*split_lines_in_tokens(void *data)
{
	t_thread_data	*td;
	t_obj_loader	*loader;
	int				line_nb;

	td = (t_thread_data *)data;
	if (!td)
		return (ft_putendl_fd("minirt: split_lines_in_tokens: Wrong arguments",
				STDERR_FILENO), NULL);
	loader = (t_obj_loader *)td->data;
	if (!loader || !loader->lines || td->start < 0 || td->end < 0
		|| td->start >= td->end)
		return (ft_putendl_fd("minirt: splitu-lines_in_tokens: Wrong arguments",
				STDERR_FILENO), NULL);
	line_nb = td->start - 1;
	while (++line_nb < td->end)
	{
		loader->tokens[line_nb]
			= ft_subsplit(loader->lines[line_nb], " \n");
		if (!loader->tokens[line_nb])
			return (perror("minirt: split_lines_in_tokens: malloc"), NULL);
	}
	return (data);
}
