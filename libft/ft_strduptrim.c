/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strduptrim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:03 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:04 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	ft_strlentrim(const char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i + j])
		j++;
	while (j > 0 && (s[i + j - 1] == ' ' || s[i + j - 1] == '\t'))
		j--;
	return (j);
}

char	*ft_strduptrim(char *src)
{
	int		x;
	int		y;
	char	*des;

	x = ft_strlentrim(src);
	y = 0;
	des = (char *)malloc(sizeof(char) * (x + 1));
	if (des == NULL)
		return (0);
	while (src[y] == ' ' || src[y] == '\t')
		y++;
	while (x > 0)
	{
		des[y] = src[y];
		++y;
		--x;
	}
	des[y] = '\0';
	return (des);
}
