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

#include "../include/libft.h"

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

int	ft_super_strcat(char **dest, const char *src)
{
	size_t	i;
	size_t	j;
	char	*aux;

	aux = malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(*dest) + 1));
	if (!aux)
		return (0);
	i = -1;
	j = 0;
	while ((*dest)[++i])
	{
		aux[j] = (*dest)[i];
		j++;
	}
	i = -1;
	while (src[++i])
	{
		aux[j] = src[i];
		j++;
	}
	aux[j] = '\0';
	free(*dest);
	*dest = aux;
	return (j);
}
