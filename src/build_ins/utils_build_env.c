/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_build_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:35 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:33:36 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

/*
t_token	*new_env(t_token *list_env, char **env)
{
	int		count;
	t_token	*aux;
	char	*shell_aux;

	list_env = ft_lstnew(ft_strdup(env[0]));
	if (!list_env)
		return (NULL);
	count = 1;
	while (env[count])
	{
		aux = ft_lstnew(ft_strdup(env[count]));
		if (!aux)
			return (NULL);
		if (ft_strncmp(aux->content, "SHLVL=", 5) == 0)
		{
			shell_aux = aux->content;
			aux->content = shell_level(shell_aux);
			free(shell_aux);
		}
		ft_lstadd_back(&list_env, aux);
		count++;
	}
	return (list_env);
}
*/
/*
Esta funcion devuelve el env despues
de todas las ejecuciones hasta el momento como arraid
*/

/*
//esta funcion entrega el env hasta el = para que se tenga que escribir igual
int	size_env(char *line_env)
{
	int	count;

	count = 0;
	while (line_env[count] != '=')
		count++;
	return (count);
}
*/

int	env_is_absolute(char **cmd)
{
	if (ft_strncmp("/", cmd[0], 1) == 0)
		return (1);
	if (ft_strncmp("./", cmd[0], 2) == 0)
		return (1);
	if (ft_strncmp("../", cmd[0], 3) == 0)
		return (1);
	return (0);
}
