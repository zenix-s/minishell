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

t_bool	is_valid_env_key(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (FALSE);
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (FALSE);
	i++;
	while (key[i] != '\0' && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_env_token	*new_env_token(char *content)
{
	t_env_token	*new_token;
	char		**split;

	new_token = malloc(sizeof(t_env_token));
	if (!new_token)
		return (NULL);
	new_token->next = NULL;
	new_token->key = NULL;
	new_token->value = NULL;
	if (!content)
		return (new_token);
	split = split_env(content);
	if (!split)
	{
		free(new_token);
		return (NULL);
	}
	new_token->key = split[0];
	new_token->value = split[1];
	free(split);
	return (new_token);
}
