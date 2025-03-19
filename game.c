#include "cub3d.h"

void	cleanup_game(t_game *game)
{
	if (game->textures.no.img)
		mlx_destroy_image(game->mlx, game->textures.no.img);
	if (game->textures.so.img)
		mlx_destroy_image(game->mlx, game->textures.so.img);
	if (game->textures.we.img)
		mlx_destroy_image(game->mlx, game->textures.we.img);
	if (game->textures.ea.img)
		mlx_destroy_image(game->mlx, game->textures.ea.img);
	if (game->win_3d)
		mlx_destroy_window(game->mlx, game->win_3d);
	if (game->textures_paths.no)
		free(game->textures_paths.no);
	if (game->textures_paths.so)
		free(game->textures_paths.so);
	if (game->textures_paths.we)
		free(game->textures_paths.we);
	if (game->textures_paths.ea)
		free(game->textures_paths.ea);
	if (game->player)
		free(game->player);
	if (game->map && game->map->grid)
		free_map(game->map);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int		update(void *param)
{
	float	rot_speed;
	t_game *game;
	
	game = (t_game *)param;
	rot_speed = 0.3;
	if (game->keys[ESC_IDX])
		close_window(game);
	if (game->keys[KEY_W_IDX])
		move_player(game, game->player->dir_x, game->player->dir_y);
	if (game->keys[KEY_S_IDX])
		move_player(game, -game->player->dir_x, -game->player->dir_y);
	if (game->keys[KEY_A_IDX])
		move_player(game, game->player->dir_y, -game->player->dir_x);
	if (game->keys[KEY_D_IDX])
		move_player(game, -game->player->dir_y, game->player->dir_x);
	if (game->keys[KEY_LEFT_IDX])
		rotate_player(game->player, -rot_speed);
	if (game->keys[KEY_RIGHT_IDX])
		rotate_player(game->player, rot_speed);
	render_frame(game);
	return (0);
}

int key_press(int key, void *param)
{
    t_game *game = (t_game *)param;
    int index_key = get_key_index(key);
    if (index_key != -1)
        game->keys[index_key] = 1;
    return 0;
}

int key_release(int key, void *param)
{
    t_game *game = (t_game *)param;
    int index_key = get_key_index(key);
    if (index_key != -1)
        game->keys[index_key] = 0;
    return 0;
}

void	init_game(t_game *game)
{
	game->win_3d = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win_3d)
		err_exit("Failed to create window", game->map);
	init_player(game);
	render_frame(game);
	mlx_hook(game->win_3d, 2, 1L << 0, key_press, game);
	mlx_hook(game->win_3d, 3, 1L << 1, key_release, game);
	mlx_hook(game->win_3d, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, update, game); 
}

int	is_valid_rgb_value(char *str)
{
	int	has_digit;

	has_digit = 0;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' ' && *str != '\t'
			&& *str != '\n')
			return (0);
		if (ft_isdigit(*str))
			has_digit = 1;
		str++;
	}
	return (has_digit);
}

void	check_rgb_values(char **rgb)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_value(rgb[i]))
		{
			free_split(rgb);
			err_exit("Invalid RGB format: values must be numbers", NULL);
		}
		i++;
	}
}
