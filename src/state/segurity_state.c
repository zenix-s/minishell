/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segurity_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:47:13 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/11 21:47:17 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	segurity_state(t_shell *shell)
{
	if (shell->input && *shell->input != '\0')
	{
		if (strlen(shell->input) > MAX_INPUT_LENGTH)
			ft_error("Error: line so long.\n");
		add_history(shell->input);
		all_heredoc(shell);
		shell->execute = pipex_state;
	}
	else
		shell->execute = clean_end_state;
}
