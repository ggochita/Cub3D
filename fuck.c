#include "cub3d.h"

void	process_line(char *line, t_parse_state *state, t_game *game)
{
	if (!is_empty_line(line))
	{
		validate_element_order(line, state);
		if (is_valid_identifier(line))
			process_identifier(line, game);
	}
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

void	check_required_elements(t_parse_state *state)
{
	if (!state->no_found || !state->so_found || !state->we_found
		|| !state->ea_found || !state->f_found || !state->c_found)
		err_exit("Missing texture or color definitions", NULL);
}

void	update_ns_textures(char *trimmed, t_parse_state *state)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		if (state->no_found)
			err_exit("Duplicate texture identifier: NO", NULL);
		state->no_found = 1;
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		if (state->so_found)
			err_exit("Duplicate texture identifier: SO", NULL);
		state->so_found = 1;
	}
}
