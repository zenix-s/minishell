/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:55:11 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/23 13:55:14 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*search(char *object, char **command)
{
	char	**path;
	int		cont;
	char	*finish;
	char	*temp;

	path = ft_split(object, ':');
	cont = 0;
	while (path[cont])
	{
		finish = ft_strjoin(path[cont], "/");
		temp = finish;
		finish = ft_strjoin(finish, command[0]);
		free(temp);
		if (access(finish, F_OK) == 0)
		{
			ft_free(path);
			return (finish);
		}
		free(finish);
		cont++;
	}
	ft_free(path);
	perror(command[0]);
	exit(127);
	return (NULL);
}

char	**obtain_env(t_env_token *list_env)
{
	int		aux;
	int		x;
	char	**env_now;
	char	*temp;

	x = 0;
	aux = ft_lstsize(list_env);
	env_now = ft_calloc(aux + 1, sizeof(char *));
	while (list_env)
	{
		temp = ft_strjoin(list_env->key, "=");
		env_now[x] = ft_strjoin(temp, list_env->value);
		free(temp);
		list_env = list_env->next;
		x++;
	}
	return (env_now);
}

/*
* si execve no ejecuta el comando, hay que salir del hijo, por eso la igualacion
 * @path -> En esta funcion es un (char *) con todas las rutas
 * @command -> Es un (char **) con los comandos ingresados
 * @env_now es un (char **) sacado con el contenido de las listas

*/

void	set_signal_interactive_child(void)
{
	struct sigaction	act;

	act.sa_handler = SIG_DFL;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	exe_all(char **command, t_env_token *list_env)
{
	char	*path;
	char	**env_now;

	// signal(SIGINT, SIG_DFL); //
	env_now = obtain_env(list_env);
	if (env_is_absolute(command, env_now) == 1)
	{
		path = command[0];
		if (access(path, F_OK) == -1)
			ft_error("No such file or directory");
	}
	else
	{
		while (list_env)
		{
			if (newcmp(list_env->key, "PATH") == 0)
				path = list_env->value;
			list_env = list_env->next;
		}
		path = search(path, command);
	}
	set_signal_interactive_child();
	execve(path, command, env_now);
	free(path);
	ft_free(env_now);
	ft_error("patata");
}

// void	exe_all(char **command, t_env_token *list_env)
// {
// 	char	*path;
// 	char	**env_now;

// 	path = NULL;
// 	while (list_env)
// 	{
// 		if (newcmp(list_env->key, "PATH") == 0)
// 		{
// 			env_now = obtain_env(list_env);
// 			path = list_env->value;
// 		}
// 		list_env = list_env->next;
// 	}
// 	if (path == NULL)
// 	{
// 		if (env_is_absolute(command) == 1)
// 		{
// 			path = command[0];
// 			if (access(path, F_OK) == -1)
// 				ft_error("No such file or directory");
// 		}
// 	}
// 	else
// 		path = search(path, command);
// 	execve(path, command, env_now);
// 	free(path);
// 	ft_free(env_now);
// 	ft_error("exe");
// }
