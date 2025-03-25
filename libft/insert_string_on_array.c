/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_string_on_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Insert a string in an array before a given position
 * @param arr The array of strings
 * @param str The string to insert
 * @param pos The position to insert the string
 * @return char** The new array of strings
 */
char	**insert_string_on_array(char *arr[], char *str, int pos)
{
	int64_t	size;
	int64_t	i;
	char	**new_arr;

	size = 0;
	if (arr == NULL || str == NULL || pos < 0)
		return (NULL);
	while (arr[size] != NULL)
		size++;
	if (pos > size)
		return (NULL);
	new_arr = (char **)malloc((size + 2) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	i = -1;
	while (++i < pos)
		new_arr[i] = arr[i];
	new_arr[pos] = ft_strdup(str);
	while (i < size)
	{
		new_arr[i + 1] = arr[i];
		i++;
	}
	new_arr[size + 1] = NULL;
	return (new_arr);
}
