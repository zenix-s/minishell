/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:18:16 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/25 22:18:22 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	segurity_loop(t_token *env_aux, int fd)
{
	while (env_aux->type != PIPE)
	{
		if (newcmp(env_aux->content, ">") == 0)
			fd = open(env_aux->next->content, O_RDONLY);
		else if (newcmp(env_aux->content, ">") == 0)
			fd = open(env_aux->next->content, O_CREAT, 0644);
		else if (newcmp(env_aux->content, ">>") == 0)
			fd = open(env_aux->next->content, O_CREAT, 0644);
		if (fd == -1)
		{
			while (env_aux->type != PIPE)
				env_aux = env_aux->next;
		}
		else
			env_aux = env_aux->next;
		close(fd);
	}
}

void	create_files_state(t_shell *shell)
{
	t_token	*env_aux;
	int		fd;

	fd = 0;
	env_aux = shell->tokens;
	while (env_aux)
	{
		segurity_loop(env_aux, fd);
		env_aux = env_aux->next;
	}
	shell->execute = pipex_state;
}
