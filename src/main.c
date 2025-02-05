
#include "../include/minishell.h"

void	main_loop(t_token *list_env)
{
	char	*line;
	int		cont;

	cont = 0;
	while (1)
	{
		line = readline("minishell :");
		if (line && *line != '\0')
		{
			if (strlen(line) > MAX_INPUT_LENGTH)
				ft_error("Error: line so long.\n");
			select_all(line, list_env, 0);
			add_history(line);
			//ft_init(line); 
		}
		free(line);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_token	*list_env;

	(void)argc;
	(void)argv;
	list_env = NULL;
	list_env = new_env(list_env, env);
	if (!list_env)
		return (0);
	head();
	main_loop(list_env);
}
