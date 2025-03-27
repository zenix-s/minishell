/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:32:56 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:32:58 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	remplace(t_env_token **list_env, char *line)
{
	t_env_token	*l_aux;
	char		*aux_line_k;
	char		*aux_line_v;

	aux_line_k = ft_substr(line, 0, ft_strrint(line, '='));
	aux_line_v = ft_substr(line, ft_strrint(line, '=') + 1, ft_strlen(line));
	l_aux = *list_env;
	while (l_aux)
	{
		if (newcmp(l_aux->key, aux_line_k) == 0)
		{
			free(l_aux->key);
			free(l_aux->value);
			l_aux->key = ft_strdup(aux_line_k);
			l_aux->value = ft_strdup(aux_line_v);
			free(aux_line_k);
			free(aux_line_v);
			return (0);
		}
		l_aux = l_aux->next;
	}
	free(aux_line_k);
	free(aux_line_v);
	return (1);
}

static void	create_var(t_env_token **list_env, char *line)
{
	t_env_token	*new_node;
	int			x;
	int			bool;

	x = 0;
	bool = 0;
	while (line[x] && bool == 0)
	{
		if (line[x] == '=')
			bool = 1;
		x++;
	}
	if (bool == 1)
	{
		new_node = new_env_token(line);
		if (!new_node)
			return ;
		if (!env_list_add_back(list_env, new_node))
			return ;
	}
}

static t_bool	is_valid_export(char *content, int *status)
{
	if (is_valid_env_key(content))
		return (TRUE);
	printf("minishell: export: %s: not a valid identifier\n", content);
	*status = 1;
	return (FALSE);
}

void	use_export(t_shell **shell, char **line_arraid, int count)
{
	char	*real_value;
	int		exit_status;

	exit_status = 0;
	while (line_arraid[++count])
	{
		real_value = remove_outer_quotes(line_arraid[count]);
		if (!is_valid_export(real_value, &exit_status))
			continue ;
		if (real_value != NULL)
		{
			if (remplace(&(*shell)->env, real_value) == 1)
				create_var(&(*shell)->env, real_value);
			free(real_value);
		}
		else
		{
			if (remplace(&(*shell)->env, line_arraid[count]) == 1)
				create_var(&(*shell)->env, line_arraid[count]);
		}
	}
	g_exit_status = exit_status;
}
