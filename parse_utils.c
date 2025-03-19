#include "cub3d.h"

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

char	*trim_start(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

int	is_valid_identifier(char *line)
{
	char	*trimmed;

	trimmed = trim_start(line);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(trimmed, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(trimmed, "C ", 2) == 0)
		return (1);
	return (0);
}

int	is_valid_path_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '/' || c == '.' || c == '_'
		|| c == '-');
}

void	check_texture_file(char *path)
{
	int	fd;
	int	len;
	int	i;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		err_exit("Texture file must have .xpm extension", NULL);
	i = 0;
	while (path[i])
	{
		if (!is_valid_path_char(path[i]))
			err_exit("Texture path contains forbidden characters", NULL);
		i++;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		err_exit("Texture file not found or inaccessible", NULL);
	close(fd);
}
