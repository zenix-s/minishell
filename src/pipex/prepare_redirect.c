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
	int	file;

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
	int		mode;
	int		aux;

	mode = 0;
	before_prepare(shell);
	while (x && x->type != PIPE)
	{
		if (x->type == REDIRECT)
		{
			if (newcmp(x->content, ">") == 0 || newcmp(x->content,
					">>") == 0)
				aux = ft_write_open(x, shell, x->next->content);
			else if (newcmp(x->content, "<") == 0
				|| newcmp(x->content, "<<") == 0)
				aux = ft_read_open(x, shell);
			if (aux == -1)
				return (aux);
			mode++;
		}
		x = x->next;
	}
	return (mode);
}
