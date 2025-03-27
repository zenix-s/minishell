/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:27:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	search_rute(char **big_arraid, char *line_arraid, int count)
{
	char	*rute;
	char	cwd[1024];
	char	**step;

	if (use_slash(big_arraid, line_arraid) == 1)
		return (1);
	if (verify_backwards_rute(line_arraid) == 1)
		return (1);
	step = ft_split(line_arraid, '/');
	while (step[count])
	{
		rute = getcwd(cwd, 1024);
		if (rute != NULL)
		{
			if (create_new_rute(rute, step[count]) == -1)
			{
				ft_free(step);
				return (-1);
			}
		}
		count++;
	}
	ft_free(step);
	return (1);
}

static void	obtain_new_oldpwd(t_env_token *list_env, t_shell *shell)
{
	char		**aux;
	char		*pwd;
	t_env_token	*l_aux;

	l_aux = list_env;
	pwd = obtain_content("PWD", l_aux);
	if (pwd)
		change_content(list_env, "OLDPWD", pwd);
	else
	{
		aux = ft_split("FOO OLDPWD FOO", ' ');
		if (aux)
		{
			use_unset(shell, aux);
			ft_free(aux);
		}
	}
}

static void	go_home(t_env_token *list_env, t_shell *shell)
{
	t_env_token	*l_aux;
	char		*home;

	l_aux = list_env;
	home = NULL;
	while (l_aux)
	{
		if (newcmp(l_aux->key, "HOME") == 0)
			home = l_aux->value;
		l_aux = l_aux->next;
	}
	if (!home)
		printf("HOME not set\n");
	else
	{
		l_aux = list_env;
		chdir(home);
		obtain_new_oldpwd(l_aux, shell);
		change_content(l_aux, "PWD", home);
	}
}

static void	clean_on_cd(t_shell *shell, t_env_token *l_aux, char *pwd)
{
	char		*new_pwd;
	char		cwd[1024];

	obtain_new_oldpwd(l_aux, shell);
	new_pwd = getcwd(cwd, sizeof(cwd));
	if (new_pwd != NULL)
	{
		pwd = ft_strdup(new_pwd);
		change_content(l_aux, "PWD", pwd);
		free(pwd);
	}
}

void	use_cd(t_env_token *l_env, char **line_arraid, t_shell *shell)
{
	char		*pwd;
	t_env_token	*l_aux;
	char		*aux;

	aux = NULL;
	if (line_arraid[1] != NULL)
		aux = remove_outer_quotes(line_arraid[1]);
	l_aux = l_env;
	pwd = obtain_content("PWD", l_env);
	if (!line_arraid[1] || newcmp(aux, "~") == 0)
		go_home(l_env, shell);
	else
	{
		if (search_rute(line_arraid, aux, 0) == -1)
			chdir(pwd);
		else
			clean_on_cd(shell, l_aux, pwd);
	}
	if (aux != NULL)
		free(aux);
}
