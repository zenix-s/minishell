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
		{
			redirect_error(aux_token->next, 1);
			return (-1);
		}
		shell->read = aux_token->next->content;
		close (file);
	}
	return (0);
}

int	ft_write_open(t_token *aux_token, t_shell *shell, char *name)
{
	int		file;

	file = 0;
	if (ft_strcmp(aux_token->content, ">") == 0)
		file = ft_open(shell, file, name, 1);
	else if (ft_strcmp(aux_token->content, ">>") == 0)
		file = ft_open(shell, file, name, 2);
	if (file == -1)
	{
		redirect_error(aux_token->next, 1);
		return (-1);
	}
	shell->write = name;
	close (file);
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

	mode = 0;
	before_prepare(shell);
	while (x && x->type != PIPE)
	{
		if (x->type == REDIRECT)
		{
			printf("---1-----read => %s\n", shell->read);
			printf("---1-----write => %s\n", shell->write);
			if (ft_strcmp(x->content, ">") == 0 || ft_strcmp(x->content, ">>"))
				aux = ft_write_open(x, shell, x->next->content);
			else if (ft_strcmp(x->content, "<") == 0)
				aux = ft_read_open(x, shell, "<");
			printf("---2-----read => %s\n", shell->read);
			printf("---2-----write => %s\n", shell->write);
			if (aux == -1)
				return (aux);
			mode++;
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
