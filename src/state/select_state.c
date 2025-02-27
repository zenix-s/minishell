/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:27:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*used to parse a command line and execute the corresponding built-in function.
*"echo", "pwd", "export", "unset", "env", and "exit" commands.
*it attempts to execute the command as an external program.
*/
void	select_all(t_shell *shell)
{
	t_shell	*aux;
	t_token	*env_aux;
	char	**line_arraid;

	env_aux = shell->tokens;
	aux = shell;
	line_arraid = ft_split(aux->tokens->content, ' ');
	if (s_build(aux, line_arraid) == 5)
		execute_cmd(line_arraid, shell->env);
	ft_free(line_arraid);
	shell->execute = cleaner;
}

int	s_build(t_shell *shell, char **line_arraid)
{
	if (ft_strcmp(line_arraid[0], "pwd") == 0)
		use_pwd();
	else if (ft_strcmp(line_arraid[0], "env") == 0)
		print_env(shell->env);
	else if (ft_strcmp(line_arraid[0], "echo") == 0)
		use_echo(line_arraid);
	else if (ft_strcmp(line_arraid[0], "export") == 0)
	{
		if (!line_arraid[1])
			print_env(shell->env);
		else
			use_export(&shell, line_arraid);
	}
	else if (ft_strcmp(line_arraid[0], "unset") == 0)
		use_unset(shell, line_arraid);
	else if (ft_strcmp(line_arraid[0], "cd") == 0)
		use_cd(shell->env, line_arraid, shell);
	else if (ft_strcmp(line_arraid[0], "exit") == 0)
	{
		free_shell(shell);
		exit(0);
	}
	else
		return (5);
	return (1);
}
