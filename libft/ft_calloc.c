
#include "../include/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*des;

	if (size > 0 && count > ULONG_MAX / size)
		return (NULL);
	des = (void *)malloc(count * size);
	if (des == NULL)
		return (NULL);
	ft_bzero (des, count * size);
	return (des);
}
