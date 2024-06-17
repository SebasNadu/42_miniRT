#include "parser.h"

double	degrees_to_radian(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	make_camera(t_camera *camera, double fov, char **pov, char **or)
{
	t_point from;
<<<<<<< HEAD
    t_point to;
    t_vector up;

	*camera = new_camera(WIDTH, HEIGHT, degrees_to_radian(fov));
	from = new_point(ft_atof(pov[0]), ft_atof(pov[1]), ft_atof(pov[2]));
	to = add(from, new_vector(ft_atof(or[0]), ft_atof(or[1]), ft_atof(or[2])));
	up = new_vector(0, 1, 0);
	set_transform_camera(camera, view_transform(&from, &to, &up));
=======
    // t_point to;
    // t_vector up;
	new_camera(camera, WIDTH, HEIGHT, degrees_to_radian(fov));
	new_point(ft_atof(pov[0]), ft_atof(pov[1]), ft_atof(pov[2]), &from);
	// up = new_vector(0, 1, 0);
>>>>>>> main
}

int	init_camera(t_line_parse_env *env, t_camera *camera)
{
	char	**pov;
	char	**orientation;

	if (ft_strarr_len(env->line) != 4)
		return (file_error(env, ERR_INC_CAM));
	env->error_type = FOV;
	if (solo((env->line[3]), 0, 180, env))
		return (1);
	env->error_type = POV;
	pov = ft_subsplit(env->line[1], ",\n");
	if (triplets(pov, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = OR;
	orientation = ft_subsplit(env->line[2], ",\n");
	if (triplets(orientation, -1, 1, env))
		return (free_s(pov), 1);
	make_camera(camera, ft_atof(env->line[3]), pov, orientation);
	free_s(pov);
	free_s(orientation);
	return (0);
}