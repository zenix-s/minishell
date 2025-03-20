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

// static void	print_echo(char **line_arraid, int arg)
// {
// 	char	*aux;

// 	while (line_arraid[arg])
// 	{
// 		aux = (ft_strtrim(line_arraid[arg], "\""));
// 		if (aux != NULL)
// 			printf("%s ", aux);
// 		free(aux);
// 		arg++;
// 	}
// }

void	use_echo(char **line_arraid)
{
	t_bool	n_flag;
	int		i;

	// int		arg;
	// int		bool;
	// char	*cut;
	// cut = ft_strtrim (line_arraid[1], "n");
	// bool = 0;
	// if (!line_arraid[1])
	// 	return ;
	// if (newcmp(cut, "-") == 0)
	// {
	// 	arg = 2;
	// 	bool = 1;
	// }
	// else
	// 	arg = 1;
	// free(cut);
	// print_echo(line_arraid, arg);
	// if (bool == 0)
	// 	printf("\n");
	// for (int i = 1; line_arraid[i]; i++)
	// {
	// 	printf("ech: [%s]\n", line_arraid[i]);
	// 	if (line_arraid[i + 1])
	// 		printf(" ");
	// }
	// printf("\n");
	//
	n_flag = FALSE;
	i = 2;
	if (line_arraid[1] && newcmp(line_arraid[1], "-n") == 0)
		n_flag = TRUE;
	while (line_arraid[i])
	{
		printf("%s", line_arraid[i]);
		if (line_arraid[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
