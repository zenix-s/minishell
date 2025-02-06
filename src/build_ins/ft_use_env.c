
#include "../../include/minishell.h"

void	use_env(t_token *list_env)
{
	char	*aux;

	while (list_env)
	{
		aux = (list_env->content);
		printf ("%s\n", aux);
		list_env = list_env->next;
	}
}
