
#include "../../include/minishell.h"

void	use_pwd(t_token *list_env)
{
	char	*aux;
	int		x;
	char	*result;

	aux = list_env -> content;

	while (list_env && (ft_strncmp("PWD", (char *) (aux), 2) != 0))
	{
		list_env = list_env->next;
		aux = list_env -> content;
	}
	if (list_env != NULL && ft_strncmp((char *) (aux), "PWD", 2) == 0)
	{
		x = ft_strlen(aux);
		result = ft_substr(list_env->content, 4, x);
		printf("%s\n", result);
		free(result);
	}
}

