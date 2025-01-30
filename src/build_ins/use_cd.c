
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

/*

TO DO ---> Cambiar el home y añadir usuario
	@ beffore es un char * con PWD= + LA RUTA
	@ tip es hacia donde vas...
*/
static char	*search_rute(char *before, char *tip)
{
	char	*rute;
	char	*aux_rute;
	int		aux;
	int		count;
	char	**step;

	aux = ft_strlen(before);
	aux_rute = ft_substr(before, 4, aux);
//	free(aux_rute);
	rute = ft_strtrim(aux_rute, "/");

	count = 0;
	step = ft_split(tip, '/');
	while (step[count])
	{
		if (strcmp(step[count], "..") == 0)
		{
			aux = ft_strlen(rute);
			while (before[aux] != '/' && aux > 0)
				aux--;
			rute = ft_substr(rute, 0, aux - 3);
		}
		else
		{
			aux_rute = ft_strjoin(rute, "/");
			free(rute);
			rute = ft_strjoin(aux_rute, step[count]);
			free (aux_rute);
		}
		count++;
	}
	ft_free(step);
	return (rute);
}

static char	*obtain_new_oldpwd(char *pwd)
{
	char	*new_oldpwd;

	if (pwd)
		new_oldpwd = ft_strjoin("OLD", pwd);
	else
		new_oldpwd = ft_strdup("OLDPWD=");
	return (new_oldpwd);
}

static void	go_home(t_token **list_env)
{
	t_token	*l_aux;

	l_aux = *list_env;
	chdir("/home");
	change_content(&l_aux, "PWD=", "PWD=/home");
}

void	use_cd(t_token **list_env, char **line_arraid)
{
	char	*new_pwd;
	char	*pwd;
	char	*new_oldpwd;
	t_token	*l_aux;
	char	*rute;

	l_aux = *list_env;
	pwd = obtain_content("PWD=", l_aux);
	new_oldpwd = obtain_new_oldpwd(pwd);
	change_content(&l_aux, "OLDPWD=", new_oldpwd);
	free(new_oldpwd);
	if (!line_arraid[1])
		go_home(&l_aux);
	else
	{
		rute = search_rute(pwd, line_arraid[1]);
		chdir(rute);
		new_pwd = ft_strjoin("PWD=", rute);
		change_content(&l_aux, "PWD=", new_pwd);
		free(new_pwd);
		free(rute);
	}
}

		/*
		while (l_aux)
		{
			if (ft_strncmp((char *)l_aux->content, "PWD", 2) == 0)
			{
				new_pwd = ft_strjoin("PWD=", rute);
				l_aux->content = ft_strdup(new_pwd);
				free(new_pwd);
			}

			if (ft_strncmp((char *)l_aux->content, "OLDPWD", 5) == 0)
			{
				new_oldpwd = ft_strjoin("OLD", pwd);
				l_aux->content = ft_strdup(new_oldpwd);
				free(new_oldpwd);
			}

			l_aux = l_aux->next;
		}
		*/