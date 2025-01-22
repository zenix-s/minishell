
#include "../../include/minishell.h"
/*
*used to parse a command line and execute the corresponding built-in function.
*"echo", "pwd", "export", "unset", "env", and "exit" commands.
*it attempts to execute the command as an external program.
*/
void	select_build(char *line, t_token *list_env)
{
	char	**line_arraid;

	line_arraid = ft_split(line, ' ');
	if (line && ft_strncmp(line_arraid[0], "echo", 3) == 0)
		use_echo(list_env, line_arraid);
//	if (line && ft_strncmp(line, "cd", 2) == 0)
//		use_cd(&list_env, line_arraid);
	else if (line && ft_strncmp(line_arraid[0], "pwd", 2) == 0)
		use_pwd(list_env);
	else if (line && ft_strncmp(line_arraid[0], "export", 5) == 0)
	{
		if (!line_arraid[1])
			use_env(list_env);
		else
			use_export(&list_env, line_arraid);
	}
	else if (line && ft_strncmp(line_arraid[0], "unset", 4) == 0)
		use_unset(&list_env, line_arraid);
	else if (line && ft_strncmp(line_arraid[0], "env", 2) == 0)
		use_env(list_env);
	else if (line && ft_strncmp(line_arraid[0], "exit", 3) == 0)
		exit(0); //no sea tan facil...
	else
		exe(line_arraid[0], list_env);
	ft_free(line_arraid);
}
