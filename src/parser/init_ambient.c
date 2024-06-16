#include "parser.h"

void	make_ambient(char **rgb, double ratio, t_world *world)
{
	double	r;
	double	g;
	double	b;

	r = (ft_atof(rgb[0]) / 255) * ratio;
	g = (ft_atof(rgb[1]) / 255) * ratio;
	b = (ft_atof(rgb[2]) / 255) * ratio;
	new_color(r, g, b, &world->ambient);
	free_s(rgb);
}

int	init_ambient(t_line_parse_env *env, t_world *world)
{
	char	**rgb;

	if (ft_strarr_len(env->line) != 3)
		return (file_error(env, ERR_INC_AMB));
	env->error_type = RATIO;
	if (solo(env->line[1], 0, 1, env))
		return (1);
	env->error_type = RGB;
	rgb = ft_subsplit(env->line[2], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
	make_ambient(rgb, ft_atof(env->line[1]), world);
	return (0);
}
