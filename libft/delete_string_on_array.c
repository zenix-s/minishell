/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_string_on_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Delete a string from an array of strings
 *
 * @param arr The array of strings
 * @param pos The position of the string to delete
 * @return char** The new array of strings
 */
char	**delete_string_on_array(char *arr[], int pos)
{
	int64_t	size;
	int64_t	i;
	char	**new_arr;

	size = 0;
	if (arr == NULL || pos < 0)
		return (NULL);
	while (arr[size] != NULL)
		size++;
	if (pos >= size)
		return (NULL);
	new_arr = (char **)malloc(size * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	i = -1;
	while (++i < pos)
		new_arr[i] = arr[i];
	--i;
	while (++i < size - 1)
		new_arr[i] = arr[i + 1];
	new_arr[size - 1] = NULL;
	return (new_arr);
}
