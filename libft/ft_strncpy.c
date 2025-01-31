/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strncpy(char *destination, const char *source, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}
	while (i < len)
	{
		destination[i] = '\0';
		i++;
	}
	return (destination);
}
