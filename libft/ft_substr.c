
#include "../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	char	*dst;
	size_t	lens;

	x = 0;
	if (!s)
		return (NULL);
	lens = ft_strlen((char *)s);
	if (len == 0 || lens == 0)
		return (ft_strdup(""));
	if (start >= lens)
		return (ft_strdup(""));
	if (len > lens - start)
		len = lens - start;
	dst = (char *)malloc(sizeof(char) * (len +1));
	if (!dst)
		return (0);
	while ((start < ft_strlen(s)) && (x < len))
	{
		dst[x] = s[start];
		start++;
		x++;
	}
	dst[x] = '\0';
	return (dst);
}
