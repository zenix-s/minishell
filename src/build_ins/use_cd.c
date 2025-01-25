
#include "../../include/minishell.h"

//int chdir(const char *path);

/*
	- Diferentes formas de cambiar de carpeta
	- porque si hago dos veces cd .. aparecen leaks pero con una sola vez no..
	- 
*/


static char	*search_rute(char *before, char *tip)
{
	char	*rute;
	int		aux;

	if (strcmp(tip, "..") == 0)
	{
		aux = ft_strlen(before);
		while (before[aux] != '/' && aux > 0)
			aux--;
		rute = ft_substr(before, 4, aux - 3);
		return (rute);
	}
	return (NULL);
}

void	use_cd(t_token **list_env, char **line_arraid)
{
	char	*new_pwd;
	char	*pwd;
	char	*new_oldpwd;
	t_token	*l_aux;
	char	*rute;

	l_aux = *list_env;
	while (l_aux)
	{
		if (ft_strncmp((char *)l_aux->content, "PWD", 2) == 0)
			pwd = (char *)l_aux->content;
		l_aux = l_aux->next;
	}
	l_aux = *list_env;
	rute = search_rute(pwd, line_arraid[1]);
	chdir(rute);
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
	free(rute);
}
