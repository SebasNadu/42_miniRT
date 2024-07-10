#include "canvas.h"

void	quit(void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
	mlx_delete_image(rt->canvas.mlx, rt->canvas.img);
	free_world(&rt->world);
	mlx_terminate(rt->canvas.mlx);
	exit(EXIT_SUCCESS);
}

void	handle_camera_position(t_mini_rt *rt, mlx_key_data_t *keydata)
{
	double		velocity;
	t_matrix	trans_m; 

	velocity = rt->canvas.mlx->delta_time * (rt->canvas.img->width * 0.05);
	if (keydata->key == MLX_KEY_RIGHT)
		translation(velocity, 0, 0, &trans_m);
	if (keydata->key == MLX_KEY_LEFT)
		translation(-velocity, 0, 0, &trans_m);
	if (keydata->key == MLX_KEY_UP)
	{
		if (keydata->modifier == MLX_SHIFT)
			translation(0, -velocity, 0, &trans_m);
		else
			translation(0, 0, velocity, &trans_m);
	}
	if (keydata->key == MLX_KEY_DOWN)
	{
		if (keydata->modifier == MLX_SHIFT)
			translation(0, velocity, 0, &trans_m);
		else
			translation(0, 0, -velocity, &trans_m);
	}
	multiply_matrices(&trans_m, &rt->camera.transform, &rt->camera.transform);
	set_transform_camera(&rt->camera, &rt->camera.transform);
	render(rt);
}

void	handle_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
	if ((keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
		&& keydata.action == MLX_PRESS)
		quit(param);
	if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT
			|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
		&& (keydata.action == MLX_PRESS))
		handle_camera_position(rt, &keydata);
}

void	handle_cursorhook(double xpos, double ypos, void *param)
{
	t_mini_rt		*rt;
	double			xoffset;
	double			yoffset;
	t_matrix		m[2];

	rt = (t_mini_rt *)param;
	xoffset = ((rt->canvas.mlx->width * 0.5) - xpos) * 0.001;
	yoffset = (ypos - (rt->canvas.mlx->height * 0.5)) * 0.001;
	if (xoffset != 0 || yoffset != 0)
	{
		rotation_y(cos(xoffset), sin(xoffset), &m[0]);
		rotation_x(cos(yoffset), sin(yoffset), &m[1]);
		multiply_matrices(&m[0], &m[1], &m[0]);
		multiply_matrices(&m[0], &rt->camera.transform, &rt->camera.transform);
		set_transform_camera(&rt->camera, &rt->camera.transform);
		render(rt);
	}
	mlx_set_mouse_pos(rt->canvas.mlx, rt->canvas.mlx->width * 0.5,
		rt->canvas.mlx->height * 0.5);
}
