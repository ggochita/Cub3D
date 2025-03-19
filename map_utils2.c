#include "cub3d.h"

int	is_empty_map_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	is_texture_or_color(char *line)
{
	char	*trimmed;

	trimmed = line;
	while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
		trimmed++;
	if (ft_strncmp(trimmed, "NO ", 3) == 0
		|| ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0
		|| ft_strncmp(trimmed, "EA ", 3) == 0
		|| ft_strncmp(trimmed, "F ", 2) == 0
		|| ft_strncmp(trimmed, "C ", 2) == 0)
		return (1);
	return (0);
}

void	process_map_line(char *line, int *in_map,
				int *count, int *last_non_empty)
{
	if (is_texture_or_color(line))
		return ;
	if (is_map_line(line))
	{
		*in_map = 1;
		(*count)++;
		*last_non_empty = *count;
	}
	else if (*in_map && !is_empty_map_line(line))
	{
		err_exit("Invalid line in map section", NULL);
	}
	else if (*in_map && is_empty_map_line(line))
		(*count)++;
}
