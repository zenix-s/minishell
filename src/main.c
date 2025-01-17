
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


//por ahora lo he puesto aqui porque no se donde ponerlo al estar asi a lo bruto
void	use_build(char *line, t_token *list_env)
{
//	if (line && ft_strcmp(line, "echo") == 0)
//		use_();
//	if (line && ft_strcmp(line, "cd") == 0)
//		use_();
	if (line && ft_strcmp(line, "pwd") == 0)
		use_pwd(list_env);
//	if (line && ft_strcmp(line, "export") == 0)
//		use_();
//	if (line && ft_strcmp(line, "unset") == 0)
//		use_unset();
	if (line && ft_strcmp(line, "env") == 0)
		use_env(list_env);
	if (line && ft_strcmp(line, "exit") == 0)
		exit(0); //seguramente no sea tan facil
	else
		printf("%s: commmand not found\n", line);
}


void	main_loop(t_token *list_env)
{
	char	*line;
	int		cont;

	cont = 0;
	while (1)
	{
		line = readline("\033[1;34mminishell \033[0m \033[1;32m▸\033[0m ");
		use_build(line, list_env);
		add_history(line);
			//ft_init(line); 
			//comento init qe me he dejado un par de semegtation por aqui
		free (line);
	}
}






int	main(int argc, char *argv[], char **env)
{
	t_token	*list_env;

	list_env = NULL;
	list_env = new_env(list_env, env);
	if (!new_env)
		return (0);
	head();
	main_loop(list_env);
}
