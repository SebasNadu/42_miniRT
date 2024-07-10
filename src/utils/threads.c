#include "utils.h"

void	threads_pool(pthread_t **threads, t_thread_data **t_data,
		int *nb_threads)
{
	static pthread_t		pool[THREADS_MAX];
	static t_thread_data	threads_data[THREADS_MAX];
	long					nprocs;

	nprocs = sysconf(_SC_NPROCESSORS_ONLN) * THREADS_FRACTION;
	if (nprocs < 1)
		nprocs = 1;
	*nb_threads = (int)nprocs;
	*threads = pool;
	*t_data = threads_data;
}

bool	set_threads_data(void *data, pthread_t **threads,
			t_thread_data **t_data, t_threads_setup *setup)
{
	int			i;

	if (!data || !setup)
		return (ft_putendl_fd("minirt: set_threads_data: Wrong arguments",
				STDERR_FILENO), false);
	threads_pool(threads, t_data, &setup->nb_threads);
	if (!threads || !t_data)
		return (ft_putendl_fd("minirt: set_threads_data: fatal on threads_pool",
				STDERR_FILENO), false);
	if (setup->nb_iters < setup->nb_threads)
		setup->nb_threads = setup->nb_iters;
	setup->iters_per_thread = setup->nb_iters / setup->nb_threads;
	i = -1;
	while (++i < setup->nb_threads)
	{
		(*t_data)[i].data = data;
		(*t_data)[i].start = i * setup->iters_per_thread;
		if (i == setup->nb_threads - 1)
			(*t_data)[i].end = setup->nb_iters;
		else
			(*t_data)[i].end = (i + 1) * setup->iters_per_thread;
	}
	return (true);
}

bool	exec_threads_for(t_thread_fn thread_fn, pthread_t *threads,
			t_thread_data *thread_data, int *nb_threads)
{
	int		i;
	void	*status;

	if (!thread_fn || !threads || !thread_data || !nb_threads)
		return (ft_putendl_fd("minirt: exec_threads_for: Wrong arguments",
				STDERR_FILENO), false);
	i = -1;
	while (++i < *nb_threads)
	{
		if (pthread_create(&threads[i], NULL,
				thread_fn, &thread_data[i]) != 0)
			return (perror("minirt: pthread_create"), false);
	}
	i = -1;
	while (++i < *nb_threads)
	{
		pthread_join(threads[i], &status);
		if (!status)
			return (perror("minirt: exec_threads_for"), false);
	}
	return (true);
}
