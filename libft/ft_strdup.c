/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:27:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup( char *src)
{
	int		x;
	int		y;
	char	*des;

	x = ft_strlen(src);
	y = 0;
	des = (char *)malloc(sizeof(char) * (x + 1));
	if (des == NULL)
		return (0);
	while (src[y] != '\0')
	{
		des[y] = src[y];
		++y;
	}
	des[y] = '\0';
	return (des);
}
