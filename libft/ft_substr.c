/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:27:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	char	*dst;
	size_t	lens;

	x = 0;
	if (!s)
		return (NULL);
	lens = ft_strlen((char *)s);
	if (len == 0 || lens == 0)
		return (ft_strdup(""));
	if (start >= lens)
		return (ft_strdup(""));
	if (len > lens - start)
		len = lens - start;
	dst = (char *)malloc(sizeof(char) * (len +1));
	if (!dst)
		return (NULL);
	while ((start < ft_strlen(s)) && (x < len))
	{
		dst[x] = s[start];
		start++;
		x++;
	}
	dst[x] = '\0';
	return (dst);
}
