
#include "../../include/minishell.h"

void	free_env_tokens(t_env_token *env)
{
	t_env_token	*current;
	t_env_token	*temp;

	current = env;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}
