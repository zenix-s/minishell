
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


void	exe_all(char **command, t_token *list_env)
{
	char	*path;
	char	**env_now;
	int		count;

	count = ft_lstsize(list_env);
	env_now = ft_calloc(count + 1, sizeof(char *));
	count = 0;
	while (list_env)
	{
		env_now[count] = ft_strdup((char *)list_env->content);
		if (ft_strncmp((char *) list_env->content, "PATH=", 5) == 0)
			path = list_env->content;
		//si no encontrara esto tendriamos que ir a rutas
		// absolutas que estan sin hacer
		list_env = list_env->next;
		count++;
	}
	path = search(path, command);
	execve(path, command, env_now);
	free(path);
	ft_free(env_now);
}
