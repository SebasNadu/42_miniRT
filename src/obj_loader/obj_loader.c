#include "obj_loader.h"

static bool	init_mutexes(t_obj_loader *loader);

t_obj_loader	*new_obj_loader(t_obj_loader *loader, t_shape *group)
{
	if (!loader)
		return (NULL);
	loader->filename = NULL;
	loader->lines = NULL;
	loader->tokens = NULL;
	loader->ignored_lines = 0;
	loader->vertices = NULL;
	loader->v_count = 0;
	loader->v_max = 0;
	loader->normals = NULL;
	loader->n_count = 0;
	loader->n_max = 0;
	loader->triangles = NULL;
	loader->t_count = 0;
	loader->t_max = 0;
	loader->groups = NULL;
	loader->gp_count = 0;
	loader->gp_max = 0;
	loader->default_group = group;
	new_group(loader->default_group);
	loader->current_gp = loader->default_group;
	if (!init_mutexes(loader))
		return (NULL);
	return (loader);
}

static bool	init_mutexes(t_obj_loader *loader)
{
	pthread_mutex_init(&loader->v_mutex, NULL);
	pthread_mutex_init(&loader->n_mutex, NULL);
	pthread_mutex_init(&loader->t_mutex, NULL);
	pthread_mutex_init(&loader->gp_mutex, NULL);
	pthread_mutex_init(&loader->ig_lines_mutex, NULL);
	if (pthread_mutex_init(&loader->v_mutex, NULL) != 0
		|| pthread_mutex_init(&loader->n_mutex, NULL) != 0
		|| pthread_mutex_init(&loader->t_mutex, NULL) != 0
		|| pthread_mutex_init(&loader->gp_mutex, NULL) != 0
		|| pthread_mutex_init(&loader->ig_lines_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&loader->v_mutex);
		pthread_mutex_destroy(&loader->n_mutex);
		pthread_mutex_destroy(&loader->t_mutex);
		pthread_mutex_destroy(&loader->gp_mutex);
		pthread_mutex_destroy(&loader->ig_lines_mutex);
		return (false);
	}
	return (true);
}
