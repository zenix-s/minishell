
#include "../../include/minishell.h"

void	use_pwd(void)
{
	char	*result;
	char	*cwd;

	cwd = (char *)ft_calloc(1024, sizeof(char));
	result = getcwd(cwd, 1024);
	printf ("%s\n", result);
	free(result);
}

