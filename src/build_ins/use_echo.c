/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:27:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	use_echo(char **line_arraid)
{
	t_bool	n_flag;
	int		i;
	char	*str;

	n_flag = FALSE;
	i = 1;
	if (line_arraid[1] && ft_strncmp(line_arraid[1], "-n", 2) == 0)
	{
		n_flag = TRUE;
		while (line_arraid[i])
		{
			if (newcmp(line_arraid[i], "n") == 0)
				n_flag = FALSE;
			i++;
		}
		i = 2;
	}
	while (line_arraid[i])
	{
		str = remove_outer_quotes(line_arraid[i]);
		printf("%s", str);
		if (line_arraid[i + 1])
			printf(" ");
		free(str);
		i++;
	}
	if (!n_flag)
		printf("\n");
	g_exit_status = 0;
}
