/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:25:54 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:25:59 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*des;

	if (size > 0 && count > ULONG_MAX / size)
		return (NULL);
	des = (void *)malloc(count * size);
	if (des == NULL)
		return (NULL);
	ft_bzero (des, count * size);
	return (des);
}
