
#include "../../include/minishell.h"

void	prepare_files(t_shell *shell)
{
	t_token	*env_aux;
	int		fd;

	env_aux = shell->tokens;
	while (env_aux)
	{
		if (ft_strcmp(env_aux->content, "<") == 0)
		{
			fd = open(env_aux->next->content, O_CREAT, 0644);
			close (fd);
		}
		if (ft_strcmp(env_aux->content, "<<") == 0)
		{
			fd = open(env_aux->next->content, O_CREAT, 0644);
			close (fd);
		}
		env_aux = env_aux->next;
	}
	shell->execute = clean_end_state;
}
