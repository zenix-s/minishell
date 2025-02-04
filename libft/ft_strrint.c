
#include "../include/minishell.h"

int	ft_strrint(const char *s, int c)
{
	int		y;

	y = ft_strlen(s) -1 ;
	while (0 <= y)
	{
		if (s[y] == (char)c)
		{
			return (y);
		}
		--y;
	}
	return (-1);
}