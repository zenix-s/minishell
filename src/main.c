
#include "../include/minishell.h"

void	head(void)
{
	printf("         .__         .__         .__             .__   .__   \n");
	printf("  _____  |__|  ____  |__|  ______|  |__    ____  |  |  |  |  \n");
	printf(" /     \\ |  | /    \\ |  | /  ___/");
	printf("|  |  \\ _/ __ \\ |  |  |  |  \n");
	printf("|  Y Y  \\|  ||   |  \\|  | \\___ \\ ");
	printf("|   Y  \\  ___/ |  |__|  |__\n");
	printf("|__|_|  /|__||___|  /|__|/____  >|___|  / \\___  >|____/|____/\n");
	printf("      \\/          \\/          \\/");
	printf("      \\/      \\/             \n");
	printf("                                      by serferna and lortega-\n");
}


void	main_loop(t_token *list_env)
{
	char	*line;
	int		cont;

	cont = 0;
	while (1)
	{
		line = readline("\033[1;34mminishell \033[0m \033[1;32m▸\033[0m ");
		if (line)
		{
			select_build(line, list_env);
			add_history(line);
			//ft_init(line); 
			//comento init qe me he dejado un par de semegtation por aqui
			free (line);
		}
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


/*
//TO DO

-Se accede a algo en la memoria que se libera cuando se usa export y luego env
*/