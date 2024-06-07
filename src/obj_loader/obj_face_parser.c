#include "obj_loader.h"

static void	fill_indices(char **params, int *vert_i, int *norm_i, int *p_len)
{
	char	**face_info;
	int		i;
	int		f_len;

	i = -1;
	while (++i < *p_len)
	{
		face_info = ft_split(params[i + 1], '/');
		f_len = ft_matrix_len(face_info);
		if (f_len >= 1)
			vert_i[i] = ft_atoi(face_info[0]);
		if (f_len == 2)
			norm_i[i] = ft_atoi(face_info[1]);
		else if (f_len > 2)
			norm_i[i] = ft_atoi(face_info[2]);
		else
			norm_i[i] = 0;
		free(face_info);
	}
}

static void	create_triangle(t_obj_loader *loader, int *vert_i, int *norm_i,
					int i)
{
	t_point		v[3];
	t_vector	n[3];

	if (vert_i[0] > 0 && vert_i[i] > 0 && vert_i[i + 1] > 0)
	{
		v[0] = loader->vertices[vert_i[0] - 1];
		v[1] = loader->vertices[vert_i[i] - 1];
		v[2] = loader->vertices[vert_i[i + 1] - 1];
		if (norm_i[0] > 0 && norm_i[i] > 0 && norm_i[i + 1] > 0)
		{
			n[0] = loader->normals[norm_i[0] - 1];
			n[1] = loader->normals[norm_i[i] - 1];
			n[2] = loader->normals[norm_i[i + 1] - 1];
			new_smooth_triangle(v, n, &loader->triangles[loader->t_count]);
		}
		else
			new_triangle(&v[0], &v[1], &v[2],
				&loader->triangles[loader->t_count]);
	}
}

static bool	fan_triangulation(t_obj_loader *loader, int *vert_i, int *norm_i, int *p_len)
{
	int			i;

	i = 0;
	while (++i < *p_len - 1)
	{
		if (loader->t_count == loader->t_max)
		{
			loader->t_max++;
			loader->triangles = ft_realloc(loader->triangles,
					loader->t_max * sizeof(t_point));
			if (!loader->triangles)
				return (false);
		}
		create_triangle(loader, vert_i, norm_i, i);
		add_child(loader->current_g, &loader->triangles[loader->t_count]);
		loader->t_count++;
	}
	return (true);
}

bool	parse_triangle(t_obj_loader *loader, char **params, int *line_nb)
{
	int		*vert_i;
	int		*norm_i;
	int		p_len;

	p_len = ft_matrix_len(params) - 1;
	if (p_len < 3)
		return (loader->ignored_lines++, print_ignore_message(*line_nb));
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
