#include "canvas.h"

bool	render(t_canvas *canvas, t_world *world, t_camera *camera)
{
	double		x;
	double		y;
	t_ray		ray;
	t_color		color;

	if (!new_canvas(canvas, camera->hsize, camera->vsize, "MiniRT"))
		return (false);
	y = -1;
	while (++y < camera->vsize - 1)
	{
		printf("\rRendering: %d%%", (int)(y / (camera->vsize - 1) * 100));
		x = -1;
		while (++x < camera->hsize - 1)
		{
			ray = ray_for_pixel(camera, x, y);
			color = color_at(world, &ray);
			write_pixel(canvas->img, x, y, color);
		}
	}
	printf("\rRendering: 100%%\n");
	return (true);
}

static uint8_t	convert_value(double value)
{
	if (value > 1.0)
		return (255);
	else if (value < 0.0)
		return (0);
	else
		return (value * 255.0 + 0.5);
}

uint32_t	get_rgb(t_color color)
{
	return (convert_value(color.b) << 16 | convert_value(color.g) << 8
		| convert_value(color.r) | 0xFF000000);
}

void	write_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color)
{
	uint8_t		*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = &img->pixels[((y * img->width) + x) << 2];
	*(pixel) = convert_value(color.r);
	*(++pixel) = convert_value(color.g);
	*(++pixel) = convert_value(color.b);
}

void	write_pixel_32(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t		*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = &img->pixels[((y * img->width) + x) << 2];
	*(uint32_t *)pixel = color;
}