
#include "../include/minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!new)
		return ;
	temp = ft_lstlast(*lst);
	if (temp)
		temp->next = new;
	else
		*lst = new;
}
