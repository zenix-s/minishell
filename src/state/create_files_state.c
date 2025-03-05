
#include "../../include/minishell.h"

void	create_files_state(t_shell *shell)
{
	t_token	*env_aux;
	int		fd;

	env_aux = shell->tokens;
	while (env_aux)
	{
		while (env_aux->type != PIPE)
		{

			if (ft_strcmp(env_aux->content, ">") == 0)
			{
				fd = open(env_aux->next->content, O_CREAT, 0644);
				close (fd);
			}
			if (ft_strcmp(env_aux->content, ">>") == 0)
			{
				fd = open(env_aux->next->content, O_CREAT, 0644);
				close (fd);
			}
			env_aux = env_aux->next;
		}
		env_aux = env_aux->next;
	}
	shell->execute = pipex_state;
}
