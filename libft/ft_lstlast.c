
#include "../include/minishell.h"

t_token	*ft_lstlast(t_token *lst)
{
	if (lst)
	{
		while (lst->next)
				lst = lst->next;
		return (lst);
	}
	return (NULL);
}
