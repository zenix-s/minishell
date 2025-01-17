
#include "../../include/minishell.h"

//actualmente solo printea el enviroment
void	use_env(char **new_env)
{
	int	count;

	count = 0;
	while (new_env[count])
	{
		printf("%s\n", new_env[count]);
		count++;
	}
}
//cuenta lo largo que es el env
int	ft_size_env(char **env)
{
	int	count;

	count = 0;
	while (env[count])
	{
		count++;
	}
	return (count);
}

//como env es un arraid he preferido dejarlo como arraid...
//esta función te crea un env propio para no tener complicaciones en el futuro
char	**ft_new_env(char **env)
{
	int		count;
	char	**new_env;

	count = ft_size_env(env);
	new_env = (char **)ft_calloc (count, sizeof(char *));
	if (!new_env)
		return (0);
	// TO DO: esto ahora mismo esta sin liberar
	//tiene que liberarse al final de todo
	count = 0;
	while (env[count])
	{
		new_env[count] = ft_strdup(env[count]);
		count++;
	}
	return (new_env);
}
