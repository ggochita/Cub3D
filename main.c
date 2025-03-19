#include "cub3d.h"

void	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		err_exit("File must have .cub extension", NULL);
}

static void	map_keys(t_game *game)
{
	for (int i = 0; i < 7; i++)
		game->keys[i] = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	if (argc != 2)
		err_exit("Usage: ./cub3D <map.cub>", NULL);
	check_file_extension(argv[1]);
	game.mlx = mlx_init();
	if (!game.mlx)
		err_exit("Error: Failed to initialize MiniLibX.", NULL);
	parse_elements(argv[1], &game);
	load_textures(&game);
	load_map(argv[1], &map);
	validate_map(&map);
	game.map = &map;
	map_keys(&game);
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}

void	update_ew_textures(char *trimmed, t_parse_state *state)
{
	if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		if (state->we_found)
			err_exit("Duplicate texture identifier: WE", NULL);
		state->we_found = 1;
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		if (state->ea_found)
			err_exit("Duplicate texture identifier: EA", NULL);
		state->ea_found = 1;
	}
}

void	update_floor_ceiling(char *trimmed, t_parse_state *state)
{
	if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		if (state->f_found)
			err_exit("Duplicate color identifier: F", NULL);
		state->f_found = 1;
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (state->c_found)
			err_exit("Duplicate color identifier: C", NULL);
		state->c_found = 1;
	}
}
