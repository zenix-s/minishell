
#include "../include/minishell.h"

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
		if (line && *line != '\0')
		{
			if (strlen(line) > MAX_INPUT_LENGTH)
				ft_error("Error: line so long.\n");
//			select_all(line, list_env); shell->tokens
			add_history(line);
		}
		tokens = tokenize_line(line, shell->env);
		print_tokens(tokens);
//		use_build(shell); //va a explotar
		free(line);
	}
}

void	print_env(t_env_token *list_env)
{
	while (list_env)
	{
		printf("%s=%s\n", list_env->key, list_env->value);
		list_env = list_env->next;
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!create_list_env(env, &(shell->env)))
		return (0);
	print_env(shell->env);
	head();
	main_loop(shell);
}
