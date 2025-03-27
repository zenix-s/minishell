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

static int	ft_all_spaces(char *world)
{
	int	x;

	x = 0;
	while (world[x])
	{
		x++;
		if (world[x] != ' ')
			return (0);
	}
	return (-1);
}

void	select_all(t_shell *shell)
{
	const char	*split[] = {" ", NULL};
	t_shell		*aux;
	char		**line_arraid;
	char		*act_command;

	if (shell->tokens == NULL || ft_all_spaces(shell->tokens->content) == -1)
	{
		shell->execute = clean_end_state;
		return ;
	}
	aux = shell;
	line_arraid = special_split(aux->tokens->content, split, NULL);
	act_command = remove_outer_quotes(line_arraid[0]);
	free(line_arraid[0]);
	line_arraid[0] = ft_strdup(act_command);
	if (act_command)
		free(act_command);
	if (s_build(aux, line_arraid) == 5)
		execute_cmd(line_arraid, shell->env);
	if (line_arraid)
		ft_free(line_arraid);
	shell->execute = clean_end_state;
}

int	s_build(t_shell *shell, char **line_arraid)
{
	if (is_string_redirect(line_arraid[0]))
		return (1);
	if (newcmp(line_arraid[0], "pwd") == 0)
		use_pwd(line_arraid);
	else if (newcmp(line_arraid[0], "env") == 0)
		use_env(shell->env, line_arraid, FALSE);
	else if (newcmp(line_arraid[0], "echo") == 0)
		use_echo(line_arraid);
	else if (newcmp(line_arraid[0], "export") == 0)
	{
		if (!line_arraid[1])
			print_env(shell->env, TRUE);
		else
			use_export(&shell, line_arraid, 0);
	}
	else if (newcmp(line_arraid[0], "unset") == 0)
		use_unset(shell, line_arraid);
	else if (newcmp(line_arraid[0], "cd") == 0)
		use_cd(shell->env, line_arraid, shell);
	else if (newcmp(line_arraid[0], "exit") == 0)
		use_exit(shell, line_arraid);
	else
		return (5);
	return (1);
}
