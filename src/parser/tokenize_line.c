/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:08 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:19 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*new_str;
	size_t	i;

	new_str = (char *)malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*get_env_value(const t_env_token *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*expand_env_var(const char *line, uint64_t *i, const t_env_token *env)
{
	int		len;
	char	*var_name;
	char	*value;
	int		start;

	start = *i + 1;
	len = 0;
	if (!ft_isalpha(line[start]) && line[start] != '_')
		return (NULL);
	while (ft_isalnum(line[start + len]) || line[start + len] == '_')
		len++;
	var_name = ft_strndup(&line[start], len);
	if (!var_name)
		return (NULL);
	value = get_env_value(env, var_name);
	free(var_name);
	*i = start + len - 1;
	return (value);
}

t_token	*tokenize_line(char *line, t_env_token *env)
{
	t_token		*tokens;
	uint64_t	i;
	char		buffer[1024];
	uint64_t	buf_index;
	t_quote		quote_state;
	int			consecutive_space;
	uint64_t	len;
	char		*env_value;

	tokens = NULL;
	i = 0;
	buf_index = 0;
	quote_state = NONE;
	consecutive_space = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '"' && quote_state != SINGLE)
		{
			if (quote_state == DOUBLE)
				quote_state = NONE;
			else
				quote_state = DOUBLE;
			buffer[buf_index++] = line[i++];
		}
		else if (line[i] == '\'' && quote_state != DOUBLE)
		{
			if (quote_state == SINGLE)
				quote_state = NONE;
			else
				quote_state = SINGLE;
			buffer[buf_index++] = line[i++];
		}
		else if (line[i] == '$' && quote_state != SINGLE)
		{
			env_value = expand_env_var(line, &i, env);
			if (env_value)
			{
				while (*env_value)
					buffer[buf_index++] = *env_value++;
			}
			else
			{
				buffer[buf_index++] = line[i++];
			}
		}
		else if (quote_state == NONE && is_separator(&line[i], &len))
		{
			if (buf_index > 0)
			{
				buffer[buf_index] = '\0';
				add_token(&tokens, buffer);
				buf_index = 0;
			}
			ft_strncpy(buffer, &line[i], len);
			buffer[len] = '\0';
			add_token(&tokens, buffer);
			i += len;
		}
		else
		{
			if ((line[i] == ' ' || line[i] == '\t') && quote_state == NONE)
			{
				if (consecutive_space == 0)
				{
					buffer[buf_index++] = ' ';
					consecutive_space = 1;
				}
				i++;
				continue ;
			}
			consecutive_space = 0;
			buffer[buf_index++] = line[i++];
		}
	}
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		add_token(&tokens, buffer);
	}
	return (tokens);
}
