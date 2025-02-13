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
		if (ft_strncmp(l_aux->key, aux_line_k, ft_strlen(l_aux->key)) == 0)
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

static char	*prepared(char *line)
{
	int		i;
	int		j;
	int		length;
	char	*result;

	i = 0;
	j = 0;
	length = ft_strlen(line);
	result = malloc(length + 1);
	if (result == NULL)
	{
		return (NULL);
	}
	while (i < length)
	{
		if (line[i] == '\"')
		{
			i++;
		}
		result[j] = line[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

void	use_export(t_shell **shell, char **line_arraid)
{
	int		count;
	int		mode;
	t_shell	*t_aux;
	char	*real_value;

	t_aux = *shell;
	count = 1;
	while (line_arraid[count])
	{
		real_value = prepared(line_arraid[count]);
		if (real_value != NULL)
		{
			mode = remplace(&t_aux->env, real_value);
			if (mode == 1)
				create_var(&t_aux->env, real_value);
			free(real_value);
		}
		else
		{
			mode = remplace(&t_aux->env, line_arraid[count]);
			if (mode == 1)
				create_var(&t_aux->env, line_arraid[count]);
		}
		count++;
	}
}
