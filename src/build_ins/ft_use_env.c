
#include "../../include/minishell.h"

void	use_env(t_token *list_env)
{
	// char	*aux;

	while (list_env)
	{
		printf ("%s\n",(char*) (list_env->content));
		list_env = list_env->next;
	}
}
//como env es un arraid he preferido dejarlo como arraid...
//esta función te crea un env propio  como lista para no tener complicaciones en el futuro

t_token	*new_env(t_token *list_env, char **env)
{
	int		count;
	t_token	*aux;

	list_env = ft_lstnew(env[0]);
	if (!list_env)
		return NULL;
					// TO DO: esto ahora mismo esta sin liberar
					//tiene que liberarse al final de todo
	count = 1;
	while (env[count])
	{
		aux = ft_lstnew(env[count]);
		if (!aux)
			return NULL;
		ft_lstadd_back(&list_env, aux);
		count++;
	}
	return (list_env);
}
