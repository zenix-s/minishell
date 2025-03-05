
#include "../../include/minishell.h"

int	ft_read_open(t_token *aux_token, t_shell *shell, char *s)
{
	int	file;

	if (ft_strcmp(aux_token->content, s) == 0)
	{
		file = open(aux_token->next->content, O_RDONLY);
		if (file == -1)
			return (-1);
		shell->read = aux_token->next->content;
		close (file);
	}
	return (0);
}

int	ft_write_open(t_token *aux_token, t_shell *shell, char *name)
{
	int		file;

	if (ft_strcmp(aux_token->content, ">") == 0)
	{
		file = open(name, O_CREAT | O_WRONLY |O_TRUNC, 0644);
		if (file == -1)
			return (-1);
		shell->write = name;
		shell->mode = 1;
		close (file);
	}
	else if (ft_strcmp(aux_token->content, ">>") == 0)
	{
		file = open(name, O_CREAT | O_WRONLY |O_TRUNC, 0644);
		if (file == -1)
			return (-1);
		shell->write = name;
		shell->mode = 2;
		close (file);
	}
	return (0);
}

int	prepare(t_shell *shell, t_token *aux_token)
{
	int		mode;
	int		aux;
	char	*foo;

	mode = 0;
	while (aux_token && aux_token->type != PIPE)
	{
		if (aux_token->type == REDIRECT)
		{
			if (ft_strcmp(aux_token->content, "<<") == 0) //este es mas largo
				shell->here[0] = aux_token->next->content;
			aux = ft_read_open(aux_token, shell, "<");
			if (aux == -1)
				return (-1);
			foo = aux_token->next->content;
			aux = ft_write_open(aux_token, shell, foo);
			if (aux == -1)
				return (-1);
			mode++;
			aux_token = aux_token->next;
		}
		aux_token = aux_token->next;
	}
	return (mode);
}