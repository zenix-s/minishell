/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:14:27 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/24 00:14:29 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_bool	exit_atoi(char *aux, int *number)
{
	int		i;
	int		sign;
	int64_t	result;

	i = 0;
	sign = 1;
	result = 0;
	if (ft_strlen(aux) == 1 && (aux[0] == '-' || aux[0] == '+'))
		return (FALSE);
	if (aux[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (aux[i])
	{
		if (!ft_isdigit(aux[i]))
			return (FALSE);
		result = result * 10 + aux[i] - '0';
		i++;
	}
	*number = result * sign;
	return (TRUE);
}

static void	err_to_many_args(void)
{
	printf("minishell: exit: too many arguments\n");
	g_exit_status = 1;
}

static void	exit_free(t_shell *shell, char *aux, char **array)
{
	if (aux != NULL)
		free(aux);
	ft_free(array);
	exit_state(shell);
}

static int	specific(t_shell *shell, char *ext, char **array, int number)
{
	if (ext && newcmp(ext, "--") == 0)
	{
		if (get_array_string_size(array) == 3)
		{
			number = ft_atoi(array[2]);
			shell->exit_status = number;
			return (exit_free(shell, ext, array), 0);
		}
		else if (get_array_string_size(array) > 3)
			return (err_to_many_args(), 3);
		shell->exit_status = 0;
		exit_free(shell, ext, array);
	}
	if (ext && !exit_atoi(ext, &number) && get_array_string_size(array) >= 2)
	{
		printf("minishell: exit: numeric argument required\n");
		shell->exit_status = 2;
		exit_free(shell, ext, array);
	}
	return (0);
}

void	use_exit(t_shell *shell, char **line_arraid)
{
	char	*aux;

	printf("exit\n");
	aux = NULL;
	if (get_array_string_size(line_arraid) >= 2)
		aux = remove_outer_quotes(line_arraid[1]);
	if (specific(shell, aux, line_arraid, 0) == 3)
	{
		free(aux);
		return ;
	}
	if (get_array_string_size(line_arraid) >= 3 && newcmp(aux, "--") != 0)
		err_to_many_args();
	else if (get_array_string_size(line_arraid) == 2)
	{
		shell->exit_status = ft_atoi(aux);
		exit_free(shell, aux, line_arraid);
	}
	else
	{
		shell->exit_status = 0;
		exit_free(shell, aux, line_arraid);
	}
}
