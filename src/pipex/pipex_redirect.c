
#include "../../include/minishell.h"

int	pipex_redirect(t_shell *shell, t_token *aux_token)
{
	char	**cmd;

	cmd = ft_split(aux_token->content, ' ');
	printf("demtro de pipex redirect --> %s\n", cmd[0]);
	if (shell->read != NULL && shell->write == NULL)
	{
		read_alone(shell, cmd);
		ft_free(cmd);
		return (1);
	}
	else if (shell->read == NULL && shell->write != NULL)
	{
		write_alone(shell, cmd);
		ft_free(cmd);
		return (1);
	}
	else if (shell->read != NULL && shell->write != NULL)
	{
		full_redirect(shell, cmd);
		ft_free(cmd);
		return (1);
	}
	ft_free(cmd);
	return (0);
}
