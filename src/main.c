/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:50:42 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/25 22:34:37 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	if (tokens == NULL)
		return ;
	current = tokens;
	while (current)
	{
		printf("[[%d] - [%s]]\n", current->type, current->content);
		current = current->next;
	}
}

void	main_loop(t_shell *shell)
{
	while (1)
	{
		shell->is_done = FALSE;
		shell->execute = readline_state;
		while (shell != NULL && !shell->is_done)
		{
			shell->execute(shell);
		}
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	head();
	shell = shell_factory(env);
	main_loop(shell);
	free_shell(shell);
}
