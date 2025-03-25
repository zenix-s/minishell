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

static void	her_d(t_shell *shell, char **line_arraid, int pipe_count)
{
	int		x;
	char	*line;
	int		text;
	char *file_name = ft_strdup("file");
	ft_super_strcat(&file_name, ft_itoa(pipe_count));
	char **aux = insert_string_on_array(shell->heredoc_files, file_name, 0);
	shell->heredoc_files = aux;
	text = open (file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	x = 0;
	while (x == 0)
	{
		line = readline(">");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", line_arraid[0]);
			close(text);
			unlink("file.txt");
			ft_free(line_arraid);
			return;
		}
		if (line && *line != '\0')
		{
			if (newcmp(line_arraid[0], line) == 0)
				x++;
			write(text, line, ft_strlen(line));
			write(text, "\n", 1);
		}
		free(line);
	}
	close(text);
	shell->read = file_name;
	//unlink(file_name);
	ft_free(line_arraid);
}

void	all_heredoc(t_shell *shell)
{
	t_token	*aux_token;
	int pipe_count;

	pipe_count = 0;
	aux_token = shell->tokens;
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
	char **aux = delete_string_on_array(shell->heredoc_files, 	get_array_string_size(shell->heredoc_files) - 1);

	shell->heredoc_files = aux;

	int i = 0;
	while (shell->heredoc_files[i])
	{
		printf("file: %s\n", shell->heredoc_files[i]);
		i++;
	}
}
