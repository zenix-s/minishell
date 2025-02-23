/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:24 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:33:25 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*busca por la clave y da la clave con el contenido
*/
char	*obtain_content(char *search, t_env_token *list_env)
{
	while (list_env)
	{
		if (ft_strcmp(list_env->key, search) == 0)
			return ((char *)list_env->value);
		list_env = list_env->next;
	}
	return (NULL);
}

//REMEMBER, this function need remove "=" in the call
void	change_content(t_env_token **list_env, char *key, char *newcont)
{
	t_env_token	*l_aux;

	l_aux = *list_env;
	while (l_aux)
	{
		if (ft_strcmp(l_aux->key, key) == 0)
		{
			free(l_aux->value);
			l_aux->value = ft_strdup(newcont);
		}
		l_aux = l_aux->next;
	}
}
