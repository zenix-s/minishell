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

t_bool	create_list_env(char **env, t_env_token **list_env)
{
	t_env_token	*new_token;
	int			count;

	count = 0;
	*list_env = NULL;
	while (env[count])
	{
		new_token = new_env_token(env[count]);
		if (!new_token)
			return (FALSE);
		if (!env_list_add_back(list_env, new_token))
			return (FALSE);
		count++;
	}
	return (TRUE);
}
