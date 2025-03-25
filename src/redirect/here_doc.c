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

void	her_d(char **line_arraid)
{
	int		x;
	char	*line;
	int		text;

	text = open ("file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	x = 0;
	while (x == 0)
	{
		line = readline(">");
		if (!line)
		{
			printf("boom\n");
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
	unlink("file.txt");
	ft_free(line_arraid);
}

void	all_heredoc(t_shell *shell)
{
	t_token	*aux_token;

	aux_token = shell->tokens;
	while (aux_token)
	{
		if (newcmp(aux_token->content, "<<") == 0)
		{
			aux_token = aux_token->next;
			her_d(ft_split(aux_token->content, ' '));
		}
		aux_token = aux_token->next;
	}
}
