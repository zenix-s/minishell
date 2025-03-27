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

char	*obtain_content(char *search, t_env_token *list_env)
{
	while (list_env)
	{
		if (newcmp(list_env->key, search) == 0)
			return (list_env->value);
		list_env = list_env->next;
	}
	return (NULL);
}

//REMEMBER, this function need remove "=" in the call
void	change_content(t_env_token *list_env, char *key, char *newcont)
{
	t_env_token	*l_aux;

	l_aux = list_env;
	while (l_aux)
	{
		if (newcmp(l_aux->key, key) == 0)
		{
			free(l_aux->value);
			l_aux->value = ft_strdup(newcont);
		}
		l_aux = l_aux->next;
	}
}

int	create_new_rute(char *rute, char *step)
{
	char	*aux;

	if (newcmp(step, "..") == 0)
		rute = ft_substr(rute, 0, ft_strrint(rute, '/'));
	else
	{
		aux = ft_strjoin(rute, "/");
		rute = ft_strjoin(aux, step);
		free(aux);
	}
	if (chdir(rute) == -1)
	{
		printf("cd: no such file or directory\n");
		free(rute);
		return (-1);
	}
	free(rute);
	return (1);
}
