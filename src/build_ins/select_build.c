
#include "../../include/minishell.h"


/*
*used to parse a command line and execute the corresponding built-in function.
*"echo", "pwd", "export", "unset", "env", and "exit" commands.
*it attempts to execute the command as an external program.
*/

//esto bien, pero necesitas que sea el comando como tal 
void	select_all(t_shell **shell)
{
	t_shell	*aux;
	char	**line_arraid;

	aux = *shell;
	line_arraid = ft_split(aux->tokens->content, ' ');
//	printf("%s\n", aux->tokens->content);
/*
	if (line_arraid[0])
	{
		if (ft_strcmp(line_arraid[0], "<<") == 0)
			foo_here_doc(line_arraid);
		else if (line_arraid[1] && ft_strcmp(line_arraid[1], "|") == 0)
			pipex(line_arraid, list_env);
		else
			select_build(line_arraid, list_env, 0);
		ft_free(line_arraid);
	}
*/
//	select_build(&aux, line_arraid);
	select_build(line_arraid);
}

//el exit seguramente tenga que hacer mas cosas
//void	select_build(t_shell **shell, char **line_arraid)
void	select_build(char **line_arraid)
{
//	if (ft_strcmp(line_arraid[x], "echo") == 0)
//		use_echo(list_env, line_arraid);
//	else if (ft_strcmp(line_arraid[x], "cd") == 0)
//		use_cd(&list_env, line_arraid);
	 if (ft_strcmp(line_arraid[0], "pwd") == 0)
		use_pwd();
//	else if (ft_strcmp(line_arraid[x], "export") == 0)
//	{
//		if (!line_arraid[x + 1])
//			use_env(list_env);
//		else
//			use_export(&list_env, line_arraid);
//	}
//	else if (ft_strcmp(line_arraid[x], "unset") == 0)
//		use_unset(&list_env, line_arraid);
	//else if (ft_strcmp(line_arraid[x], "env") == 0)
	//	use_env(list_env);
//	else if (ft_strcmp(line_arraid[x], "exit") == 0)
//		exit(0);
//	else
//		execute_command(line_arraid, list_env);
}


//TO DO

// crear la lista de funciones de sistema (?) distinta al env cuando se usa export A (sin igual)