#include "cub3d.h"

int	count_map_lines(const char *filename)
{
	int		fd;
	char	*line;
	int		count;
	int		in_map;
	int		last_non_empty;

	fd = open_map_file(filename);
	count = 0;
	in_map = 0;
	last_non_empty = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_map_line(line, &in_map, &count, &last_non_empty);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (last_non_empty);
}
