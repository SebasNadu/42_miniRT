#include "world.h"

void	divide_group(t_shape *group, int threshold)
{
	t_shape	*left;
	t_shape	*right;
	t_shape	*current;

	if (!check_group(group, &threshold))
		return ;
	left = NULL;
	right = NULL;
	if (threshold <= group->group.count)
	{
		partition_children(group, &left, &right);
		if (left)
			make_subgroup(group, &left);
		if (right)
			make_subgroup(group, &right);
	}
	current = group->group.root;
	while (current)
	{
		divide_group(current, threshold);
		current = current->next;
	}
	group->bounds_of(group);
}

static void	*divide_groups(void *data)
{
	t_thread_data	*td;
	t_world			*world;
	int				index;

	td = (t_thread_data *)data;
	if (!td || !td->data)
		return (ft_putendl_fd("minirt: divide_groups: Wrong arguments",
				STDERR_FILENO), NULL);
	world = (t_world *)td->data;
	if (!world->objs || td->start < 0 || td->end < 0 || td->start >= td->end)
		return (ft_putendl_fd("minirt: divide_groups: Wrong arguments",
				STDERR_FILENO), NULL);
	index = td->start - 1;
	while (++index < td->end)
		divide_group(&world->objs[index], BVH_THRESHOLD);
	return (data);
}

void	create_bvh(t_world *world)
{
	t_threads_setup	tsetup;
	t_thread_data	*tdata;
	pthread_t		*threads;
	int				i;

	if (!world || !world->objs || !world->objs_count)
		return ;
	if (world->objs_count < 3
		|| world->objs_inside_count + world->objs_ext_count < 64)
	{
		i = -1;
		while (++i < world->objs_count)
			divide_group(&world->objs[i], BVH_THRESHOLD);
		return ;
	}
	tsetup.nb_iters = world->objs_count;
	if (!set_threads_data(world, &threads, &tdata, &tsetup))
		return ;
	if (!exec_threads_for(divide_groups, threads, tdata, &tsetup.nb_threads))
		return ;
}
