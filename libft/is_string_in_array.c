/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_string_in_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:06:05 by serferna          #+#    #+#             */
/*   Updated: 2025/02/26 09:06:05 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

uint64_t	is_string_in_array(const char *str, const char *search[])
{
	uint64_t	i;
	uint64_t	len;

	if (search == NULL)
		return (0);
	i = 0;
	while (search[i] != NULL)
	{
		len = ft_strlen(search[i]);
		if (ft_strncmp(str, search[i], len) == 0)
			return (len);
		i++;
	}
	return (0);
}
