/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:01:21 by sebasnadu         #+#    #+#             */
/*   Updated: 2024/07/25 19:01:23 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void		handle_mousehook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		handle_scrollhook(double xdelta, double ydelta, void *param);

#endif
