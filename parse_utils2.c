#include "cub3d.h"

void	validate_rgb_format(char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		else if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\t'
			&& str[i] != '\n')
			err_exit("Invalid character in RGB color format", NULL);
		i++;
	}
	if (comma_count != 2)
		err_exit("Invalid RGB format: must be R,G,B", NULL);
}

char	*clean_path(char *str)
{
	char	*trimmed;
	char	*result;
	int		len;

	trimmed = trim_start(str);
	len = ft_strlen(trimmed);
	while (len > 0 && (trimmed[len - 1] == ' '
			|| trimmed[len - 1] == '\t' || trimmed[len - 1] == '\n'))
		len--;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		err_exit("Memory allocation failed", NULL);
	ft_strlcpy(result, trimmed, len + 1);
	return (result);
}

int	init_parse(const char *filename, t_parse_state *state)
{
	int	fd;

	ft_memset(state, 0, sizeof(t_parse_state));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err_exit("Failed to open map file", NULL);
	return (fd);
}
