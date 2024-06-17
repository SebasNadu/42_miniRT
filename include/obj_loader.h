#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# include <fcntl.h>

# include "shapes.h"
# include "groups.h"

typedef enum e_obj_type
{
	VERTICE,
	NORMAL,
	FACE,
}	t_obj_type;

typedef struct s_obj_loader
{
	char const		*filename;
	char			**lines;
	char			***tokens;
	int				ignored_lines;
	t_point			*vertices;
	int				v_count;
	int				v_max;
	t_vector		*normals;
	int				n_count;
	int				n_max;
	t_shape			*triangles;
	int				t_count;
	int				t_max;
	t_shape			*groups;
	int				gp_count;
	int				gp_max;
	t_shape			*current_gp;
	t_shape			*default_group;
	pthread_mutex_t	v_mutex;
	pthread_mutex_t	n_mutex;
	pthread_mutex_t	t_mutex;
	pthread_mutex_t	gp_mutex;
	pthread_mutex_t	ig_lines_mutex;
}	t_obj_loader;

// obj_loader.c
t_obj_loader	*new_obj_loader(t_obj_loader *loader, t_shape *group);
// obj_open_read.c
bool			open_obj_file(char const *filename, int *fd,
					ssize_t *file_size);
bool			read_file_to_memory(char const *filename, char **file_content);
bool			check_extension(char const *filename, char const *ext);
// obj_split_file_content.c
bool			split_file_in_lines(char **file_content, char ***lines,
					char ****tokens, int *nb_lines);
void			*split_lines_in_tokens(void *data);
// obj_file_parse_lines.c
bool			obj_parse_line(t_obj_loader *loader, char **params,
					int line_nb);
// obj_file_parser.c
bool			parse_obj_file(t_obj_loader *loader, char const *filename);
// obj_loader_utils.c
bool			print_ignore_message(char const *filename, int *line_nb);
int				ft_matrix_len(char **matrix);
bool			is_float(char *str);
bool			are_floats(char *str1, char *str2, char *str3);
void			free_matrix(char **matrix);
void			free_3d_array(char ***array);
// obj_triangles_utils.c
bool			fan_triangulation(t_obj_loader *loader, int *vert_i,
					int *norm_i, int *p_len);
void			create_triangle(t_obj_loader *loader, int *vert_i, int *norm_i,
					int i);
void			fill_indices(char **params, int *vert_i, int *norm_i,
					int *p_len);
// set_max_values.c
void			*set_max_values(void *data);
#endif
