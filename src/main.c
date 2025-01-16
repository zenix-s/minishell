
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

void	main_loop(char **env)
{
	char	*line;
	int		cont;

	cont = 0;
	while (1)
	{
		line = readline("\033[1;34minishell \033[0m \033[1;32m▸\033[0m ");
		if (line  && ft_strcmp(line, "exit") == 0)
			exit(0);
		else
		{
			if (line)
			{
				add_history(line);
				printf("%s\n", line);
			}
			ft_init(line);
			free (line);
		}
	}
}

int	main(int argc, char *argv[], char **env)
{
	head();
	main_loop(env);
	printf("Terinado");
}
