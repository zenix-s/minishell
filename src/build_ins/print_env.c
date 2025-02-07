
#include "../../include/minishell.h"

void	print_env(t_env_token *list_env)
{
	while (list_env)
	{
		printf("%s=%s\n", list_env->key, list_env->value);
		list_env = list_env->next;
	}
}
