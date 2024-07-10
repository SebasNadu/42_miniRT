#include "parser.h"

#ifdef THREADS

static bool	set_render_threads(t_mini_rt	*rt)
{
	t_threads_setup	tsetup; 

	tsetup.nb_iters = rt->canvas.img->height;
	if (!set_threads_data(rt, &rt->canvas.threads, &rt->canvas.tdata, &tsetup))
		return (ft_putendl_fd("minirt: set_render_threads: fail to set threads",
				STDERR_FILENO), false);
	rt->canvas.nb_threads = tsetup.nb_threads;
	return (true);
}

int	main(int argc, char **argv)
{
	t_mini_rt	minirt;

	if (parser(argc, argv, &minirt))
		return (1);
	new_canvas(&minirt.canvas, WIDTH, HEIGHT, "MiniRT");
	set_render_threads(&minirt);
	render(&minirt);
	mlx_image_to_window(minirt.canvas.mlx, minirt.canvas.img, 0, 0);
	mlx_close_hook(minirt.canvas.mlx, &quit, &minirt);
	mlx_key_hook(minirt.canvas.mlx, &handle_keyhook, &minirt);
	mlx_cursor_hook(minirt.canvas.mlx, &handle_cursorhook, &minirt);
	mlx_loop(minirt.canvas.mlx);
	mlx_set_mouse_pos(minirt.canvas.mlx, minirt.canvas.mlx->width * 0.5,
		minirt.canvas.mlx->height * 0.5);
	free_world(&minirt.world);
	mlx_terminate(minirt.canvas.mlx);
	return (0);
}
#else

int	main(int argc, char **argv)
{
	t_mini_rt	minirt;

	if (parser(argc, argv, &minirt))
		return (1);
	new_canvas(&minirt.canvas, WIDTH, HEIGHT, "MiniRT");
	render(&minirt);
	printf("Render time: %f's\n", mlx_get_time());
	mlx_image_to_window(minirt.canvas.mlx, minirt.canvas.img, 0, 0);
	mlx_close_hook(minirt.canvas.mlx, &quit, &minirt);
	mlx_key_hook(minirt.canvas.mlx, &handle_keyhook, &minirt);
	mlx_cursor_hook(minirt.canvas.mlx, &handle_cursorhook, &minirt);
	mlx_loop(minirt.canvas.mlx);
	mlx_set_mouse_pos(minirt.canvas.mlx, minirt.canvas.mlx->width * 0.5,
		minirt.canvas.mlx->height * 0.5);
	free_world(&minirt.world);
	mlx_terminate(minirt.canvas.mlx);
	return (0);
}

#endif
