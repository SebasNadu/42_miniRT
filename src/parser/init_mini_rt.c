#include "parser.h"

int	init_mini_rt(t_world *world, t_mini_rt *minirt,t_e_counts *count)
{
	int	objs_count;

	objs_count = count->cylinder + count->sphere + count->plane;
	world->objs_count = objs_count;
	world->lights_count = count->light;
	world->objs = (t_shape *)malloc(sizeof(t_shape) * (objs_count));
	if (!world->objs)
	    return (print_error(MALLOC_FAIL));
	world->lights = (t_light *)malloc(sizeof(t_light) * (world->lights_count));
	if (!(world->lights))
		return (print_error(MALLOC_FAIL));
	if (read_lines_init(world, minirt, count->fd))
		return (1);
	return (0);	
}

int	init_minirt(t_mini_rt *minirt, t_e_counts *env)
{
	new_world(&minirt->world);
	if (init_mini_rt(&(minirt->world), minirt, env))
		return (1);
	return (0);
}
