
#include "../../include/minishell.h"

//int chdir(const char *path);

static char	*search_rute(char *before, char *tip)
{
	char	*rute;
	int		aux;

	if (strncmp(tip, "..", 1) == 0)
	{
		aux = ft_strlen(before);
		while (before[aux] != '/' && aux > 0)
			aux--;
		rute = ft_substr(before, 4, aux - 3);
		printf("%s\n",rute);
		return (rute);
	}
	return (NULL);
}

void	use_cd(t_token **list_env, char **line_arraid)
{
	char	*pwd;
	char	*oldpwd;
	t_token	*l_aux;
	char	*rute;

	l_aux = *list_env;
	while (l_aux)
	{
		if (ft_strncmp((char *)l_aux->content, "PWD", 2) == 0)
			pwd = (char *)l_aux->content;
		if (ft_strncmp((char *)l_aux->content, "OLDPWD", 5) == 0)
			oldpwd = (char *)l_aux->content;
		l_aux = l_aux->next;
	}
	l_aux = *list_env;
	rute = search_rute(pwd, line_arraid[1]);
	chdir(rute);
	while (l_aux)
	{
		if (ft_strncmp((char *)l_aux->content, "PWD", 2) == 0)
			l_aux->content = ft_strdup(oldpwd);
		if (ft_strncmp((char *)l_aux->content, "OLDPWD", 5) == 0)
			l_aux->content = ft_strdup(rute);
		l_aux = l_aux->next;
	}
}
