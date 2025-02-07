
#include "../include/minishell.h"

static char	*search(char *object, char **command)
{
	char	**path;
	int		cont;
	char	*finish;
	char	*temp;

	path = ft_split(object + 5, ':');
	cont = 0;
	while (path[cont])
	{
		finish = ft_strjoin(path[cont], "/");
		temp = finish;
		finish = ft_strjoin(finish, command[0]);
		free (temp);
		if (access(finish, F_OK) == 0)
		{
			ft_free(path);
			return (finish);
		}
		free(finish);
		cont++;
	}
	ft_free(path);
	perror("error on function search");
	exit(1);
	return (NULL);
}
/*
* si execve no ejecuta el comando, hay que salir del hijo, por eso la igualacion
 * @path -> En esta funcion es un (char *) con todas las rutas 
 * @command -> Es un (char **) con los comandos ingresados
 * @env_now es un (char **) sacado con el contenido de las listas 

*/

void	exe_all(char **command, t_token *list_env)
{
	char	*path;
	char	**env_now;

	env_now = obtain_env(list_env);
	if (env_is_absolute(command) == 1)
	{
		path = command[0];
		if (access(path, F_OK) == -1)
			ft_error("No such file or directory");
	}
	else
	{
		while (list_env)
		{
			if (ft_strncmp((char *) list_env->content, "PATH=", 5) == 0)
				path = list_env->content;
			list_env = list_env->next;
		}
		path = search(path, command);
	}
	execve(path, command, env_now);
	free(path);
	ft_free(env_now);
}
