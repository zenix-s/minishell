
#include "../include/minishell.h"
#include <stddef.h>
#include <stdio.h>
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

int	has_unclosed_quotes(const char *line)
{
	size_t	i;
	t_quote	quote_state;

	i = 0;
	quote_state = NONE;
	while (line[i])
	{
		quote_state = get_quote_type(quote_state, line[i]);
		i++;
	}
	return (quote_state != NONE);
}

int	manage_unclosed_quotes(char **line)
{
	char	*new_line;
	char	*temp;

	new_line = readline("- ");
	if (!new_line)
		return (0);
	temp = *line;
	*line = malloc(ft_strlen(*line) + ft_strlen(new_line) + 2);
	if (!*line)
	{
		free(temp);
		free(new_line);
		exit(EXIT_FAILURE);
	}
	ft_strcpy(*line, temp);
	ft_strcat(*line, "\n");
	ft_strcat(*line, new_line);
	free(temp);
	free(new_line);
	return (1);
}

void	main_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			break ;
		while (has_unclosed_quotes(line))
		{
			if (!manage_unclosed_quotes(&line))
				break ;
		}
		tokens = tokenize_line(line, shell->env);
		print_tokens(tokens);
		// use_build(line, list_env);
		// add_history(line);
		// ft_init(line);
		// comento init qe me he dejado un par de semegtation por aqui
		free(line);
	}
}

void	print_env(t_env_token *list_env)
{
	while (list_env)
	{
		printf("[%s]=[%s]\n", list_env->key, list_env->value);
		list_env = list_env->next;
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_env_token	*env_token;
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));

	// t_token	*list_env;
	// list_env = NULL;
	// list_env = new_env(list_env, env);
	// if (!new_env)
	// 	return (0);
	if (!create_list_env(env, &(shell->env)))
		return (0);
	print_env(shell->env);
	head();
	main_loop(shell);
}
