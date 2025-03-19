#include "cub3d.h"

void	check_horizontal_border(t_map *map, int i, int last_char)
{
	int	j;

	j = 0;
	while (j <= last_char)
	{
		if (map->grid[i][j] != '1' && map->grid[i][j] != ' ')
			err_exit("Map must be surrounded by walls (horizontal)", map);
		j++;
	}
}

void	check_vertical_border(t_map *map, int i, int last_char)
{
	if (map->grid[i][0] != '1' && map->grid[i][0] != ' ')
		err_exit("Map must be surrounded by walls (left border)", map);
	if (map->grid[i][last_char] != '1' && map->grid[i][last_char] != ' ')
		err_exit("Map must be surrounded by walls (right border)", map);
}

int	is_space_closed(t_map *map, int i, int j)
{
	if (!is_valid_position(map, i - 1, j))
		return (0);
	if (map->grid[i - 1][j] != '1' && !is_playable_space(map->grid[i - 1][j])
		&& map->grid[i - 1][j] != ' ')
		return (0);
	if (!is_valid_position(map, i + 1, j))
		return (0);
	if (map->grid[i + 1][j] != '1' && !is_playable_space(map->grid[i + 1][j])
		&& map->grid[i + 1][j] != ' ')
		return (0);
	if (!is_valid_position(map, i, j - 1))
		return (0);
	if (map->grid[i][j - 1] != '1' && !is_playable_space(map->grid[i][j - 1])
		&& map->grid[i][j - 1] != ' ')
		return (0);
	if (!is_valid_position(map, i, j + 1))
		return (0);
	if (map->grid[i][j + 1] != '1' && !is_playable_space(map->grid[i][j + 1])
		&& map->grid[i][j + 1] != ' ')
		return (0);
	return (1);
}

void	check_map_alignment(t_map *map)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	width = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j] && map->grid[i][j] != '\n')
			j++;
		if (j > width)
			width = j;
		i++;
	}
	map->width = width;
}

void	check_borders(t_map *map)
{
	int	i;
	int	j;
	int	last_char;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		last_char = 0;
		while (map->grid[i][j] && map->grid[i][j] != '\n')
		{
			if (map->grid[i][j] != ' ')
				last_char = j;
			j++;
		}
		if (i == 0 || i == map->height - 1)
			check_horizontal_border(map, i, last_char);
		else
			check_vertical_border(map, i, last_char);
		i++;
	}
}
