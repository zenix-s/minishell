/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_is_absolute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:35 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:33:36 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_is_absolute(char **cmd)
{
	if (ft_strncmp("/", cmd[0], 1) == 0)
		return (1);
	if (ft_strncmp("./", cmd[0], 2) == 0)
		return (1);
	if (ft_strncmp("../", cmd[0], 3) == 0)
		return (1);
	return (0);
}
