
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

void	ft_error(char *texto)
{
	perror(texto);
	exit(0);
}



//por ahora lo he puesto aqui porque no se donde ponerlo al estar asi a lo bruto
void	use_build(char *line, t_token *list_env)
{
	char	**line_arraid;

	line_arraid = ft_split(line, ' ');
	if (line && ft_strncmp(line, "echo", 3) == 0)
		use_echo(list_env, line_arraid);
	if (line && ft_strncmp(line, "cd", 2) == 0)
		use_cd(&list_env, line_arraid);
	else if (line && ft_strcmp(line, "pwd") == 0)
		use_pwd(list_env);
	else if (line && ft_strncmp(line, "export", 5) == 0)
		use_export(&list_env, line_arraid);
	else if (line && ft_strncmp(line, "unset", 4) == 0)
		use_unset(&list_env, line_arraid);
	else if (line && ft_strcmp(line, "env") == 0)
		use_env(list_env);
	else if (line && ft_strcmp(line, "exit") == 0)
		exit(0); //no sea tan facil...
	else
		exe(line_arraid[0], list_env);
	free (line_arraid);
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
			use_build(line, list_env);
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

	list_env = NULL;
	list_env = new_env(list_env, env);
	if (!new_env)
		return (0);
	head();
	main_loop(list_env);
}
