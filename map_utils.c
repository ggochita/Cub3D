#include "cub3d.h"

void	allocate_map_grid(t_map *map, int height)
{
	map->grid = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map->grid)
		err_exit("Memory allocation failed for map grid", NULL);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

void	load_map(const char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	map->height = count_map_lines(filename);
	allocate_map_grid(map, map->height);
	fd = open_map_file(filename);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_line(line))
		{
			map->grid[i++] = ft_strdup(line);
		}
		free(line);
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	close(fd);
	map->width = ft_strlen(map->grid[0]);
}

int	open_map_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err_exit("Failed to open map file", NULL);
	return (fd);
}
