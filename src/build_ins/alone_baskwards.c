/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_baskwards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:20:09 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/26 23:20:12 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	go_back(char **steps)
{
	char	*rute;
	char	cwd[1024];
	int		c;
	char	*aux;

	c = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror(ERR_CWD_NOT_FOUND);
		return ;
	}
	while (steps[c])
	{
		rute = getcwd(cwd, 1024);
		aux = ft_substr(rute, 0, ft_strrint(rute, '/'));
		if (chdir(aux) == -1)
		{
			chdir("/");
			free(aux);
			return ;
		}
		free(aux);
		c++;
	}
	return ;
}

int	verify_backwards_rute(char *line_arraid)
{
	char	**steps;
	int		count;

	count = 0;
	steps = ft_split(line_arraid, '/');
	while (steps[count])
	{
		if (newcmp(steps[count], "..") != 0)
		{
			ft_free(steps);
			return (-1);
		}
		count++;
	}
	go_back(steps);
	ft_free(steps);
	return (1);
}

int	use_slash(char **big_arraid, char *line_arraid)
{
	if (big_arraid[2])
	{
		printf("minishell : cd: too many arguments\n");
		return (1);
	}
	if (newcmp(line_arraid, "/") == 0)
	{
		chdir("/");
		return (1);
	}
	return (-1);
}
