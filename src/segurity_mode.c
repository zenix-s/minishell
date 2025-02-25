
#include "../include/minishell.h"


void	segurity(t_shell *shell)
{
	if (shell->input && *shell->input != '\0')
	{
		if (strlen(shell->input) > MAX_INPUT_LENGTH)
			ft_error("Error: line so long.\n");
		add_history(shell->input);
		//select_all(&shell);
		shell->execute = redirect_state;
	}
	else
		shell->is_done = TRUE;

}
