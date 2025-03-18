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

static void	print_echo(char **line_arraid, int arg)
{
	char	*aux;

	while (line_arraid[arg])
	{
		aux = (ft_strtrim(line_arraid[arg], "\""));
		if (aux != NULL)
			printf("%s ", aux);
		free(aux);
		arg++;
	}
}

void	use_echo(char **line_arraid)
{
	int		arg;
	int		bool;
	char	*cut;

	cut = ft_strtrim (line_arraid[1], "n");
	bool = 0;
	if (!line_arraid[1])
		return ;
	if (newcmp(cut, "-") == 0)
	{
		arg = 2;
		bool = 1;
	}
	else
		arg = 1;
	free(cut);
	print_echo(line_arraid, arg);
	if (bool == 0)
		printf("\n");
}
