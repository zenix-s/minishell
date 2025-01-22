
#include "../../include/minishell.h"

t_token	*new_env(t_token *list_env, char **env)
{
	int		count;
	t_token	*aux;

	list_env = ft_lstnew(env[0]);
	if (!list_env)
		return (NULL);
	count = 1;
	while (env[count])
	{
		aux = ft_lstnew(env[count]);
		if (!aux)
			return (NULL);
		ft_lstadd_back(&list_env, aux);
		count++;
	}
	return (list_env);
}

//esta funcion entrega el env hasta el = para que se tenga que escribir igual
int	size_env(char *line_env)
{
	int	count;

	count = 0;
	while (line_env[count] != '=')
		count++;
	return (count);
}

void	ft_free(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
}
