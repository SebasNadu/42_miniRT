#include "utils.h"
#include "world.h"

static void	free_csg(t_shape *csg);

static void	free_pattern(t_pattern *pattern)
{
	if (pattern->has_pattern)
	{
		if (pattern->a)
			free(pattern->a);
		if (pattern->b)
			free(pattern->b);
	}
}

static void	free_group(t_shape *root)
{
	t_shape	*tmp;

	while (root)
	{
		if (root->is_group)
			free_group(root->group.root);
		free_pattern(&root->material.pattern);
		tmp = root;
		root = root->next;
		free(tmp);
	}
	root = NULL;
}

static void	free_csg(t_shape *csg)
{
	if (csg)
	{
		if (csg->is_csg)
		{
			if (csg->csg.left)
				free_csg(csg->csg.left);
			csg->csg.left = NULL;
			if (csg->csg.right)
				free_csg(csg->csg.right);
			csg->csg.right = NULL;
		}
		if (csg->is_group)
		{
			free_group(csg->group.root);
			csg->group.root = NULL;
		}
		free_pattern(&csg->material.pattern);
		free(csg);
	}
}

void	free_world(t_world *world)
{
	int		i;

	i = -1;
	while (++i < world->objs_count)
	{
		free_pattern(&world->objs[i].material.pattern);
		if (world->objs[i].is_group)
		{
			free_group(world->objs[i].group.root);
			world->objs[i].group.root = NULL;
		}
		if (world->objs[i].is_csg)
		{
			if (world->objs[i].csg.left)
				free_csg(world->objs[i].csg.left);
			world->objs[i].csg.left = NULL;
			if (world->objs[i].csg.right)
				free_csg(world->objs[i].csg.right);
			world->objs[i].csg.right = NULL;
		}
	}
	free(world->lights);
	free(world->objs);
}
