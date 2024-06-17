#include "obj_loader.h"

static bool	parse_triangle(t_obj_loader *loader, char **params, int *line_nb)
{
	int		*vert_i;
	int		*norm_i;
	int		p_len;

	p_len = ft_matrix_len(params) - 1;
	if (p_len < 3)
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	vert_i = malloc(p_len * sizeof(int));
	norm_i = malloc(p_len * sizeof(int));
	if (!vert_i || !norm_i)
		return (false);
	fill_indices(params, vert_i, norm_i, &p_len);
	if (!fan_triangulation(loader, vert_i, norm_i, &p_len))
		return (false);
	free(vert_i);
	free(norm_i);
	return (true);
}

static bool	parse_group(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1])
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	if (loader->gp_count >= loader->gp_max)
		return (false);
	new_group(&loader->groups[loader->gp_count]);
	loader->current_gp = &loader->groups[loader->gp_count];
	add_child(loader->default_group, loader->current_gp);
	loader->gp_count++;
	return (true);
}

static bool	parse_normal(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	if (loader->n_count >= loader->n_max)
	{
		return (false);
	}
	new_point(ft_atof(params[1]), ft_atof(params[2]), ft_atof(params[3]),
		&loader->normals[loader->n_count]);
	loader->n_count++;
	return (true);
}

static bool	parse_vertice(t_obj_loader *loader, char **params, int *line_nb)
{
	if (!params[1] || !params[2] || !params[3] || params[4]
		|| !are_floats(params[1], params[2], params[3]))
	{
		print_ignore_message(loader->filename, line_nb);
		loader->ignored_lines++;
		return (true);
	}
	if (loader->v_count >= loader->v_max)
		return (false);
	new_point(ft_atof(params[1]), ft_atof(params[2]), ft_atof(params[3]),
		&loader->vertices[loader->v_count]);
	loader->v_count++;
	return (true);
}

bool	obj_parse_line(t_obj_loader *loader, char **params, int line_nb)
{
	int	type_size;

	if (!params[0])
	{
		print_ignore_message(loader->filename, &line_nb);
		loader->ignored_lines++;
		return (true);
	}
	type_size = ft_strlen(params[0]) + 1;
	if (ft_strncmp(params[0], "v", type_size) == 0)
		return (parse_vertice(loader, params, &line_nb));
	else if (ft_strncmp(params[0], "vn", type_size) == 0)
		return (parse_normal(loader, params, &line_nb));
	else if (ft_strncmp(params[0], "f", type_size) == 0)
		return (parse_triangle(loader, params, &line_nb));
	else if (ft_strncmp(params[0], "g", type_size) == 0)
		return (parse_group(loader, params, &line_nb));
	print_ignore_message(loader->filename, &line_nb);
	loader->ignored_lines++;
	return (true);
}
