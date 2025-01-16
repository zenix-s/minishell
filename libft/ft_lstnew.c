
#include "../minishell.h"

t_token	*ft_lstnew(void *content)
{
	t_token	*head;

	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}
