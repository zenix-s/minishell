/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:08 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:19 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*shell_level(char *var)
{
	char	**level;
	int		number;
	char	*aux_n;
	char	*result;

	level = ft_split(var, '=');
	number = ft_atoi(level[1]);
	number++;
	aux_n = ft_itoa(number);
	result = ft_strdup(level[0]);
	ft_super_strcat(&result, "=");
	ft_super_strcat(&result, aux_n);
	free(aux_n);
	ft_free(level);
	return (result);
}

static t_bool	process_env(char *content, int *count, t_env_token **list_env)
{
	t_env_token	*new_token;

	new_token = new_env_token(content);
	if (!new_token)
		return (FALSE);
	if (!env_list_add_back(list_env, new_token))
		return (FALSE);
	(*count)++;
	return (TRUE);
}

t_bool	create_list_env(char **env, t_env_token **list_env)
{
	int		count;
	char	*foo;

	count = 0;
	*list_env = NULL;
	foo = NULL;
	while (env[count])
	{
		if (ft_strncmp(env[count], "SHLVL=", 6) == 0)
		{
			foo = shell_level(env[count]);
			if (!process_env(foo, &count, list_env))
				return (free(foo), FALSE);
			free(foo);
			continue ;
		}
		process_env(env[count], &count, list_env);
	}
	return (TRUE);
}
