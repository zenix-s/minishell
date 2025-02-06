
#include "../include/minishell.h"

void	ft_lstdelone(t_token *lst, void (*del)(void*))
{
	printf("dentro de la funcion del0");
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	printf("dentro de la funcion del1");
	free(lst);
	lst = NULL;
}
