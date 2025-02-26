
#include "../../include/minishell.h"

void	error_state(int mod)
{
	if (mod == -1)
		perror("Error opening file");
	//shell->execute = cleaner;
}
