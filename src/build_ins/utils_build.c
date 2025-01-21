
#include "../../include/minishell.h"

//esta funcion entrega el env hasta el = para que se tenga que escribir igual
int	size_env(char *line_env)
{
	int	count;

	count = 0;
	while (line_env[count] != '=')
		count++;
	return (count);
}


