#ifndef CANVAS_H
# define CANVAS_H

# include "MLX42/MLX42.h"
# include "camera.h"
# include "libft.h"
# include "lights.h"
# include "world.h"
# include <fcntl.h>
# include <stdbool.h>

# define CANVAS_WIDTH 800
# define CANVAS_HEIGHT 600

typedef struct s_canvas {
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				nb_threads;
	pthread_t		*threads;
	t_thread_data	*tdata;
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
// Render Utils
uint32_t	get_rgb(t_color *color);
void		write_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
				t_color *color);
void		write_pixel_32(mlx_image_t *img, uint32_t x, uint32_t y,
				uint32_t color);
// Multisampling
void		multisample_only_dof(t_mini_rt *rt, double xy_offset[2], t_ray *ray,
				t_color *color);
void		multisample(t_mini_rt *rt, double xy_offset[4], t_ray *ray,
				t_color *color);
// Save
void		canvas_to_ppm(t_canvas *canvas, char *filename);
t_color		*read_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
				t_color *color);
t_color		*pixel_at(mlx_texture_t *texture, uint32_t x, uint32_t y,
				t_color *color);
t_color		*full_pixel_at(mlx_texture_t *texture, uint32_t x, uint32_t y,
				t_color *color);
// hooks
void		quit(void *param);
void		handle_keyhook(mlx_key_data_t keydata, void *param);
void		handle_cursorhook(double xpos, double ypos, void *param);
#endif
