
#include "../../include/minishell.h"

void	use_pwd(char **n_env)
{
	char	*pwd_line;
	int		count;

	count = 0;
	while (n_env[count] != NULL && (ft_strncmp ("PWD", n_env[count], 2) != 0))
	{
		count++;
	}
	if (n_env[count] != NULL && ft_strncmp (n_env[count], "PWD", 2) == 0)
		printf("%s", n_env[count]);
}

