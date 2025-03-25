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

void	use_exit(t_shell *shell, char **line_arraid)
{
	printf("exit\n");
	free_shell(shell);
	if (get_array_string_size(line_arraid) >= 3)
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_status = 127;
		return ;
	}
	else if (get_array_string_size(line_arraid) == 2)
		if (ft_isalpha(atoi(line_arraid[1])) == 0)
			printf("pito\n");
		else
			exit(ft_atoi(line_arraid[1]));
	else
		exit(0);
}
