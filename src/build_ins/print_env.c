/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:27:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(t_env_token *list_env, t_bool is_export)
{
	char	**env_now;
	int		cont;

	cont = 0;
	env_now = obtain_env(list_env);
	while (env_now[cont])
	{
		if (ft_strncmp(env_now[cont], "PATH=", 5) == 0)
		{
			while (list_env)
			{
				if (is_export)
					printf("declare -x ");
				printf("%s=%s\n", list_env->key, list_env->value);
				list_env = list_env->next;
			}
			ft_free(env_now);
			return ;
		}
		cont++;
	}
	ft_free(env_now);
	printf("minishell: env: No such file or directory\n");
	g_exit_status = 127;
}

void	use_env(t_env_token *list_env, char **line_arraid, t_bool is_export)
{
	if (line_arraid[1])
	{
		if (line_arraid[1][0] == '-' )
		{
			printf("minishell env dont use argument\n");
			g_exit_status = 125;
		}
		else
		{
			printf("env: %s: No such file or directory \n", line_arraid[1]);
			g_exit_status = 127;
		}
		return ;
	}
	else
		print_env(list_env, is_export);
}
