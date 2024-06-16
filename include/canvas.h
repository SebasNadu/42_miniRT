#ifndef CANVAS_H
# define CANVAS_H

# include <stdbool.h>
# include <fcntl.h>
# include "MLX42/MLX42.h"
# include "libft.h"
# include "world.h"
# include "camera.h"
# include "lights.h"

# define CANVAS_WIDTH	800
# define CANVAS_HEIGHT 600

typedef struct s_canvas {
	mlx_t				*mlx;
	mlx_image_t			*img;
	int					*width;
	int					*height;
}	t_canvas;

typedef struct s_mini_rt {
	t_canvas	canvas;
	t_world		world;
	t_camera	camera;
}	t_mini_rt;

// Canvas
bool		new_canvas(t_canvas *canvas, int width, int height, char *title);
// Render
bool		render(t_mini_rt *rt);
uint32_t	get_rgb(t_color *color);
void		write_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
				t_color *color);
void		write_pixel_32(mlx_image_t *img, uint32_t x, uint32_t y,
				uint32_t color);
// Save
void		canvas_to_ppm(t_canvas *canvas, char *filename);
t_color		*read_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
				t_color *color);
t_color		*pixel_at(mlx_texture_t *texture, uint32_t x, uint32_t y,
				t_color *color);
// hooks
void		handle_keyhook(mlx_key_data_t keydata, void *param);
void		quit(void *param);
#endif
