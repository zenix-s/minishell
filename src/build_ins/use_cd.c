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
/*
static int	create_new_rute(char *rute, char *step)
{
	char	*aux;

	if (strcmp(step, "..") == 0)
		rute = ft_substr(rute, 0, ft_strrint(rute, '/'));
	else
	{
		aux = ft_strjoin(rute, "/");
		rute = ft_strjoin(aux, step);
		free(aux);
	}
	if (chdir(rute) == -1)
	{
		free(rute);
		return (-1);
	}
	free(rute);
	return (1);
}
*/
/*
static int	search_rute(char *line_arraid, int count)
{
	char	*rute;
	char	*cwd;
	char	**step;

	cwd = (char *)ft_calloc(1024, sizeof(char));
	if (!cwd)
		return (-1);
	step = ft_split(line_arraid, '/');
	while (step[count])
	{
		rute = getcwd(cwd, 1024);
		if (create_new_rute(rute, step[count]) == -1)
		{
			printf("cd: no such file or directory: %s\n", line_arraid);
			free(cwd);
			ft_free(step);
			return (-1);
		}
		count++;
	}
	free(cwd);
	ft_free(step);
	return (1);
}
*/
/*
static void	obtain_new_oldpwd(t_token **list_env)
{
	char	*new_oldpwd;
	char	**aux;
	char	*pwd;
	t_token	*l_aux;

	l_aux = *list_env;
	pwd = obtain_content("PWD=", l_aux);
	if (pwd)
	{
		new_oldpwd = ft_strjoin("OLD", pwd);
		change_content(&l_aux, "OLDPWD=", new_oldpwd);
		free(new_oldpwd);
	}
	else
	{
		aux = ft_split("FOO OLDPWD FOO", ' ');
//		use_unset (list_env, aux);
		ft_free(aux);
	}
}
*/

static void	go_home(t_env_token **list_env)
{
	t_env_token	*l_aux;
	char		*home;

	l_aux = *list_env;
	home = NULL;
	while (l_aux)
	{
		if (ft_strcmp(l_aux->key, "HOME") == 0)
			home = l_aux->value;
		l_aux = l_aux->next;
	}
	if (!home)
		printf("HOME not set\n");
	else
	{
		l_aux = *list_env;
		chdir(home);
		change_content(&l_aux, "PWD=", home);
	}
}

void	use_cd(t_env_token **list_env, char **line_arraid)
{
	char		*pwd;
	t_env_token	*l_aux;
//	char		*aux;
//	char		*new_pwd;
	char		*cwd;

	l_aux = *list_env;
	pwd = obtain_content("PWD=", l_aux);
	cwd = (char *)ft_calloc(1024, sizeof(char));
	if (!line_arraid[1])
		go_home(&l_aux);
	/*
	else
	{
		if (search_rute(line_arraid[1], 0) == -1)
		{
			aux = ft_substr(pwd, 4, ft_strlen(pwd));
			chdir(aux);
			free(aux);
		}
		else
		{
			obtain_new_oldpwd(&l_aux);
			new_pwd = getcwd(cwd, 1024);
			pwd = ft_strjoin("PWD=", new_pwd);
			change_content(&l_aux, "PWD=", pwd);
			free(pwd);
			free(new_pwd);
		}
	}
	*/
	free(cwd);
}
