
#include "../../include/minishell.h"


/*
*busca por la clave y da la clave con el contenido
*/
char	*obtain_content(char *search, t_token *list_env)
{
	char	*result;
	int		size;

	size = ft_strlen(search);
	result = NULL;
	while (list_env)
	{
		if (ft_strncmp(list_env->content, search, size) == 0)
			result = list_env->content;
		list_env = list_env->next;
	}
	return (result);
}

void	change_content(t_token **list_env, char *key, char *newcont)
{
	t_token	*l_aux;
	int		size_key;

	size_key = ft_strlen(key);
	l_aux = *list_env;
	while (l_aux)
	{
		if (ft_strncmp(l_aux->content, key, size_key) == 0)
		{
			free(l_aux->content);
			l_aux->content = ft_strdup(newcont);
		}
		l_aux = l_aux->next;
	}
}

