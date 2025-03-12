#include "../../../include/minishell.h"

void	parser_end_state(t_shell *shell)
{
	print_tokens(shell->tokens);
	shell->execute = clean_end_state;
	// shell->execute = segurity_state;
}
