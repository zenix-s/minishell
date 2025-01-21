
#include "../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		k;
	int		lens1;
	int		lens2;

	i = 0;
	k = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	newstr = malloc(lens1 + lens2 + 1);
	if (!newstr)
		return (NULL);
	while (s1[i])
		newstr[k++] = s1[i++];
	i = 0;
	while (s2[i])
		newstr[k++] = s2[i++];
	newstr[k] = '\0';
	return (newstr);
}