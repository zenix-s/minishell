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

void	her_d(char **line_arraid, t_token *env_aux, t_shell *aux, int mode)
{
	int		x;
	char	*line;
	int		text;

	text = open("file.txt", O_CREAT | O_WRONLY |O_TRUNC, 0644);
	x = 0;
	while (x == 0)
	{
		line = readline("");
		if (line && *line != '\0')
		{
			if (ft_strcmp(line_arraid[0], line) == 0)
				x++;
			write(text, line, ft_strlen(line));
			write(text, "\n", 1);
		}
		free(line);
	}
	close(text);
	if (mode == 1)
		stnd_in(env_aux, aux, mode);
	if (mode == 5)
		unlink("file.txt");
	ft_free(line_arraid);
}
