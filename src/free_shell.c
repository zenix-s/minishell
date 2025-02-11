
#include "../include/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->env)
		free_env_tokens(shell->env);
	free(shell);
}
