/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (i);
}

int ft_super_strcat(char **dest, const char *src)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;
	size_t	j;
	char	*aux;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(*dest);
	aux = (char *)malloc(sizeof(char) * (src_len + dest_len + 1));
	if (!aux)
		return (0);
	i = 0;
	j = 0;
	while ((*dest)[i])
	{
		aux[j] = (*dest)[i];
		i++;
		j++;
	}
	i = 0;
	while (src[i])
	{
		aux[j] = src[i];
		i++;
		j++;
	}
	aux[j] = '\0';
	free(*dest);
	*dest = aux;
	return (j);
}
