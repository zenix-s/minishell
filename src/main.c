
#include "../include/minishell.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

// por ahora lo he puesto aqui porque no se donde ponerlo al estar asi a lo bruto
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
		exit(0); // seguramente no sea tan facil
	else
		printf("%s: commmand not found\n", line);
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("[%s]\n", current->content);
		current = current->next;
	}
}

int has_unclosed_quotes(const char *line)
{
    int in_quotes;
    size_t i;

    in_quotes = 0;
    i = 0;
    while (line[i])
	{
		if (line[i] == '\"')
			in_quotes = !in_quotes;
		i++;
	}
    return in_quotes;
}

void	main_loop(t_token *list_env)
{
	char	*line;
	char	*new_line;
	char	*temp;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break ;
		while (has_unclosed_quotes(line))
		{
			new_line = readline("minishell: ");
			if (!new_line)
			{
				free(line);
				break ;
			}
			temp = line;
			line = malloc(ft_strlen(line) + ft_strlen(new_line) + 2);
			if (!line)
			{
				free(temp);
				free(new_line);
				exit(EXIT_FAILURE);
			}
			strcpy(line, temp);
			strcat(line, "\n");
			strcat(line, new_line);
			free(temp);
			free(new_line);
		}

		tokens = tokenize_line(line);
		print_tokens(tokens);
		// use_build(line, list_env);
		// add_history(line);
		// ft_init(line);
		// comento init qe me he dejado un par de semegtation por aqui
		free(line);
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
