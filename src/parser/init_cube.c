#include "parser.h"

/*
cube 0.0,0.0,0.0 5.0 5.0 5.0 10,0,255

x,y,z coordinates of the center of the cube: 0.0,0.0,0.0 (Center position of the cube.)
width of the cube: 5.0 (Width of the cube along the x-axis.)
height of the cube: 5.0 (Height of the cube along the y-axis.)
depth of the cube: 5.0 (Depth of the cube along the z-axis.)
R,G,B colors: 10, 0, 255 (Colors of the cube in RGB format, where each component is in the range [0-255].)
*/

typedef struct s_cube_info
{
    double  width;
    double  height;
    double  depth;
    double	r;
	double	g;
	double	b;
}   t_cube_info;

void    make_cube(t_cube_info *cube, char **center, char **axis, t_shape *obj)
{
    t_vector axis_v;
    t_vector default_axis; // Assuming default alignment along y-axis
    t_matrix trans_m, scale_m, rot_m, final_m;

    new_cube(obj);
    new_color(cube->r, cube->g, cube->b, &obj->material.color);
    new_vector(0, 1, 0, &default_axis);
    translation(ft_atof(center[0]), ft_atof(center[1]), ft_atof(center[2]), &trans_m);
    scaling(cube->width, cube->height, cube->depth, &scale_m);
    new_vector(ft_atof(axis[0]), ft_atof(axis[1]), ft_atof(axis[2]), &axis_v);
    calculate_rotation_matrix(&default_axis, &axis_v, &rot_m);
    multiply_matrices(&rot_m, &trans_m, &final_m);
    multiply_matrices(&scale_m, &final_m, &final_m);
    set_transform(obj, &final_m);
}

int cube_info(t_line_parse_env *env, t_cube_info *cube)
{
    char    **rgb;

    cube->depth = ft_atof(env->line[5]);
    cube->height = ft_atof(env->line[4]);
    cube->width = ft_atof(env->line[2]);
    env->error_type = HEIGHT_VALID;
	if (solo(env->line[4], EPSILON, (double)INT_MAX, env))
		return (1);
    env->error_type = WIDTH_VALID;
	if (solo(env->line[3], EPSILON, (double)INT_MAX, env))
		return (1);
    env->error_type = DEPTH_VALID;
	if (solo(env->line[5], EPSILON, (double)INT_MAX, env))
		return (1);
    env->error_type = RGB;
    rgb = ft_subsplit(env->line[6], ",\n");
	if (triplets(rgb, 0, 255, env))
		return (1);
    cube->r = (ft_atof(rgb[0]) / 255);
    cube->g = (ft_atof(rgb[1]) / 255);
    cube->b = (ft_atof(rgb[2]) / 255);
    return (0);
}

int init_cube(t_line_parse_env *env, t_shape *obj)
{
    t_cube_info cube;
    char    **center;
    char    **norm;

    if (ft_strarr_len(env->line) != 7)
		return (file_error(env, ERR_CUBE));
    if (cube_info(env, &cube))
    {
        return (1);
    }
	env->error_type = CENT;
	center = ft_subsplit(env->line[1], ",\n");
	if (triplets(center, (double)INT_MIN, (double)INT_MAX, env))
		return (1);
	env->error_type = NORMAL;
	norm = ft_subsplit(env->line[2], ",\n");
	if (triplets(norm, -1, 1, env))
		return (free_s(center), 1);
    make_cube(&cube, center, norm, obj);
    free_s(norm);
    free_s(center);
    return (0);
}