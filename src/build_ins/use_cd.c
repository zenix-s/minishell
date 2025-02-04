
#include "../../include/minishell.h"

//int chdir(const char *path);

/*
	- Diferentes formas dE USAR CD :
		- cd  ->clear.
		- cd ..
		- cd nombre de carpeta
		- cd con diferentes nombres de carpeta 
	- porque si hago dos veces cd .. aparecen leaks pero con una sola vez no..
	- 
*/

static int	create_new_rute(char *rute, char *step)
{
	char	*aux;

	if (strcmp(step, "..") == 0)
		rute = ft_substr(rute, 0, ft_strrint(rute, '/'));
	else
	{
		aux = ft_strjoin(rute, "/");
		rute = ft_strjoin(aux, step);
		free(aux);
	}
	if (chdir(rute) == -1)
	{
		free(rute);
		return (-1);
	}
	free(rute);
	return (1);
}

static int	search_rute(char *line_arraid)
{
	char	*rute;
	char	*aux;
	char	*cwd;
	char	**step;
	int		count;

	count = 0;
	cwd = (char *)ft_calloc(1024, sizeof(char));
	if (!cwd)
		return (-1);
	step = ft_split(line_arraid, '/');
	while (step[count])
	{
		rute = getcwd(cwd, 1024);
		aux = rute;
		if (create_new_rute(rute, step[count]) == -1)
		{
			printf("cd: no such file or directory: %s\n", line_arraid);
			free(cwd);
			ft_free(step);
			return (-1);
		}
		count++;
	}
	free(cwd);
	ft_free(step);
	return (1);
}

static void	obtain_new_oldpwd(t_token **list_env)
{
	char	*new_oldpwd;
	char	**aux;
	char	*pwd;
	t_token	*l_aux;

	l_aux = *list_env;
	pwd = obtain_content("PWD=", l_aux);
	aux = ft_split("FOO OLDPWD FOO", ' ');
	if (pwd)
	{
		new_oldpwd = ft_strjoin("OLD", pwd);
		change_content(&l_aux, "OLDPWD=", new_oldpwd);
		free(new_oldpwd);
	}
	else
	{
		new_oldpwd = NULL;
		use_unset (list_env, aux);
	}
	ft_free(aux);
}

static void	go_home(t_token **list_env)
{
	t_token	*l_aux;
	char	*home;
	char	*aux;

	l_aux = *list_env;
	home = obtain_content("HOME=", l_aux);
	if (!home)
		printf("HOME not set\n");
	else
	{
		home = ft_substr(home, 5, ft_strlen(home));
		chdir(home);
		aux = ft_strjoin("PWD=", home);
		change_content(&l_aux, "PWD=", aux);
		free(home);
		free(aux);
	}
}

void	use_cd(t_token **list_env, char **line_arraid)
{
	char	*new_pwd;
	char	*pwd;
	t_token	*l_aux;
	char	*rute;
	char	*aux;

	l_aux = *list_env;
	pwd = obtain_content("PWD=", l_aux);
	obtain_new_oldpwd(&l_aux);
	if (!line_arraid[1])
		go_home(&l_aux);
	else
	{
		if (search_rute(line_arraid[1]) == -1)
		{
			aux = ft_substr(pwd, 4, ft_strlen(pwd));
			chdir(aux);
			free(aux);
		}
		new_pwd = ft_strjoin("PWD=", rute);
		change_content(&l_aux, "PWD=", new_pwd);
		free(new_pwd);
	}
}
