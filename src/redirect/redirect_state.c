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
//>> no escribe nada en bash y aqui si
//actualmente busca muy sesgado
int	follow_mode(t_token *env_aux)
{
	int	x;

	x = 0;
	while (env_aux)
	{
		if (ft_strcmp(env_aux->content, "<<") == 0)
		{
			if (x == 0)
				return (5);
			return (1);
		}
		if (ft_strcmp(env_aux->content, ">") == 0)
			return (2);
		if (ft_strcmp(env_aux->content, ">>") == 0)
			return (3);
		if (ft_strcmp(env_aux->content, "<") == 0)
			return (4);
		env_aux = env_aux->next;
		x++;
	}
	return (0);
}

int	finish_redirect(t_shell *shell, t_token *aux_shell)
{
	t_token	*env_aux;
	int		mod;

	env_aux = aux_shell;
	mod = follow_mode(env_aux);
	if (mod == 1 || mod == 5)
		her_d(ft_split(env_aux->next->next->content, ' '), env_aux, shell, mod);
	if (mod == 2 || mod == 3)
		stnd_out(env_aux, shell, mod);
	if (mod == 4)
		stnd_in(env_aux, shell, mod);
	return (mod);
}

static void	dup_close(int copy, int file)
{
	dup2(copy, STDIN_FILENO);
	close(copy);
	close(file);
}

// otra opcion es abrir directamente los tres casos, asi te ahorras todo lo demas 
//solo entrada
//solo salida
//las dos
//ademas esto se puede usar como distintos estados
void	redirect_state(t_shell *shell)
{
	int		file_in;
	int		file_out;
	int		stdin_copy;
	int		stdout_copy;
	char	**cmd;

	if (shell->read != NULL)
	{
		file_in = open(shell->read, O_RDONLY);
		if (file_in == -1)
			return ;
		stdin_copy = dup(STDIN_FILENO);
		if (dup2(file_in, STDIN_FILENO) == -1)
			ft_error("Error redirigiendo la entrada estándar");
	}
	if (shell->write != NULL)
	{
		if (shell->mode == 1)
			file_out = open(shell->write, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (shell->mode == 2)
			file_out = open(shell->write, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (file_out == -1)
			ft_error("Error abriendo el archivo de salida");
		stdout_copy = dup(STDOUT_FILENO);
		if (dup2(file_out, STDOUT_FILENO) == -1) //
			ft_error("Error redirigiendo la salida estándar");
	}
	if (shell->read != NULL || shell->write != NULL)
	{
		cmd = ft_split(shell->tokens->content, ' ');
		if (s_build(shell, cmd) == 5)
			execute_cmd(cmd, shell->env);
		ft_free(cmd);
	}
	if (shell->read != NULL)
		dup_close(stdin_copy, file_in);
	if (shell->write != NULL)
		dup_close(stdout_copy, file_out);
	if (shell->read == NULL && shell->write == NULL)
		shell->execute = select_all;
	else
		shell->execute = clean_end_state;
//	else
//	{
//		error_state(mode);
//	}
}
