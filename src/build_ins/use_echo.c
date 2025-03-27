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

static t_bool	is_only_n_and_digits(const char *str)
{
	int	i;

	i = 2;
	if (str[0] != '-' || str[1] != 'n')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	use_echo(char **line_arraid)
{
	t_bool	n_flag;
	int		i;
	char	*str;

	i = 1;
	n_flag = FALSE;
	if (line_arraid[1])
		n_flag = is_only_n_and_digits(line_arraid[1]);
	if (n_flag == TRUE)
		i = 2;
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
