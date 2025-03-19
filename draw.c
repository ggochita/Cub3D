#include "cub3d.h"

void	draw_floor_and_ceiling(t_game *game, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(img, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

int	is_valid_position(t_map *map, int i, int j)
{
	if (i < 0 || i >= map->height)
		return (0);
	if (j < 0 || j >= (int)ft_strlen(map->grid[i]))
		return (0);
	return (1);
}

int	is_playable_space(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line == '1' || *line == '0')
		return (1);
	return (0);
}
