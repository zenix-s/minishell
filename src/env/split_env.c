/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:08 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:19 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_env(char *env)
{
	char	**split;
	size_t	i;

	i = 0;
	split = malloc(sizeof(char *) * 2);
	if (!split)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	split[0] = malloc(i + 1);
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	ft_strncpy(split[0], env, i);
	split[0][i] = '\0';
	split[1] = ft_strdup(env + i + 1);
	if (!split[1])
	{
		free(split[0]);
		free(split);
		return (NULL);
	}
	return (split);
}
