#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && 126 >= c)
		return (1);
	else
		return (0);
}
