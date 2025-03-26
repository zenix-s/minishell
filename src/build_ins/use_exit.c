/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:14:27 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/24 00:14:29 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	specific(t_shell *shell, char **line_arraid)
{
	if (line_arraid[1] && newcmp(line_arraid[1], "--") == 0)
	{
		shell->exit_status = 0;
		exit_state(shell);
	}
	if (line_arraid[1] && newcmp(line_arraid[1], "-") == 0)
	{
		printf("minishell: exit: numeric argument required\n");
		shell->exit_status = 2;
		exit_state(shell);
	}
}

void	use_exit(t_shell *shell, char **line_arraid)
{
	printf("exit\n");
	specific(shell, line_arraid);
	if (get_array_string_size(line_arraid) >= 2 &&
		!is_string_numeric(line_arraid[1]))
	{
		printf("minishell: exit: numeric argument required\n");
		shell->exit_status = 2;
		exit_state(shell);
	}
	if (get_array_string_size(line_arraid) >= 3)
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	else if (get_array_string_size(line_arraid) == 2)
	{
		shell->exit_status = ft_atoi(line_arraid[1]);
		exit_state(shell);
	}
	else
	{
		shell->exit_status = 0;
		exit_state(shell);
	}
}
