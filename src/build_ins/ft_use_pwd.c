
#include "../../include/minishell.h"

void	use_pwd(t_token *list_env)
{
	char	*aux;

	aux = list_env -> content;

	while (list_env && (ft_strncmp ("PWD", (char*) (aux), 2) != 0))
	{
		list_env = list_env->next;
		aux = list_env -> content;
	}
	if (list_env != NULL && ft_strncmp ((char*) (aux), "PWD", 2) == 0)
		printf ("%s\n",(char*) (list_env->content));
}

