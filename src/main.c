
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
		if (line[i] == '\"' && quote_state != SINGLE)
		{
			if (quote_state == DOUBLE)
				quote_state = NONE;
			else
				quote_state = DOUBLE;
		}
		else if (line[i] == '\'' && quote_state != DOUBLE)
		{
			if (quote_state == SINGLE)
				quote_state = NONE;
			else
				quote_state = SINGLE;
		}
		i++;
	}
	return (quote_state != NONE);
}

int	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

int	ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (i);
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

void	main_loop(t_env_token *list_env)
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
		tokens = tokenize_line(line, list_env);
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
		// printf("%s\n", (char *)(list_env->content));
		printf("[%s]=[%s]\n", list_env->key, list_env->value);
		list_env = list_env->next;
	}
}

t_bool	end_list_add_back(t_env_token **head, t_env_token *new)
{
	t_env_token	*temp;

	if (!*head)
	{
		*head = new;
		return (TRUE);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (TRUE);
}

// content is in the form "key=value" value can contain '=' characters so we need to split it just once
// we will use the first '=' character to split the string in two
char	**split_env(char *env)
{
	char	**split;
	size_t	i;

	i = 0;
	split = malloc(sizeof(char *) * 2);
	if (!split)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	split[0] = malloc(i + 1);
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	ft_strncpy(split[0], env, i);
	split[0][i] = '\0';
	split[1] = ft_strdup(env + i + 1);
	if (!split[1])
	{
		free(split[0]);
		free(split);
		return (NULL);
	}
	return (split);
}

t_env_token	*new_env_token(char *content)
{
	char		*key;
	char		*value;
	t_env_token	*new_token;
	char		**split;

	new_token = malloc(sizeof(t_env_token));
	if (!new_token)
		return (NULL);
	new_token->next = NULL;
	new_token->key = NULL;
	new_token->value = NULL;
	if (!content)
		return (new_token);
	split = split_env(content);
	if (!split)
	{
		free(new_token);
		return (NULL);
	}
	new_token->key = split[0];
	new_token->value = split[1];
	free(split);
	return (new_token);
}

t_bool	create_list_env(char **env, t_env_token **list_env)
{
	t_env_token	*new_token;
	int			count;

	count = 0;
	*list_env = NULL;
	while (env[count])
	{
		new_token = new_env_token(env[count]);
		if (!new_token)
			return (FALSE);
		if (!end_list_add_back(list_env, new_token))
			return (FALSE);
		count++;
	}
	return (TRUE);
}

int	main(int argc, char *argv[], char **env)
{
	t_env_token	*env_token;

	// t_token	*list_env;
	// list_env = NULL;
	// list_env = new_env(list_env, env);
	// if (!new_env)
	// 	return (0);
	if (!create_list_env(env, &env_token))
		return (0);
	print_env(env_token);
	head();
	main_loop(env_token);
}
