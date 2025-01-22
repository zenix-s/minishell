
#include "../../include/minishell.h"

//int chdir(const char *path);

void	use_cd(t_token **list_env, char **line_arraid)
{
	char	*pwd;
	char	*oldpwd;
	t_token	*l_aux;

	l_aux = *list_env;

	//cambia OLDPWD por PWD

	//usa chdir

	//cambia el PWD
	while(l_aux)
	{
		//if (ft_strncmp((char *)list_env->content, "PWD", 2))
			//nuevo content pero como...
		l_aux = l_aux->next;
	}

}
