/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_string_in_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:06:05 by serferna          #+#    #+#             */
/*   Updated: 2025/02/26 09:06:05 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_string_in_array(const char *str, const char *array[]) {
  int i;

  i = 0;
  while (array[i]) {
    if (strcmp(str, array[i]) == 0)
      return (1);
    i++;
  }
  return (0);
}
