/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:39:05 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/25 15:39:09 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirect_error(t_token *list, int mode)
{
	if (mode == 1)
	{
		printf("bash: ");
		printf("%s", list->content);
		printf(": No such file or directory\n");
	}
	if (mode == 2)
	{
		printf("bash: ");
		printf("%s", list->content);
		printf(": Permission denied\n");
	}
}

int	ft_open(t_shell *shell, int file, char *name, int mode)
{
	if (mode == 1)
	{
		file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file == -1)
			return (-1);
		shell->mode = 1;
		return (file);
	}
	else if (mode == 2)
	{
		file = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file == -1)
			return (-1);
		shell->mode = 2;
		return (file);
	}
	return (-1);
}
