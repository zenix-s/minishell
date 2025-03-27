/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:43:33 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/25 21:43:36 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_alone(t_shell *shell, char **cmd)
{
	int	file_in;
	int	stdin_copy;

	file_in = open(shell->read, O_RDONLY);
	if (file_in == -1)
		return ;
	stdin_copy = dup(STDIN_FILENO);
	if (dup2(file_in, STDIN_FILENO) == -1)
		ft_error("Error redirecting standard input");
	if (cmd && s_build(shell, cmd) == 5)
		execute_cmd(cmd, shell->env);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	close(file_in);
}

void	write_alone(t_shell *shell, char **cmd)
{
	int	file_out;
	int	stdout_copy;

	if (shell->mode == 1)
		file_out = open(shell->write, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->mode == 2)
		file_out = open(shell->write, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (file_out == -1)
		ft_error("Error opening output file");
	stdout_copy = dup(STDOUT_FILENO);
	if (dup2(file_out, STDOUT_FILENO) == -1)
		ft_error("dup 2 error");
	if (cmd != NULL && s_build(shell, cmd) == 5)
		execute_cmd(cmd, shell->env);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	close(file_out);
}

int	new_open(t_shell *shell)
{
	if (shell->mode == 1)
		return (open(shell->write, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (shell->mode == 2)
		return (open(shell->write, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

void	full_redirect(t_shell *shell, char **cmd)
{
	int	file_in;
	int	file_out;
	int	stdin_copy;
	int	stdout_copy;

	file_in = open(shell->read, O_RDONLY);
	if (file_in == -1)
		return ;
	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1 || dup2(file_in, STDIN_FILENO) == -1)
		ft_error("Error redirecting standard input");
	file_out = new_open(shell);
	if (file_out == -1)
		ft_error("Error opening output file");
	stdout_copy = dup(STDOUT_FILENO);
	if (dup2(file_out, STDOUT_FILENO) == -1)
		ft_error("dup2 error");
	if (cmd && s_build(shell, cmd) == 5)
		execute_cmd(cmd, shell->env);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	close(file_in);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	close(file_out);
}

void	redirect_state(t_shell *shell)
{
	char	**cmd;
	t_token	*aux_token;

	aux_token = shell->tokens;
	shell->execute = clean_end_state;
	if (prepare(shell, aux_token) == -1)
		return ;
	if (shell->tokens && shell->tokens->content)
		cmd = ft_split(shell->tokens->content, ' ');
	else
		cmd = NULL;
	if (shell->read != NULL && shell->write == NULL)
		read_alone(shell, cmd);
	else if (shell->read == NULL && shell->write != NULL)
		write_alone(shell, cmd);
	else if (shell->read != NULL && shell->write != NULL)
		full_redirect(shell, cmd);
	if (cmd)
		ft_free(cmd);
	if (shell->read == NULL && shell->write == NULL)
		shell->execute = select_all;
}
