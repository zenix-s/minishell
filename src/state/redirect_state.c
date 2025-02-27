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
			else
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

int	little_redirect(t_shell *shell)
{
	t_token	*env_aux;
	int		mod;

	env_aux = shell->tokens;
	mod = follow_mode(env_aux);
	if (mod == 1 || mod == 5)
		her_d(ft_split(env_aux->next->next->content, ' '), env_aux, shell, mod);
	if (mod == 2 || mod == 3)
		stnd_out(env_aux, shell, mod);
	if (mod == 4)
		stnd_in(env_aux, shell, mod);
	return (mod);
}

void	redirect_state(t_shell *shell)
{
	t_token	*env_aux;
	int		mod;

	env_aux = shell->tokens;
	mod = follow_mode(env_aux);
	if (mod == 1 || mod == 5)
		her_d(ft_split(env_aux->next->next->content, ' '), env_aux, shell, mod);
	if (mod == 2 || mod == 3)
		stnd_out(env_aux, shell, mod);
	if (mod == 4)
		mod = stnd_in(env_aux, shell, mod);
	if (mod >= 0)
		shell->execute = select_all;
	else
	{
		error_state(mod);
		shell->execute = clean_end_state;
	}
}
