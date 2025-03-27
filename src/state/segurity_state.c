/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segurity_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:47:13 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/11 21:47:17 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	created_files(t_shell *shell)
{
	t_token	*aux_token;
	int		file;

	aux_token = shell->tokens;
	while (aux_token)
	{
		if (newcmp(aux_token->content, ">") == 0)
		{
			file = open(aux_token->next->content,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			close(file);
		}
		if (newcmp(aux_token->content, ">>") == 0)
		{
			file = open(aux_token->next->content,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
			close(file);
		}
		aux_token = aux_token->next;
	}
}

void	segurity_state(t_shell *shell)
{
	if (shell->input && *shell->input != '\0')
	{
		if (ft_strlen(shell->input) > MAX_INPUT_LENGTH)
			ft_error("Error: line so long.\n");
		created_files(shell);
		all_heredoc(shell);
		if (g_exit_status == 330)
		{
			shell->execute = clean_end_state;
			g_exit_status = 130;
			return ;
		}
		shell->execute = pipex_state;
	}
	else
		shell->execute = clean_end_state;
}
