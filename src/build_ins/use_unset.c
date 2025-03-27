/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:07 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:33:10 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env_token	*prev(t_env_token **list_env, char *line)
{
	t_env_token	*l_aux;

	l_aux = *list_env;
	while (l_aux)
	{
		if (newcmp (l_aux->next->key, line) != 0)
			l_aux = l_aux->next;
		else
			return (l_aux);
	}
	return (NULL);
}

static t_env_token	*search_a(t_env_token *list_env, char *line)
{
	t_env_token	*l_aux;
	char		*char_env;

	if (!list_env)
		return (NULL);
	l_aux = list_env;
	while (l_aux)
	{
		char_env = l_aux->key;
		if (newcmp(line, char_env) == 0)
			return (l_aux);
		l_aux = l_aux->next;
	}
	return (NULL);
}

void	use_unset(t_shell *shell, char **line_arraid)
{
	int			count;
	t_env_token	*list_aux;
	t_env_token	*prev_aux;
	char		*aux;

	count = 1;
	while (line_arraid[count] != NULL)
	{
		aux = remove_outer_quotes(line_arraid[count]);
		list_aux = search_a(shell->env, aux);
		if (list_aux)
		{
			prev_aux = prev(&shell->env, list_aux->key);
			if (prev_aux->next != NULL)
				prev_aux->next = prev_aux->next->next;
			else
				prev_aux->next = NULL;
			free(list_aux->key);
			free(list_aux->value);
			free(list_aux);
		}
		free (aux);
		list_aux = shell->env;
		count++;
	}
}
