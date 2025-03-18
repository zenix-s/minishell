/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:42:38 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/11 21:42:41 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file == -1)
			return (-1);
		shell->write = name;
		shell->mode = 1;
		close (file);
	}
	else if (ft_strcmp(aux_token->content, ">>") == 0)
	{
		file = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file == -1)
			return (-1);
		shell->write = name;
		shell->mode = 2;
		close (file);
	}
	return (0);
}

static void	before_prepare(t_shell *shell)
{
	shell->mode = 0;
	shell->write = NULL;
	shell->read = NULL;
}

int	prepare(t_shell *shell, t_token *x)
{
	int		mode;
	int		aux;
	char	*name;

	mode = 0;
	before_prepare(shell);
	while (x && x->type != PIPE)
	{
		if (x->type == REDIRECT)
		{
			if (ft_strcmp(x->content, "<") == 0)
				aux = ft_read_open(x, shell, "<");
			if (aux == -1)
				return (aux);
			if (ft_strcmp(x->content, ">") == 0 || ft_strcmp(x->content, ">>"))
			{
				name = x->next->content;
				aux = ft_write_open(x, shell, name);
				if (aux == -1)
					return (aux);
			}
			mode++;
			x = x->next;
		}
		x = x->next;
	}
	return (mode);
}

void	prepare_in_loop(t_shell *shell)
{
	t_token	*token_aux;

	token_aux = shell->tokens;
	while (token_aux)
	{
		prepare(shell, token_aux);
		while (token_aux && token_aux->type != PIPE)
			token_aux = token_aux->next;
		if (token_aux && token_aux->type == PIPE)
			token_aux = token_aux->next;
	}
}
