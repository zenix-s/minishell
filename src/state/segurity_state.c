
#include "../../include/minishell.h"


void	segurity_state(t_shell *shell)
{
	if (shell->input && *shell->input != '\0')
	{
		if (strlen(shell->input) > MAX_INPUT_LENGTH)
			ft_error("Error: line so long.\n");
		add_history(shell->input);
		
		//shell->execute = create_files_state;
		shell->execute = pipex_state;
	}
	else
		shell->execute = clean_end_state;
}
