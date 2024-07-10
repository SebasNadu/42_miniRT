#include "world.h"

static bool	is_included(t_list *container, t_shape *obj)
{
	t_list	*tmp;

	tmp = container;
	while (tmp)
	{
		if (tmp->content == obj)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static void	remove_obj(t_list **container, t_shape *obj)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *container;
	prev = NULL;
	while (tmp)
	{
		if (tmp->content == obj)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*container = tmp->next;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

#ifdef THREADS

static t_list	*new_lst(t_shape *shape)
{
	static t_list	pool[MAX_NODES];
	static size_t	index = 0;
	t_list			*node;

	pthread_mutex_lock(&g_lst_pool_mutex);
	node = &pool[index++];
	if (index >= MAX_NODES)
		index = 0;
	pthread_mutex_unlock(&g_lst_pool_mutex);
	node->content = shape;
	node->next = NULL;
	return (node);
}

#else

static t_list	*new_lst(t_shape *shape)
{
	static t_list	pool[MAX_NODES];
	static size_t	index = 0;
	t_list			*node;

	node = &pool[index++];
	if (index >= MAX_NODES)
		index = 0;
	node->content = shape;
	node->next = NULL;
	return (node);
}

#endif

static void	set_indices(t_list *container, double *n)
{
	if (!ft_lstsize(container))
		*n = 1.0;
	else
		*n = ((t_shape *)container
				->content)->material.refractive_index;
}

void	find_refractive_indices(t_comps *comps, t_hit *i, t_hit *xs)
{
	t_list	*container;
	t_hit	*tmp;

	container = NULL;
	tmp = xs;
	while (tmp) 
	{
		if (i == tmp) 
			set_indices(container, &comps->n1);
		if (tmp && is_included(container, tmp->obj))
			remove_obj(&container, tmp->obj);
		else
			ft_lstadd_front(&container, new_lst(tmp->obj));
		if (i == tmp) 
		{
			set_indices(container, &comps->n2);
			return ;
		}
		tmp = tmp->next;
	}
}
