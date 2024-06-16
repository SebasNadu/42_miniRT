#include "canvas.h"

bool	new_canvas(t_canvas *canvas, int width, int height, char *title)
{
	canvas->mlx = mlx_init(width, height, title, true);
	if (!canvas->mlx)
		return (false);
	canvas->width = &canvas->mlx->width;
	canvas->height = &canvas->mlx->height;
	canvas->img = mlx_new_image(canvas->mlx, width, height);
	if (!canvas->img)
		return (false);
	ft_memset(canvas->img->pixels, 255,
		(*canvas->width * *canvas->height) << 2);
	return (true);
}

t_color	*read_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color *color)
{
	uint8_t			*pixel;
	double const	inv_255 = 0.00392157;

	if ((x >= img->width || y >= img->height) || !img || !img->pixels)
		return (NULL);
	pixel = img->pixels + ((y * img->width + x) << 2);
	color->r = pixel[0] * inv_255;
	color->g = pixel[1] * inv_255;
	color->b = pixel[2] * inv_255;
	return (color);
}

t_color	*pixel_at(mlx_texture_t *texture, uint32_t x, uint32_t y,
			t_color *color)
{
	uint8_t			*pixel;
	double const	inv_255 = 0.00392157;

	if ((x >= texture->width || y >= texture->height) || !texture
		|| !texture->pixels)
		return (NULL);
	pixel = texture->pixels + ((y * texture->width + x)
			* texture->bytes_per_pixel);
	color->r = pixel[0] * inv_255;
	color->g = pixel[1] * inv_255;
	color->b = pixel[2] * inv_255;
	return (color);
}
