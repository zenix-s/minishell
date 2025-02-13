/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:26:13 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:26:16 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

static int	ft_digits(int nbr)
{
	int	digits;

	if (nbr <= 0)
		digits = 1;
	else
		digits = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len = ft_digits(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = '0' + ft_abs(n % 10);
		n = ft_abs(n / 10);
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
