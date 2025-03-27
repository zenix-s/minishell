/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:15:23 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/25 16:15:27 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_bool	save_heredoc_file(t_shell *shell, char *file_name)
{
	char	**aux;

	if (shell->heredoc_files == NULL)
	{
		shell->heredoc_files = malloc(sizeof(char *) * 2);
		if (shell->heredoc_files == NULL)
			return (FALSE);
		shell->heredoc_files[0] = ft_strdup(file_name);
		if (shell->heredoc_files[0] == NULL)
		{
			free(shell->heredoc_files);
			return (FALSE);
		}
		shell->heredoc_files[1] = NULL;
	}
	else
	{
		aux = insert_string_on_array(shell->heredoc_files, file_name, 0);
		if (aux == NULL)
			return (FALSE);
		free(shell->heredoc_files);
		shell->heredoc_files = aux;
	}
	return (TRUE);
}

static void	heredoc_error(char **line_array, int file, char *file_name,
		char *line)
{
	if (line != NULL)
	{
		free(line);
		printf("minishell: warning: ");
		printf("here-document delimited by end-of-file");
		printf(" (wanted `%s')\n", line_array[0]);
	}
	close(file);
	free(file_name);
	ft_free(line_array);
}

static t_bool	manage_heredoc_line(char **line_array, int file,
		char *file_name, int *x)
{
	char	*line;

	line = readline(">");
	if (g_exit_status == 330 || !line)
		return (heredoc_error(line_array, file, file_name, line), FALSE);
	if (line && *line != '\0')
	{
		if (newcmp(line_array[0], line) == 0)
			(*x)++;
		else
		{
			write(file, line, ft_strlen(line));
			write(file, "\n", 1);
		}
	}
	free(line);
	return (TRUE);
}

static void	her_d(t_shell *shell, char **line_arraid, int pipe_count)
{
	int		x;
	int		text;
	char	*file_name;

	file_name = generate_here_doc_file_name(pipe_count);
	if (!save_heredoc_file(shell, file_name))
	{
		free(file_name);
		ft_free(line_arraid);
		return ;
	}
	text = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	x = 0;
	while (x == 0)
		if (!manage_heredoc_line(line_arraid, text, file_name, &x))
			return ;
	close(text);
	free(file_name);
	ft_free(line_arraid);
}

void	all_heredoc(t_shell *shell)
{
	t_token	*aux_token;
	int		pipe_count;

	pipe_count = 0;
	aux_token = shell->tokens;
	set_signal_for_heredoc();
	while (aux_token)
	{
		if (newcmp(aux_token->content, "|") == 0)
			pipe_count++;
		if (newcmp(aux_token->content, "<<") == 0)
		{
			aux_token = aux_token->next;
			her_d(shell, ft_split(aux_token->content, ' '), pipe_count);
		}
		aux_token = aux_token->next;
	}
	init_sigaction();
}
