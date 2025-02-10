
#include "../include/minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
	temp = ft_lstlast(*lst);
	if (temp)
		temp->next = new_token;
	else
		*lst = new_token;
}
