
#include "../include/minishell.h"

void	ft_bzero(void *s, unsigned int n)
{
	char			*dst;
	unsigned int	x;

	dst = s;
	x = 0;
	while (x < n)
	{
		dst[x] = '\0';
		++x;
	}
}
