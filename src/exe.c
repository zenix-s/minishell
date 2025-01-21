
#include "../include/minishell.h"

static char	*search(char *object, char *command)
{
	char	**path;
	int		cont;
	char	*finish;

	path = ft_split(object + 5, ':');
	cont = 0;
	while (path[cont])
	{
		finish = ft_strjoin(path[cont], "/");
		finish = ft_strjoin(finish, command);
		if (access(finish, F_OK) == 0)
			return (finish);
		cont++;
	}
	perror("error cmd");
//	exit(errno);
}

void	exe(char *command, t_token *list_env)
{
	char	*path;
	char	**a_command;
	char	**env_now;
	int		count;

	count = ft_lstsize(list_env);
	env_now = ft_calloc(count + 1, sizeof(char *));
	a_command = ft_split(command, ' ');
	count = 0;
	while (list_env)
	{
		env_now[count] = ft_strdup((char *)list_env->content);
		if (ft_strncmp((char *) list_env->content, "PATH=", 5) == 0)
			path = (char *) list_env->content;
		//si no encontrara esto tendriamos que ir a rutas
		// absolutas que estan sin hacer
		list_env = list_env->next;
		count++;
	}
	path = search(path, command);
	execve(path, a_command, env_now);
/*
	perror(command);
	free(env_now);
	free(a_command);
	exit(0);
*/
}