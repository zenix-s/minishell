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

int	ft_read_open(t_token *aux_token, t_shell *shell)
{
	int		file;

	if (newcmp(aux_token->content, "<") == 0)
	{
		file = open(aux_token->next->content, O_RDONLY);
		if (file == -1)
		{
			redirect_error(aux_token->next, 1);
			return (-1);
		}
		if (shell->read != NULL)
			free(shell->read);
		shell->read = ft_strdup(aux_token->next->content);
		close(file);
	}
	if (newcmp(aux_token->content, "<<") == 0)
	{
		if (shell->read != NULL)
			free(shell->read);
		shell->read = generate_here_doc_file_name(shell->n_pipex);
	}
	return (0);
}

int	ft_write_open(t_token *aux_token, t_shell *shell, char *name)
{
	int	file;

	file = 0;
	if (newcmp(aux_token->content, ">") == 0)
		file = ft_open(shell, file, name, 1);
	else if (newcmp(aux_token->content, ">>") == 0)
		file = ft_open(shell, file, name, 2);
	if (file == -1)
	{
		redirect_error(aux_token->next, 1);
		return (-1);
	}
	shell->write = name;
	close(file);
	return (0);
}

static void	before_prepare(t_shell *shell)
{
	shell->mode = 0;
	shell->write = NULL;
	if (shell->read != NULL)
		free(shell->read);
	shell->read = NULL;
}

int	prepare(t_shell *shell, t_token *x)
{
	int	mode;
	int	aux;
	t_token *aux_tok;

	mode = 0;
	aux_tok = x;
	before_prepare(shell);
	while (aux_tok && aux_tok->type != PIPE)
	{
		if (aux_tok->type == REDIRECT)
		{
			if (newcmp(aux_tok->content, ">") == 0 || newcmp(aux_tok->content, ">>") == 0)
				aux = ft_write_open(x, shell, aux_tok->next->content);
			else if (newcmp(aux_tok->content, "<") == 0 || newcmp(aux_tok->content,
					"<<") == 0)
				aux = ft_read_open(x, shell);
			if (aux == -1)
				return (aux);
			mode++;
		}
		aux_tok = aux_tok->next;
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
		{
			shell->n_pipex++;
			token_aux = token_aux->next;
		}
	}
}
