/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:50:42 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/23 13:50:45 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("[[%d] - [%s]]\n", current->type, current->content);
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

	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			free_shell(shell);
			exit(EXIT_SUCCESS);
		}
		while (has_unclosed_quotes(line))
		{
			if (!manage_unclosed_quotes(&line))
				break ;
		}
		shell->tokens = tokenize_line(line, shell);
		//print_tokens(shell->tokens);
		if (line && *line != '\0')
		{
			if (strlen(line) > MAX_INPUT_LENGTH)
				ft_error("Error: line so long.\n");
			select_all(&shell);
			add_history(line);
		}
		free(line);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGQUIT)
	{
		printf("Ctrl + \\.\n");
	}
	if (sig == SIGINT)
	{
		printf("Ctrl + C.\n");
	}
	(void)context;
	(void)info;
}

static void	init_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGQUIT, &sa, 0);
	sigaction(SIGINT, &sa, 0);
}

int	main(int argc, char *argv[], char **env)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	init_sigaction();
	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!create_list_env(env, &(shell->env)))
		return (0);
	//print_env(shell->env);
	head();
	main_loop(shell);
	free_shell(shell);
}
