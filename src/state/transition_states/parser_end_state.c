#include "../../../include/minishell.h"

void parser_end_state(t_shell *shell)
{
	shell->execute = segurity_state;
}
