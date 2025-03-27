/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/02/25 20:11:11 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*get_var_name(const char *content, uint64_t *start)
{
	uint64_t	len;
	char		*var_name;

	len = 0;
	if (content[*start] == '"'
		|| content[*start] == '?'
		|| content[*start] == '\'')
		len++;
	while (ft_isalnum(content[*start + len]) || content[*start + len] == '_')
		len++;
	var_name = ft_strndup(&content[*start], len);
	if (!var_name)
		return (NULL);
	*start += len;
	return (var_name);
}
