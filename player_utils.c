#include "cub3d.h"

void	set_direction(t_player *player, float dir_x, float dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

void	set_plane(t_player *player, float plane_x, float plane_y)
{
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

void	init_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		set_direction(player, 0, -1);
		set_plane(player, 0.66, 0);
	}
	else if (direction == 'S')
	{
		set_direction(player, 0, 1);
		set_plane(player, -0.66, 0);
	}
	else if (direction == 'E')
	{
		set_direction(player, 1, 0);
		set_plane(player, 0, 0.66);
	}
	else if (direction == 'W')
	{
		set_direction(player, -1, 0);
		set_plane(player, 0, -0.66);
	}
}

int			get_key_index(int key)
{
	if (key == KEY_LEFT)
		return (KEY_LEFT_IDX);
	if (key == KEY_RIGHT)
		return (KEY_RIGHT_IDX);
	if (key == KEY_W)
		return (KEY_W_IDX);
	if (key == KEY_A)
		return (KEY_A_IDX);
	if (key == KEY_S)
		return (KEY_S_IDX);
	if (key == KEY_D)
		return (KEY_D_IDX);
	if (key == KEY_ESC)
		return (ESC_IDX);
	return (-1);
}
