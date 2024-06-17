#include "obj_loader.h"

bool	check_extension(char const *filename, char const *ext)
{
	char const	*file_ext;

	file_ext = ft_strrchr(filename, '.');
	if (file_ext)
	{
		if (ft_strncmp(file_ext, ext, ft_strlen(ext) + 1) == 0)
			return (true);
	}
	return (false);
}

bool	open_obj_file(char const *filename, int *fd, ssize_t *file_size)
{
	struct stat	file_stat;

	if (!check_extension(filename, ".obj"))
		return (ft_putendl_fd("minirt: Wrong file extension, .obj expected",
				STDERR_FILENO), false);
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		return (ft_putstr_fd("minirt: ", STDERR_FILENO),
			perror(filename), false);
	if (fstat(*fd, &file_stat) < 0)
	{
		close(*fd);
		return (ft_putstr_fd("minirt: ", STDERR_FILENO),
			perror(filename), false);
	}
	*file_size = file_stat.st_size;
	return (true);
}

bool	read_file_to_memory(char const *filename, char **file_content)
{
	int			fd;
	ssize_t		file_size;

	if (!open_obj_file(filename, &fd, &file_size))
		return (false);
	*file_content = malloc(file_size + 1);
	if (!file_content || !*file_content)
		return (ft_putstr_fd("minirt: ", STDERR_FILENO),
			perror("malloc"), close(fd), false);
	if (read(fd, *file_content, file_size) != file_size)
		return (ft_putstr_fd("minirt: ", STDERR_FILENO),
			perror(filename), close(fd), false);
	(*file_content)[file_size] = '\0';
	close(fd);
	return (true);
}
