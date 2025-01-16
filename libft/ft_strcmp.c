
#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		dif;
	size_t	x;

	dif = 0;
	x = 0;
	while (!dif && (s1[x] != '\0') && (s2[x] != '\0'))
	{
		dif = (unsigned char)s1[x] - (unsigned char)s2[x];
		x++;
	}
	if (!dif && (s1[x] == '\0' || s2[x] == '\0'))
		dif = (unsigned char)s1[x] - (unsigned char)s2[x];
	return (dif);
}