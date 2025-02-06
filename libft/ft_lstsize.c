
#include "../include/minishell.h"

int	ft_lstsize(t_token *lst)
{
	int	x;

	x = 0;
	while (lst)
	{
		x++;
		lst = lst->next;
	}
	return (x);
}
