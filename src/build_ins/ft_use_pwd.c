
#include "../../include/minishell.h"

void	use_pwd(t_token *list_env)
{
	char	*result;
	char	*cwd;
	t_token	*l_aux;

	cwd = (char *)ft_calloc(1024, sizeof(char));
	l_aux = list_env;
	result = getcwd(cwd, 1024);
	printf ("%s\n", result);
	free(result);
}

