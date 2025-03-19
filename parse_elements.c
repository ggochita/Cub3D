/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:18:20 by ayassaye          #+#    #+#             */
/*   Updated: 2025/03/13 20:27:55 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/** Met à jour l'état du parsing en fonction de l'identifiant */
void	update_parse_state(char *trimmed, t_parse_state *state)
{
	update_ns_textures(trimmed, state);
	update_ew_textures(trimmed, state);
	update_floor_ceiling(trimmed, state);
}

/** Vérifie l'ordre des éléments et leur présence */
void	validate_element_order(char *line, t_parse_state *state)
{
	char	*trimmed;

	if (is_empty_line(line))
		return ;
	trimmed = trim_start(line);
	if (state->map_started && !is_valid_char(trimmed[0]))
		err_exit("Invalid element after map section", NULL);
	if (is_valid_identifier(line))
	{
		if (state->map_started)
			err_exit("Texture/color definition after map", NULL);
		update_parse_state(trimmed, state);
	}
	else if (!is_empty_line(line) && is_valid_char(trimmed[0]))
		state->map_started = 1;
}

/** Traite un identifiant et met à jour le jeu */
void	process_identifier(char *line, t_game *game)
{
	char	*trimmed;

	trimmed = trim_start(line);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		game->textures_paths.no = clean_path(trimmed + 3);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		game->textures_paths.so = clean_path(trimmed + 3);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		game->textures_paths.we = clean_path(trimmed + 3);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		game->textures_paths.ea = clean_path(trimmed + 3);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		game->floor_color = parse_color(trimmed + 2);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		game->ceiling_color = parse_color(trimmed + 2);
}

/** Convertit une couleur "R,G,B" en un entier */
int	parse_color(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	char	*trimmed;

	trimmed = trim_start(line);
	validate_rgb_format(trimmed);
	rgb = ft_split(trimmed, ',');
	if (!rgb)
		err_exit("Memory allocation failed for color parsing", NULL);
	if (ft_array_size(rgb) != 3)
	{
		free_split(rgb);
		err_exit("Invalid RGB format: must have 3 values", NULL);
	}
	check_rgb_values(rgb);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		err_exit("RGB values must be between 0 and 255", NULL);
	return ((r << 16) | (g << 8) | b);
}

/** Parse les éléments du fichier .cub */
void	parse_elements(const char *filename, t_game *game)
{
	int				fd;
	char			*line;
	t_parse_state	state;

	fd = init_parse(filename, &state);
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(line, &state, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	finalize_parse(&state, game);
}
