#include "parser.h"

void	set_type(t_line_parse_env *parse)
{
	if (parse->line[0] == NULL)
		parse->type = EMPTY_LINE;
	else if (!ft_strncmp(parse->line[0], "A", 2))
		parse->type = AMBIENT;
	else if (!ft_strncmp(parse->line[0], "C", 2))
		parse->type = CAMERA;
	else if (!ft_strncmp(parse->line[0], "L", 2))
		parse->type = LIGHT;
	else if (!ft_strncmp(parse->line[0], "sp", 2))
		parse->type = SPHERE;
	else if (!ft_strncmp(parse->line[0], "cy", 2))
		parse->type = CYLINDER;
	else if (!ft_strncmp(parse->line[0], "pl", 2))
		parse->type = PLANE;
}

int	parse_line(int fd, t_line_parse_env *parse)
{
	parse->line_number++;
	parse->temp = get_next_line(fd);
	if (!parse->temp || parse->temp[0] == '\0')
	{
		free(parse->temp);
		return (1);
	}
	parse->line = ft_subsplit (parse->temp, " \t\n");
	free(parse->temp);
	set_type(parse);
	return (0);
}

int	read_lines_init(t_world *world, t_mini_rt *minirt, int fd)
{
	t_line_parse_env	parse;
<<<<<<< HEAD
	int	i;
	int	obj;
=======
	int					i;
>>>>>>> main

	parse.line_number = 0;
	i = 0;
	obj = 0;
	while (1)
	{
		if (parse_line(fd, &parse))
			break ;
		if (parse.type == AMBIENT && init_ambient(&parse, world))
			return (free_s(parse.line));
		if (parse.type == CAMERA && init_camera(&parse, &(minirt->camera)))
			return (free_s(parse.line));
		if (parse.type == LIGHT && init_light(&parse, &(world->lights[i++])))
			return (free_s(parse.line));
		if (parse.type == SPHERE && init_sphere(&parse, &(world->objs[obj++])))
			return (free_s(parse.line));
		free_s(parse.line);
	}
	return (0);
}
