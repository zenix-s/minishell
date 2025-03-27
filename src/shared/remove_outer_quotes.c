/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_outer_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:00 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:42 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_quote_amount(char *str)
{
	int		amount;
	int		i;
	t_bool	can_count;
	t_quote	quote;

	amount = 0;
	can_count = FALSE;
	i = 0;
	quote = NONE;
	while (str[i])
	{
		quote = get_quote_type(quote, str[i]);
		if (quote != NONE)
			can_count = TRUE;
		if (quote == NONE && can_count)
		{
			amount++;
			can_count = FALSE;
		}
		i++;
	}
	if (quote != NONE)
		amount++;
	return (amount);
}

char	*remove_outer_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	t_quote	quote;

	new_str = malloc(ft_strlen(str) - get_quote_amount(str) + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	j = 0;
	quote = NONE;
	while (str[++i])
	{
		if ((quote == NONE && get_quote_type(quote, str[i]) != NONE)
			|| (quote != NONE && get_quote_type(quote, str[i]) == NONE))
			quote = get_quote_type(quote, str[i]);
		else
		{
			new_str[j] = str[i];
			j++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

t_bool	add_quotes(char *value, char **new_value)
{
	char	*aux;

	aux = (char *)malloc(sizeof(char) * (ft_strlen(value) + 3));
	if (!aux)
		return (FALSE);
	aux[0] = '"';
	ft_strcpy(aux + 1, value);
	aux[ft_strlen(value) + 1] = '"';
	aux[ft_strlen(value) + 2] = '\0';
	free(*new_value);
	*new_value = aux;
	return (TRUE);
}
