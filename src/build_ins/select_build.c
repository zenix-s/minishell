/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:27:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//esta funcion esta claramente en pañales
//actualmente busca muy sesgado
static int	follow_mode(t_token *env_aux)
{
	int	mode;

	while (env_aux)
	{
		//esto mal buscado es para si sale << en primer lugar...
		if (ft_strcmp(env_aux->content, "<<") == 0)
			mode = 1;
		if (ft_strcmp(env_aux->content, ">") == 0)
			mode = 2;
		if (ft_strcmp(env_aux->content, ">>") == 0)
			mode = 3;
		if (ft_strcmp(env_aux->content, "<") == 0)
			mode = 4;
		env_aux = env_aux->next;
	}
	return (mode);
}

/*
*used to parse a command line and execute the corresponding built-in function.
*"echo", "pwd", "export", "unset", "env", and "exit" commands.
*it attempts to execute the command as an external program.
*/
void	select_all(t_shell **shell)
{
	t_shell	*aux;
	t_token	*env_aux;
	char	**line_arraid;
	int		mode;

	env_aux = (*shell)->tokens;
	aux = *shell;
	mode = follow_mode(env_aux);
	//esto puede asumir mas cosas?
	if (mode == 1)
	{
		her_d(ft_split(env_aux->next->next->content, ' '), env_aux, &aux, mode);
		return ;
	}
	if (mode == 2 || mode == 3)
	{
		stnd_out(env_aux, &aux, mode);
		return ;
	}
	if (mode == 4)
	{
		stnd_in(env_aux, &aux, mode);
		return ;
	}
	mode = 0;
	if (env_aux->next)
	{
		while (env_aux)
		{
			if (env_aux->type == PIPE)
				mode++;
			env_aux = env_aux->next;
		}
		if (mode != 0)
		{
			select_pipex(shell, mode);
			return ;
		}
	}
	line_arraid = ft_split(aux->tokens->content, ' ');
	if (select_build(&aux, line_arraid) == 5)
		execute_command(line_arraid, (*shell)->env);
	ft_free(line_arraid);
}

//el exit seguramente tenga que hacer mas cosas
int	select_build(t_shell **shell, char **line_arraid)
{
	if (ft_strcmp(line_arraid[0], "pwd") == 0)
		use_pwd();
	else if (ft_strcmp(line_arraid[0], "env") == 0)
		print_env((*shell)->env);
	else if (ft_strcmp(line_arraid[0], "echo") == 0)
		use_echo(line_arraid);
	else if (ft_strcmp(line_arraid[0], "export") == 0)
	{
		if (!line_arraid[1])
			print_env((*shell)->env);
		else
			use_export(shell, line_arraid);
	}
	else if (ft_strcmp(line_arraid[0], "unset") == 0)
		use_unset(shell, line_arraid);
	else if (ft_strcmp(line_arraid[0], "cd") == 0)
		use_cd(&(*shell)->env, line_arraid, shell);
	else if (ft_strcmp(line_arraid[0], "exit") == 0)
		exit(0);
	else
		return (5);
	return (1);
}
