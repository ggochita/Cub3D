#include "cub3d.h"

void	check_interior(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->height - 1)
	{
		j = 1;
		while (map->grid[i][j] && map->grid[i][j] != '\n')
		{
			if (is_playable_space(map->grid[i][j]))
			{
				if (!is_space_closed(map, i, j))
				{
					err_exit("Map must be surrounded by walls", map);
				}
			}
			j++;
		}
		i++;
	}
}

void	check_closed_map(t_map *map)
{
	check_map_alignment(map);
	check_borders(map);
	check_interior(map);
}

void	check_player_position(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
		err_exit("No player position found in map", map);
	if (player_count > 1)
		err_exit("Multiple player positions found in map", map);
}

void	check_forbidden_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j] && map->grid[i][j] != '\n')
		{
			if (!is_valid_char(map->grid[i][j]))
			{
				err_exit("Map contains forbidden characters", map);
			}
			j++;
		}
		i++;
	}
}

void	validate_map(t_map *map)
{
	if (!map || !map->grid || map->height <= 0)
		err_exit("Invalid map data", map);
	check_forbidden_chars(map);
	check_closed_map(map);
	check_player_position(map);
}
