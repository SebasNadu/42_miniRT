#include "tuples.h"
#include "canvas.h"
#include "utils.h"
#include <stdio.h>

typedef struct s_projectile {
	t_point		position;
	t_vector	velocity;
}	t_projectile;

typedef struct s_environment {
	t_vector	gravity;
	t_vector	wind;
}	t_environment;

static t_projectile	projectile(t_point *position, t_vector *velocity)
{
	return ((t_projectile){(*position), (*velocity)});
}

static t_environment	environment(t_vector *gravity, t_vector *wind)
{
	return ((t_environment){(*gravity), (*wind)});
}

static t_projectile	tick(t_environment env, t_projectile proj)
{
	t_point		pos;
	t_vector	vel;

	add(&proj.position, &proj.velocity, &pos);
	add(add(&proj.velocity, &env.gravity, &vel), &env.wind, &vel);
	return (projectile(&pos, &vel));
}

static void	write_dot(mlx_image_t *img, int x, int y, t_color color)
{
	write_pixel(img, x, y, &color);
	write_pixel(img, x + 1, y, &color);
	write_pixel(img, x, y + 1, &color);
	write_pixel(img, x + 1, y + 1, &color);
	write_pixel(img, x - 1, y, &color);
	write_pixel(img, x, y - 1, &color);
	write_pixel(img, x - 1, y - 1, &color);
	write_pixel(img, x - 1, y + 1, &color);
	write_pixel(img, x + 1, y - 1, &color);
}

static void	render_projectile_motion(t_canvas *canvas)
{
	t_color			c;
	t_projectile	p;
	t_environment	e;
	t_point			t[2];

	new_color(1, 0, 0, &c);
	p = projectile(new_point(0, 0, 0, &t[0]), multiply(
				normalize(new_vector(1, 1.8, 0, &t[1]), &t[1]), 11.25, &t[1]));
	e = environment(new_vector(0, -0.1, 0, &t[0]),
			new_vector(-0.01, 0, 0, &t[1]));
	printf("x: %f, y: %f, z: %f\n", p.position.x, p.position.y, p.position.z);
	while (p.position.y >= 0.0)
	{
		p = tick(e, p);
		write_dot(canvas->img, p.position.x, *canvas->height - p.position.y, c);
		printf("x: %f, y: %f, z: %f\n",
			p.position.x, p.position.y, p.position.z);
	}
}

int	main(void)
{
	t_canvas	rt;

	if (!new_canvas(&rt, 900, 550, "Chapter 02"))
		return (1);
	render_projectile_motion(&rt);
	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	mlx_close_hook(rt.mlx, &quit, &rt);
	mlx_key_hook(rt.mlx, &handle_keyhook, &rt);
	mlx_loop(rt.mlx);
	mlx_terminate(rt.mlx);
	return (0);
}
