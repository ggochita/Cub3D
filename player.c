#include "cub3d.h"

void	init_player_direction(t_player *player, char direction);

void	init_player(t_game *game)
{
	int	i;
	int	j;

	game->player = malloc(sizeof(t_player));
	if (!game->player)
		err_exit("Memory allocation failed for player.", game->map);
	i = -1;
	while (++i < game->map->height)
	{
		j = -1;
		while (game->map->grid[i][++j])
		{
			if (ft_strchr("NSEW", game->map->grid[i][j]))
			{
				game->player->x = j + 0.5;
				game->player->y = i + 0.5;
				init_player_direction(game->player, game->map->grid[i][j]);
				game->map->grid[i][j] = '0';
				return ;
			}
		}
	}
}

void	move_player(t_game *game, float dir_x, float dir_y)
{
	float	new_x;
	float	new_y;
	float	move_speed;

	move_speed = 0.09;
	new_x = game->player->x + dir_x * move_speed;
	new_y = game->player->y + dir_y * move_speed;
	if (game->map->grid[(int)game->player->y][(int)new_x] != '1')
		game->player->x = new_x;
	if (game->map->grid[(int)new_y][(int)game->player->x] != '1')
		game->player->y = new_y;
}

void	rotate_player(t_player *player, float angle)
{
	float	old_dir_x;
	float	old_plane_x;
	float	rot_speed;

	rot_speed = 0.2;
	angle *= rot_speed;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle)
		+ player->plane_y * cos(angle);
}
