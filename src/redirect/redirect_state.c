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

int	loop_redirect(t_shell *shell, t_token *aux_token)
{
	int	mode;
	int	result;
	int	loop;

	loop = 0;
	result = 0;
	mode = finish_redirect(shell, aux_token);
/*
	while (aux_token && aux_token->type != PIPE)
	{
		if (mode != 0)
			result = mode;
		while (aux_token && aux_token->type != PIPE && aux_token->type != REDIRECT)
			aux_token = aux_token->next;
		if (aux_token && aux_token->type != PIPE)
			aux_token = aux_token->next;
		loop++;
	}
	return (result);
*/
	return (mode);
}

int	prepare(t_shell *shell, t_token *aux_token)
{
	int	mode;
	int	file;

	mode = 0;
	while (aux_token && aux_token->type != PIPE)
	{
		if (aux_token->type == REDIRECT)
		{
			if (ft_strcmp(aux_token->content, "<<") == 0) //este es mas largo
				shell->here[0] = aux_token->next->content;
			if (ft_strcmp(aux_token->content, "<") == 0)
			{
				file = open(aux_token->next->content, O_RDONLY);
				if (file == -1)
					return (-1);
				shell->read = aux_token->next->content;
				close (file);
			}
			if (ft_strcmp(aux_token->content, ">") == 0)
			{
				file = open(aux_token->next->content, O_CREAT | O_WRONLY |O_TRUNC, 0644);
				if (file == -1)
					return (-1);
				shell->write = aux_token->next->content;
				shell->mode = 1;
				close (file);
			}
			if (ft_strcmp(aux_token->content, ">>") == 0)
			{
				file = open(aux_token->next->content, O_CREAT | O_WRONLY |O_TRUNC, 0644);
				if (file == -1)
					return (-1);
				shell->write = aux_token->next->content;
				shell->mode = 2;
				close (file);
			}
			mode++;
			aux_token = aux_token->next;
		}
		aux_token = aux_token->next;
	}
	return (mode);
}

void	redirect_state(t_shell *shell)
{
	int		mode;
	t_token	*aux_token;

	aux_token = shell->tokens;
	mode = prepare(shell, aux_token);
	//mode = loop_redirect(shell, aux_token);
	if (mode <= 0)
		shell->execute = select_all;
	else
	{
		error_state(mode);
		shell->execute = clean_end_state;
	}
}
