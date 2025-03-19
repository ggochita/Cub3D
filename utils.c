#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	err_exit(const char *message, t_map *map)
{
	if (map)
		free_map(map);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	finalize_parse(t_parse_state *state, t_game *game)
{
	check_required_elements(state);
	check_texture_file(game->textures_paths.no);
	check_texture_file(game->textures_paths.so);
	check_texture_file(game->textures_paths.we);
	check_texture_file(game->textures_paths.ea);
}
