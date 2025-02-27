
#include "../../include/minishell.h"

//La linea final acaba el proceso.
void	clean_end_state(t_shell *shell)
{
	free(shell->input);
	free_tokens(shell->tokens);
	shell->tokens = NULL;

	shell->is_done = TRUE;
}
