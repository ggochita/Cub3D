#include "cub3d.h"

void	load_texture(void *mlx, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		err_exit("Failed to load texture file.", NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

void	load_textures(t_game *game)
{
	load_texture(game->mlx, &game->textures.no, game->textures_paths.no);
	load_texture(game->mlx, &game->textures.so, game->textures_paths.so);
	load_texture(game->mlx, &game->textures.we, game->textures_paths.we);
	load_texture(game->mlx, &game->textures.ea, game->textures_paths.ea);
}
